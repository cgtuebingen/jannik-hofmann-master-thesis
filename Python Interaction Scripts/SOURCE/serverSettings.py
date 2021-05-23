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

def onModuleReload(): checkSettings()

# TEMPORARY DEBUGGING SETTINGS
DEBUG_USE_FAKE_STRUCTURE = True # overrides retrieval of tf model summary
# This allows the server to draw a precached structure without loading any model


# WEBSOCKET SERVER ADDRESS
SERVER_IP = "localhost"
SERVER_PORT = 80

# WEBSOCKET SERVER SETTINGS
MAX_MESSAGE_SIZE = 2**24 # in bytes. should not be larger than 2**24 without changing msgpack specs
TIMES_TO_RETRY_ESTABLISHING_SERVER = 10 # needs to be at least 1
SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER = 1 # should be at least 1

# If true, giving commands with a ampersand will chain commands and execute them successively
# If enabled and you want to relay an ampersand to a command, escape it with a double ampersand
AMPERSAND_CHAINS_COMMANDS = True
# If commands can be chained, this determines whether following commands will still be executed
# after encountering an error with a previous command or after "server stop" has been called
EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE = False

# Allows the websocket client to execute and evaluate any string with python.
# Easier for debugging, but will introduce security concerns.
# Automatically disabled by checkSettings() over unencrypted internet connections outside of localhost
ALLOW_REMOTE_CODE_EXECUTION = True

# Available neural networks that can be loaded via keywords
# Start with a \ or / to indicate a path relative to the location of the centralController.py script
# Path will then be automatically converted to absolute in checkSettings()-functions
# Behind each filepath add a colon and specify the variable name of the model in that script
# (would default to 'model' as variable name that contains the tf model)
AVAILABLE_NN_PATHS = {
	"vgg16": R"\..\..\First tests\VGGNet16 Tensorflow\vgg16experimentation.py : model",
	"resnet": R"\..\..\First tests\ResNet50 Tensorflow\resnet.py : model",
}
DEFAULT_NN_VARIABLE_NAME = "model"

# default location of DNN python file. Will be loaded if "loadnn" is received without attributes
# You can use a key of AVAILABLE_NN_PATHS here.
# Start with a \ or / to indicate a path relative to the location of the centralController.py script
# Path will then be automatically converted to absolute in checkSettings()-functions
DEFAULT_LOAD_NN_PATH = "vgg16"

# Where is the log file located?
# Start with a \ or / to indicate a path relative to the location of the centralController.py script
# Path will then be automatically converted to absolute in checkSettings()-functions
LOGFILE_PATH = R"\..\logs"
# Append logfile name. This should contain some unique datetime-identifier and be easily sortable.
LOGFILE_PATH +=	R"\session " + datetime.now().strftime("on %Y-%m-%d at %H %M") + ".txt"

#LOGFILE_PATH = None# This deactivates logging entirely. Not recommended.

# Desired level of debugging verbosity in console and debug. The lower you go the more verbose
# debug info gets printed. -10 = all debug, 0 = only warnings and errors, 3 = ignore mild warnings,
# 10 = ignore all warnings, 13 = ignore mild errors, 20 = don't print any non-critical errors.
# Also changes what is stored in the logfile.
DESIRED_VERBOSITY = -10

# Prints colored output in the console. Nevertheless, ansi color codes will be emitted from the log
PRINT_COLOR_ANSI_CODES = True
# Respond with color-formatted debug and status strings to the client.
RESPOND_WITH_COLOR_ANSI_CODES = False
# Change this value if you can see a text in the console that recommends you to.
ONLY_USE_SIMPLE_ANSI_CODES = True

# Append new timestamp in the logfile if last log entry is older than ___ seconds:
LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S = 1

# parameters that signify an affirmation or activation of some sort
POSITIVE_PARAMETERS = ["true", "1", "yes", "some", "accept", "t", "y", "pos", "positive", "yup",
	"j", "yeah", "sure", "active", "activate", "activated", "+", "affirm", "confirm", "confirmed",
	"confirmation", "affirmation"]
# parameters that signify a negation or deactivation of some sort
NEGATIVE_PARAMETERS = ["false", "0", "no", "none", "ignore", "f", "n", "neg", "negative", "nope",
	"x", "nah", "inactive", "deactivate", "deactivated", "-", "negate", "negated", "deny", "denied",
	"refuse", "refused", "ignored"]


# Settings checks and warnings. Verifies user settings and gives warnings / recommendations
# WarningFunction is of type warn(string: message, int: verbosityLevel)
def checkSettings():
	# Use only global variables for this function
	global SERVER_IP, SERVER_PORT, MAX_MESSAGE_SIZE, TIMES_TO_RETRY_ESTABLISHING_SERVER, \
	SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER, AMPERSAND_CHAINS_COMMANDS, \
	EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE, ALLOW_REMOTE_CODE_EXECUTION, \
	AVAILABLE_NN_PATHS, DEFAULT_LOAD_NN_PATH, LOGFILE_PATH, DESIRED_VERBOSITY, \
	PRINT_COLOR_ANSI_CODES, RESPOND_WITH_COLOR_ANSI_CODES, ONLY_USE_SIMPLE_ANSI_CODES, \
	LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S, POSITIVE_PARAMETERS, NEGATIVE_PARAMETERS, \
	DEFAULT_NN_VARIABLE_NAME
	
	# to be able to retrieve SCRIPT_PATH()
	import centralController

	# The following checks should be self-explanatory,
	# as they contain a verbose warning describing the issue
	# Any changes applied to the settings by this function should be broadcasted to the user!

	POSITIVE_PARAMETERS = sorted(POSITIVE_PARAMETERS)
	NEGATIVE_PARAMETERS = sorted(NEGATIVE_PARAMETERS)

	if SERVER_IP != "localhost" and SERVER_IP != "127.0.0.1" and \
		SERVER_IP != "::1" and ALLOW_REMOTE_CODE_EXECUTION:

		msg = "SECURITY WARNING: Remote code execution over " + \
			"unencrypted connections is not recommended and will be disabled!"
		loggingFunctions.warn(msg, 9)
		ALLOW_REMOTE_CODE_EXECUTION = False # overwrite user decision for security reasons
		# you can theoretically disable this overwrite, but at your own risk!

	assert((type(LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S) is float) or
		(type(LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S) is int))
	LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S = max(0, LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S)
	if LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S < 0.01:
		msg = "LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S lower than 0.01 is not recommended for " + \
			"easily readable log files. New lines might printed with individual timestamps!"
		loggingFunctions.warn(msg, 1)

	assert(type(MAX_MESSAGE_SIZE) is int)
	if MAX_MESSAGE_SIZE < 256:
		msg = "MAX_MESSAGE_SIZE cannot be smaller than 256, otherwise unexpected behaviour " + \
			"and recursion loops will occur! Setting MAX_MESSAGE_SIZE to 256."
		loggingFunctions.warn(msg, 8)
		MAX_MESSAGE_SIZE = 256
	if MAX_MESSAGE_SIZE < 2**12:
		msg = f"MAX_MESSAGE_SIZE smaller than {2**10} is not recommended as responses might not " + \
			"get passed through than its current value of {MAX_MESSAGE_SIZE} bytes."
		loggingFunctions.warn(msg, 7)

	assert(type(TIMES_TO_RETRY_ESTABLISHING_SERVER) is int)
	if TIMES_TO_RETRY_ESTABLISHING_SERVER < 1:
		msg = "TIMES_TO_RETRY_ESTABLISHING_SERVER has to be at least 1, otherwise the server " + \
			"cannot be started. Setting TIMES_TO_RETRY_ESTABLISHING_SERVER to 1."
		loggingFunctions.warn(msg, 8)
		TIMES_TO_RETRY_ESTABLISHING_SERVER = 1

	assert(type(SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER) is int or
		type(SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER) is float)
	if SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER <= 0:
		msg = "SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER cannot be smaller than or equal to 0!\n" + \
			"Setting SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER to 0.1"
		loggingFunctions.warn(msg, 8)
		SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER = 0.1
	elif SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER < 0.1:
		msg = "SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER should be at least 0.1"
		loggingFunctions.warn(msg, 8)

	# Adds the server script path to a given path if it starts with / or \
	def addServerScriptPath(filepath: str):
		if filepath.startswith(("\\", "/")):
			return centralController.SCRIPT_PATH() + filepath
		else:
			return filepath

	if LOGFILE_PATH is None or LOGFILE_PATH == "":
		msg = "No valid logpath given in settings. Logging will be disabled. This is not recommended"
		loggingFunctions.warn(msg, 4)
	else:
		assert(type(LOGFILE_PATH) is str)
		LOGFILE_PATH = addServerScriptPath(LOGFILE_PATH)
	
	AVAILABLE_NN_PATHS = {keyword:addServerScriptPath(path) for (keyword, path) in AVAILABLE_NN_PATHS.items()}

	assert(type(DEFAULT_LOAD_NN_PATH) is str)
	if DEFAULT_LOAD_NN_PATH not in AVAILABLE_NN_PATHS.keys():
		addServerScriptPath(DEFAULT_LOAD_NN_PATH)

	if PRINT_COLOR_ANSI_CODES:
		if ONLY_USE_SIMPLE_ANSI_CODES:
			print('\u001b[40m' + beautifulDebug.ansicode(30) + beautifulDebug.ansicode(120, False) + # green text on black background
			"You can disable ONLY_USE_SIMPLE_ANSI_CODES in the server settings for more " +
			"nuanced colors in the console output.\n" + beautifulDebug.RESET)
		else:
			print('\u001b[40m' + beautifulDebug.YELLOW + beautifulDebug.ansicode(232, False) + # green text on black background
			"Please enable ONLY_USE_SIMPLE_ANSI_CODES in the server settings for correct colors in " +
			"the console output!\nOtherwise, warnings and errors could be overlooked easily." +
			beautifulDebug.RESET)



	# ^ ^ ^ ^ ^ ADD NEW SETTINGS CHECKS ABOVE THIS LINE ^ ^ ^ ^ ^
	# ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
	# Now checking whether any local variables should've been global references to settings.
	# This ensures that this function really changes the settings
	# instead of creating local variables in its function context.
	localVariables = {varname for varname, value in locals().items() if
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