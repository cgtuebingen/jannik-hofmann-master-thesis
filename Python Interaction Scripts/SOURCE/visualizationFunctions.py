#!/usr/bin/env python

# This module contains all of the functions and calculations for visualizing the neural networks
# in 3D space. It uses the visualizationSettings.py to achieve this task.
# Furthermore, it defines the rules for interaction of the UE4 player with the 3D environment

# USED LIBRARIES
import asyncio
import os
import sys
import time
from datetime import datetime
import traceback
import math
import msgpack
from aioconsole import ainput
import re
import importlib.util
import numpy as np
from types import SimpleNamespace
import ast
import random
import matplotlib.pyplot as plt
import itertools
import functools
import networkx as nx

# LOCAL IMPORTS
import visualizationSettings as design
import websocketServer as server
import aiInteraction as ai
import serverCommands
import loggingFunctions
import serverSettings as setting
import debugAndTesting
from forceatlas2 import ForceAtlas2

# Coordinates class stored 3 floats x, y, z
class Coordinates:
	# You can initialize Coordinates in the following ways:
	def __init__(self, a = None, b = None, c = None, *, x = None, y = None, z = None, default = 0):
		# By another Coordinates instance, to copy it
		if type(a) is Coordinates:
			self.x, self.y, self.z = a.x, a.y, a.z
		# Without parameters as default, default, default
		elif a is None:
			self.x = default.x if type(default) is Coordinates else float(default)
			self.y = default.y if type(default) is Coordinates else float(default)
			self.z = default.z if type(default) is Coordinates else float(default)
		# By a tuple or list which acts the same way as one, two or three parameters
		elif type(a) is tuple or type(a) is list:
			if a is tuple:
				a = list(a)
			if len(a) == 1:
				self.x, self.y, self.z = float(a[0]), float(a[0]), float(a[0])
			if len(a) == 2:
				self.x, self.y, self.z = float(a[0]), float(a[0]), float(a[1])
			if len(a) > 2:
				self.x, self.y, self.z = float(a[0]), float(a[1]), float(a[2])
		# One parameter: All the same
		else:
			self.x, self.y, self.z = float(a), float(a), float(a)
		
		# Two parameters: x=y, z
		if b is not None:
			self.z = b.z if type(b) is Coordinates else float(b)
		# Three parameters: x, y, z
		if c is not None:
			self.y = b.y if type(b) is Coordinates else float(b)
			self.z = c.z if type(c) is Coordinates else float(c)
		
		# Or specify/override parameters x, y, z by name
		if (x is not None): self.x = x.x if type(x) is Coordinates else float(x)
		if (y is not None): self.y = y.y if type(y) is Coordinates else float(y)
		if (z is not None): self.z = z.z if type(z) is Coordinates else float(z)

	# String representations
	def __str__(self):
		return f"({self.x:.2f}, {self.y:.2f}, {self.z:.2f})".replace(".00", "")
	def __repr__(self):
		return f"({self.x:.2f}, {self.y:.2f}, {self.z:.2f})".replace(".00", "")

	# Overloading operators
	def __add__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 0)
		new = self.copy()
		new.add(other)
		return new
	def __sub__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 0)
		new = self.copy()
		new.sub(other)
		return new
	def __mul__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 1)
		new = self.copy()
		new.scale(other)
		return new
	def __truediv__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 1)
		new = self.copy()
		new.scale(1/other.x, 1/other.y, 1/other.z)
		return new
	def __or__(self, other): # | returns the average between two points
		if type(other) is not Coordinates:
			other = Coordinates(other, default = self)
		new = self.copy()
		new.avg(other)
		return new
	def __eq__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other)
		return math.isclose(self.x, other.x) and \
			math.isclose(self.y, other.y) and \
			math.isclose(self.z, other.z)

	# Return a copy of the Coordinates
	def copy(self):
		copy = Coordinates(self)
		return copy

	# Multiply it with other Coordinates, same structure as __init__()
	def scale(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args, default = 1)
		if (x is not None): factor.x = x.x if type(x) is Coordinates else float(x)
		if (y is not None): factor.y = y.y if type(y) is Coordinates else float(y)
		if (z is not None): factor.z = z.z if type(z) is Coordinates else float(z)
		self.x *= factor.x
		self.y *= factor.y
		self.z *= factor.z
		return self

	# Add it with other Coordinates, same structure as __init__()
	def add(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args)
		if (x is not None): factor.x = x.x if type(x) is Coordinates else float(x)
		if (y is not None): factor.y = y.y if type(y) is Coordinates else float(y)
		if (z is not None): factor.z = z.z if type(z) is Coordinates else float(z)
		self.x += factor.x
		self.y += factor.y
		self.z += factor.z
		return self

	# Add it with other Coordinates, same structure as __init__()
	def sub(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args)
		if (x is not None): factor.x = x.x if type(x) is Coordinates else float(x)
		if (y is not None): factor.y = y.y if type(y) is Coordinates else float(y)
		if (z is not None): factor.z = z.z if type(z) is Coordinates else float(z)
		self.x -= factor.x
		self.y -= factor.y
		self.z -= factor.z
		return self

	# Middle between two Coordinates, same structure as __init__()
	def avg(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args, default = self)
		if (x is not None): factor.x = x.x if type(x) is Coordinates else float(x)
		if (y is not None): factor.y = y.y if type(y) is Coordinates else float(y)
		if (z is not None): factor.z = z.z if type(z) is Coordinates else float(z)
		self.x += factor.x
		self.y += factor.y
		self.z += factor.z
		self.x /= 2
		self.y /= 2
		self.z /= 2
		return self

	# Convert x, y, z to tuples
	def xyz(self):
		return (self.x, self.y, self.z)

	# Convert x, y, z to a list
	def list(self):
		return [self.x, self.y, self.z]

	# Switch x and y axes because of how Unreal Engine works
	# (Here in python, z is horizontal and y the vertical one, in UE the other way around)
	def switchYZ(self):
		self.y, self.z = self.z, self.y
		return self

# Transform coordinates to representation that makes sense for Unreal Engine viewing
def transformCoordinates(originalposition = None, originalsize = None, positionIsCenterPoint = False):
	position = Coordinates(originalposition)
	size = Coordinates(originalsize)
	if position is not None:
		#position.scale(z = 1/5)
		position.add(10000, 0, -10000)
		position.switchYZ()
	if size is None: return position
	size.switchYZ()
	if not positionIsCenterPoint:
		position += size/2
	size.scale(1/100)
	if position is None: return size
	return position, size

# Format a color to always have three float values between 0 and 1
def formatColor(color):
	if (type(color) is str):
		if color[0] == '#':   color = color[1:]
		if len(color) == 0:   color = '0' * 6 + 'ff' # empty => black
		elif len(color) == 1: color = color * 6 + 'ff' #x => #xxxxxxff
		elif len(color) == 2: color = color * 3 + 'ff' #xy => #xyxyxyff
		elif len(color) == 3: color = color[0]*2 + color[1]*2 + color[2]*2 + 'ff' #rgb => rrggbbff
		elif len(color) == 4: color = color[0]*2 + color[1]*2 + color[2]*2 + color[3]*2 #rgba => rrggbbaa
		elif len(color) == 5: color = color[0]*2 + color[1]*2 + color[2]*2 + color[3:] #rgbxy => rrggbbxy
		elif len(color) == 6: color = color + 'ff' #rrggbb => #rrggbbff
		elif len(color) == 7: color = color + color[-1] #rrggbba => #rrggbbaa
		elif len(color) > 8:  color = color[:8] #rrggbbaax* => #rrggbbaa
		converted = []
		for i in range(4):
			hex = color[i*2:i*2+2]
			val = int(hex, 16)
			converted.append(val/256)
		return converted
	
	# Tuple to list
	if (type(color) is tuple): color = list(color)
	# Make a single number into a list
	if type(color) is not list: color = [color]
	# Make sure we have 3 values in that list
	while (len(color) < 3): color.append(color[0])
	# In case anyone was fancy and specified numbers in the 0-255 range
	if any(value > 1 for value in color):
		for i in range(3):
			color[i] = color[i] / 255
	# append alpha:
	if len(color) < 4: color.append(1)
	return color

def colorToHex(color):
	color = formatColor(color)
	hex = "#"
	for part in color:
		part *= 255
		part = int(round(part))
		hex += "%0.2X" % part
	print (hex)
	return hex

# Spawns a cuboid at the specified coordinates with the specified color via a client-connection
async def spawnCuboid(connection, position, size, color, rotator = None, positionIsCenterPoint = False, processDescription = None):
	if type(position) is not Coordinates:
		position = Coordinates(position)
	if type(size) is not Coordinates:
		size = Coordinates(size)
	color = formatColor(color)
	if rotator is None:
		rotator = 0
	if type(rotator) is not Coordinates:
		rotator = Coordinates(rotator)
	if connection is None:
		# Just log what we would be doing
		loggingFunctions.log(f"Would be spawning a cuboid at position {position} " +
		f" with size {size}{', rotation ' + str(rotator) if rotator != 0 else ''} and color {color}.")
		if (rotator.x == 0):
			rectangle = plt.Rectangle(
				(position.z - size.z/2, position.y - size.y/2),
				size.z, size.y,
				color = list(color),
				linewidth = 0)
			plt.gca().add_patch(rectangle)
		else:
			rectangle = plt.Rectangle(
				(position.z, position.y),
				size.z/2, size.y/2,
				color = list(color),
				linewidth = 0,
				angle=-rotator.x)
			plt.gca().add_patch(rectangle)
			rectangle = plt.Rectangle(
				(position.z, position.y),
				size.z/2, size.y/2,
				color = list(color),
				linewidth = 0,
				angle=180-rotator.x)
			plt.gca().add_patch(rectangle)
	else:
		# Transform coordinates to UE
		position, size = transformCoordinates(position, size, positionIsCenterPoint)
		# Append them into one large array and send them away as instruction
		posSizeColor = [float(i) for i in
			position.list() + size.list() + formatColor(color) + rotator.list()]
		await connection.send(("SPAWN CUBOID pos size color opacity rot", posSizeColor))
		if processDescription is None:
			processDescription = "Spawning cuboids in the virtual world"
		else:
			processDescription = "Spawning cuboids in the virtual world for " + processDescription
		await server.sleep(0.2, processDescription) # TODO: Find way to spawn all in the same frame

# From AI layer dimensions, calculate a reasonable size for visual representation
def sizeFromLayerDimensions(layerDims):
	size = []
	for dim in layerDims:
		# Append useful dim values to size-list until we have 3
		if dim is not None and dim > 0 and len(size) < 3:
			size.append(dim)
	# If we have less, just put 1 in the front a few times
	while (len(size) < 3):
		size = [1] + size
	scaleDims = getattr(design.layouting, 'scaleLayerSizes', None)
	addToDims = getattr(design.layouting, 'addToLayerSizes', None)
	minDims = getattr(design.layouting, 'minLayerDimensions', None)
	maxDims = getattr(design.layouting, 'maxLayerDimensions', None)
	if scaleDims is None:
		scaleDims = [1, 1, 1]
	if type(scaleDims) is tuple:
		scaleDims = list(scaleDims)
	if type(scaleDims) is not list:
		scaleDims = [scaleDims]
	if len(scaleDims) == 1:
		scaleDims *= 3
	if len(scaleDims) == 2:
		scaleDims = [scaleDims[0]] + scaleDims
	if addToDims is None:
		addToDims = [1, 1, 1]
	if type(addToDims) is tuple:
		addToDims = list(addToDims)
	if type(addToDims) is not list:
		addToDims = [addToDims]
	if len(addToDims) == 1:
		addToDims *= 3
	if len(addToDims) == 2:
		addToDims = [addToDims[0]] + addToDims
	for i in range(3):
		size[i] *= scaleDims[i]
		size[i] += addToDims[i]
	if minDims is None:
		minDims = size
	if type(minDims) is tuple:
		minDims = list(minDims)
	if type(minDims) is not list:
		minDims = [minDims]
	if len(minDims) == 1:
		minDims *= 3
	if len(minDims) == 2:
		minDims = [minDims[0]] + minDims
	if maxDims is None:
		maxDims = size
	if type(maxDims) is tuple:
		maxDims = list(maxDims)
	if type(maxDims) is not list:
		maxDims = [maxDims]
	if len(maxDims) == 1:
		maxDims *= 3
	if len(maxDims) == 2:
		maxDims = [maxDims[0]] + maxDims
	for i in range(3):
		size[i] = max(size[i], minDims[i])
		size[i] = min(size[i], maxDims[i])
	return Coordinates(size)

# DEPRECATED
# Draws the tfnet.layer structure via the client-connection
# Returns whether we could successfully draw the architecture
# If connection is None, then the cuboids cannot be drawn but will be displayed in a graphic
# Linearly = All layers spread on z axis, with their center on x = 0, y = 0
async def drawstructureLinearly(connection = None):
	if not hasattr(ai.tfnet, "validstructure") or not ai.tfnet.validstructure:
		# Wait, we can't draw that
		return False
	position = Coordinates() # center position of first cube at origin
	drawnLayers = [] # For later reference for drawing layer connections

	# If no connection has been given, initialize matplotlib
	if connection is None:
		plt.axes()
	
	for index, layer in enumerate(ai.tfnet.layers):
		# Retrieve reasonable size and scale x, y by 50
		size = sizeFromLayerDimensions(layer[2]).scale(50, 1)
		# Shift the position, so layers don't overlap
		position.add(z = size/2)
		# Check if actually connected to previously drawn layer
		if not ai.tfnet.layers[index-1][0] in layer[4]:
				position.add(z = 1000) # increase distance between unconnected layers
		# Retrieve color for this layer type
		color = design.layerColors.get(layer[1].lower(),
			design.layerColors.get("default"))
		# Spawn that thing and append it to drawnLayers
		await spawnCuboid(connection, position, size, color, positionIsCenterPoint = True)
		drawnLayers.append([position.copy(), size.copy(), color])
		# Draw connections between layers if applicable
		if design.connections.display and \
			(len(layer[4]) > 1 or layer[4][0] != ai.tfnet.layers[index-1][0]):
			# connected to another layer than just the previous one. Check which one it is
			for connectedIndex, connectedLayer in enumerate(ai.tfnet.layers):
				# Check if that layer matches with the connected list and isn't just the previous
				if connectedLayer[0] in layer[4] and connectedIndex < index-1:
					# retrieve position and size of the connected layer
					cposition, csize, *_ = drawnLayers[connectedIndex]
					# calculate random x and y connection properties (so connections don't overlap)
					minval = min(size.x, size.y, csize.x, csize.y)/2
					maxval = max(size.x, size.y, csize.x, csize.y)/2
					randomPos = Coordinates(
						x = random.uniform(-minval * 0.8, minval * 0.8),
						y = random.uniform(maxval * 1.3, maxval * 2))
					if True:#not design.angledConnections:
						await spawnCuboid(connection,
							Coordinates(randomPos, size/2, position - design.connections.strength/2),
							Coordinates(design.connections.strength, y = randomPos - size/2),
							design.connections.color)
						await spawnCuboid(connection,
							Coordinates(randomPos, randomPos, cposition - design.connections.strength/2),
							Coordinates(design.connections.strength, z = position - cposition + design.connections.strength),
							design.connections.color)
						await spawnCuboid(connection,
							Coordinates(randomPos, csize/2, cposition - design.connections.strength/2),
							Coordinates(design.connections.strength, y = randomPos - csize/2),
							design.connections.color)
					else: # direct connections between layers instead of angled ones
						# define proportion of horizontal bar to angle away on each side
						deltaz = random.uniform(0, 0.5)
						deltaz *= (position.z - cposition.z + design.connections.strength)
						def alpha(size, degrees = True):
							alpha = math.atan(deltaz / (randomPos.y - size.y/2))
							if degrees: return math.degrees(alpha)
							else: return alpha
						
						posz = position - deltaz/2
						origsizey = randomPos - size/2
						sizey = origsizey / math.cos(alpha(size, False))
						await spawnCuboid(connection,
							Coordinates(randomPos, size/2 + origsizey/2, posz),
							Coordinates(design.connections.strength, y = sizey),
							design.connections.color,
							rotator = Coordinates(x = -alpha(size)),
							positionIsCenterPoint = True)
						
						posz = cposition - design.connections.strength/2 + deltaz
						sizez = position - cposition + design.connections.strength - deltaz * 2
						await spawnCuboid(connection,
							Coordinates(randomPos, randomPos, posz + sizez/2),
							Coordinates(design.connections.strength, z = sizez),
							design.connections.color,
							positionIsCenterPoint = True)
						
						posz = cposition + deltaz/2
						origsizey = randomPos - csize/2
						sizey = origsizey / math.cos(alpha(csize, False))
						await spawnCuboid(connection,
							Coordinates(randomPos, csize/2 + origsizey/2, posz),
							Coordinates(design.connections.strength, y = sizey),
							design.connections.color,
							rotator = Coordinates(x = alpha(csize)),
							positionIsCenterPoint = True)
		position.add(z = size/2 + design.layouting.horizontalSpaceBetweenLayers)
	
	# Displaying plot if no client connection was given
	if connection is None:
		plt.axis('auto')
		plt.show()

	return True

class Layer:
	layerList = []

	def __init__(self, position = 0, size = 0, color = "default", parents = [], activeAreaAbove = 0, activeAreaBelow = 0, index = None):
		if index is None:
			index = len(Layer.layerList)
		self.position = Coordinates(position)
		self.size = Coordinates(size)
		self.activeAreaAbove = Coordinates(activeAreaAbove)
		self.activeAreaBelow = Coordinates(activeAreaBelow)
		self.color = design.layerColors.get(color.lower(),
			design.layerColors.get("default"))
		self.index = index
		self.parents = []
		self.findParents(parents)
		self.justmoved = []

	def append(self):
		Layer.layerList.append(self)

	@classmethod
	def resetAllLayers(cls):
		Layer.layerList = []
		return cls

	def findParents(self, connectedLayerName):
		if type(connectedLayerName) is list:
			for name in connectedLayerName:
				self.findParents(name)
			return
		for connectedIndex, connectedLayer in enumerate(ai.tfnet.layers):
			# Check if that layer matches with the connected list, also matches previous
			if connectedLayer[0] == connectedLayerName and connectedIndex < len(Layer.layerList):
				self.parents.append(Layer.layerList[connectedIndex])

	@functools.lru_cache(maxsize=256)
	def isDescendantOf(self, ofIndex):
		if ofIndex in self.parents:
			return True
		return any(parent.isDescendantOf(ofIndex) for parent in self.parents)

	def isDescendantOfList(self, ofList):
		return any(self.isDescendantOf(option) for option in ofList)

	def isAncestorOf(self, ofIndex):
		# Also accepts a list as ofIndex parameter
		if type(ofIndex) is list:
			return any(self.isAncestorOf(option) for option in ofIndex)
		return ofIndex.isDescendantOf(self)

	def haveRelatedDescendant(self, other):
		# Also accepts a list as other parameter
		if type(other) is list:
			return any(self.haveRelatedDescendant(option) for option in other)
		
		return not set(self.descendants + [self]).isdisjoint(other.descendants + [other])

	def descendants(self):
		return [descendant for descendant in Layer.layerList if descendant.isDescendantOf(self)]

	def ancestors(self):
		return [ancestor for ancestor in Layer.layerList if ancestor.isAncestorOf(self)]
	
	def moveWithDescendants(self, moveBy = 0, dontMoveSameAgain = False):
		if not dontMoveSameAgain:
			self.justmoved = []
		if moveBy == 0:
			return
		for descendant in self.descendants():
			if descendant not in self.justmoved:
				descendant.position += moveBy
				self.justmoved.append(descendant)
	
	def doesItOverlap(self, start, end, startt, endd, minimumSpace = 0):
		if type(start) is Coordinates and type(end) is Coordinates and type(startt) is Coordinates and type(endd) is Coordinates:
			return self.doesItOverlap(start.x, end.x, startt.x, endd.x, design.layouting.verticalSpaceBetweenLayers) \
			and self.doesItOverlap(start.y, end.y, startt.y, endd.y, design.layouting.verticalSpaceBetweenLayers) \
			and self.doesItOverlap(start.z, end.z, startt.z, endd.z, design.layouting.horizontalSpaceBetweenLayers)
		if minimumSpace == 0:
			return not (end <= startt or start >= endd)
		else:
			return self.doesItOverlap(start - minimumSpace, end + minimumSpace, startt, endd)

	def whoOverlaps(self):
		badOnes = []
		for layer in Layer.layerList:
			if (self.index > layer.index) \
			and self.doesItOverlap(self.position - self.size/2, self.position + self.size/2, layer.position - layer.size/2, layer.position + layer.size/2):
				badOnes.append(layer)
		return badOnes
		
# DEPRECATED
# Draws the tfnet.layer structure via the client-connection
# Returns whether we could successfully draw the architecture
# If connection is None, then the cuboids cannot be drawn but will be displayed in a graphic
# Tree Basic = Trying to align layers with their connected ones in a tree-like format
async def drawstructureTreeBasic(connection = None):
	if not hasattr(ai.tfnet, "validstructure") or not ai.tfnet.validstructure:
		# Wait, we can't draw that
		return False
	position = Coordinates() # center position of first cube at origin
	drawnLayers = [] # For later reference for drawing layer connections

	# If no connection has been given, initialize matplotlib
	if connection is None:
		plt.axes()
	
	Layer.resetAllLayers()

	for index, layer in enumerate(ai.tfnet.layers):
		# Create layer instance and append it to layerList
		current = Layer(position = 0, size = sizeFromLayerDimensions(layer[2]).scale(50, 1),
			parents = layer[4], color = layer[1], index = index)
		Layer.layerList.append(current)
	
	for current in Layer.layerList:
		# z is set to be directly behind the furthest parent layer
		current.position.z = max([0] + [layer.position.z + layer.size.z/2 for layer in current.parents])
		current.position.z += design.layouting.horizontalSpaceBetweenLayers + current.size.z/2
		
		if len(current.parents) == 0:
			pass # position.x and y stay at 0
		elif len(current.parents) == 1:
			current.position = Coordinates(current.parents[0].position, z = current.position) # x and y change
		else:
			positions = []
			maxY = 0
			minY = 0
			for parent in current.parents:
				if parent.isDescendantOfList(current.parents):
					# move parent and its children by this amount:
					moveBy = min(current.size.y, parent.size.y)/2 + design.layouting.verticalSpaceBetweenLayers
					moveBy = Coordinates(y = moveBy)
					parent.moveWithDescendants(moveBy)
					current.activeAreaAbove += moveBy
					for grandparent in current.parents:
						if parent.isDescendantOf(grandparent):
							grandparent.activeAreaAbove += moveBy
				else:
					positions.append(parent.position.y)
					maxY = max(maxY, parent.position.y + parent.size.y / 2)
					minY = min(minY, parent.position.y - parent.size.y / 2)
			current.position.y = sum(positions) / len(positions)
			current.activeAreaAbove.y = maxY - current.position.y - current.size.y / 2
			current.activeAreaBelow.y = minY - current.position.y + current.size.y/2

		# now check if the desired position is already taken and if so, move things
		current.moveWithDescendants(0) # resetting who just moved
		minY = current.position.y
		for layer in current.whoOverlaps():
			#if layer.position.y > current.position.y:
				# move layer up, current down
				# overlap between the two:
				#moveBy = current.position.y + current.size.y/2 - layer.position.y - layer.size.y/2
				# OVERWRITE: It's safer to calculate to just move everyone by a const. value
				moveBy = current.size.y
				moveBy += design.layouting.verticalSpaceBetweenLayers # add some space
				moveBy /= 2 # everyone does half the work
				moveBy = Coordinates(y = moveBy)
				layer.moveWithDescendants(moveBy, dontMoveSameAgain = True)
				minY = min(minY, layer.position.y - layer.size.y/2)
				for parent in layer.parents:
					parent.activeAreaAbove.y = max(parent.activeAreaAbove.y,
						layer.position.y + layer.size.y/2)
		if len(current.whoOverlaps()) > 0:
			current.position.y = minY - design.layouting.verticalSpaceBetweenLayers - current.size.y/2
		for parent in current.parents:
			parent.activeAreaAbove.y = max(parent.activeAreaAbove.y,
				current.position.y + current.size.y/2)
			parent.activeAreaBelow.y = max(parent.activeAreaBelow.y,
				current.position.y - current.size.y/2)

	for current in Layer.layerList:
		await spawnCuboid(connection, current.position, current.size, current.color, positionIsCenterPoint = True)
		for parent in current.parents:
			y = parent.position.y
			z = parent.position.z
			yy = current.position.y
			zz = current.position.z
			deltay = yy-y
			deltaz = zz-z
			drawIt = True
			if deltay == 0:
				drawIt = False
				#alpha = math.pi/2
				#long = deltaz
			else:
				alpha = math.atan(deltaz/deltay)
				long = deltay / math.cos(alpha)
			if drawIt:
				await spawnCuboid(connection,
					Coordinates(current.position.x, (y+yy)/2, (z+zz)/2),
					Coordinates(design.connections.strength, z = long),
					color = design.connections.color,
					rotator = Coordinates(x = 90-math.degrees(-alpha)),
					positionIsCenterPoint = True)

	# Displaying plot if no client connection was given
	if connection is None:
		plt.axis('auto')
		plt.show()

	return True

# Draws a given layout via the connection by sending drawing instructions.
# If connection is None, then the cuboids cannot be drawn but will be displayed in a graphic
# Positions are given in an array as parameter, the other info is retrieved from ai.tfnet.layers
async def drawLayout(connection, positions):
	positionOffset = Coordinates(0, positions[0][1], positions[0][0]).scale(-1)
	drawnLayers = [] # For later reference for drawing layer connections

	# If no connection has been given, initialize matplotlib
	if connection is None:
		plt.axes()
	
	Layer.resetAllLayers()

	for index, layer in enumerate(ai.tfnet.layers):
		# Create layer instance and append it to layerList
		Layer.layerList.append(Layer(
			position = (positionOffset + (0, positions[index][1], positions[index][0])),
			size = sizeFromLayerDimensions(layer[2]),
			parents = layer[4],
			color = layer[1],
			index = index,
		))
	
	for index, current in enumerate(Layer.layerList):
		await spawnCuboid(connection, current.position, current.size, current.color,
			positionIsCenterPoint = True,
			processDescription = f"layer {index} of {len(Layer.layerList)}")
		if design.connections.display:
			for parent in current.parents:
				y = parent.position.y
				z = parent.position.z
				yy = current.position.y
				zz = current.position.z
				deltay = yy-y
				deltaz = zz-z
				if not design.connections.displayBetweenGroupedLayers:
					if math.isclose(deltaz - current.size.z/2 - parent.size.z/2,
						design.layouting.horizontalSpaceBetweenGroupedLayers) and \
						math.isclose(deltay, 0):
							continue # connection between grouped layers should not be drawn
				thickness = min(design.connections.strength,
					parent.size.x/2, parent.size.y/2,
					current.size.x/2, current.size.y/2)
				if deltay == 0:
					#drawIt = False
					alpha = math.pi/2
					long = deltaz
				else:
					alpha = math.atan(deltaz/deltay)
					long = deltay / math.cos(alpha)
				await spawnCuboid(connection,
					Coordinates(current.position.x, (y+yy)/2, (z+zz)/2),
					Coordinates(thickness, z = long),
					color = design.connections.color,
					rotator = Coordinates(x = 90-math.degrees(-alpha)),
					positionIsCenterPoint = True,
					processDescription = f"connections to layer {index} of {len(Layer.layerList)}")

	# Displaying plot if no client connection was given
	if connection is None:
		plt.axis('auto')
		plt.show()

	return True

# Draws the tfnet.layer structure via the client-connection
# Returns whether we could successfully draw the architecture
# If connection is None, then the cuboids cannot be drawn but will be displayed in a graphic
# Using modified forceatlas2-algorithm for layouting
async def drawstructureForceLayout(connection = None):
	if not hasattr(ai.tfnet, "layoutPositions") or ai.tfnet.layoutPositions is None:
		# layouting hasn't been calculated yet, so we need to do the force layout from scratch

		if not hasattr(ai.tfnet, "validstructure") or not ai.tfnet.validstructure:
			# Wait, we can't draw that, network doesn't have a valid structure...
			return False
		
		# Creating a graph layout from the layer structure...
		graph = nx.Graph()
		graph.add_nodes_from(range(len(ai.tfnet.layers)))
		positioning = 0
		positions = {}
		sizes = []
		# Add each layer to the graph
		for index, layer in enumerate(ai.tfnet.layers):
			newSize = sizeFromLayerDimensions(layer[2])
			# Aligning all layers along the z axis
			positioning += newSize.z/2
			# storing the accumulated z position
			positions[index] = [positioning, 0]
			# Keep aligning all layers with horizontal spacing for initilization
			positioning += newSize.z/2
			positioning += design.layouting.horizontalSpaceBetweenLayers * 5
			# storing size
			sizes.append((newSize.z, newSize.y))
			# Find all parents of the current layer
			for indexParent, layerParent in enumerate(ai.tfnet.layers):
				if layerParent[0] in layer[4]: # is a parent
					graph.add_edge(indexParent, index) # add an edge in the graph

		# Layouting instructions for modified forceatlas2-algorithm
		NUMBER_OF_ITERATIONS = design.layouting.iterations
		NUMBER_OF_PLOTS = design.layouting.debug.drawPlots * design.layouting.debug.numberOfPlots
		forceatlas2 = ForceAtlas2(
			# Behavior alternatives
			outboundAttractionDistribution=True, # Dissuade hubs
			edgeWeightInfluence=1.0,
			groupLinearlyConnectedNodes=True, # only available with networkx layout
			orderconnectedQuadsOnXaxis=True, # orders connected nodes by their index on x axis
			# spacing between the nodes:
			desiredHorizontalSpacing=design.layouting.horizontalSpaceBetweenLayers,
			desiredVerticalSpacing=design.layouting.verticalSpaceBetweenLayers,
			bufferZone=design.layouting.bufferZone,
			desiredHorizontalSpacingWithinGroup=design.layouting.horizontalSpaceBetweenGroupedLayers,

			# Performance
			jitterTolerance=1.0, # Tolerance
			barnesHutOptimize=False,
			barnesHutTheta=1.2,

			# Tuning
			scalingRatio=2.0,
			strongGravityMode=False,
			gravity=1.0,
			randomlyOffsetNodes=(0, design.layouting.bufferZone/20),

			# Log
			verbose=True,
			debugDisplayPlot=NUMBER_OF_PLOTS,
			addedMsPerFrame=0
		)
		# execute force based algorithm
		ai.tfnet.layoutPositions = await forceatlas2.forceatlas2_networkx_layout_async(graph, pos=positions, quadsizes=sizes, iterations=NUMBER_OF_ITERATIONS)
	# draw layers at the resulting positions
	return await drawLayout(connection, ai.tfnet.layoutPositions)

# Choose which one to use by default
async def drawstructure(connection = None):
	await drawstructureForceLayout(connection)

# Will draw all kernels for the selected layer as defined in trainable var "{layername}/kernel:0"
async def drawKernels(connection, layerIndex, refreshTrainVars=False):
	if len(Layer.layerList) <= layerIndex:
		await connection.sendstatus(16, f"tf draw structure needs to be called before any kernel can be drawn!")
	if refreshTrainVars:
		ai.tfRefreshTrainableVars()
	trainableVars = ai.tfnet.layers[layerIndex][5]
	if not 'kernel' in trainableVars or len(trainableVars['kernel']) == 0:
		# No kernel found for this layer. Let's try to refresh
		if not refreshTrainVars:
			return await drawKernels(connection, layerIndex, True)
		# Still no kernel found. Output error msg and return
		await connection.sendstatus(16, f"Layer {layerIndex} does not have any kernels that could be visualized!")
		return False
	kernel = trainableVars['kernel'][0]
	await connection.sendstatus(-10, f"Now drawing kernels with dimensions {kernel.shape} of layer {layerIndex}...")
	colored = (layerIndex == 1 and kernel.shape[2] == 3)
	pixelsPerGroup = kernel.shape[:2]
	if colored:
		if len(kernel.shape) < 4:
			groups = (1, 1)
		elif len(kernel.shape) == 4:
			groups = (kernel.shape[3], 1)
		elif len(kernel.shape) == 5:
			groups = kernel.shape[3:5]
	else:
		if len(kernel.shape) < 3:
			groups = (1, 1)
		elif len(kernel.shape) == 3:
			groups = (kernel.shape[2], 1)
		elif len(kernel.shape) == 4:
			groups = kernel.shape[2:4]
	size = Coordinates(design.kernels.defaultPixelDimensions, z = design.kernels.thickness)
	if size.z <= 1:
		size.z *= size.x
	# -- here you could add responsive calculations that adjust the pixel size
	#    depending on how many there and how large everything would be.
	if design.kernels.minPixelDimensions is not None:
		size.x = max(size.x, design.kernels.minPixelDimensions[0])
		size.y = max(size.y, design.kernels.minPixelDimensions[1])
	if design.kernels.maxPixelDimensions is not None:
		size.x = min(size.x, design.kernels.maxPixelDimensions[0])
		size.y = min(size.y, design.kernels.maxPixelDimensions[1])
	spacing = Coordinates(design.kernels.spacingBetweenKernels, z = 0)
	if spacing.x <= 1 or spacing.y <= 1:
		spacing.x *= size.x
		spacing.y *= size.y
	structureWidth = groups[0] * pixelsPerGroup[0] * size.x + (groups[0]-1) * spacing.x
	structureHeight = groups[1] * pixelsPerGroup[1] * size.y + (groups[1]-1) * spacing.y
	progress = 0
	for groupy in range(groups[1]):
		for groupx in range(groups[0]):
			for pixely in range(pixelsPerGroup[1]):
				for pixelx in range(pixelsPerGroup[0]):
					if not colored:
						nplocation = [1] * len(kernel.shape)
						if len(kernel.shape) > 0: nplocation[0] = pixelx
						if len(kernel.shape) > 1: nplocation[1] = pixely
						if len(kernel.shape) > 2: nplocation[2] = groupx
						if len(kernel.shape) > 3: nplocation[3] = groupy
						color = kernel[tuple(nplocation)]
						# normalize color
						color -= np.min(kernel)
						color /= np.max(kernel) - np.min(kernel)
					else: # colored
						nplocation = [1] * len(kernel.shape)
						if len(kernel.shape) > 0: nplocation[0] = pixelx
						if len(kernel.shape) > 1: nplocation[1] = pixely
						if len(kernel.shape) > 3: nplocation[3] = groupx
						if len(kernel.shape) > 4: nplocation[4] = groupy
						color = []
						for rgb in range(3):
							nplocation[2] = rgb
							color.append(kernel[tuple(nplocation)])
							# normalize color
							color[rgb] -= np.min(kernel)
							color[rgb] /= np.max(kernel) - np.min(kernel)
					position = Coordinates(
						# x
						+ Layer.layerList[layerIndex].position.x
						- Layer.layerList[layerIndex].size.x / 2
						- design.kernels.spacingFromLayer
						- structureWidth
						+ groupx * pixelsPerGroup[0] * size.x
						+ groupx * spacing.x
						+ pixelx * size.x
					, # y
						+ Layer.layerList[layerIndex].position.y
						- structureHeight / 2
						+ groupy * pixelsPerGroup[1] * size.y
						+ groupy * spacing.y
						+ pixely * size.y
					, # z
						+ Layer.layerList[layerIndex].position.z
						- Layer.layerList[layerIndex].size.z / 2
						- size.z / 2
					)
					progress += 1
					processDescription = f"kernels of layer {layerIndex} at pixel {progress} " + \
						f"of {groups[1] * groups[0] * pixelsPerGroup[1] * pixelsPerGroup[0]}"
					await spawnCuboid(connection, position, size, color,
						processDescription = processDescription)


# FOR DEBUGGING, executed if you start this script directly
async def testVis():
	loadRealNN = False
	
	setting.checkSettings()
	if loadRealNN:
		path = setting.DEFAULT_LOAD_NN_PATH
		path = setting.AVAILABLE_NN_PATHS.get(path, path)
		ai.preparemodule(path)
		ai.importtf()
	else:
		structure = debugAndTesting.const_fake_structure
		await ai.parsestructure(None, structure)
	await drawstructure()

# call this module as main module, visualization will be tested and displayed as a grahic
if __name__ == '__main__':
	loop = asyncio.get_event_loop()
	loop.run_until_complete(testVis())
	loop.close()
