#!/usr/bin/env python

# This module takes care of writing debug info into the log file and printing that info onto
# the python console. It uses verbosity levels in order to decide what information to relay

# USED LIBRARIES
import asyncio
import os
import sys
import time
from datetime import datetime
import traceback

# LOCAL IMPORTS
import beautifulDebug
import serverSettings as setting


# stores the last time something was appended to the log
lastlogwrite = None

# appends the text into the logfile specified by setting.LOGFILE_PATH
# returns whether the text could be successfully appended
def log(text):
	# abort if no logfile path or path couldn't be accessed previously
	if (setting.LOGFILE_PATH is None or
		setting.LOGFILE_PATH == "ERROR" or
		setting.LOGFILE_PATH == ""):
		
		return False

	# removing escape characters that look pretty in console but ugly in textfiles
	text = beautifulDebug.removeAnsiEscapeCharacters(text)
	# new line after each entry so a human can read the logfile
	text += "\n"
	
	try:
		# append to logfile
		file = open(setting.LOGFILE_PATH, 'a')

		global lastlogwrite
		dateTimeObj = datetime.now()
		if (lastlogwrite == None):
			# to be able to retrieve SCRIPT_PATH()
			import centralController
			# Nothing was written yet in the logfile this session. Let's start with something nice:
			file.write("Logfile created on " + dateTimeObj.strftime("%Y-%m-%d at %H:%M:%S") + "\n" +
				"Current server script location is " +
				centralController.SCRIPT_PATH() + "\nVerbosity level set to" +
				str(setting.DESIRED_VERBOSITY) + "\n\n")
		# If there is a lastlogwrite value, check if it older than specified in the settings file
		elif (time.time() - lastlogwrite >= setting.LOG_NEW_TIMESTAMP_IF_LAST_ENTRY_OLDER_THAN_S):
			# If so, attach the current timestamp
			file.write("\n" + dateTimeObj.strftime("%H:%M:%S (%Y-%m-%d)") + "\n")
		
		# write the actual log text and close the file
		file.write(text)
		file.close()

		# store when this happened
		lastlogwrite = time.time()

		return True

	except IOError:
		# uh oh, something went wrong... Let's warn the user, but only once this time
		print(beautifulDebug.special(5, 3, 0) +
			f"ERROR accessing/creating logfile at {setting.LOGFILE_PATH}:\n" +
			traceback.format_exc() + beautifulDebug.RESET)
		setting.LOGFILE_PATH = "ERROR"
		return False


# Use outside of websocket connections, where senddebug cannot be utilized. This will only warn on the
# server console and log it. Any client connection will not receive warnings passed to this function!
def warn(text, verbosity = 5):
	if setting.PRINT_COLOR_ANSI_CODES:
		text = beautifulDebug.special(5, 5, 0, text)
	printlog("\n" + text + "\n", verbosity)


# Prints and logs a specified text, optionally according to specified verbosity preferences
def printlog(text, verbosity = None):
	if verbosity is not None:
		if (verbosity < setting.DESIRED_VERBOSITY):
			# Not important enough for the user, discard
			return True

	# Reverse any formatting if the user doesn't want it
	if not setting.PRINT_COLOR_ANSI_CODES:
		text = beautifulDebug.removeAnsiEscapeCharacters(text)
	print(text)
	# Log function does its own removal of formatting, no need to worry about it here
	return log(text)
