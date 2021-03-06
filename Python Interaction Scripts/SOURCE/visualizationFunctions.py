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

# LOCAL IMPORTS
import visualizationSettings as design
import aiInteraction as ai
import serverCommands

# Coordinates class stored 3 floats x, y, z
class Coordinates:
	# You can initialize Coordinates in the following ways:
	def __init__(self, a = None, b = None, c = None, *, x = None, y = None, z = None, default = 0):
		# By another Coordinates instance, to copy it
		if type(a) is Coordinates:
			self.x, self.y, self.z = a.x, a.y, a.z
		# Without parameters as default, default, default
		elif a is None:
			self.x, self.y, self.z = float(default), float(default), float(default)
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
		return f"({self.x}, {self.y}, {self.z})"
	def __repr__(self):
		return f"({self.x}, {self.y}, {self.z})"

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

	# Convert x, y, z to a list
	def list(self):
		return [self.x, self.y, self.z]

	# Switch x and y axes because of how Unreal Engine works
	# (Here in python, z is horizontal and y the vertical one, in UE the other way around)
	def switchYZ(self):
		self.y, self.z = self.z, self.y
		return self

# Transform coordinates to representation that makes sense for Unreal Engine viewing
def transformCoordinates(originalposition = None, originalsize = None):
	position = Coordinates(originalposition)
	size = Coordinates(originalsize)
	if position is not None:
		position.scale(z = 1/5).add(10000, 1100, -5500).switchYZ()
	if size is None: return position
	size.scale(1/250).switchYZ()
	if position is None: return size
	return position, size

# Format a color to always have three float values between 0 and 1
def formatColor(color):
	# Tuple to list
	if (type(color) is tuple):
		color = list(color)
	# Make a single number into a list
	if type(color) is not list:
		color = [color]
	# Make sure we have 3 values in that list
	while (len(color) < 3):
		color.append(color[0])
	# In case anyone was fancy and specified numbers in the 0-255 range
	if any(value > 1 for value in color):
		color = [value / 255 for value in color]
	return color

# Spawns a cuboid at the specified coordinates with the specified color via a client-connection
async def spawnCuboid(connection, position, size, color):
	# Transform coordinates to UE
	position, size = transformCoordinates(position, size)
	# Append them into one large array and send them away as instruction
	posSizeColor = [float(i) for i in
		position.list() + size.list() + color]
	await connection.send(("SPAWN CUBOID pos size color", posSizeColor))
	await asyncio.sleep(0.2) # TODO: Find way to spawn all in the same frame

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
	return Coordinates(size)

# Draws the tfnet.layer structure via the client-connection
# Returns whether we could successfully draw the architecture
async def drawstructure(connection):
	if not ai.tfnet.validstructure:
		# Wait, we can't draw that
		return False
	position = Coordinates() # center position of first cube at origin
	drawnLayers = [] # For later reference for interconnected layers

	for index, layer in enumerate(ai.tfnet.layers):
		# Retrieve reasonable size and scale x, y by 50
		size = sizeFromLayerDimensions(layer[2]).scale(50, 1)
		# Shift the position, so layers don't overlap
		position.add(z = size)
		# Check if actually connected to previously drawn layer
		if not ai.tfnet.layers[index-1][0] in layer[4]:
			position.add(z = 1000) # increase distance between unconnected layers
		# Retrieve color for this layer type
		color = design.layerColors.get(layer[1].lower(),
			design.layerColors.get("default"))
		color = formatColor(color)
		# Spawn that thing and append it to drawnLayers
		await spawnCuboid(connection, position, size, color)
		drawnLayers.append([position.copy(), size.copy(), color])
		# Draw connections between layers if applicable
		if design.drawConnections and \
			(len(layer[4]) > 1 or layer[4][0] != ai.tfnet.layers[index-1][0]):
			# connected to another layer than just the previous one. Check which one it is
			for connectedIndex, connectedLayer in enumerate(ai.tfnet.layers):
				# Check if that layer matches with the connected list and isn't just the previous
				if connectedLayer[0] in layer[4] and connectedIndex < index-1:
					# retrieve color preference
					connectionColor = formatColor(design.connectionColor)
					# retrieve position and size of the connected layer
					cposition, csize, *_ = drawnLayers[connectedIndex]
					# calculate random x and y connection properties (so connections don't overlap)
					xy = min(size.x, size.y, csize.x, csize.y)/2
					randomx = random.uniform(-xy*0.3, xy*0.3)
					randomy = random.uniform(xy*1, xy*1.4)
					print(f"position, c {position}, {cposition}")
					await spawnCuboid(connection,
						Coordinates(randomx, randomy/2, position),
						Coordinates(design.connectionStrength, y = 2.5 * randomy),
						connectionColor)
					await spawnCuboid(connection,
						Coordinates(randomx, randomy, position | cposition),
						Coordinates(design.connectionStrength, z = (position - cposition) / 2),
						connectionColor)
					await spawnCuboid(connection,
						Coordinates(randomx, randomy/2, cposition),
						Coordinates(design.connectionStrength, y = 2.5 * randomy),
						connectionColor)
		position.add(z = size + 300)
	return True
