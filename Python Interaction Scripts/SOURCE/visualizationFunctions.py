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
from matplotlib import cm
import itertools
import functools
import networkx as nx
from PIL import Image
from scipy.ndimage import gaussian_filter
from tqdm import tqdm

# LOCAL IMPORTS
import visualizationSettings as design
import websocketServer as server
import aiInteraction as ai
import serverCommands
import loggingFunctions
import serverSettings as setting
import debugAndTesting
from forceatlas2 import ForceAtlas2
import fileHandling

# Singal to see whether client is ready to receive the next drawing instruction
readyToDraw = True

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
			if type(a) is tuple:
				a = list(a)
			self.x, self.y, self.z = float(a[0]), float(a[len(a)//3]), float(a[len(a)-1])
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
		if x is not None: self.x = x.x if type(x) is Coordinates else float(x)
		if y is not None: self.y = y.y if type(y) is Coordinates else float(y)
		if z is not None: self.z = z.z if type(z) is Coordinates else float(z)

	# String representations
	def __str__(self):
		return f"({self.x:.2f}, {self.y:.2f}, {self.z:.2f})".replace(".00", "")
	def __repr__(self):
		return self.__str__()

	# Overloading operators
	def __add__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 0)
		return self.copy().add(other)

	def __sub__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 0)
		return self.copy().sub(other)

	def __mul__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 1)
		return self.copy().scale(other)

	def __truediv__(self, other):
		if type(other) is not Coordinates:
			other = Coordinates(other, default = 1)
		return self.copy().scale(1/other.x, 1/other.y, 1/other.z)

	def __or__(self, other): # | returns the average between two points
		if type(other) is not Coordinates:
			other = Coordinates(other, default = self)
		return self.copy().avg(other)

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
		factor = Coordinates(*args, default = 1, x = x, y = y, z = z)
		self.x *= factor.x
		self.y *= factor.y
		self.z *= factor.z
		return self

	# Add it with other Coordinates, same structure as __init__()
	def add(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args, x = x, y = y, z = z)
		self.x += factor.x
		self.y += factor.y
		self.z += factor.z
		return self

	# Add it with other Coordinates, same structure as __init__()
	def sub(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args, x = x, y = y, z = z)
		self.x -= factor.x
		self.y -= factor.y
		self.z -= factor.z
		return self

	# Middle between two Coordinates, same structure as __init__()
	def avg(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args, default = self, x = x, y = y, z = z)
		return (self + factor) / 2

	# Convert Coordinates to tuples
	def xy(self): return self.x, self.y
	def yz(self): return self.y, self.z
	def xz(self): return self.x, self.z
	def xyz(self): return self.x, self.y, self.z

	# Convert Coordinates to a list
	def list(self):
		return [self.x, self.y, self.z]

	# Switch y and z axes because of how Unreal Engine works
	# (Here in python, z is horizontal and y the vertical one, in UE the other way around)
	def switchYZ(self):
		self.y, self.z = self.z, self.y
		return self
	# The other two functions for easier access in case it's needed:
	def switchXY(self):
		self.x, self.y = self.y, self.x
		return self
	def switchXZ(self):
		self.x, self.z = self.z, self.x
		return self

# Transform coordinates to representation that makes sense for Unreal Engine viewing
def transformCoordinates(originalposition = None, originalsize = None, positionIsCenterPoint = False):
	if originalposition is not None:
		position = Coordinates(originalposition)
		position.add(10000, 0, -10000)
		position.switchYZ()
	if originalsize is not None:
		size = Coordinates(originalsize)
		size.switchYZ()
		if not positionIsCenterPoint:
			position += size/2
		size.scale(1/100)
	if originalposition is None:
		return size
	if originalsize is None:
		return position
	return position, size

# Format a color to always have three float values between 0 and 1
def formatColor(color):
	if type(color) is str:
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
			hex = color[i*2 : i*2 + 2]
			val = int(hex, 16)
			converted.append(val / 255)
		return converted
	
	# Tuple to list
	if type(color) is tuple: color = list(color)
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
		part = int(round(part * 255))
		hex += "%0.2X" % part
	return hex

# Packs cuboid drawing instructions into a list, that can be sent alone or in a batch via websocket later
async def packCuboid(position, size, color, rotator = 0, positionIsCenterPoint = False):
	if type(position) is not Coordinates:
		position = Coordinates(position)
	if type(size) is not Coordinates:
		size = Coordinates(size)
	color = formatColor(color)
	if type(rotator) is not Coordinates:
		rotator = Coordinates(rotator)
	# Transform coordinates to UE
	position, size = transformCoordinates(position, size, positionIsCenterPoint)
	# Append them into one large array and send them away as instruction
	propertyList = [float(i) for i in
		position.list() + size.list() + formatColor(color) + rotator.list()]
	return ("SPAWN CUBOID pos size color opacity rot", propertyList)

# Packs image drawing instructions into a list, that can be sent alone or in a batch via websocket later
async def packImage(path, position, size, rotator = 0, positionIsCenterPoint = False):
	if type(position) is not Coordinates:
		position = Coordinates(position)
	if type(size) is not Coordinates:
		size = Coordinates(size)
	if type(rotator) is not Coordinates:
		rotator = Coordinates(rotator)
	# Transform coordinates to UE
	position, size = transformCoordinates(position, size, positionIsCenterPoint)
	# Append them into one large array and send them away as instruction
	propertyList = [path] + \
		[float(i) for i in position.list() + size.list() + rotator.list()]
	return ("SPAWN IMAGE path pos size rot", propertyList)

# Spawns a cuboid at the specified coordinates with the specified color via a client-connection
# Rotations might not work perfectly yet, especially with axis switching...
async def debugDrawCuboidInPlot(position, size, color, rotator = 0, ignoreAxis = 'z'):
	if type(position) is not Coordinates:
		position = Coordinates(position)
	if type(size) is not Coordinates:
		size = Coordinates(size)
	color = formatColor(color)
	if type(rotator) is not Coordinates:
		rotator = Coordinates(rotator)
	# Just log what we would be doing
	loggingFunctions.log(f"Would be spawning a cuboid at position {position} " +
	f" with size {size}{', rotation ' + str(rotator) if rotator != 0 else ''} and color {color}.")
	if ignoreAxis in ('x', 0):
		position.switchXZ()
		size.switchXZ()
		rotator.switchXZ()
	elif ignoreAxis in ('y', 1):
		position.switchYZ()
		size.switchYZ()
		rotator.switchYZ()
	if rotator.z == 0:
		rectangle = plt.Rectangle(
			(position.x - size.x/2, position.y - size.y/2),
			size.x, size.y,
			color = list(color),
			linewidth = 0)
		plt.gca().add_patch(rectangle)
	else:
		rectangle = plt.Rectangle(
			(position.x, position.y),
			size.x/2, size.y/2,
			color = list(color),
			linewidth = 0,
			angle = -rotator.z)
		plt.gca().add_patch(rectangle)
		rectangle = plt.Rectangle(
			(position.x, position.y),
			size.x/2, size.y/2,
			color = list(color),
			linewidth = 0,
			angle = 180-rotator.z)
		plt.gca().add_patch(rectangle)

# Contains all of the drawing instructions that have been queued into batches
cuboidQueue = []
lastCheckEmptyQueue = None
lastQueueEmptiedAt = None
def resetCuboidQueue():
	global cuboidQueue, lastQueueEmptiedAt
	cuboidQueue = []
	lastQueueEmptiedAt = time.time()

async def waitUntilReadyToDraw(processDescription):
	global readyToDraw
	for i in range(int(math.ceil(design.maxDrawWaitTimeout / design.recheckDrawReadyInterval))):
		if readyToDraw:
			return True
		await server.sleep(design.recheckDrawReadyInterval,
			'Waiting for "server draw next" request by client before drawing ' + processDescription)
	readyToDraw = True
	return False

async def waitForServerDrawNext(processDescription):
	global readyToDraw
	readyToDraw = False
	await server.sleep(0, processDescription)
	for i in range(int(math.ceil(design.maxDrawWaitTimeout / design.recheckDrawReadyInterval))):
		if readyToDraw:
			return
		await server.sleep(sleepInterval,
			'Waiting for "server draw next" request by client after ' + processDescription)
	readyToDraw = True

# Spawns a cuboid at the specified coordinates with the specified color via a client-connection
# Ignores batches and just spawns it directly.
async def spawnCuboidDirectly(connection, position, size, color, rotator = None,
	positionIsCenterPoint = False, processDescription = None, waitAfterwardsForServerDrawNext = True):

	if not connection:
		return await debugDrawCuboidInPlot(position, size, color, rotator)

	if processDescription is None:
		processDescription = "Spawning cuboids in the virtual world"
	else:
		processDescription = "Spawning cuboids in the virtual world for " + processDescription

	await waitUntilReadyToDraw(processDescription)

	drawResponse = await packCuboid(position, size, color, rotator, positionIsCenterPoint)
	await connection.send(drawResponse, sendAlsoAsDebugMsg=design.debugWhenDrawingObject,
		printText=f"SPAWN CUBOID at position {position} with size {size}.")
	if waitAfterwardsForServerDrawNext:
		await waitForServerDrawNext(processDescription)

# Directly spawns an image at the specified coordinates via a client-connection, does not use batch
async def spawnImage(connection, filepath, position, size, rotator = None,
	positionIsCenterPoint = False, processDescription = None, waitAfterwardsForServerDrawNext = True, sleepBefore = 0):

	if not connection:
		os.startfile(filepath)
		return

	if processDescription is None:
		processDescription = "Spawning image in the virtual world"
	else:
		processDescription = "Spawning image in the virtual world for " + processDescription
	
	if sleepBefore > 0:
		await server.sleep(sleepBefore, "Sleeping before " + processDescription)

	drawResponse = await packImage(filepath, position, size, rotator, positionIsCenterPoint)

	await waitUntilReadyToDraw(processDescription)

	await connection.send(drawResponse, sendAlsoAsDebugMsg=design.debugWhenDrawingObject,
		printText="SPAWN IMAGE from file " + fileHandling.separateFilename(filepath)[1])
	if waitAfterwardsForServerDrawNext:
		await waitForServerDrawNext(processDescription)

async def spawnDoubleImagePlaneAlongZ(connection, filepath, position, size,
	positionIsCenterPoint = False, processDescription = None, waitAfterwardsForServerDrawNext = True, sleepBefore = 0):
	if type(size) is Coordinates:
		size = size.copy()
	else:
		if len(size) == 2:
			size = Coordinates(*size, 0)
		else:
			size = Coordinates(size)
	size.switchYZ()
	rotator = (90, 0, 0)
	await spawnImage(connection, filepath, position, size, rotator,
		positionIsCenterPoint, processDescription, waitAfterwardsForServerDrawNext, sleepBefore)
	rotator = (90, 0, 180)
	await spawnImage(connection, filepath, position, size, rotator,
		positionIsCenterPoint, processDescription, waitAfterwardsForServerDrawNext, sleepBefore)

# Sends the whole cuboidQueue as batch or drawing instructions to the client
async def sendCuboidBatch(connection, processDescription, waitAfterwardsForServerDrawNext=True):
	if processDescription is None:
		processDescription = "Spawning cuboids in the virtual world"
	else:
		processDescription = "Spawning cuboids in the virtual world for " + processDescription
	
	await waitUntilReadyToDraw(processDescription)
	
	await connection.send(("SPAWN CUBOID BATCH", cuboidQueue), sendAlsoAsDebugMsg=design.debugWhenDrawingObject,
		printText=f"SPAWN CUBOID BATCH containing {len(cuboidQueue)} objects up to {processDescription}.")
	resetCuboidQueue()
	await server.sleep(0, processDescription)
	if waitAfterwardsForServerDrawNext:
		await waitForServerDrawNext(processDescription)

sleepInterval = design.checkSentBatchAfter
while sleepInterval > 0.05: sleepInterval /= 2
# checks if the cuboidQueue is empty after the specified number of seconds
# after the last queueCuboid call. This ensures that the user didn't forget
# to do call sendCuboidBatch() after queueing the last instructions
async def checkEmptyQueue(connection, processDescription):
	global lastCheckEmptyQueue, sleepInterval
	lastCheckEmptyQueue = time.time()
	startTime = time.time()
	while time.time() < startTime + design.checkSentBatchAfter:
		await server.sleep(sleepInterval, "Queueing cuboid spawn instructions")
		if lastQueueEmptiedAt is None:
			return
		if lastCheckEmptyQueue != startTime:
			# checkEmptyQueue has been called again in the meantime and is running in a later instance.
			# Therefore we can safely terminate this instance
			return
		if len(cuboidQueue) == 0:
			# queue is empty, batch has been cleared, everything is fine
			return
		if lastQueueEmptiedAt > startTime:
			# queue has been emptied in the meantime, our cuboid has beent sent out
			return
	# No new checkEmptyQueues running and there is something in the queue
	try:
		await connection.senddebug(17, "It appears that sendCuboidBatch() hasn't been called after " +
			"queueing the last cuboid draw instructions! Batch will be left alone, probably not " +
			"all desired objects are shown in the virtual world.\n" +
			"Please call sendCuboidBatch() after drawing " + processDescription)
	except: # can't send warning over connection, doing it in the python server console instead
		loggingFunctions.warn("It appears, sendCuboidBatch() hasn't been called after " +
			"queueing the last cuboid draw instructions! Batch will be left alone, probably not " +
			"all desired objects are shown in the virtual world.\n" +
			"Please call sendCuboidBatch() after drawing " + processDescription)
	

# Queues a cuboid to be spawned at the specified coordinates with the specified color via a client-connection
# Uses batch size as specified in visualization settings
# You have to call sendCuboidBatch to finally clear the queue after sending the last cuboid!
async def queueCuboid(connection, position, size, color, rotator = None,
	positionIsCenterPoint = False, processDescription = None):
	if not connection:
		return await debugDrawCuboidInPlot(position, size, color, rotator)
	drawResponse = await packCuboid(position, size, color, rotator, positionIsCenterPoint)
	cuboidQueue.append(drawResponse)
	# Give other asyncio threads a chance to pass through
	await server.sleep(0, "Creating cuboid spawn instructions for " + processDescription)
	if len(cuboidQueue) >= design.objectBatchSize:
		await sendCuboidBatch(connection, processDescription)
	else:
		asyncio.create_task(checkEmptyQueue(connection, processDescription))


# From AI layer dimensions, calculate a reasonable size for visual representation
def sizeFromLayerDimensions(layerDims):
	size = []
	for dim in layerDims:
		# Append useful dim values to size-list until we have 3
		if dim is not None and dim > 0 and len(size) < 3:
			size.append(dim)
	# If we have less, just put 1 in the front a few times
	while len(size) < 3:
		size = [1] + size
	def getDims(designName, default):
		dims = getattr(design.layouting, designName, default)
		if dims is None: return default
		if type(dims) is tuple: dims = list(dims)
		elif type(dims) is not list: dims = [dims]
		if len(dims) == 1: dims *= 3
		elif len(dims) == 2: dims = [dims[0]] + dims
		return dims
	scaleDims = getDims('scaleLayerSizes', [1, 1, 1])
	addToDims = getDims('addToLayerSizes', [0, 0, 0])
	for i in range(3):
		size[i] *= scaleDims[i]
		size[i] += addToDims[i]
	minDims = getDims('minLayerDimensions', size)
	maxDims = getDims('maxLayerDimensions', size)
	for i in range(3):
		size[i] = min(size[i], maxDims[i])
		size[i] = max(size[i], minDims[i])
	return Coordinates(size)

# retrieves the layer color based on its type description
# Tries first with the whole name ignoring spaces,
# then removes any "2D" at the end and tries again
def getLayerColor(layerType, defaultValue = design.layerColors.get("default", .4)):
	layerType = layerType.lower()
	result = design.layerColors.get(layerType, None)
	if result is not None:
		return result
	if layerType.endswith("2d"):
		layerType = layerType[:-2]
		result = design.layerColors.get(layerType, None)
		if result is not None:
			return result
	return defaultValue

class Layer:
	layerList = []
	def __init__(self, position = 0, size = 0, type = "unknown", parents = [],
		activeAreaAbove = 0, activeAreaBelow = 0, index = None):
			self.position = Coordinates(position)
			self.size = Coordinates(size)
			self.activeAreaAbove = Coordinates(activeAreaAbove)
			self.activeAreaBelow = Coordinates(activeAreaBelow)
			self.type = type
			self.color = getLayerColor(type)
			self.index = len(Layer.layerList) if index is None else index
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
			if self.index > layer.index and \
				self.doesItOverlap(self.position - self.size/2, self.position + self.size/2,
					layer.position - layer.size/2, layer.position + layer.size/2):

						badOnes.append(layer)
		return badOnes

# Draws a given layout via the connection by sending drawing instructions.
# If not connection, then the cuboids cannot be drawn but will be displayed in a graphic
# Positions are given in an array as parameter, the other info is retrieved from ai.tfnet.layers
async def drawLayout(connection, positions):
	positionOffset = Coordinates(0, positions[0][1], positions[0][0]).scale(-1)
	typeCount = dict()
	Layer.resetAllLayers()

	# If no connection has been given, initialize matplotlib
	if not connection:
		plt.axes()
	
	for index, layer in enumerate(ai.tfnet.layers):
		layerType = layer[1]
		# Create layer instance and append it to layerList
		Layer.layerList.append(Layer(
			position = (positionOffset + (0, positions[index][1], positions[index][0])),
			size = sizeFromLayerDimensions(layer[2]),
			parents = layer[4],
			type = layerType,
			index = index,
		))
		if layerType in typeCount:
			typeCount[layerType] += 1
		else:
			typeCount[layerType] = 1
	
	connectionCount = hiddenConnectionCount = 0
	for index, current in enumerate(Layer.layerList):
		await queueCuboid(connection, current.position, current.size, current.color,
			positionIsCenterPoint = True,
			processDescription = f"layer {index} of {len(Layer.layerList)}")
		
		# connections:
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
							hiddenConnectionCount += 1
							continue # connection between grouped layers should not be drawn
				thickness = min(design.connections.strength,
					parent.size.x/2, parent.size.y/2,
					current.size.x/2, current.size.y/2)
				if deltay == 0:
					alpha = math.pi/2
					long = deltaz
				else:
					alpha = math.atan(deltaz/deltay)
					long = deltay / math.cos(alpha)
				await queueCuboid(connection,
					Coordinates(current.position.x, (y+yy)/2, (z+zz)/2),
					Coordinates(thickness, z = long),
					color = design.connections.color,
					rotator = Coordinates(x = 90-math.degrees(-alpha)),
					positionIsCenterPoint = True,
					processDescription = f"connections to layer {index} of {len(Layer.layerList)}")
				connectionCount += 1

	await sendCuboidBatch(connection, "last layers of structure", False)
	successMsg = f"Successfully drew the neural network with {len(Layer.layerList)} layers.\n" + \
		f"Composition: " + ', '.join([f"{n} {desc}" for (desc, n) in typeCount.items()])
	if design.connections.displayBetweenGroupedLayers:
		successMsg += f", {connectionCount} connections" 
	else:
		successMsg += f", {connectionCount} visible connections, {hiddenConnectionCount} hidden connections"
	warningMsg = False
	for layerType in typeCount.keys():
		if getLayerColor(layerType, None) is None:
			# This layer type has no specified color!
			if not warningMsg:
				warningMsg = "Some layer types could not be recognized and are displayed in " + \
					"default color! Please check your visualization settings and add a " + \
					"layerColor for the following layer types: " + layerType
			else:
				warningMsg += ", " + layerType
	if warningMsg:
		await connection.sendstatus(3, warningMsg)
	
	await connection.sendstatus(-30, successMsg)

	# Displaying plot if no client connection was given
	if not connection:
		plt.axis('auto')
		plt.show()

	return True

# Draws the tfnet.layer structure via the client-connection
# Returns whether we could successfully draw the architecture
# If not connection, then the cuboids cannot be drawn but will be displayed in a graphic
# Using modified forceatlas2-algorithm for layouting
async def drawstructure(connection = None):
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
		forceatlas2 = ForceAtlas2(
			# Behavior alternatives
			outboundAttractionDistribution = True, # Dissuade hubs
			edgeWeightInfluence = 1.0,
			groupLinearlyConnectedNodes = True, # only available with networkx layout
			orderconnectedQuadsOnXaxis = True, # orders connected nodes by their index on x axis
			# spacing between the nodes:
			desiredHorizontalSpacing = design.layouting.horizontalSpaceBetweenLayers,
			desiredVerticalSpacing = design.layouting.verticalSpaceBetweenLayers,
			bufferZone = design.layouting.bufferZone,
			desiredHorizontalSpacingWithinGroup = design.layouting.horizontalSpaceBetweenGroupedLayers,
			# Performance
			jitterTolerance = 1.0, # Tolerance
			barnesHutOptimize = False,
			# Tuning
			scalingRatio = 2.0,
			strongGravityMode = False,
			gravity = 1.0,
			randomlyOffsetNodes = (0, design.layouting.bufferZone / 20),
			# Log
			verbose = True,
		)
		# execute force based algorithm
		ai.tfnet.layoutPositions = await forceatlas2.forceatlas2_networkx_layout_async(graph, pos=positions, quadsizes=sizes, iterations=NUMBER_OF_ITERATIONS)
	# draw layers at the resulting positions
	return await drawLayout(connection, ai.tfnet.layoutPositions)

# Helps to create uniquely identifiable filename for the cachefiles
def settingToStr(description, setting, ignoreValue=None):
	if setting is True: return '-' + description
	if setting is False: return ""
	if type(setting) in [tuple, list]:
		if math.isclose(float(setting[0]), float(setting[1])):
			setting = setting[0]
		else:
			setting = str(setting[0] + '-' + str(setting[1]))
	if ignoreValue is not None:
		if type(ignoreValue) is str and setting == ignoreValue:
			return ""
		if type(ignoreValue) in [int, float] and math.isclose(setting, ignoreValue):
			return ""
	return '-' + description + str(setting).replace('.', ',')

def settingsToFilename(prefix="", settings=[], filetype="png"):
	parameters = ""
	for setting in settings:
		parameters += settingToStr(*setting)
	if filetype[0] != '.':
		filetype = '.' + filetype
	return prefix + parameters + filetype.lower()

# Some subfunctions for color normalization and editing
# makeExponent takes a value from 0 to 100 to produce an exponent. value 50 results in exponent 1
@functools.lru_cache(maxsize=4)
def makeExponent(value):
	if math.isclose(value, 50): return 1
	if value < 50: return 1 - (value - 50) / 50
	else: return 1 / makeExponent(100 - value)

# Will draw all kernels for the selected layer as defined in trainable var "{layername}/kernel:0"
async def drawKernels(connection, layerIndex, refreshTrainVars=False, canUseCachedFile=True, draw=True):
	async def status(verbosity, text):
		if connection:
			await connection.sendstatus(verbosity, text)
		else:
			if verbosity < 0: loggingFunctions.printlog(text)
			else: loggingFunctions.warn(text)
	
	design_k = design.kernels
	design_tx = design_k.renderTexture
	filename = settingsToFilename(f"layer-{layerIndex}_settings", [
		("res", design_tx.defaultPixelResolution),
		("max", design_tx.maxTextureResolution),
		("space", design_k.spacingBetweenKernels),
		("bright", design_k.brightness, 50),
		("contr", design_k.contrast, 50),
		("opac", design_tx.opacity, 1),
		("aa", design_tx.antiAliasing),
		("singleSp", not design_k.hideSpacingBetweenSingles),
		("wrap", design_k.wrapIfDimLeftover),
		("bgr", design.flipRGBtoBGR),
	])
	filepath = ai.internalCachePath("kernels", filename)
	canUseCachedFile = canUseCachedFile and os.path.exists(filepath) and \
		not (draw and connection and design_k.spawnIndividualCuboids)
	renderTexture = not design_k.spawnIndividualCuboids or \
		design_tx.saveToRendersFolder or \
		not connection or not draw
	
	if len(Layer.layerList) <= layerIndex:
		await status(16, f"Layer {layerIndex} doesn't exist! The index {layerIndex} is higher " +
			"than the number of {len(Layer.layerList)} drawn layers in this network.")
		return
	if refreshTrainVars:
		ai.tfRefreshTrainableVars()
	trainableVars = ai.tfnet.layers[layerIndex][5]
	if not 'kernel' in trainableVars or len(trainableVars['kernel']) == 0:
		# No kernel found for this layer. Let's try to refresh
		if not refreshTrainVars:
			return await drawKernels(connection, layerIndex, True)
		# Still no kernel found. Output error msg and return
		await status(16, f"Layer {layerIndex} does not have any kernels that could be visualized!")
		return False
	kernel = trainableVars['kernel'][0]
	await status(-10, f"Calculating kernels with dimensions {kernel.shape} of layer {layerIndex}...\n" +
		"Depending on the kernel size, this might take some time. " +
		'You can see a progress bar in the python server console or type "server info" to see the status.')
	colored = (len(kernel.shape) > 2 and kernel.shape[2] == 3)
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
	wrapping = False
	if groups[1] == 1 and design_k.wrapIfDimLeftover:
		wrapping = True
		newGroupy = math.floor(math.sqrt(groups[0]))
		groups = (math.ceil(groups[0] / newGroupy), newGroupy)
	size = Coordinates(design_k.defaultPixelDimensions, z = design_k.thickness)
	if size.z <= 1:
		size.z *= size.x
	# -- here you could add responsive calculations that adjust the pixel size
	#    depending on how many there are and how large everything should be.
	if design_k.minPixelDimensions is not None:
		size.x = max(size.x, design_k.minPixelDimensions[0])
		size.y = max(size.y, design_k.minPixelDimensions[1])
	if design_k.maxPixelDimensions is not None:
		size.x = min(size.x, design_k.maxPixelDimensions[0])
		size.y = min(size.y, design_k.maxPixelDimensions[1])
	spacing = Coordinates(design_k.spacingBetweenKernels, z = 0)
	if design_k.hideSpacingBetweenSingles and \
		pixelsPerGroup[0] == 1 and pixelsPerGroup[1] == 1:
			spacing = Coordinates(0)
	elif spacing.x <= 1 and spacing.y <= 1:
		spacing.x *= size.x
		spacing.y *= size.y
	structureWidth = groups[0] * pixelsPerGroup[0] * size.x + (groups[0]-1) * spacing.x
	structureHeight = groups[1] * pixelsPerGroup[1] * size.y + (groups[1]-1) * spacing.y
	thisLayer = Layer.layerList[layerIndex]

	if not canUseCachedFile: # (re)creating the texture file for all of the kernels
		if renderTexture:
			resolution = list(design_tx.defaultPixelResolution)
			# Applying max resolution to texture size
			resolution[0] = min(resolution[0], design_tx.maxTextureResolution / structureWidth * design_k.defaultPixelDimensions[0])
			resolution[1] = min(resolution[1], design_tx.maxTextureResolution / structureHeight * design_k.defaultPixelDimensions[1])
			# Creating render array to be filled with color (and opacity) values
			if not design_tx.antiAliasing:
				render = np.zeros([int(round(structureHeight * resolution[1] / design_k.defaultPixelDimensions[1])),
					int(round(structureWidth * resolution[0] / design_k.defaultPixelDimensions[0])), 4], np.uint8)
			else: # anti Aliasing
				resolution[0] = max(1, int(round(resolution[0])))
				resolution[1] = max(1, int(round(resolution[1])))
				spacingResolution = [0, 0]
				spacingResolution[0] = int(round(spacing.x / design_k.defaultPixelDimensions[0] * resolution[0]))
				spacingResolution[1] = int(round(spacing.y / design_k.defaultPixelDimensions[1] * resolution[1]))
				def renderDim(axis):
					return groups[axis] * pixelsPerGroup[axis] * resolution[axis] + \
						(groups[axis]-1) * spacingResolution[axis]
				render = np.zeros([renderDim(1), renderDim(0), 4], np.uint8)

		# Normalizes the color values of the whole input array, using contrast, brightness settings.
		# Returns a uint8-array of the same shape with values between 0 and 255
		def normalizeColors(input):
			colors = np.copy(input)
			colors /= max(np.max(kernel), -np.min(kernel))
			colors = abs(colors) ** makeExponent(design_k.contrast)
			colors = np.where(input >= 0, colors, -colors)
			colors = colors / 2 + 0.5
			colors = colors ** makeExponent(design_k.brightness)
			return np.around(colors * 255).astype(np.uint8)
		try:
			# Normalizing the colors in the whole kernel at once
			colors = normalizeColors(kernel)
		except MemoryError:
			# Ok, note that it didn't work
			colors = None
		# colorsRow normalizes the colors within one row at once.
		# The caching is crucial to achieve higher performance than normalizing each single value
		@functools.lru_cache(maxsize=1)
		def colorsRow(row):
			return normalizeColors(kernel[..., row])
		# Retrieves the normalized color either from colors or from colorsRow
		def getColor(nplocation):
			if colors is None:
				return colorsRow(nplocation[-1])[tuple(nplocation[:-1])]
			else:
				return colors[tuple(nplocation)]
		
		progress = 0
		updateEvery = 1000 # every how many iterations the progress bar and the coroutine yielding should update
		totalIterations = groups[1] * groups[0] * pixelsPerGroup[1] * pixelsPerGroup[0]
		opacity = int(round(design_tx.opacity * 255))
		with tqdm(total=totalIterations) as pbar:
			for groupy in range(groups[1]):
				for groupx in range(groups[0]):
					for pixely in range(pixelsPerGroup[1]):
						for pixelx in range(pixelsPerGroup[0]):
							try:
								nplocation = [1] * len(kernel.shape)
								if len(kernel.shape) > 0: nplocation[0] = pixelx
								if len(kernel.shape) > 1: nplocation[1] = pixely
								if not colored:
									if wrapping and len(kernel.shape) > 2:
										nplocation[2] = groupx + groupy * groups[0]
									else:
										if len(kernel.shape) > 2: nplocation[2] = groupx
										if len(kernel.shape) > 3: nplocation[3] = groupy
									color = [getColor(nplocation)] * 3
								else: # colored
									if wrapping and len(kernel.shape) > 3:
										nplocation[3] = groupx + groupy * groups[0]
									else:
										if len(kernel.shape) > 3: nplocation[3] = groupx
										if len(kernel.shape) > 4: nplocation[4] = groupy
									color = []
									for nplocation[2] in range(3):
										if design.flipRGBtoBGR:
											color.insert(0, getColor(nplocation))
										else:
											color.append(getColor(nplocation))
								color.append(opacity)
							except IndexError:
								# Can't be pixelx or pixely due to groups intialization from kernel.shape
								# So we definitely need to break out of the pixelx, pixely and groupx loops
								pixelx = pixely = groupx = math.inf # (pixelx optional, is taken care of by break)
								# Now decide on whether we need to break out of all of the loops...
								if wrapping:
									if len(kernel.shape) <= 2 + colored or \
									groupx + groupy * groups[0] > kernel.shape[2 + colored]:
										groupy = math.inf
								else:
									if len(kernel.shape) <= 3 + colored or \
									groupy > kernel.shape[3 + colored]:
										groupy = math.inf
								break # breaking out of every loop whose counter was set to math.inf
							
							if not design_tx.antiAliasing or (draw and design_k.spawnIndividualCuboids and connection):
								x = groupx * pixelsPerGroup[0] * size.x + groupx * spacing.x + pixelx * size.x
								y = groupy * pixelsPerGroup[1] * size.y + groupy * spacing.y + pixely * size.y
							progress += 1
							if progress % updateEvery == 0 or progress > totalIterations - updateEvery:
								pbar.update(updateEvery)
							processDesc = f"kernels of layer {layerIndex} at pixel {progress} " + \
								f"of {totalIterations}"
							if renderTexture:
								if not design_tx.antiAliasing:
									def treatWithResolution(axis, addSize=False):
										if axis == 0: val = x / size.x
										else: val = y / size.y
										if addSize: val += 1
										return int(round(val * resolution[axis]))
									render[
										treatWithResolution(1) : treatWithResolution(1, True),
										treatWithResolution(0) : treatWithResolution(0, True)
									] = color
								else: # anti Aliasing
									y_aa = groupy * pixelsPerGroup[1] * resolution[1] + groupy * spacingResolution[1] + pixely * resolution[1]
									x_aa = groupx * pixelsPerGroup[0] * resolution[0] + groupx * spacingResolution[0] + pixelx * resolution[0]
									render[
										y_aa : y_aa + resolution[1],
										x_aa : x_aa + resolution[0]
									] = color
							if draw and design_k.spawnIndividualCuboids and connection:
								position = Coordinates(
								# x
									+ thisLayer.position.x
									- thisLayer.size.x / 2
									- design_k.spacingFromLayer
									- structureWidth
									+ x
								, # y
									+ thisLayer.position.y
									+ structureHeight / 2
									- size.y
									- y
								, # z
									+ thisLayer.position.z
									- size.z / 2
								)
								await queueCuboid(connection, position, size, color, processDescription = processDesc)
							elif progress % updateEvery:
								await server.sleep(0, processDesc)	

		# After looping through all of the kernels
		if draw and design_k.spawnIndividualCuboids and connection:
			await sendCuboidBatch(connection, "last kernels of layer " + str(layerIndex), False)
		if renderTexture:
			Image.fromarray(render).save(filepath)
			if design_tx.saveToRendersFolder:
				externalFilepath = ai.externalImagePath("kernels", filename)
				Image.fromarray(render).save(externalFilepath)
	
	# Sending the cached texture, this gets also executed if we can use the cached file
	# and skipped rendering it again
	if renderTexture:
		if connection:
			await connection.sendfile(filepath)
			if draw and not design_k.spawnIndividualCuboids:
				position = thisLayer.position.copy()
				position.x -= thisLayer.size.x / 2 + design_k.spacingFromLayer + structureWidth / 2
				await spawnDoubleImagePlaneAlongZ(connection, filepath, position, (structureWidth, structureHeight), True,
					f"kernel texture of layer {layerIndex}", sleepBefore=.2)
				# TODO: Change filepath to path relative to client
				# after sendfile command has been implemented client side
		if not connection or design_tx.displayTextureImage:
			os.startfile(filepath)


async def drawInputPrediction(connection, inputData = setting.DEBUG.DEFAULT_INPUT_IMAGE):
	result = ai.tfKerasPredict(inputData)
	await connection.send("Result of the prediction: " + result, sendAlsoAsDebugMsg=True)
	layer = Layer.layerList[0]
	position = layer.position
	position.z -= layer.size.z / 2 + 1
	description = 'Drawing input prediction for file ' + inputData
	await spawnDoubleImagePlaneAlongZ(connection, inputData, position, layer.size, True, description, sleepBefore=.2)
	

async def drawKernelActivations(connection, layerIndex, selectKernel, inputData, justRenderTextures=False, returnInsteadOfSave=False):
	if type(selectKernel) is int:
		selectKernel = [selectKernel]
	def listToStr(l, removeSpaces=False):
		l = str(l).replace(' ', '') if removeSpaces else str(l)
		if l.startswith('[') and l.endswith(']'): l = l[1:-1]
		return l

	out = np.asarray(ai.tfKerasGetLayerOutput(layerIndex, inputData))
	while out.shape[0] == 1:
		out = np.reshape(out, out.shape[1:])
	out = out.copy()
	if selectKernel is not None:
		originalOutShape = out.shape
		for i in selectKernel:
			if i >= 0:
				if len(selectKernel) <= len(originalOutShape)-2:
					out = out[:, :, i]
				else:
					out = out[i]
	colored = (len(out.shape) == 3 and out.shape[2] == 3)
	if colored or len(out.shape) == 2:
		out -= np.min(out)
		out *= 255 / np.max(out)
		out = np.asarray(np.round(out), dtype=np.uint8)
		if colored and design.flipRGBtoBGR:
			out = out[..., ::-1]
		if returnInsteadOfSave:
			return out
		texture = Image.fromarray(out)
		filename = settingsToFilename(f"layer-{layerIndex}-kernel-{listToStr(selectKernel, True)}", [
			("bgr", design.flipRGBtoBGR),
		])
		filename = ai.internalCachePath("layerOutput", filename)
		texture.save(filename)
	else:
		async def recursivelyBuildAllKernels(selectKernel, shape, originalShape=None):
			if originalShape is None:
				originalShape = list(shape)
			output = []
			irange = range(shape[0])
			if len(originalShape) == len(shape):
				irange = tqdm(irange, f"Kernel activations of layer {layerIndex}")
			for i in irange:
				if len(shape) == 1:
					await server.sleep(0, "Calculating activations for kernel " + listToStr(selectKernel + [i]) + \
						f" of {listToStr(originalShape)} of layer {layerIndex}")
					out = await drawKernelActivations(connection, layerIndex, selectKernel + [i], inputData, justRenderTextures=True)
					output.append(out)
				else:
					output.append(await recursivelyBuildAllKernels(selectKernel + [i], shape[1:], originalShape))
			return output
		images = await recursivelyBuildAllKernels([], out.shape[2:4]) # images will have shape like last argument
		# Now let's arrange these images in one large texture:
		if len(out.shape) == 3 and design.kernels.wrapIfDimLeftover: # wrapping
			rows = math.floor(math.sqrt(out.shape[2]))
			columns = math.ceil(out.shape[2] / rows)
		else:
			columns = out.shape[2]
			if len(out.shape) == 3: rows = 1
			else: rows = out.shape[3]
		def selectImage(x, y):
			if len(out.shape) == 3:
				index = x + y * columns
				if len(images) > index:
					return images[index]
				print(f"No image at {x}, {y}")
				return None
			result = images[x, y]
			while type(result) is list: result = result[0]
			print(result)
			return result
		image = selectImage(0, 0)
		width = image.size[0]
		height = image.size[1]
		texture = Image.new(image.mode, (width * columns, height * columns))
		for y in range(rows):
			for x in range(columns):
				image = selectImage(x, y)
				if image is None:
					continue
				texture.paste(image, (x * width, y * height))
		filename = settingsToFilename(f"layer-{layerIndex}-all-kernels", [
			("bgr", design.flipRGBtoBGR),
		])
		filename = ai.internalCachePath("layerOutput", filename)
		texture.save(filename)
	
	# Draw the texture image
	if not justRenderTextures:
		thisLayer = Layer.layerList[layerIndex]
		sizex = max(texture.size[0], thisLayer.size.x)
		sizey = max(texture.size[1], thisLayer.size.y)
		position = thisLayer.position.copy()
		position.x += thisLayer.size.x / 2 + design.kernels.spacingFromLayer + sizex / 2
		await spawnDoubleImagePlaneAlongZ(connection, filename, position, (sizex, sizey), True,
			f"kernel activations of layer {layerIndex}", sleepBefore=.2)
	return texture

async def drawSaliency(connection, inputData=setting.DEBUG.DEFAULT_INPUT_IMAGE, index=-1, justRenderTextures=False):
	result, description = ai.tfKerasGetSaliency(inputData, index)
	result = gaussian_filter(result, design.saliency.blurRadius)
	result -= np.min(result)
	result /= np.max(result) + 1e-18
	result = result ** makeExponent(design.saliency.brightness)
	image = np.uint8(getattr(cm, design.saliency.colormap, "gray")(result)*255)
	image = image[..., :3].astype(np.uint64)
	opacity = (result * design.saliency.opacityMaximum + (1 - result) * design.saliency.opacityMinimum) ** makeExponent(design.saliency.opacityBrightness)
	opacity = np.expand_dims(opacity, -1)
	input_image = await drawKernelActivations(connection, 0, None, inputData, returnInsteadOfSave=True)
	input_image = input_image.astype(np.uint64)
	if design.saliency.additiveMixing:
		image = input_image * design.saliency.imageOpacity + image * opacity
	else:
		image = image * opacity + input_image * (1 - opacity) * design.saliency.imageOpacity
	image = np.clip(image, 0, 255).astype(np.uint8)
	image = Image.fromarray(image)
	filename = settingsToFilename(f"prediction-{description.lower().replace(' ', '-')}_settings", [
		("cmap-", design.saliency.colormap, "gray"),
		("bright", design.saliency.brightness, 50),
		("blur", design.saliency.blurRadius, 0),
		("opMin", design.saliency.opacityMinimum, 0),
		("opMax", design.saliency.opacityMaximum, 1),
		("opBright", design.saliency.opacityBrightness, 50),
		("additive", design.saliency.additiveMixing),
		("imgOp", design.saliency.imageOpacity),
	])
	filepath = ai.internalCachePath("saliency", filename)
	image.save(filepath)
	
	# Draw the texture image
	if not justRenderTextures:
		thisLayer = Layer.layerList[0]
		sizex = thisLayer.size.x
		sizey = thisLayer.size.y
		position = thisLayer.position.copy()
		position.y += thisLayer.size.y / 2 + design.kernels.spacingFromLayer + sizey / 2
		await spawnDoubleImagePlaneAlongZ(connection, filepath, position, (sizex, sizey), True,
			f"saliency map of index {index}", sleepBefore=.2)
	return image


# FOR DEBUGGING, executed if you start this script directly
async def testVis():
	loadRealNN = False
	
	setting.checkSettings()
	if loadRealNN:
		path = setting.FILEPATHS.NN_LOAD_DEFAULT_MODEL
		path = setting.FILEPATHS.AVAILABLE_MODELS.get(path, path)
		ai.preparemodule(path)
		ai.importtf()
		# await ai.tf_getstructure(printStructure=False)
		# await drawstructure(None)
		# await ai.tf_refreshtrainablevars()
		# await drawKernels(None, 2)
	else:
		structure = debugAndTesting.const_fake_structure
		await ai.parsestructure(None, structure)
	await drawstructure()

# call this module as main module, visualization will be tested and displayed as a grahic
if __name__ == '__main__':
	loop = asyncio.get_event_loop()
	loop.run_until_complete(testVis())
	loop.close()
