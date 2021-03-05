#!/usr/bin/env python

# This module contains the interaction of the server with the imported tensorflow and
# pytorch neural networks. It takes care of loading them, calculating predictions, as well as
# retrieving weight data and meta information about the architectures.
# The functions in this module do not perform any high-level checks and will raise Exceptions
# (for example if tf functions are called before any tf network has been initialized yet)
# Exception handling should be implemented by the module that calls these functions

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
import serverCommands

# Definitions / initializations
nnloaded = False
nnprepared = False
nn_spec = None
nn_module = None
tfnet = SimpleNamespace()
pytorchnet = SimpleNamespace()
tf = None

# Returns whether a tf network has been loaded and initialized successfully
def tfloaded():
	return hasattr(tfnet, 'loaded') and tfnet.loaded

# Prepares a python module and execs it.
# Afterwards, if no error was thrown, call importtf for tensorflow networks
def preparemodule(path, allowPreparingNewModuleOnTop = False):
	global nn_spec, nn_module, nnprepared
	if not allowPreparingNewModuleOnTop and (nnprepared or nnloaded):
		raise AssertionError("The ai interface has already loaded a module in the past and should not load another (or the same) nn script on top. You can override this check by setting the flag by calling preparemodule(path, True)")
	nn_spec = importlib.util.spec_from_file_location("", path)
	nn_module = importlib.util.module_from_spec(nn_spec)
	nn_spec.loader.exec_module(nn_module)
	nnprepared = True

# Returns whether the prepared module contains a tensorflow neural network
def preparedModuleIsTf():
	return True # TODO: Check if tensorflow or pytorch

# Imports the tf library to finish loading the tensorflow module.
# Call this after having called preparemodule(path)
def importtf():
	if not nnprepared:
		raise ModuleNotFoundError("Network hasn't been prepared properly! Call preparemodule(path) with a path to an exsisting tensorflow network before calling this function!")
	global tfnet, tf, nnloaded
	import tensorflow as tfref
	tf = tfref
	tfnet.loaded = True
	nnloaded = True

# Returns the version of tensorflow
def tfversion():
	global tf, tfnet
	tfnet.version = tf.__version__
	return tfnet.version

# Just returns a model summary. Call parsestructure afterwards.
def tfmodelsummary():
	structure = []
	global nn_module
	nn_module.model.summary(print_fn=lambda x: structure.append(x), line_length=1024)
	return structure

def makeModelSummaryReadable(structure):
	structure = "\n".join(structure)
	structure = re.sub(r" +", " ", structure)
	lineLength = max([len(
		re.sub(r"\-\-+", "", re.sub(r"\=\=+", "", re.sub(r"\_\_+", "", re.sub(r" +", " ", line))))
	) for line in structure])
	structure = re.sub(r"\-\-+", "-" * lineLength, structure)
	structure = re.sub(r"\=\=+", "=" * lineLength, structure)
	structure = re.sub(r"\_\_+", "_" * lineLength, structure)
	return structure

linearStructure = SimpleNamespace(
	structureName = "Simple linear model",
	readableStructureContent = "Layer (type), Output shape, Param #",
	regexHeader = r"Layer \(type\) *Output Shape *Param \# *",
	regexLine = r"[a-z0-9\_]* \([A-Za-z0-9 ]*\)   *\[?\((None|[0-9]*|\, )*\)\]?   *[0-9]* *",
)
interconnectedStructure = SimpleNamespace(
	structureName = "Interconnected model",
	readableStructureContent = linearStructure.readableStructureContent + ", Connected to",
	regexHeader = linearStructure.regexHeader + r"Connected to *",
	regexLine = linearStructure.regexLine + r"[a-z0-9\_]*(\[0\])* *",
)
tfStructureTypes = [
	linearStructure,
	interconnectedStructure,
]

def tfresetstructure():
	global tfnet
	tfnet.validstructure = False
	tfnet.layers = []

async def parsestructure(connection, structure = None):
	if structure is None:
		structure = tfmodelsummary()
	global tfnet
	mainStructurePart = 0
	layerCount = 0
	tfresetstructure()
	for line in structure:
		foundLineMatch = False
		def regexMatch(expr):
			return re.fullmatch(expr, line) is not None
		
		if regexMatch(r"\=*"):
			mainStructurePart += 1
			foundLineMatch = True
		elif regexMatch(r"\_*"):
			foundLineMatch = True
		elif mainStructurePart == 0:
			if (line.startswith("Model: \"")):
				tfnet.modelname = line.replace("Model: ", "").replace('"', '')
				foundLineMatch = True
			else:
				for type in tfStructureTypes:
					if regexMatch(type.regexHeader):
						tfnet.validstructure = True
						tfnet.structureType = type
						foundLineMatch = True
		elif mainStructurePart == 1:
			if regexMatch(tfnet.structureType.regexLine):
				line = re.sub("   *", "\n", line).strip()
				# split according to structure type heading
				if tfnet.structureType == linearStructure:
					layertype, shape, params = line.split("\n")
					if len(tfnet.layers) > 0:
						connectedTo = tfnet.layers[-1][0] # connect to previous layer by layername
					else:
						connectedTo = ""
				elif tfnet.structureType == interconnectedStructure:
					try:
						layertype, shape, params, connectedTo = line.split("\n")
					except:
						layertype, shape, params = line.split("\n")
						if len(tfnet.layers) > 0:
							connectedTo = tfnet.layers[-1][0] # connect to previous layer by layername
						else:
							connectedTo = ""
				# process layertype into layername and ltype
				layername, ltype = layertype.split("(")
				layername = layername.strip()
				ltype = ltype.replace(")", "")
				# process shape
				if (shape.startswith("[") and shape.endswith("]")):
					shape = shape[1:-1]
				shape = ast.literal_eval(shape)
				# process params
				params = int(params)
				# process connectedTo
				while(connectedTo.endswith("[0]")):
					connectedTo = connectedTo[:-3]
				connectedTo = [connectedTo]
				# repackage and append
				layer = layername, ltype, shape, params, connectedTo
				tfnet.layers.append(layer)
				foundLineMatch = True
			elif tfnet.structureType == interconnectedStructure and \
				"Connected to" in tfnet.structureType.regexHeader:

				connectedTo = line.strip()
				while(connectedTo.endswith("[0]")):
					connectedTo = connectedTo[:-3]
				tfnet.layers[-1][4].append(connectedTo)
				foundLineMatch = True
		elif mainStructurePart == 2:
			lineToInt = int(re.sub(r"[a-zA-Z\:\, ]", "", line))
			if (line.startswith("Total param")):
				tfnet.totalparams = lineToInt
				foundLineMatch = True
			elif (line.startswith("Trainable param")):
				tfnet.trainableparams = lineToInt
				foundLineMatch = True
			elif (line.startswith("Non-trainable param")):
				tfnet.nontrainableparams = lineToInt
				foundLineMatch = True
		if not foundLineMatch:
			#tfresetstructure() # This would  quit parsing at this point and result in no structure
			await connection.senddebug(14, f'Line "{line}" in tf network structure is unexpected ' + \
				f"and cannot be parsed! Integrity of the architecture data cannot be guaranteed!")
		tfnet.layerCount = layerCount
	
	if tfnet.validstructure:
		return True
	else:
		validStructureList = []
		for type in tfStructureTypes:
			validStructureList.append("\n    " + type.structurename + ": " + type.readableStructureContent)
		await connection.sendstatus(17, f"Tensorflow network structure does not adhere to expected " +
			f"format!\nReceived structure: {structure[2]}\nExpected one of the following structures:" +
			validStructureList)
		return False