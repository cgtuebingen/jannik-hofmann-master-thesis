# This is the fastest python implementation of the ForceAtlas2 plugin from Gephi
# intended to be used with networkx, but is in theory independent of
# it since it only relies on the adjacency matrix.  This
# implementation is based directly on the Gephi plugin:
#
# https://github.com/gephi/gephi/blob/master/modules/LayoutPlugin/src/main/java/org/gephi/layout/plugin/forceAtlas2/ForceAtlas2.java
#
# For simplicity and for keeping code in sync with upstream, I have
# reused as many of the variable/function names as possible, even when
# they are in a more java-like style (e.g. camelcase)
#
# I wrote this because I wanted an almost feature complete and fast implementation
# of ForceAtlas2 algorithm in python
#
# NOTES: Currently, this only works for weighted undirected graphs.
#
# Copyright (C) 2017 Bhargav Chippada <bhargavchippada19@gmail.com>
#
# Available under the GPLv3

# Modified for layouting of DNNs

import random
from sys import version_info
import time

import networkx
import numpy
import scipy
from tqdm import tqdm
from datetime import datetime

#from . import fa2util
import fa2util
import itertools
import math
import functools
import asyncio
import os

from visualizationSettings import layouting
import websocketServer as server
import aiInteraction as ai
import fileHandling

class Timer:
	def __init__(self, name="Timer"):
		self.name = name
		self.start_time = 0.0
		self.total_time = 0.0

	def start(self):
		self.start_time = time.time()

	def stop(self):
		self.total_time += (time.time() - self.start_time)

	def display(self):
		print(self.name, " took ", "%.2f" % self.total_time, " seconds")


class ForceAtlas2:
	def __init__(self,
		# Behavior alternatives
		outboundAttractionDistribution=False,  # Dissuade hubs
		linLogMode=False,  # NOT IMPLEMENTED
		adjustSizes=False,  # Prevent overlap (NOT IMPLEMENTED)
		edgeWeightInfluence=1.0,
		orderconnectedQuadsOnXaxis=False, # orders connected nodes by their index on x axis
		desiredVerticalSpacing=0, # spacing between the nodes
		desiredHorizontalSpacing=50, # spacing between the nodes
		desiredHorizontalSpacingWithinGroup=None, # spacing between the nodes
		bufferZone=50,
		groupLinearlyConnectedNodes=False, # only available with networkx layout

		# Performance
		jitterTolerance=1.0,  # Tolerance
		barnesHutOptimize=True,
		barnesHutTheta=1.2,
		multiThreaded=False,  # NOT IMPLEMENTED

		# Tuning
		scalingRatio=2.0,
		strongGravityMode=False,
		gravity=1.0,
		randomlyOffsetNodes=0.0,

		# Log
		verbose=True,
		addedMsPerFrame=0
	):
		assert linLogMode == adjustSizes == multiThreaded == False, "You selected a feature that has not been implemented yet..."
		self.outboundAttractionDistribution = outboundAttractionDistribution
		self.linLogMode = linLogMode
		self.adjustSizes = adjustSizes
		self.edgeWeightInfluence = edgeWeightInfluence
		self.orderconnectedQuadsOnXaxis = orderconnectedQuadsOnXaxis
		self.desiredHorizontalSpacing = desiredHorizontalSpacing
		self.desiredVerticalSpacing = desiredVerticalSpacing
		self.desiredHorizontalSpacingWithinGroup = desiredHorizontalSpacingWithinGroup
		self.bufferZone = bufferZone
		self.groupLinearlyConnectedNodes = groupLinearlyConnectedNodes
		self.jitterTolerance = jitterTolerance
		self.barnesHutOptimize = barnesHutOptimize
		self.barnesHutTheta = barnesHutTheta
		self.scalingRatio = scalingRatio
		self.strongGravityMode = strongGravityMode
		self.gravity = gravity
		self.randomlyOffsetNodes = randomlyOffsetNodes
		self.verbose = verbose
		self.addedMsPerFrame = addedMsPerFrame

	def init(self,
			 G,  # a graph in 2D numpy ndarray format (or) scipy sparse matrix format
			 pos=None,  # Array of initial positions
			 quadsizes=None # Array of rectangular node sizes
			 ):
		isSparse = False
		if isinstance(G, numpy.ndarray):
			# Check our assumptions
			assert G.shape == (G.shape[0], G.shape[0]), "G is not 2D square"
			assert numpy.all(G.T == G), "G is not symmetric.  Currently only undirected graphs are supported"
			assert isinstance(pos, numpy.ndarray) or (pos is None), "Invalid node positions"
		elif scipy.sparse.issparse(G):
			# Check our assumptions
			assert G.shape == (G.shape[0], G.shape[0]), "G is not 2D square"
			assert isinstance(pos, numpy.ndarray) or (pos is None), "Invalid node positions"
			G = G.tolil()
			isSparse = True
		else:
			assert False, "G is not numpy ndarray or scipy sparse matrix"

		# Put nodes into a data structure we can understand
		nodes = []
		for i in range(0, G.shape[0]):
			n = fa2util.QuadNode()
			if isSparse:
				n.mass = 1 + len(G.rows[i])
			else:
				n.mass = 1 + numpy.count_nonzero(G[i])
			n.old_dx = 0
			n.old_dy = 0
			n.dx = 0
			n.dy = 0
			if pos is None:
				n.x = random.random()
				n.y = random.random()
			else:
				n.x = pos[i][0]
				n.y = pos[i][1]
			n.id = i
			if quadsizes is not None:
				n.width = quadsizes[i][0]
				n.height = quadsizes[i][1]
			nodes.append(n)

		# Put edges into a data structure we can understand
		edges = []
		es = numpy.asarray(G.nonzero()).T
		for e in es:  # Iterate through edges
			if e[1] <= e[0]: continue  # Avoid duplicate edges
			edge = fa2util.Edge()
			edge.node1 = e[0]  # The index of the first node in `nodes`
			edge.node2 = e[1]  # The index of the second node in `nodes`
			edge.weight = G[tuple(e)]
			edges.append(edge)

		return nodes, edges

	# Given an adjacency matrix, this function computes the node positions
	# according to the ForceAtlas2 layout algorithm.  It takes the same
	# arguments that one would give to the ForceAtlas2 algorithm in Gephi.
	# Not all of them are implemented.  See below for a description of
	# each parameter and whether or not it has been implemented.
	#
	# This function will return a list of X-Y coordinate tuples, ordered
	# in the same way as the rows/columns in the input matrix.
	#
	# The only reason you would want to run this directly is if you don't
	# use networkx.  In this case, you'll likely need to convert the
	# output to a more usable format.  If you do use networkx, use the
	# "forceatlas2_networkx_layout" function below.
	#
	# Currently, only undirected graphs are supported so the adjacency matrix
	# should be symmetric.
	async def forceatlas2(self,
					G,  # a graph in 2D numpy ndarray format (or) scipy sparse matrix format
					pos=None,  # Array of initial positions
					quadsizes=None, # List of sizes of the graph nodes [(width, height)]
					iterations=100,  # Number of times to iterate the main loop
					groups=None,
					individualG=None,
					individualPosOffset=None,
					individualSizes=None,
					):
		# Initializing, initAlgo()
		# ================================================================

		if self.groupLinearlyConnectedNodes:
			assert groups is not None and individualG is not None and \
				individualPosOffset is not None and individualSizes is not None
		if self.randomlyOffsetNodes != 0:
			pos += (numpy.random.rand(*pos.shape) - 0.5) * 2 * self.randomlyOffsetNodes

		# speed and speedEfficiency describe a scaling factor of dx and dy
		# before x and y are adjusted.  These are modified as the
		# algorithm runs to help ensure convergence.
		speed = 1.0
		speedEfficiency = 1.0
		nodes, edges = self.init(G, pos, quadsizes)
		outboundAttCompensation = 1.0
		if self.outboundAttractionDistribution:
			outboundAttCompensation = numpy.mean([n.mass for n in nodes])
		# ================================================================

		# Main loop, i.e. goAlgo()
		# ================================================================

		barneshut_timer = Timer(name="BarnesHut Approximation")
		repulsion_timer = Timer(name="Repulsion forces")
		overlap_repulsion_timer = Timer(name="Overlap repulsion forces")
		gravity_timer = Timer(name="Gravitational forces")
		attraction_timer = Timer(name="Attraction forces")
		applyforces_timer = Timer(name="AdjustSpeedAndApplyForces step")
		draw_timer = Timer(name="Drawing the plot")

		# exponentialCurveFactor 0 = linear, 1 = slight curve, 5 = really strong curve
		# exponentialCurveFactorpositive: curved downward, negative: curved upward
		# reverse: False = from 0 to 1, True = from 1 to 0
		# Here an example with the exponentialCurveFactor of 5:
		# https://www.wolframalpha.com/input/?i=%28e%5E%28+++++5+++++*x%29%2Fe-1%2Fe%29%2F%28e%5E%28+++++5+++++%29%2Fe-1%2Fe%29+in+x%3D%5B0%2C1%5D
		@functools.lru_cache(maxsize=25)
		def exponentialCurve(x, exponentialCurveFactor):
			if exponentialCurveFactor == 0:
				return x
			return (math.e**(exponentialCurveFactor*x) / math.e - 1/math.e) / \
				(math.e**exponentialCurveFactor / math.e - 1/math.e)

		@functools.lru_cache(maxsize=25)
		def interpretExponentialCurve(i, rule):
			iRange = getattr(rule, 'withinIterations', range(0, iterations))
			if iRange is None or len(iRange) == 0 or i not in iRange:
				return 0
			importance = getattr(rule, 'importance', "constant").lower()
			if importance in "disabled disable never off none zero 0 x deactivated inactive no".split():
				return 0
			strength = getattr(rule, 'strength', 1)
			if importance in "constant enabled enable always active activated 1 on one yes".split():
				return strength
			if len(iRange) == 1:
				return strength
			# x gets progress of i within the withinIterations range resulting in a range from 0 to 1
			x = (i - min(iRange)) / (max(iRange) - min(iRange))
			exponentialCurveFactor = getattr(rule, 'exponentialCurveFactor', 0)
			if importance in "increasing increase inc + more up".split():
				return strength * exponentialCurve(x, exponentialCurveFactor)
			if importance in "decreasing decrease dec - less down".split():
				return strength * exponentialCurve(1 - x, exponentialCurveFactor)
			if importance in "middle mid midway half center mirror mirrored".split():
				x = min(x, 1 - x) * 2
				return strength * exponentialCurve(x, exponentialCurveFactor)
			if importance in "outsides antimirror outside".split():
				x = max(x - 0.5, 0.5 - x) * 2
				return strength * exponentialCurve(x, exponentialCurveFactor)
			# otherwise can't parse! So print warning and ignore it
			print("Warning! Exponential curve function cannot understand importance parameter " + rule.importance)
			return 0

		#for _i in niters:
		def execute_once(i):
			nonlocal speed, speedEfficiency, nodes, edges, outboundAttCompensation, barneshut_timer, repulsion_timer, overlap_repulsion_timer, gravity_timer, attraction_timer, applyforces_timer, quadsizes

			for n in nodes:
				n.old_dx = n.dx
				n.old_dy = n.dy
				n.dx = 0
				n.dy = 0

			# Barnes Hut optimization
			if self.barnesHutOptimize:
				barneshut_timer.start()
				rootRegion = fa2util.Region(nodes)
				rootRegion.buildSubRegions()
				barneshut_timer.stop()

			# Charge repulsion forces
			repulsion_timer.start()
			# parallelization should be implemented here
			strength = interpretExponentialCurve(i, layouting.classicRepulsion)
			if strength > 0:
				if self.barnesHutOptimize:
					rootRegion.applyForceOnNodes(nodes, self.barnesHutTheta, self.scalingRatio*strength)
				else:
					fa2util.apply_repulsion_fast(nodes, self.scalingRatio*strength)
			repulsion_timer.stop()

			if quadsizes is not None:
				overlap_repulsion_timer.start()
				strength = interpretExponentialCurve(i, layouting.overlapRepulsion)
				if strength > 0:
					fa2util.apply_overlap_repulsion(nodes, self.scalingRatio*strength, self.desiredHorizontalSpacing, self.desiredVerticalSpacing, self.bufferZone)
				overlap_repulsion_timer.stop()

			# Gravitational forces
			gravity_timer.start()
			strength = interpretExponentialCurve(i, layouting.gravity)
			if strength > 0:
				fa2util.apply_gravity(nodes, self.gravity, scalingRatio=self.scalingRatio*strength, useStrongGravity=self.strongGravityMode)
			gravity_timer.stop()

			# If other forms of attraction were implemented they would be selected here.
			attraction_timer.start()
			strength = interpretExponentialCurve(i, layouting.connectedAttraction)
			if strength > 0:
				if self.orderconnectedQuadsOnXaxis:
					fa2util.apply_attraction_to_sides(nodes, edges, self.outboundAttractionDistribution, outboundAttCompensation*strength, self.edgeWeightInfluence, self.desiredHorizontalSpacing, self.bufferZone)
				else:
					fa2util.apply_attraction(nodes, edges, self.outboundAttractionDistribution, outboundAttCompensation*strength, self.edgeWeightInfluence)
			# order along x axis: directional attraction
			if self.orderconnectedQuadsOnXaxis:
				strength = interpretExponentialCurve(i, layouting.shiftOnAxisToOrderByIndex)
				if strength > 0:
					fa2util.apply_directional_attraction(nodes, edges, self.outboundAttractionDistribution, strength, self.edgeWeightInfluence, self.desiredHorizontalSpacing)
			attraction_timer.stop()

			# Adjust speeds and apply forces
			applyforces_timer.start()
			values = fa2util.adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, self.jitterTolerance)
			speed = values['speed']
			speedEfficiency = values['speedEfficiency']
			applyforces_timer.stop()
		
		async def execute_once_async(i):
			await server.sleep(0, f"Layouting at iteration {i} of {iterations}")
			execute_once(i)
		

		if layouting.renderGif.displayPlot or layouting.renderGif.saveAsGif:
			def draw(i):
				nonlocal draw_timer, ax, fig
				draw_timer.start()
				import networkx as nx
				ax.clear()
				oldG = nx.from_scipy_sparse_matrix(G)
				positions = dict(zip(oldG.nodes(), [(n.x, n.y) for n in nodes]))
				labels = dict(zip(oldG.nodes(), range(G.shape[0])))
				if not self.groupLinearlyConnectedNodes:
					nx.draw_networkx_nodes(oldG, positions, node_size=50, label=None, node_color="white", alpha=0.94)
				if quadsizes is not None:
					for n in nodes:
						from matplotlib import patches
						color = (.2,.3,0,.2) if self.groupLinearlyConnectedNodes else (.5,0,0,.3)
						rect = patches.Rectangle((n.x-quadsizes[n.id][0]/2, n.y-quadsizes[n.id][1]/2),
							quadsizes[n.id][0], quadsizes[n.id][1], edgecolor=color, fill=False)
						ax.add_patch(rect)
				if not self.groupLinearlyConnectedNodes:
					nx.draw_networkx_edges(oldG, positions, edge_color="blue", alpha=0.505)
					nx.draw_networkx_labels(oldG, positions, labels, font_size=11, font_weight='bold', font_color='white')
					nx.draw_networkx_labels(oldG, positions, labels, font_size=10, font_color='black')

				if self.groupLinearlyConnectedNodes: # draw individual nodes
					indG = nx.from_scipy_sparse_matrix(individualG)
					individualPositions = []
					for index in range(len(indG)):
						x, y = 0, 0
						for g, group in enumerate(groups):
							for n, node in enumerate(group):
								if index == node:
									x = positions[g][0] + individualPosOffset[g][n][0]
									y = positions[g][1] + individualPosOffset[g][n][1]
						individualPositions.append([x, y])
					labels = dict(zip(indG.nodes(), range(individualG.shape[0])))
					nx.draw_networkx_nodes(indG, individualPositions, node_size=50, label=None, node_color="white", alpha=0.94)
					if individualSizes is not None:
						for n in range(len(individualSizes)):
							from matplotlib import patches
							rect = patches.Rectangle((individualPositions[n][0]-individualSizes[n][0]/2, individualPositions[n][1]-individualSizes[n][1]/2),
								individualSizes[n][0], individualSizes[n][1], edgecolor=(.5,0,0,.3), fill=False)
							ax.add_patch(rect)
					nx.draw_networkx_edges(indG, individualPositions, edge_color="blue", alpha=0.505)
					nx.draw_networkx_labels(indG, individualPositions, labels, font_size=11, font_weight='bold', font_color='white')
					nx.draw_networkx_labels(indG, individualPositions, labels, font_size=10, font_color='black')
				ax.set_xticks([])
				ax.set_yticks([])
				fig.suptitle(f'Iteration {i} of {iterations}', fontsize=15, va='top')
				# if i > 0:
				#     from time import sleep
				#     initialFrameTime = 1 # seconds
				#     accelerationFactor = 0.2
				#     if accelerationFactor == 0:
				#         sleeptime = initialFrameTime
				#     else:
				#         accelerationFactor = 1 / accelerationFactor
				#         sleeptime=initialFrameTime * accelerationFactor/(i+accelerationFactor)
				#     sleep(sleeptime)
				draw_timer.stop()
			
			if self.verbose: pbar = tqdm(total=iterations)
			iterationCounter = 0
			def update(i):
				nonlocal iterationCounter
				goUntil = int(i * iterations / layouting.renderGif.framesInAnimation)
				goUntil = min(goUntil, iterations)
				while iterationCounter < goUntil:
					iterationCounter += 1
					execute_once(iterationCounter)
					if self.verbose: nonlocal pbar
					if self.verbose: pbar.update(1)
				draw(iterationCounter)
				#print("gountil " + str(goUntil))
				#print("drawing " + str(iterationCounter))

			import matplotlib.pyplot as plt
			from matplotlib.animation import FuncAnimation
			fig, ax = plt.subplots()
			fig.set_size_inches(*getattr(layouting.renderGif, "plotSizeInches", (20, 10)))
			draw(0)
			anim = FuncAnimation(fig, update, frames=layouting.renderGif.framesInAnimation+1,
				interval=max(self.addedMsPerFrame, 10), repeat=False)
			if not layouting.renderGif.saveAsGif:
				plt.show()
			else:
				filepath = 'layouting-animation.gif'
				filepath = ai.externalImagePath(filepath)
				fileHandling.createFilepath(filepath)
				anim.save(filepath,
					writer='imagemagick',
					fps=layouting.renderGif.framesInAnimation / layouting.renderGif.animationLength,
					dpi=getattr(layouting.renderGif, "gifDpi", 100))
				if layouting.renderGif.displayPlot:
					os.startfile(filepath)
			if self.verbose: pbar.close()

		else: # no plot to be rendered
			# Each iteration of this loop represents a call to goAlgo().
			niters = range(iterations)
			if self.verbose:
				niters = tqdm(niters)
			for i in niters:
				await execute_once_async(i)
		
		if self.verbose:
			if self.barnesHutOptimize:
				barneshut_timer.display()
			repulsion_timer.display()
			overlap_repulsion_timer.display()
			gravity_timer.display()
			attraction_timer.display()
			applyforces_timer.display()
			draw_timer.display()
		# ================================================================
		if self.groupLinearlyConnectedNodes:
			layerposition = {}
			for g, group in enumerate(groups):
				for l, layer in enumerate(group):
					layerposition[layer] = (nodes[g].x + individualPosOffset[g][l][0], nodes[g].y)
			return [layerposition[i] for i in range(len(individualSizes))]        
		else:
			return [(n.x, n.y) for n in nodes]

	def groupNodes(self, G, pos, quadsizes, weight_attr):
		if self.desiredHorizontalSpacingWithinGroup is None:
			self.desiredHorizontalSpacingWithinGroup = self.desiredHorizontalSpacing

		M = networkx.to_scipy_sparse_matrix(G, dtype='f', format='lil', weight=weight_attr)
		
		def connectedIndices(index):
			return scipy.sparse.find(M[index])[1].tolist()
		def connectedIndicesHigher(index):
			return [i for i in connectedIndices(index) if i > index]
		def connectedIndicesLower(index):
			return [i for i in connectedIndices(index) if i < index]
		flatten = itertools.chain.from_iterable
		groups = []
		for index in range(len(G)):
			if len(connectedIndicesHigher(index)) == 1:
				otherindex = connectedIndicesHigher(index)[0]
				if len(connectedIndicesLower(otherindex)) == 1:
					# Grouping node index with otherindex
					#print(f"Grouping {index} with {otherindex}")
					if index not in flatten(groups): # create new group
						groups.append([index, otherindex])
					else: # add to existing group
						for group in groups:
							if index in group:
								group.append(otherindex)
				else:
					# check if index is already contained in any group
					if index not in flatten(groups):
						groups.append([index]) # layer is not grouped, stays alone
		
		graph = networkx.Graph()
		graph.add_nodes_from(range(len(groups)))
		for index in range(len(G)):
			group1 = None
			for g, group in enumerate(groups):
				if index in group:
					group1 = g
			for otherindex in connectedIndicesHigher(index):
				group2 = None
				for g, group in enumerate(groups):
					if otherindex in group:
						group2 = g
				if group1 is not None and group2 is not None and group1 != group2:
					graph.add_edge(group1, group2)
		GroupedM = networkx.to_scipy_sparse_matrix(graph, dtype='f', format='lil', weight=weight_attr)

		groupspos, groupssize, groupsoffsets = {}, [], []
		for index, group in enumerate(groups):
			NAIVE = False
			if NAIVE: # naive alignment just takes the original node positions
				minx = pos[group[0]][0] - quadsizes[group[0]][0]/2
				maxx = pos[group[0]][0] + quadsizes[group[0]][0]/2
				miny = pos[group[0]][1] - quadsizes[group[0]][1]/2
				maxy = pos[group[0]][1] + quadsizes[group[0]][1]/2
				for node in group[1:]:
					minx = min(minx, pos[node][0] - quadsizes[node][0]/2)
					maxx = max(maxx, pos[node][0] + quadsizes[node][0]/2)
					miny = min(miny, pos[node][1] - quadsizes[node][1]/2)
					maxy = max(maxy, pos[node][1] + quadsizes[node][1]/2)
				#print(f"group min ({minx}, {miny}) max ({maxx}, {maxy})")
				groupspos[index] = [(minx+maxx)/2, (miny+maxy)/2]
				groupssize.append((maxx-minx, maxy-miny))
				offsets = []
				for node in group:
					offsets.append([pos[node][0]-groupspos[index][0], pos[node][1]-groupspos[index][1]])
				groupsoffsets.append(offsets)
			else: # use position of first node, then align horizontally with desired spacing + buffer
				groupwidth = - self.desiredHorizontalSpacingWithinGroup
				maxheight = 0
				for node in group:
					groupwidth += quadsizes[node][0]
					groupwidth += self.desiredHorizontalSpacingWithinGroup
					maxheight = max(maxheight, quadsizes[node][1])
				groupssize.append((groupwidth, maxheight))
				groupspos[index] = [pos[group[0]][0] - quadsizes[0][0]/2 + groupwidth/2, pos[group[0]][1]]
				offsets = []
				offset = - groupwidth / 2
				for node in group:
					offset += quadsizes[node][0] / 2
					offsets.append([offset, 0])
					offset += quadsizes[node][0] / 2
					offset += self.desiredHorizontalSpacingWithinGroup
				groupsoffsets.append(offsets)
		groupssize = numpy.array(groupssize)

		return graph, groups, GroupedM, groupspos, groupssize, groupsoffsets

	# A layout for NetworkX.
	#
	# This function returns a NetworkX layout, which is really just a
	# dictionary of node positions (2D X-Y tuples) indexed by the node name.
	async def forceatlas2_networkx_layout_async(self, G, pos=None, quadsizes=None, iterations=100, weight_attr=None):
		try:
			import cynetworkx
		except ImportError:
			cynetworkx = None

		assert isinstance(G, networkx.classes.graph.Graph) or \
			(cynetworkx and isinstance(G, cynetworkx.classes.graph.Graph)), "Not a networkx graph"
		assert isinstance(pos, dict) or (pos is None), "pos must be specified as a dictionary, as in networkx"
		assert not(self.groupLinearlyConnectedNodes and pos is None), \
			"can only group linearly connected nodes when a list of positions is given"

		M = networkx.to_scipy_sparse_matrix(G, dtype='f', format='lil', weight=weight_attr)
		
		if self.groupLinearlyConnectedNodes:
			graph, groups, GroupedM, groupspos, groupssize, groupsoffsets = self.groupNodes(G, pos, quadsizes, weight_attr)

		if quadsizes is not None:
			if not isinstance(quadsizes, numpy.ndarray):
				quadsizes = numpy.array(quadsizes)
			assert quadsizes.shape[0] == M.shape[0], \
				"quadsizes has the wrong length. It must have exactly as many entries as there are nodes"
			assert quadsizes.shape[1] == 2, \
				"quadsizes has the wrong dimensions. Each node entry must have exactly two float values: width and height"
		if pos is None:
			l = await self.forceatlas2(M, pos=None, quadsizes=quadsizes, iterations=iterations)
		else:
			if self.groupLinearlyConnectedNodes:
				groupsposlist = numpy.asarray([groupspos[i] for i in graph.nodes()])
				l = await self.forceatlas2(GroupedM, pos=groupsposlist, quadsizes=groupssize, iterations=iterations,
					groups=groups, individualG=M, individualPosOffset=groupsoffsets, individualSizes=quadsizes)
			else:
				poslist = numpy.asarray([pos[i] for i in G.nodes()])
				l = await self.forceatlas2(M, pos=poslist, quadsizes=quadsizes, iterations=iterations)
		return dict(zip(G.nodes(), l))

	def forceatlas2_networkx_layout(self, G, pos=None, quadsizes=None, iterations=100, weight_attr=None):
		return asyncio.run(self.forceatlas2_networkx_layout_async(G, pos, quadsizes, iterations, weight_attr))

	# A layout for igraph.
	#
	# This function returns an igraph layout
	async def forceatlas2_igraph_layout_async(self, G, pos=None, quadsizes=None, iterations=100, weight_attr=None):
		from scipy.sparse import csr_matrix
		import igraph

		def to_sparse(graph, weight_attr=None):
			edges = graph.get_edgelist()
			if weight_attr is None:
				weights = [1] * len(edges)
			else:
				weights = graph.es[weight_attr]

			if not graph.is_directed():
				edges.extend([(v, u) for u, v in edges])
				weights.extend(weights)

			return csr_matrix((weights, zip(*edges)))

		assert isinstance(G, igraph.Graph), "Not a igraph graph"
		if isinstance(pos, list):
			pos = numpy.array(pos)
		assert isinstance(pos, numpy.ndarray) or (pos is None), "pos must be a list or numpy array"

		if self.groupLinearlyConnectedNodes:
			graph, groups, GroupedM, groupspos, groupssize, groupsoffsets = self.groupNodes(G, pos, quadsizes)

		if quadsizes is not None:
			if not isinstance(quadsizes, numpy.ndarray):
				quadsizes = numpy.array(quadsizes)
			assert quadsizes.shape[0] == G.shape[0], \
				"quadsizes has the wrong length. It must have exactly as many entries as there are nodes"
			assert quadsizes.shape[1] == 2, \
				"quadsizes has the wrong dimensions. Each node entry must have exactly two float values: width and height"

		adj = to_sparse(G, weight_attr)
		if self.groupLinearlyConnectedNodes:
			groupsposlist = numpy.asarray([groupspos[i] for i in graph.nodes()])
			coords = await self.forceatlas2(GroupedM, pos=groupsposlist, quadsizes=groupssize, iterations=iterations,
				groups=groups, individualG=adj, individualPosOffset=groupsoffsets, individualSizes=quadsizes)
		else:
			poslist = numpy.asarray([pos[i] for i in G.nodes()])
			coords = await self.forceatlas2(adj, pos=poslist, quadsizes=quadsizes, iterations=iterations)

		return igraph.layout.Layout(coords, 2)

	def forceatlas2_igraph_layout(self, G, pos=None, quadsizes=None, iterations=100, weight_attr=None):
		asyncio.run(self.forceatlas2_igraph_layout_async(G, pos, quadsizes, iterations, weight_attr))