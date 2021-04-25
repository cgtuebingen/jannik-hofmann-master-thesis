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
modelvarname = None
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
	global nn_spec, nn_module, nnprepared, modelvarname
	# Check if model variable name has been specified
	# by searching for a ':' in the filename / in the string after the last folder
	if ':' in path.rsplit('/', 1)[-1].rsplit('\\', 1)[-1]:
		path, modelvarname = path.rsplit(':', 1)
		path = path.strip()
		modelvarname = modelvarname.strip()
	else:
		modelvarname = 'model'
	if not allowPreparingNewModuleOnTop and (nnprepared or nnloaded):
		raise AssertionError("The ai interface has already loaded a module in the past and should not load another (or the same) nn script on top. You can override this check by setting the flag by calling preparemodule(path, True)")
	print(path)
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
	global nn_module, modelvarname
	getattr(nn_module, modelvarname).summary(print_fn=lambda x: structure.append(x), line_length=1024)
	return structure

# Converts a model summary of arbitrary line length into a more human-readable format for output
# in the console or via debug-responses
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

# TF Structure type definitions as they appear in the tf model summary.
# Each structure needs to contain the following elements:
# structureName as a simple representation for the user
# readableStructureContent that explains the expected summary-columns in a human-friendly way
# regexHeader needs to match exactly the table header with arbitrary-length whitespacing
# regexLine needs to match any line in the model summary that specifies a layer
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
# All created tf structures need to be mentioned here:
tfStructureTypes = [
	linearStructure,
	interconnectedStructure,
]

# resets the saved structure information of tfnet
def tfresetstructure():
	# removes attributes from a class whether they exist or not
	def remove(attribute):
		if (hasattr(tfnet, attribute)):
			delattr(tfnet, attribute)
	
	global tfnet
	tfnet.validstructure = False
	remove("layers")
	remove("modelname")
	remove("structureType")
	remove("totalparams")
	remove("trainableparams")
	remove("nontrainableparams")
	remove("layerCount")

# Parses a given tf model summary string as structure and saves relevant information to tfnet
# Structure should be in the form of the result of tfmodelsummary()
# If none is provided, the structure will be directly retrieved by tfmodelsummary()
async def parsestructure(connection, structure = None, quitParsingOnUnknownLine = False):
	if structure is None:
		structure = tfmodelsummary()
	# Initializations
	tfresetstructure()
	global tfnet
	tfnet.layers = []
	mainStructurePart = 0
	# Go through all lines of the structure:
	for line in structure:
		foundLineMatch = False # For error detection, so we don't miss anything
		# Use regexMatch to completely match the current line with a regex
		def regexMatch(expr):
			return re.fullmatch(expr, line) is not None
		
		# Spacer line between main parts of the structure
		if regexMatch(r"\=*"):
			# Check if there's a valid structureType recognized before proceeding
			if not hasattr(tfnet, "structureType"):
				# No valid header has been found, cannot proceed
				# Resetting the structure information and declaring the structure invalid
				tfresetstructure()
				# Also quitting further parsing for good measure
				break
			mainStructurePart += 1
			foundLineMatch = True
		# Spacer line between layers. Has no effect
		elif regexMatch(r"\_*"):
			foundLineMatch = True
		# part 0 contains the model info and header
		elif mainStructurePart == 0:
			# Retrieve model name
			if (line.startswith("Model: \"")):
				tfnet.modelname = line.replace("Model: ", "").replace('"', '')
				foundLineMatch = True
			else:
				# Try to match any structure in the listed tf types by its regexHeader
				for type in tfStructureTypes:
					if regexMatch(type.regexHeader):
						# Found valid one, save the structure type to tfnet
						tfnet.validstructure = True
						tfnet.structureType = type
						foundLineMatch = True
		# part 1 contains all the layers
		elif mainStructurePart == 1:
			# Try to match the structures regexLine as layer description
			if regexMatch(tfnet.structureType.regexLine):
				# Columns separated by many spaces are split into separate strings
				line = re.sub("   *", "\n", line).strip().split("\n")
				# Now parsing layer line according to each structure specifications...

				# Linear structure
				if tfnet.structureType == linearStructure:
					# Former columns are put into their own variables
					layertype, shape, params = line
					# connectedTo needs to be created manually:
					if len(tfnet.layers) > 0:
						# If this isn't the first line, write the previous layers name as connected
						# as the layers in the linearStructure are always only connected to prev.
						connectedTo = tfnet.layers[-1][0]
					else: # First layer isn't connected to anything
						connectedTo = ""
				
				# Interconnected structure
				elif tfnet.structureType == interconnectedStructure:
					try:
						# retrieve all information from line
						layertype, shape, params, connectedTo = line
					except:
						# sometimes the layer doesn't have anything in the connected to-column
						layertype, shape, params = line
						# connectedTo then needs to be created manually:
						if len(tfnet.layers) > 0:
							# If this isn't the first line, write previous layers name as connected
							# as the layers in linearStructure are always only connected to prev.
							connectedTo = tfnet.layers[-1][0]
						else: # First layer isn't connected to anything
							connectedTo = ""
				# process layertype "layername (type)" into layername and ltype
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
				connectedTo = [connectedTo] # needs to be an array to add more connections later
				# repackage to tuple and append to tfnet.layers
				layer = layername, ltype, shape, params, connectedTo
				tfnet.layers.append(layer)
				foundLineMatch = True
			
			# If a layer is connected to more than one, the connections are written in new lines
			# So if the structureType has this column and we couldn't match the line yet,
			# assume that it contains heaps of whitespace and another connection in the
			# connected to-column as additional connection for the previous layer
			elif "Connected to" in tfnet.structureType.regexHeader:
				connectedTo = line.strip()
				# process connected to
				while(connectedTo.endswith("[0]")):
					connectedTo = connectedTo[:-3]
				# Append this layername to the previously created layer
				# (in tuple position that corresponds to the connected to-array)
				tfnet.layers[-1][4].append(connectedTo)
				foundLineMatch = True
		# part 2 contains parameter counts about the whole network
		elif mainStructurePart == 2:
			# get the number thats written behind ":" in the line
			#lineToInt = int(re.sub(r"[a-zA-Z\:\, ]", "", line)) # old implementation
			lineToInt = int(line.split(":")[1].strip().replace(",", ""))
			# Self explanatory retrieval and storage of values
			if (line.startswith("Total param")):
				tfnet.totalparams = lineToInt
				foundLineMatch = True
			elif (line.startswith("Trainable param")):
				tfnet.trainableparams = lineToInt
				foundLineMatch = True
			elif (line.startswith("Non-trainable param")):
				tfnet.nontrainableparams = lineToInt
				foundLineMatch = True
		# If the line has not been recognized...
		if not foundLineMatch:
			if quitParsingOnUnknownLine:
				# Error message
				await connection.sendstatus(17, f'Line "{line}" in tf network structure is unexpected ' + \
					f"and cannot be parsed! Quitting parsing to prevent inaccurate architecture information.")
				# Resetting the structure information and declaring the structure invalid
				tfresetstructure()
				# Also quitting further parsing for good measure
				break
			else:
				# Warning message
				await connection.senddebug(14, f'Line "{line}" in tf network structure is unexpected ' + \
					f"and cannot be parsed! Integrity of the architecture data cannot be guaranteed!")
	
	if tfnet.validstructure:
		# Everything fine, count layers and return happy
		tfnet.layerCount = len(tfnet.layers)
		return True
	else:
		# Nothing's fine. Let the client know what we expected and what we got.
		receivedStructure = re.sub(r"   *", ", ", structure[2])
		if receivedStructure.endswith(", "):
			receivedStructure = receivedStructure[:-2]
		warningMsg = f"Tensorflow network structure does not adhere to expected " + \
			f"format!\nReceived structure: " + receivedStructure + \
			f"\nExpected one of the following structures:"
		# Populate with all accepted tf structure types by their readable names and content repres.
		for type in tfStructureTypes:
			warningMsg += "\n    " + type.structureName + ": " + type.readableStructureContent
		# Tell the client how disappointed we are
		await connection.sendstatus(17, warningMsg)
		return False