#!/usr/bin/env python

# This module stores all the relevant server settings for the python websocket server.
# These settings are later checked and verified, to decrease the chance of errors occuring.

# USED LIBRARIES
import os
import types
from datetime import datetime

# LOCAL IMPORTS
import loggingFunctions
import beautifulDebug
import fileHandling

def onModuleReload(): checkSettings()

# TEMPORARY DEBUGGING SETTINGS
class DEBUG:
	USE_FAKE_STRUCTURE = True # overrides retrieval of tf model summary when no nn is loaded
	# This allows the server to draw a precached structure without loading any model

class SERVER:
	# WEBSOCKET SERVER ADDRESS
	IP = "localhost"
	PORT = 80

	# OTHER WEBSOCKET SERVER SETTINGS
	MAX_MESSAGE_SIZE = 2**24 # in bytes. should not be larger than 2**24 without changing msgpack specs
	TIMES_TO_RETRY_ESTABLISHING_SERVER = 10 # needs to be at least 1, otherwise the server won't run
	SECONDS_BETWEEN_TRIES = 1 # should be at least 1
	TIMES_TO_RETRY_STOPPING_COROUTINES = 40

class FILEPATHS:
	# Available neural networks that can be loaded via keywords
	# Start with a \ or / to indicate a path relative to the location of the centralController.py script
	# Path will then be automatically converted to absolute in checkSettings()-functions
	# Behind each filepath add a colon and specify the variable name of the model in that script
	# (would default to FILEPATHS.DEFAULT_NN_VARIABLE_NAME as variable name that contains the tf model)
	AVAILABLE_MODELS = {
		"vgg16": R"\..\..\First tests\VGGNet16 Tensorflow\vgg16experimentation.py : model",
		"resnet": R"\..\..\First tests\ResNet50 Tensorflow\resnet.py : model",
	}
	# If variable name is not specified (applies to this list of available models and when the user
	# loads a custom .py by directly typing the path in with the "nn load" command)
	DEFAULT_NN_VARIABLE_NAME = "model"

	# default location of DNN python file. Will be loaded if "nn load" is received without attributes
	# You can use a key of FILEPATHS.AVAILABLE_MODELS here.
	# Start with a \ or / to indicate a path relative to the location of the centralController.py script
	# Path will then be automatically converted to absolute in checkSettings()-functions
	NN_LOAD_DEFAULT_MODEL = "vgg16"

	# Where is the log file located?
	# Start with a \ or / to indicate a path relative to the location of the centralController.py script
	# Path will then be automatically converted to absolute in checkSettings()-functions
	LOGFILE = R"\..\logs"
	# Append logfile name. This should contain some unique datetime-identifier and be easily sortable.
	LOGFILE +=	R"\session " + datetime.now().strftime("on %Y-%m-%d at %H %M") + ".txt"
	#LOGFILE = None # Use this to deactivate logging entirely. Not recommended!

	# Where to store rendered images from the visualization
	OUTPUT_IMAGES = R"\..\renders"
	# Where to temporarily cache images rendered for the Unreal Engine (e.g. textures)
	FILECACHE = R"\..\filecache"

class COMMANDS:
	# Here you can define your own macros that get recognized as commands
	# Use these to define more complicated behaviour or make routines quickly available
	# Recommended to be used with AMPERSAND_CHAINS_COMMANDS enabled
	# To reload these macros you need to execute the command "server reload serverCommands"
	MACROS = {
		"fresh": "server reload setting server vis design & almostnowait & tf draw layers",
		"recom": "server reload setting & eval setting.COMMANDS.MACROS & server reload serverCommands",
		"kk": "tf draw kernel",
		"almostnowait": "py design.maxDrawWaitTimeout = 0.5 & eval design.maxDrawWaitTimeout",
		"nowait": "py design.maxDrawWaitTimeout = 0 & eval design.maxDrawWaitTimeout",
		"new": "server reload ai & nn load vgg16 & tf draw layers & nn is loaded",
		"shape": "tf get layers & tf draw kernels",
	}

	# Allows the websocket client to execute and evaluate any string with python.
	# Easier for debugging, but will introduce security concerns.
	# Necessary for commands like python, eval, send struct, server reload
	# Automatically disabled by checkSettings() over unencrypted internet connections outside of localhost
	ALLOW_REMOTE_CODE_EXECUTION = True

	# If true, giving commands with a ampersand will chain commands and execute them successively
	# If enabled and you want to relay an ampersand to a command, escape it with a double ampersand
	AMPERSAND_CHAINS_COMMANDS = True
	# If commands can be chained, this determines whether following commands will still be executed
	# after encountering an error with a previous command or after "server stop" has been called
	EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE = False

	# parameters that signify an affirmation or activation of some sort
	POSITIVE_PARAMETERS = ["true", "1", "yes", "some", "accept", "t", "y", "pos", "positive", "yup",
		"j", "yeah", "sure", "active", "activate", "activated", "+", "affirm", "confirm", "confirmed",
		"confirmation", "affirmation"]
	# parameters that signify a negation or deactivation of some sort
	NEGATIVE_PARAMETERS = ["false", "0", "no", "none", "ignore", "f", "n", "neg", "negative", "nope",
		"x", "nah", "inactive", "deactivate", "deactivated", "-", "negate", "negated", "deny", "denied",
		"refuse", "refused", "ignored"]

class FORMAT_OUTPUT:
	# Desired level of debugging verbosity in console and debug. The lower you go the more verbose
	# debug info gets printed. -10 = all debug, 0 = only warnings and errors, 3 = ignore mild warnings,
	# 10 = ignore all warnings, 13 = ignore mild errors, 20 = don't print any non-critical errors.
	# Also changes what is stored in the logfile.
	DESIRED_VERBOSITY = -10

	# Whether or not the server should try to break printed text at spaces when printing in console
	# False: No smart line breaks, True: Split at spaces, String: Split after any character in that string
	SMART_LINE_BREAKS = ' -_+*/|\\\t=()[]\{\}'
	# Prints colored output in the console. Nevertheless, ansi color codes will be emitted from the log
	PRINT_COLOR_ANSI_CODES = True
	# You can use this workaround, works better for some console, but might lead to weird spaces in others
	USE_ALTERNATIVE_ANSI_CODE_WORKAROUND = True
	# Change this value if you can see a text in the console that recommends you to.
	# Rather than setting True here, you can also try to flip the Alternative workaround value above.
	ONLY_USE_SIMPLE_ANSI_CODES = False
	# Respond with color-formatted debug and status strings to the client. Use this only when reading
	# server responses in a console while simulating a client (not recommended for UE4 client)
	RESPOND_WITH_COLOR_ANSI_CODES = False

	# Append new timestamp in the logfile if last log entry is older than ___ seconds:
	LOG_TIMESTAMP_AFTER_SECONDS = 1


# Settings checks and warnings. Verifies user settings and gives warnings / recommendations
# These checks get executed immedaitely while the module is being loaded:
FILEPATHS.OUTPUT_IMAGES = fileHandling.ensureFolderEnding(fileHandling.addServerScriptPath(FILEPATHS.OUTPUT_IMAGES))
fileHandling.createFilepath(FILEPATHS.OUTPUT_IMAGES)
FILEPATHS.FILECACHE = fileHandling.ensureFolderEnding(fileHandling.addServerScriptPath(FILEPATHS.FILECACHE))
fileHandling.createFilepath(FILEPATHS.FILECACHE)

# this gets called manually after all modules are loaded or whenever serverSettings are reloaded
# WarningFunction is of type warn(string: message, int: verbosityLevel)
def checkSettings():
	# Use only global variables for this function
	# global # Add any variables outside of classes to global command
	
	# The following checks should be self-explanatory,
	# as they contain a verbose warning describing the issue
	# Any changes applied to the settings by this function should be broadcasted to the user!

	COMMANDS.POSITIVE_PARAMETERS = sorted(COMMANDS.POSITIVE_PARAMETERS)
	COMMANDS.NEGATIVE_PARAMETERS = sorted(COMMANDS.NEGATIVE_PARAMETERS)

	if SERVER.IP != "localhost" and SERVER.IP != "127.0.0.1" and \
		SERVER.IP != "::1" and COMMANDS.ALLOW_REMOTE_CODE_EXECUTION:

		msg = "SECURITY WARNING: Remote code execution over " + \
			"unencrypted connections is not recommended and will be disabled!"
		loggingFunctions.warn(msg, 9)
		COMMANDS.ALLOW_REMOTE_CODE_EXECUTION = False # overwrite user decision for security reasons
		# you can theoretically disable this overwrite, but at your own risk!

	assert type(FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS) is float or \
		type(FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS) is int
	FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS = max(0, FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS)
	if FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS < 0.01:
		msg = "FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS lower than 0.01 is not recommended for " + \
			"easily readable log files. New lines might be printed with individual timestamps!"
		loggingFunctions.warn(msg, 1)

	assert type(SERVER.MAX_MESSAGE_SIZE) is int
	if SERVER.MAX_MESSAGE_SIZE < 256:
		msg = "SERVER.MAX_MESSAGE_SIZE cannot be smaller than 256, otherwise unexpected behaviour " + \
			"and recursion loops will occur! Setting SERVER.MAX_MESSAGE_SIZE to 256."
		loggingFunctions.warn(msg, 8)
		SERVER.MAX_MESSAGE_SIZE = 256
	if SERVER.MAX_MESSAGE_SIZE < 2**12:
		msg = f"SERVER.MAX_MESSAGE_SIZE smaller than {2**10} is not recommended as responses might not " + \
			"get passed through than its current value of {SERVER.MAX_MESSAGE_SIZE} bytes."
		loggingFunctions.warn(msg, 7)

	assert type(SERVER.TIMES_TO_RETRY_ESTABLISHING_SERVER) is int
	if SERVER.TIMES_TO_RETRY_ESTABLISHING_SERVER < 1:
		msg = "SERVER.TIMES_TO_RETRY_ESTABLISHING_SERVER has to be at least 1, otherwise the server " + \
			"cannot be started. Setting SERVER.TIMES_TO_RETRY_ESTABLISHING_SERVER to 1."
		loggingFunctions.warn(msg, 8)
		SERVER.TIMES_TO_RETRY_ESTABLISHING_SERVER = 1

	assert type(SERVER.TIMES_TO_RETRY_STOPPING_COROUTINES) is int

	assert type(SERVER.SECONDS_BETWEEN_TRIES) is int or \
		type(SERVER.SECONDS_BETWEEN_TRIES) is float
	if SERVER.SECONDS_BETWEEN_TRIES <= 0:
		msg = "SERVER.SECONDS_BETWEEN_TRIES cannot be smaller than or equal to 0!\n" + \
			"Setting SERVER.SECONDS_BETWEEN_TRIES to 0.1"
		loggingFunctions.warn(msg, 8)
		SERVER.SECONDS_BETWEEN_TRIES = 0.1
	elif SERVER.SECONDS_BETWEEN_TRIES < 0.1:
		msg = "SERVER.SECONDS_BETWEEN_TRIES should be at least 0.1"
		loggingFunctions.warn(msg, 8)

	if FILEPATHS.LOGFILE is None or FILEPATHS.LOGFILE == "":
		msg = "No valid logpath given in settings. Logging will be disabled. This is not recommended"
		loggingFunctions.warn(msg, 4)
	else:
		assert type(FILEPATHS.LOGFILE) is str
		FILEPATHS.LOGFILE = fileHandling.addServerScriptPath(FILEPATHS.LOGFILE)
	fileHandling.createFilepath(FILEPATHS.LOGFILE)
	
	FILEPATHS.AVAILABLE_MODELS = {keyword:fileHandling.addServerScriptPath(path)
		for (keyword, path) in FILEPATHS.AVAILABLE_MODELS.items()}

	if FILEPATHS.NN_LOAD_DEFAULT_MODEL not in FILEPATHS.AVAILABLE_MODELS.keys():
		FILEPATHS.NN_LOAD_DEFAULT_MODEL = fileHandling.addServerScriptPath(FILEPATHS.NN_LOAD_DEFAULT_MODEL)
	
	if FORMAT_OUTPUT.PRINT_COLOR_ANSI_CODES:
		if FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES:
			text = ('\u001b[40m' + beautifulDebug.ansicode(30) + beautifulDebug.ansicode(120, False) + # green text on black background
			"You can disable FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES in the server settings for more " +
			"nuanced colors in the console output.\n" + beautifulDebug.RESET)
			if FORMAT_OUTPUT.SMART_LINE_BREAKS:
				beautifulDebug.printWithLinebreaks(text)
			else:
				print(text)
		else:
			text = ('\u001b[40m' + beautifulDebug.YELLOW + beautifulDebug.ansicode(232, False) + # green text on black background
			"Please try changing the value FORMAT_OUTPUT.USE_ALTERNATIVE_ANSI_CODE_WORKAROUND " +
			"in the settings. If doesn't make this message disappear, please enable " +
			"FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES in the server settings for correct colors " +
			"in the console output!\nOtherwise, warnings and errors could be overlooked easily." +
			beautifulDebug.RESET)
			if FORMAT_OUTPUT.SMART_LINE_BREAKS:
				beautifulDebug.printWithLinebreaks(text)
			else:
				print(text)



	# ^ ^ ^ ^ ^ ADD NEW SETTINGS CHECKS ABOVE THIS LINE ^ ^ ^ ^ ^
	# ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
	# Now checking whether any local variables should've been global references to settings.
	# This ensures that this function really changes the settings
	# instead of creating local variables in its function context.
	localVariables = {
		varname for varname, value in locals().items() if
			varname not in [] and # you could add variable names as strings in this array to
			# override the warning. NOT RECOMMENDED!
			type(value) not in [types.BuiltinFunctionType, types.ModuleType, types.FunctionType] and
			varname[0] != '_' and
			varname in globals().keys()
	}
	if len(localVariables) > 0:
		msg = f"Namespace problem found in settings check!\n" + \
		f"The variable{'s' if len(localVariables) > 1 else ''} " + \
		f"{', '.join(localVariables)} in settings check is treated as a local variable! " + \
		"Please add it to the list of global variables at the beginning of the " + \
		"checkSettings-function in the serverSettings-file. Otherwise, checks and changes " + \
		"to the settings are not applied properly.\n(This error can can be avoided by " + \
		"renaming either the local or global variable in the checkSettings-function)"
		#loggingFunctions.warn(msg, 18)
		raise NameError(msg)
	return # DO NOT ADD ANY SETTINGS CHECKS HERE!