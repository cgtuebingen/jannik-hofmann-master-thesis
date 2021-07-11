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
import functools
import ast
import random
from PIL import Image
from numpy.lib.function_base import select


# LOCAL IMPORTS
import serverCommands
import serverSettings as setting
import loggingFunctions
import beautifulDebug
import fileHandling
import websocketServer as server
import visualizationSettings as design


# Definitions / initializations
nnloaded = False
nnprepared = False
modelvarname = None
nn_spec = None
nn_module = None
tfnet = SimpleNamespace()
pytorchnet = SimpleNamespace()
tf = None
gradientCache = dict()
# Structure of tfnet.layers: (layername, ltype, shape, params, connectedTo, trainableVariables)
# trainableVariables is a (maybe empty) dict of lists. Lists have same indices as tfnet.layers:
# e.g. {'kernel': [ndarrays], 'bias': [ndarrays], 'gamma': [ndarrays], 'beta': [ndarrays]}

# Used to store and retrieve module variables before and after module reload.
# With empty parameter, returns a list of variable values that should be saved.
# This list can then be used as parameter on the second call to overwrite the freshly initialized vars
def onModuleReloadVars(vars = None):
	global nnloaded, nnprepared, modelvarname, nn_spec, nn_module, tfnet, pytorchnet, tf, gradientCache
	if vars is None:
		return nnloaded, nnprepared, modelvarname, nn_spec, nn_module, tfnet, pytorchnet, tf, gradientCache
	nnloaded, nnprepared, modelvarname, nn_spec, nn_module, tfnet, pytorchnet, tf, gradientCache = vars


# MINOR HELPER FUNCTIONS

# Returns the current reference to the model
def model(): return getattr(nn_module, modelvarname)
# Returns whether a tf network has been loaded and initialized successfully
def tfloaded(): return hasattr(tfnet, 'loaded') and tfnet.loaded
# Adds the verbose model name and optional timestamp to a path
def addNetworkInfoToPath(path, filenameOrSubfolder="", filename="", timestamp=False):
	if hasattr(tfnet, 'modelname_verbose'):
		path += tfnet.modelname_verbose + os.path.sep
	if filenameOrSubfolder and filename:
		filenameOrSubfolder += os.sep
	filename = filenameOrSubfolder + filename
	if timestamp and '.' in filename:
		filename = filename.rsplit('.', 1)
		filename = filename[0] + '_' + datetime.now().strftime("%Y-%m-%d_%H-%M-%S") + '.' + filename[1]
	return fileHandling.createFilepath(path + filename)
# Returns the path for caching files
def internalCachePath(filenameOrSubfolder="", filename="", timestamp=False):
	return addNetworkInfoToPath(setting.FILEPATHS.FILECACHE, filenameOrSubfolder, filename, timestamp)
# Returns the path for storing renders
def externalImagePath(filenameOrSubfolder="", filename="", timestamp=True):
	return addNetworkInfoToPath(setting.FILEPATHS.OUTPUT_IMAGES, filenameOrSubfolder, filename, timestamp)


# MAIN FUNCTIONS FOR AI INTERACTION

# Prepares a python module and execs it.
# Does not throw errors but returns strings with the error message!
# Afterwards, if no error was thrown, call importtf for tensorflow networks
def preparemodule(path, allowPreparingNewModuleOnTop = False):
	global nn_spec, nn_module, nnprepared, modelvarname

	# Checking if something already has been loaded and if we're allowed to load on top
	if not allowPreparingNewModuleOnTop and (nnprepared or nnloaded):
		return ("The ai interface has already loaded a module in the past and " +
			"should not load another (or the same) nn script on top. You can override this " +
			"check by setting the flag by calling preparemodule(path, True)")

	# Check if model variable name has been specified by searching for a ':' in the filename
	if ':' in fileHandling.separateFilename(path)[1]:
		path, modelvarname = path.rsplit(':', 1)
		path = path.strip()
		modelvarname = modelvarname.strip()
	elif setting.FILEPATHS.DEFAULT_NN_VARIABLE_NAME:
		modelvarname = setting.FILEPATHS.DEFAULT_NN_VARIABLE_NAME
	else:
		return ("No name for the model variable has been defined! Please specify how to acccess the " +
			"network model by adding the varname after the AI script path, separated by a colon.")

	# Checking to see that the file actually exists
	if not os.path.exists(path):
		return (f'File at location "{path}" does not exist! No file could be found at the ' +
		'specified network script location! Please make sure you typed the path correctly ' +
		'and that relative paths in the settings are relative to the source folder of the ' +
		'servers centralController.py')

	# Importing the network python file
	loggingFunctions.printlog("Loading network from " + path)
	nn_spec = importlib.util.spec_from_file_location("", path)
	if nn_spec is None:
		return (f'Python script at location "{path}" could not be loaded as a module! ' +
		'Please make sure that the file at this location is a valid python script ' +
		'that can be imported as a module by python')
	# Creating a module from that file
	nn_module = importlib.util.module_from_spec(nn_spec)
	# And executing its code
	nn_spec.loader.exec_module(nn_module)

	# Now let's check if the modelvarname exists...
	try:
		getattr(nn_module, modelvarname)
	except:
		return (f'No variable named "{modelvarname}" found ' +
			f'in "{fileHandling.separateFilename(path)[1]}"!\n' +
			"The specified variable " + modelvarname +
			" for the model within the script does not exist!\n" +
			"Please make sure that you correctly identify the model variable name and " +
			"append it to the filename of the network python script, separated just by a colon.")
	
	# Storing what file name and network model var we're using
	nnprepared = fileHandling.separateFilename(path)[1].replace('.py', '') + '-' + modelvarname
	return True


# Returns whether the prepared module contains a tensorflow neural network
def preparedModuleIsTf():
	return True # TODO: Check if tensorflow or pytorch

# Imports the tf library to finish loading the tensorflow module.
# Call this after having called preparemodule(path)
def importtf():
	if not nnprepared:
		raise ModuleNotFoundError("Network hasn't been prepared properly! Call preparemodule(path) " +
			"with a path to an exsisting tensorflow network before calling this function!")
	global tfnet, tf, nnloaded
	import tensorflow as tfref
	tf = tfref
	tfnet.loaded = True
	tfnet.modelname_verbose = nnprepared
	nnloaded = True

# Returns the version of tensorflow
def tfversion():
	global tf, tfnet
	tfnet.version = tf.__version__
	return tfnet.version

# Just returns a model summary. Call parsestructure afterwards.
def tfmodelsummary():
	structure = []
	model().summary(print_fn=lambda x: structure.append(x), line_length=1024)
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
	removeAttributes = ["layers", "modelname", "structureType", "totalparams", "trainableparams",
		"nontrainableparams", "layerCount", "layoutPositions", "trainableVariables"]
	global tfnet
	tfnet.validstructure = False
	for attr in removeAttributes:
		if hasattr(tfnet, attr):
			delattr(tfnet, attr)
	

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
			if line.startswith("Model: \""):
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
				if shape.startswith("[") and shape.endswith("]"):
					shape = shape[1:-1]
				shape = ast.literal_eval(shape)
				# process params
				params = int(params)
				# process connectedTo
				while(connectedTo.endswith("[0]")):
					connectedTo = connectedTo[:-3]
				connectedTo = [connectedTo] # needs to be an array to add more connections later
				# repackage to tuple and append to tfnet.layers
				layer = [layername, ltype, shape, params, connectedTo, dict()]
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
			if line.startswith("Total param"):
				tfnet.totalparams = lineToInt
				foundLineMatch = True
			elif line.startswith("Trainable param"):
				tfnet.trainableparams = lineToInt
				foundLineMatch = True
			elif line.startswith("Non-trainable param"):
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

# Retrieves the name of the layer by index. Just passes strings without looking at them
def getLayerName(index):
	if type(index) is str:
		return index
	assert type(index) is int, "index for getLayerName needs to be int (or already str)!"
	assert index < len(tfnet.layers), "index larger than number of layers! Maybe the network structure hasn't been loaded yet?"
	assert index >= 0, "index has to be >= 0!"
	return tfnet.layers[index][0]

def getInputImageSize():
	target_size = list(tfnet.layers[0][2])
	while target_size[0] is None or target_size[0] < 2:
		target_size = target_size[1:]
	return target_size[:2]

# retrieves all trainable variables relating to this layer
def tfGetTrainableVars(layerIndexOrName = None):
	if layerIndexOrName is None:
		return tfnet.trainableVariables
	layerIndexOrName = getLayerName(layerIndexOrName)
	return [var for var in model().trainable_variables if var.name.startswith(layerIndexOrName + '/')]

# Refreshes and stores all trainable variables for each layer in layer[5] as a dictionary of lists
def tfRefreshTrainableVars():
	shapeDict = dict()
	tfnet.trainableVariables = model().trainable_variables
	for index, layer in enumerate(tfnet.layers):
		trainVars = tfGetTrainableVars(layer[0])
		layerVarDict = dict()
		for var in trainVars:
			shapeDict[str(index) + ": " + var.name] = var.shape if isinstance(var, np.ndarray) else var.numpy().shape
			name = var.name.rsplit('/', 1)[1].split(':')[0]
			# name is something like "kernel", "bias", "beta" or "gamma"
			if name in layerVarDict:
				layerVarDict[name].append(var.numpy())
			else:
				layerVarDict[name] = [var.numpy()]
		layer[5] = layerVarDict
	return shapeDict

def tfKerasPreprocessImage(imagePath):
	try:
		image = nn_module.load_img(imagePath, target_size=getInputImageSize())
		image = nn_module.img_to_array(image)
	except:
		image = nn_module.image.load_img(imagePath, target_size=getInputImageSize())
		image = nn_module.image.img_to_array(image)
	image = image.reshape((1, image.shape[0], image.shape[1], image.shape[2]))
	image = nn_module.preprocess_input(image)
	return image

def is_str(inputData):
	try:
		return type(inputData) is str
	except:
		return False

def tfKerasPredict(inputData):
	NUMBER_OF_RELEVANT_PREDICTIONS = 10
	if is_str(inputData):
		inputData = tfKerasPreprocessImage(inputData)
	prediction = nn_module.decode_predictions(model().predict(inputData), top=NUMBER_OF_RELEVANT_PREDICTIONS)[0]
	indices = np.argsort(model()(inputData, training=False).numpy().flatten())[::-1][0:NUMBER_OF_RELEVANT_PREDICTIONS]
	result = [f"{label[1]} ({label[2]*100:.3f}%) [{index}]"
		for index, label in zip(indices, prediction)]
	return '\n'.join(result)

def tfKerasGetLayerOutput(layerIndex, inputData):
	import keras
	if is_str(inputData):
		inputData = tfKerasPreprocessImage(inputData)
	output = model().get_layer(getLayerName(layerIndex)).output
	partialModel = keras.Model(inputs=model().input, outputs=output)
	return partialModel(inputData)

def tfKerasGetSaliency(inputData, index=-1):
	if is_str(inputData):
		inputData = tfKerasPreprocessImage(inputData)
	if not re.fullmatch(R"-?[0-9]+", index): # get label by name
		for i, prediction in enumerate(nn_module.decode_predictions(model().predict(inputData), top=tfnet.layers[-1][2][-1])[0]):
			if index.lower().replace('_', ' ') == prediction[1].lower().replace('_', ' '):
				index = '-' + str(i+1)
				break
		else:
			print("Found nothing")
			index = '-1'
	images = tf.Variable(inputData, dtype=float)
	with tf.GradientTape() as tape:
		pred = model()(images, training=False)
		best_labels = np.argsort(pred.numpy().flatten())[::-1]
		index = int(index)
		if index < 0:
			topIndex = -index-1
			index = best_labels[topIndex]
		else:
			topIndex = np.where(best_labels == index)[0][0]
		loss = pred[0][index]
	
	prediction = nn_module.decode_predictions(model().predict(inputData), top=tfnet.layers[-1][2][-1])[0][topIndex]
	result = np.max(tf.math.abs(tape.gradient(loss, images)), axis=3)[0]
	print(f"{prediction[1]} ({beautifulDebug.floatToShortStr(prediction[2]*100)}%) [{index}]")
	return (result, f"{index}-{prediction[1]}-{beautifulDebug.floatToShortStr(prediction[2]*100)}%")

@functools.lru_cache(maxsize=256)
def tfKerasGetGradients(inputData, index=-1):
	if design.integratedGradients.cacheCalculationResults:
		seed = str(inputData) + '\n' + str(index)
		if seed in gradientCache:
			return (gradientCache[seed][0].copy(), gradientCache[seed][1])
	
	from alibi.explainers import IntegratedGradients
	
	if is_str(inputData):
		inputData = tfKerasPreprocessImage(inputData)

	if not re.fullmatch(R"-?[0-9]+", index): # get label by name
		for i, prediction in enumerate(nn_module.decode_predictions(model().predict(inputData), top=tfnet.layers[-1][2][-1])[0]):
			if index.lower().replace('_', ' ') == prediction[1].lower().replace('_', ' '):
				index = '-' + str(i+1)
				break
		else:
			print("Found nothing")
			index = '-1'
	images = tf.Variable(inputData, dtype=float)
	with tf.GradientTape() as tape:
		pred = model()(images, training=False)
		best_labels = np.argsort(pred.numpy().flatten())[::-1]
		index = int(index)
		if index < 0:
			topIndex = -index-1
			index = best_labels[topIndex]
		else:
			topIndex = np.where(best_labels == index)[0][0]
		loss = pred[0][index]
	prediction = nn_module.decode_predictions(model().predict(inputData), top=tfnet.layers[-1][2][-1])[0][topIndex]
	
	def calculate_attributions():
		ig = IntegratedGradients(model(), layer=None, method="gausslegendre", n_steps=50, internal_batch_size=100)
		return ig.explain(inputData, baselines=None, target=[np.int64(index)]).attributions
	
	attributions = None
	if not design.integratedGradients.calculateDirectlyOnCpu:
		try:
			attributions = calculate_attributions()
		except tf.errors.ResourceExhaustedError:
			attributions = None
			print("Resources exhausted. Trying again on CPU")
	if attributions is None:
		with tf.device("/cpu:0"):
			attributions = calculate_attributions()
	
	result = np.asarray(attributions).squeeze()
	print(f"{prediction[1]} ({beautifulDebug.floatToShortStr(prediction[2]*100)}%) [{index}]")
	result = (result, f"{index}-{prediction[1]}-{beautifulDebug.floatToShortStr(prediction[2]*100)}%")

	if design.integratedGradients.cacheCalculationResults:
		gradientCache[seed] = result
	
	return result
