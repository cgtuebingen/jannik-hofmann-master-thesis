#!/usr/bin/env python

"""
 This file loggingFunctions.py is part of NeuralVisUAL.
 
 NeuralVisUAL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 NeuralVisUAL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with NeuralVisUAL.  If not, see <https://www.gnu.org/licenses/>.
"""

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

# appends the text into the logfile specified by setting.FILEPATHS.LOGFILE
# returns whether the text could be successfully appended
def log(text, tryToCreateNewFile = True):
	global lastlogwrite
	
	# abort if no logfile path or path couldn't be accessed previously
	if setting.FILEPATHS.LOGFILE is None or \
		setting.FILEPATHS.LOGFILE == "ERROR" or \
		setting.FILEPATHS.LOGFILE == "":
			return False

	# removing escape characters that look pretty in console but ugly in textfiles
	text = beautifulDebug.removeAnsiEscapeCharacters(text)
	# new line after each entry so a human can read the logfile
	text += "\n"
	
	try:
		# append to logfile
		file = open(setting.FILEPATHS.LOGFILE, 'a')

		dateTimeObj = datetime.now()
		if lastlogwrite is None:
			# to be able to retrieve SCRIPT_PATH()
			import centralController
			# Nothing was written yet in the logfile this session. Let's start with something nice:
			file.write("Logfile created on " + dateTimeObj.strftime("%Y-%m-%d at %H:%M:%S") + "\n" +
				"Current server script location is " +
				centralController.SCRIPT_PATH() + "\nVerbosity level set to " +
				str(setting.FORMAT_OUTPUT.DESIRED_VERBOSITY) + "\n\n")
		# If there is a lastlogwrite value, check if it older than specified in the settings file
		elif time.time() - lastlogwrite >= setting.FORMAT_OUTPUT.LOG_TIMESTAMP_AFTER_SECONDS:
			# If so, attach the current timestamp
			file.write("\n" + dateTimeObj.strftime("%H:%M:%S (%Y-%m-%d)") + "\n")
		
		# write the actual log text and close the file
		file.write(text)
		file.close()

		# store when this happened
		lastlogwrite = time.time()

		return True

	except FileNotFoundError:
		if tryToCreateNewFile:
			lastlogwrite = None
			return log(text, tryToCreateNewFile = False) # this avoids infinite recursion
		else:
			# uh oh, something went wrong... Let's warn the user, but only once this time
			print(beautifulDebug.special(5, 3, 0) +
				f"ERROR finding logfile at {setting.FILEPATHS.LOGFILE}:\n" +
				traceback.format_exc() + beautifulDebug.RESET)
			setting.FILEPATHS.LOGFILE = "ERROR"
			return False
	except IOError:
		# uh oh, something went wrong... Let's warn the user, but only once this time
		print(beautifulDebug.special(5, 3, 0) +
			f"ERROR accessing/creating logfile at {setting.FILEPATHS.LOGFILE}:\n" +
			traceback.format_exc() + beautifulDebug.RESET)
		setting.FILEPATHS.LOGFILE = "ERROR"
		return False


# Use outside of websocket connections, where senddebug cannot be utilized. This will only warn on the
# server console and log it. Any client connection will not receive warnings passed to this function!
def warn(text, verbosity = 5):
	if setting.FORMAT_OUTPUT.PRINT_COLOR_ANSI_CODES:
		text = beautifulDebug.special(5, 5, 0, text)
	printlog("\n" + text + "\n", verbosity)


# Prints and logs a specified text, optionally according to specified verbosity preferences
# allowSmartLineBreaks only works if setting.FORMAT_OUTPUT.SMART_LINE_BREAKS is also enabled
def printlog(text, verbosity = None, allowSmartLineBreaks=True):
	if verbosity is not None:
		if verbosity < setting.FORMAT_OUTPUT.DESIRED_VERBOSITY:
			# Not important enough for the user, discard
			return True

	# Reverse any formatting if the user doesn't want it
	if not setting.FORMAT_OUTPUT.PRINT_COLOR_ANSI_CODES:
		text = beautifulDebug.removeAnsiEscapeCharacters(text)
	if setting.FORMAT_OUTPUT.SMART_LINE_BREAKS and allowSmartLineBreaks:
		beautifulDebug.printWithLinebreaks(text, setting.FORMAT_OUTPUT.SMART_LINE_BREAKS)
	else:
		print(text)
	# Log function does its own removal of formatting, no need to worry about it here
	return log(text)
