#!/usr/bin/env python

# This module stores all the relevant server settings for the python websocket server.
# These settings are later checked and verified, to decrease the chance of errors occuring.

# USED LIBRARIES
import os
from datetime import datetime

# LOCAL IMPORTS
import loggingFunctions


# WEBSOCKET SERVER SETTINGS
SERVER_IP = "localhost"
SERVER_PORT = 80
MAX_MESSAGE_SIZE = 2**24 # in bytes. should not be larger than 2**24 without changing msgpack specs
TIMES_TO_RETRY_ESTABLISHING_SERVER = 10 # needs to be at least 1
SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER = 1 # should be at least 1

# If true, giving commands with a ampersand will chain commands and execute them successively
# If enabled and you want to relay an ampersand to a command, escape it with a double ampersand
AMPERSAND_CHAINS_COMMANDS = True
# If commands can be chained, this determines whether following commands will still be executed
# after encountering an error with a previous command
EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE = False

# Allows the websocket client to execute and evaluate any string with python.
# Easier for debugging, but will introduce security concerns.
# Automatically disabled by checkSettings() over unencrypted internet connections outside of localhost
ALLOW_REMOTE_CODE_EXECUTION = True

# default location of DNN python file. Will be loaded if "loadnn" is received without attributes
# Start with a \ or / to indicate a path relative to the location of the centralController.py script
# Path will then be automatically converted to absolute in checkSettings()-functions
DEFAULT_LOAD_NN_PATH = R"\..\..\First tests\VGGNet16 Tensorflow\vgg16experimentation.py"

# Where is the log file located?
# Start with a \ or / to indicate a path relative to the location of the centralController.py script
# Path will then be automatically converted to absolute in checkSettings()-functions
LOGFILE_PATH = R"\..\logs"
# Append logfile name. This should contain some unique datetime-identifier and be easily sortable.
LOGFILE_PATH +=	R"\session " + datetime.now().strftime("on %Y-%m-%d at %H %M") + ".txt"

#LOGFILE_PATH = None# This deactivates logging entirely. Not recommended.

# Desired level of debugging verbosity in console and debug. The higher you go the more verbose
# debug info gets printed. 11 = all debug, 0 = only warnings and errors, -1 = ignore mild warnings,
# -9 = ignore all warnings, -10 = ignore mild errors, -19 = don't print any non-critical errors.
# Also changes what is stored in the logfile.
DESIRED_VERBOSITY = 11

# Prints colored output in the console. Nevertheless, ansi color codes will be emitted from the log
PRINT_COLOR_ANSI_CODES = True
# Respond with color-formatted debug and status strings to the client.
RESPOND_WITH_COLOR_ANSI_CODES = True

# Append new timestamp in the logfile if last log entry is older than ___ seconds:
LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S = 1

# parameters that signify a negation or deactivation of some sort
POSITIVE_PARAMETERS = ["true", "1", "yes", "some", "accept", "t", "y", "pos", "positive", "yup",
	"j", "yeah", "sure", "active", "activate", "activated", "+"]
# parameters that signify a negation or deactivation of some sort
NEGATIVE_PARAMETERS = ["false", "0", "no", "none", "ignore", "f", "n", "neg", "negative", "nope",
	"x", "nah", "inactive", "deactivate", "deactivated", "-"]


# Settings checks and warnings. Verifies user settings and gives warnings / recommendations
# WarningFunction is of type warn(string: message, int: verbosityLevel)
def checkSettings():
	# Use only global variables for this function
	global SERVER_IP, SERVER_PORT, MAX_MESSAGE_SIZE, TIMES_TO_RETRY_ESTABLISHING_SERVER, \
	SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER, AMPERSAND_CHAINS_COMMANDS, \
	EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE, ALLOW_REMOTE_CODE_EXECUTION, \
	DEFAULT_LOAD_NN_PATH, LOGFILE_PATH, DESIRED_VERBOSITY, \
	PRINT_COLOR_ANSI_CODES, RESPOND_WITH_COLOR_ANSI_CODES, \
	LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S, POSITIVE_PARAMETERS, NEGATIVE_PARAMETERS
	
	# to be able to retrieve SCRIPT_PATH()
	import centralController

	# The following checks should be self-explanatory,
	# as they contain a verbose warning describing the issue
	# Any changes applied to the settings by this function should be broadcasted to the user!

	if (SERVER_IP != "localhost" and SERVER_IP != "127.0.0.1" and
		SERVER_IP != "::1" and ALLOW_REMOTE_CODE_EXECUTION):
		msg = "SECURITY WARNING: Remote code execution over " + \
			"unencrypted connections is not recommended and will be disabled!"
		loggingFunctions.warn(msg, 9)
		ALLOW_REMOTE_CODE_EXECUTION = False # overwrite user decision for security reasons
		# you can theoretically disable this overwrite, but at your own risk!

	assert((type(LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S) is float) or
		(type(LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S) is int))
	LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S = max(0, LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S)
	if (LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S < 0.01):
		msg = "LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S lower than 0.01 is not recommended for " + \
			"easily readable log files. New lines might printed with individual timestamps!"
		loggingFunctions.warn(msg, 1)

	assert(type(MAX_MESSAGE_SIZE) is int)
	if (MAX_MESSAGE_SIZE < 256):
		msg = "MAX_MESSAGE_SIZE cannot be smaller than 256, otherwise unexpected behaviour " + \
			"and recursion loops will occur! Setting MAX_MESSAGE_SIZE to 256."
		loggingFunctions.warn(msg, 8)
		MAX_MESSAGE_SIZE = 256
	if (MAX_MESSAGE_SIZE < 2**12):
		msg = f"MAX_MESSAGE_SIZE smaller than {2**10} is not recommended as responses might not " + \
			"get passed through than its current value of {MAX_MESSAGE_SIZE} bytes."
		loggingFunctions.warn(msg, 7)

	assert(type(TIMES_TO_RETRY_ESTABLISHING_SERVER) is int)
	if (TIMES_TO_RETRY_ESTABLISHING_SERVER < 1):
		msg = "TIMES_TO_RETRY_ESTABLISHING_SERVER has to be at least 1, otherwise the server " + \
			"cannot be started. Setting TIMES_TO_RETRY_ESTABLISHING_SERVER to 1."
		loggingFunctions.warn(msg, 8)
		TIMES_TO_RETRY_ESTABLISHING_SERVER = 1

	assert(type(SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER) is int or
		type(SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER) is float)
	if (SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER <= 0):
		msg = "SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER cannot be smaller than or equal to 0!\n" + \
			"Setting SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER to 0.1"
		loggingFunctions.warn(msg, 8)
		SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER = 0.1
	elif (SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER < 0.1):
		msg = "SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER should be at least 0.1"
		loggingFunctions.warn(msg, 8)

	if (LOGFILE_PATH is None or LOGFILE_PATH == ""):
		msg = "No valid logpath given in settings. Logging will be disabled. This is not recommended"
		loggingFunctions.warn(msg, 4)
	else:
		assert(type(DEFAULT_LOAD_NN_PATH) is str) and (type(LOGFILE_PATH) is str)
		if (DEFAULT_LOAD_NN_PATH.startswith(("\\", "/"))):
			DEFAULT_LOAD_NN_PATH = centralController.SCRIPT_PATH() + DEFAULT_LOAD_NN_PATH
		if (LOGFILE_PATH.startswith(("\\", "/"))):
			LOGFILE_PATH = centralController.SCRIPT_PATH() + LOGFILE_PATH

	# Use this to check whether you left out any variables in the "global" definition above:
	#print(locals())
