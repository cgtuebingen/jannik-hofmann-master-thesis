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
import  serverCommands

class Coordinates:
	def __init__(self, a = None, b = None, c = None, *, x = None, y = None, z = None):
		if type(a) is Coordinates:
			self.x, self.y, self.z = a.x, a.y, a.z
		elif a is None:
			self.x, self.y, self.z = float(0), float(0), float(0)
		elif type(a) is tuple or type(a) is list:
			if a is tuple:
				a = list(a)
			if len(a) == 1:
				self.x, self.y, self.z = float(a[0]), float(a[0]), float(a[0])
			if len(a) == 2:
				self.x, self.y, self.z = float(a[0]), float(a[0]), float(a[1])
			if len(a) > 2:
				self.x, self.y, self.z = float(a[0]), float(a[1]), float(a[2])
		else:
			self.x, self.y, self.z = float(a), float(a), float(a)
		if b is not None:
			self.z = float(b)
		if c is not None:
			if b is not None:
				self.y = float(b)
			self.z = float(c)
		if (x is not None): self.x = float(x)
		if (y is not None): self.y = float(y)
		if (z is not None): self.z = float(z)

	def __str__(self):
		return f"({self.x}, {self.y}, {self.z})"
	def __repr__(self):
		return f"({self.x}, {self.y}, {self.z})"

	def scale(self, *args, x = None, y = None, z = None):
		if (len(args) == 0):
			factor = Coordinates(1)
		else:
			factor = Coordinates(*args)
		if (x is not None): factor.x = float(x)
		if (y is not None): factor.y = float(y)
		if (z is not None): factor.z = float(z)
		self.x *= factor.x
		self.y *= factor.y
		self.z *= factor.z
		return self

	def add(self, *args, x = None, y = None, z = None):
		factor = Coordinates(*args)
		if (x is not None): factor.x = float(x)
		if (y is not None): factor.y = float(y)
		if (z is not None): factor.z = float(z)
		self.x += factor.x
		self.y += factor.y
		self.z += factor.z
		return self

	def list(self):
		return [self.x, self.y, self.z]

	def switchYZ(self):
		self.y, self.z = self.z, self.y
		return self

def transformCoordinates(originalposition = None, originalsize = None):
	position = Coordinates(originalposition)
	size = Coordinates(originalsize)
	if position is not None:
		position.scale(z = 1/5).add(10000, 1100, -5500).switchYZ()
	if size is None: return position
	size.scale(1/250).switchYZ()
	if position is None: return size
	return position, size

def formatColor(color):
	if (type(color) is not tuple) and (type(color) is not list):
		color = [color]
	color = list(color)
	while (len(color) < 3):
		color.append(color[0])
	if any(value > 1 for value in color):
		color = [value / 255 for value in color]
	return color

async def spawnCuboid(connection, position, size, color):
	position, size = transformCoordinates(position, size)
	posSizeColor = [float(i) for i in
		position.list() + size.list() + color]
	await connection.send(("SPAWN CUBOID pos size color", posSizeColor))
	await asyncio.sleep(0.2) # TODO: Find way to spawn all in the same frame

def sizeFromLayerDimensions(layerDims):
	size = []
	for dim in layerDims:
		if dim is not None and dim > 0 and len(size) < 3:
			size.append(dim)
	while (len(size) < 3):
		size = [1] + size
	return Coordinates(size)

async def drawstructure(connection):
	if not ai.tfnet.validstructure:
		return False
	position = Coordinates() # center position of first cube
	drawnLayers = []
	for index, layer in enumerate(ai.tfnet.layers):
		size = sizeFromLayerDimensions(layer[2]).scale(50, 1)
		position.add(z = size.z)
		# connected to
		if not ai.tfnet.layers[index-1][0] in layer[4]:
			pass #pos[2] += 1000 # increase distance between unconnected layers
		color = design.layerColors.get(layer[1].lower(),
			design.layerColors.get("default"))
		color = formatColor(color)
		drawnLayers.append([position, size, color])
		await spawnCuboid(connection, position, size, color)
		if (len(layer[4]) > 1) or layer[4][0] != ai.tfnet.layers[index-1][0]:
			# connected to another layer than just the previous one
			for connectedIndex, connectedLayer in enumerate(ai.tfnet.layers):
				if connectedLayer[0] in layer[4]:
					connectionColor = formatColor(.3)
					connectedCoordinates = drawnLayers[connectedIndex]
					cposition = Coordinates(connectedCoordinates[0])
					csize = Coordinates(connectedCoordinates[1])
					xy = min(size.x, size.y, csize.x, csize.y)/2
					randomx = random.uniform(-xy*0.3, xy*0.3)
					randomy = random.uniform(xy*1, xy*1.4)
					connectionStrength = 70
					await spawnCuboid(connection, Coordinates(randomx, randomy/2, size.z),
						Coordinates(connectionStrength, 2.5*randomy, connectionStrength),
						connectionColor)
					await spawnCuboid(connection, Coordinates(randomx, randomy/2, cposition.z),
						Coordinates(connectionStrength, 2.5*randomy, connectionStrength),
						connectionColor)
					await spawnCuboid(connection, Coordinates(randomx, randomy, (size.z+cposition.z)/2),
						Coordinates(connectionStrength, connectionStrength, (size.z-cposition.z)/2),
						connectionColor)
		position.add(z = size.z + 300)
	return True
