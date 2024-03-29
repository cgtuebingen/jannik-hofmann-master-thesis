#!/usr/bin/env python

"""
 This file serverCommands.py is part of NeuralVisUAL.
 
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

# This module contains all of the different server command functions that can be executed by a
# connected websocket client (called by websocketServer.py).
# It also contains a few helper functions to manage the commandList, send data, files, debug
# and status messages, and to verify and retrieve parameters sent along with the commands.
# Every command function has a reference stored in the commandList, so that it can be found
# by the websocketServer script.

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
import importlib
import importlib.util
import numpy as np
from types import SimpleNamespace
import ast
import random
import types

# LOCAL IMPORTS
import beautifulDebug
import serverSettings as setting
import websocketServer as server
import aiInteraction as ai
import visualizationFunctions as vis
import loggingFunctions
import loggingFunctions
import debugAndTesting
import visualizationSettings as design
import fileHandling

def onModuleReload(): Request(None, None) # initialize command list

# Seeding random library
random.seed()
# dictionary to translate from string command to function name.
# resulting tuple has function name in the first part and an explanation in the second part,
# optional third part contains details about its recommended usage
commandList = {}
commandListInitialized = False
# In main section, the structure of all values in this dictionary is automatically changed to
# commandList[command_without_spaces] =
# 	(function, verbose_command_with_spaces, explanation, details_about_usage)
preparedCommands = []

# Other definitions / initializations
clientVersionVerifiedAndConnected = False


# The request class is instantiated by every new client command from websocketServer.py
# and stores the websocket connection as well as the command that should be executed
class Request:
	def __init__(self, websocketref, commandref):
		self.websocket = websocketref
		self.command = commandref
		
		# Initializing the command list if that hasn't happened yet:
		global commandList
		global commandListInitialized
		if not commandListInitialized:
			# ensure that commands in the command list do not contain any spaces
			for key in list(commandList.keys()):
				oldCommand = commandList.pop(key)
				# replace spaces in key
				newKey = key.replace(" ", "").lower()
				# New structure: commandList[command_without_spaces] =
				# 	(function, verbose_command_with_spaces, explanation, details_about_usage)
				newStructure = [oldCommand[0], key] + list(oldCommand[1:])
				commandList[newKey] = newStructure
			
			# replace aliases with references to original functions
			for key in list(commandList.keys()):
				oldCommand = commandList.pop(key)
				functionRef = oldCommand[0]
				if type(functionRef) is str and functionRef.startswith("ALIAS:"):
					tmpAliasKey = functionRef[len("ALIAS:"):].replace(" ", "").lower()
					functionRef = commandList[tmpAliasKey][0]
				commandList[key] = [functionRef] + oldCommand[1:]

			# Add command macros to the list
			for (key, value) in setting.COMMANDS.MACROS.items():
				commandList[key.replace(" ", "").lower()] = ["MACRO: " + value, key, "Macro: " + value,
					f'Macro defined by user in server settings. The command "{key}" ' +
					f'will be unpacked and executes "{value}"']
			
			commandListInitialized = True

			ignoreSameBeginningInTheseKeys = {
				# Only add new combinations to this list when you made sure that nobody would put a
				# space after the first word or if you added a check to the shorter command to call
				# the other one if the first parameter is just the next word.
				"py": ["python"],
				"eval": ["evaluate"],
				"serverip": ["serveripport"],
				"tfdrawkernel": ["tfdrawkernels"],
				"servercachedel": ["servercachedelete"],
			}
			for key in list(commandList.keys()):
				clashingCommands = [matches for matches in list(commandList.keys()) if matches.startswith(key) and matches != key]
				if len(clashingCommands) > 0:
					if not(ignoreSameBeginningInTheseKeys.get(key, []) == clashingCommands):
						if len(clashingCommands) == 1:
							warnText = f'Unexpected command clash! Command "{key}" starts in the same way as command "{clashingCommands[0]}"'
						else:
							joinedCommands = '"' + '", "'.join(clashingCommands) + '"'
							warnText = f'Unexpected command clash! Command "{key}" starts in the same way as these commands: {joinedCommands}'
						warnText += "\nPlease make sure that the commands are recognized correctly when the user adds spaces inbetween."
						loggingFunctions.warn(warnText, 2)
	
	def __bool__(self): # to check if a command is not None
		return True

	# Use this function to define command aliases for the same commands
	# originalCommand should be of type str
	def commandAlias(originalCommand):
		return ("ALIAS:" + originalCommand,
			f'Same as the "{originalCommand}" command',
			f'Type "help {originalCommand}" for more information', originalCommand)

	# This functions checks any structure if it contains integer numbers outside of the int64-range
	# If so, it returns False, otherwise True. The structure can contain any combination of data-
	# types, including nested lists, tuples and dictionaries.
	def numbersInRangeOfInt64(self, data):
		if type(data) is list and len(data) == 0:
			return True
		elif type(data) is list and len(data) == 1:
			return self.numbersInRangeOfInt64(data[0])
		elif type(data) is list:
			return all(self.numbersInRangeOfInt64(element) for element in data)
		elif type(data) is tuple:
			return self.numbersInRangeOfInt64(list(data))
		elif type(data) is dict:
			return self.numbersInRangeOfInt64(list(data.keys())) and self.numbersInRangeOfInt64(list(data.values()))
		elif type(data) is int:
			return data >= -(2**63) and data <= 2**63-1
		else:
			return True

	# ensures in a recursive manner that the data is serializable by msgpack
	def makeDataSerializable(self, data):
		acceptedTypes = [str, int, float, bool, bytes, None]
		if type(data) in acceptedTypes:
			return data
		if type(data) is list:
			return [self.makeDataSerializable(item) for item in data]
		if type(data) is tuple:
			return tuple(self.makeDataSerializable(list(data)))
		if type(data) is dict:
			return {self.makeDataSerializable(k):self.makeDataSerializable(v)
				for (k, v) in data.items()}
		else:
			return str(data)

	# Sends the specified message to the websocket client and prints it in console
	# utilizing messagepack and projects data specification.
	# Returns a boolean that signals whether the message was small enough to be sent properly
	async def send(self, data, printText = True, forceDataSerializable = False, sendAlsoAsDebugMsg = False):
		if forceDataSerializable:
			data = self.makeDataSerializable(data)
		
		# check for ints that are too large
		if not self.numbersInRangeOfInt64(data):
			# message contains numbers outside of int64 range
			# Will prevent message from being sent in order to prevent undefined results
			# Caution when changing this debug message! The content of this message should stay
			# below a length of 256 to avoid this message being cut off by the message size checks below
			await self.senddebug(14, f"Error sending message! This message contains numbers outside of " +
				f"the int64 range! Please convert them to float before sending these values!\n" +
				f"Beginning of the message " +
				f"you were trying to send: {str(data)[0:min(256, setting.SERVER.MAX_MESSAGE_SIZE-248)]}...")
			return False

		message_size_too_large = False
		if len(str(data)) > setting.SERVER.MAX_MESSAGE_SIZE:
			# nope, too large to even try packing it. might cause buffer overflow otherwise
			message_size_too_large = len(str(data))
			packed = None
		else:
			# let's try to pack this up with msgpack
			try:
				packed = msgpack.packb(data)
			except:
				if not forceDataSerializable: # try again with forced serialization
					return await self.send(data, printText, forceDataSerializable=True)
				else: # basically raising that error itself again
					packed = msgpack.packb(data)
			if len(packed) > setting.SERVER.MAX_MESSAGE_SIZE:
				# still larger than expected
				message_size_too_large = len(packed)
		
		if message_size_too_large is False: # message can be sent
			if printText is True:
				printText = data
			if sendAlsoAsDebugMsg:
				if printText not in (None, False, ""):
					await self.senddebug(-9, beautifulDebug.removeAnsiEscapeCharacters(str(printText)))
				else:
					await self.senddebug(-9, beautifulDebug.removeAnsiEscapeCharacters(str(data)))
			await self.websocket.send(packed) # actually send it via websocket
			if printText not in (None, False, ""):
				# and print it in the console and debug
				loggingFunctions.printlog("> " + str(printText), -3)
			return True
		else: # message too large to be sent properly!
			# Caution when changing this debug message! The content of this message needs to stay
			# below a length of 256 to avoid recursive loops for very small MAX_MESSAGE_SIZE setting
			await self.senddebug(14, f"Error sending message! This message is {message_size_too_large} " +
				f"bytes long and exceeds the limit of {setting.SERVER.MAX_MESSAGE_SIZE} bytes!\n" +
				f"Content has to be shortened before being sent.\nBeginning of the message " +
				f"you were trying to send: {str(data)[0:min(256, setting.SERVER.MAX_MESSAGE_SIZE-246)]}...")
			return False
	
	# Sends the file specified by path over binary data via msgpack to the websocket client
	# Optionally sends the already specified data and path is only used as the filename
	# File cannot be larger than MAX_MESSAGE_SIZE
	# TODO: chop up large files and send them in chunks to the client
	async def sendfile(self, path, data = None, sendAlsoAsDebugMsg = True):
		assert type(path) is str
		try:
			if data is None:
				# Try to retrieve data from path
				file = open(path, "rb")
				data = file.read()
				file.close()
			else:
				if type(data) is str:
					raise NotImplementedError("You need to pass binary data to sendfile, " +
						"strings are not accepted due to unspecified encoding standard!")
		except:
			# Probably a wrong path
			await self.sendstatus(14, f"File {path} could not be found or opened!")
			return False

		assert type(data) is bytes
		filesize = fileHandling.formatFilesize(data)
		# get the filename itself
		path, filename = fileHandling.separateFilename(path)
		# Structure of a sent file tuple:
		struct = ("FILE", filename, data)
		# Some formatting fun
		#filename = beautifulDebug.underline(filename)
		msg = beautifulDebug.B_GREEN + "Sent file "
		msg += beautifulDebug.special(0, 2, 0) + path + os.path.sep
		msg += beautifulDebug.B_GREEN + filename
		msg += beautifulDebug.special(0, 2, 0) + f" ({filesize})"
		#msg += beautifulDebug.B_GREEN + " via msgpack."
		msg += beautifulDebug.RESET
		return await self.send(struct, printText=msg, sendAlsoAsDebugMsg=sendAlsoAsDebugMsg)

	# Sends a status response to the client. Statuscodes:
	# -30 = success / completed (usually as response to commands that don’t receive data back)
	# -20 = idle / waiting for new commands or for user input 
	# -10 = processing
	# 0 = undefined (or status could not be retrieved)
	# 1 = general warning / something going on, but rectifying (seldom used)
	# 10 = general failure, command cancelled (not further defined which type)
	# 20 = critical failure (this should be always accompanied by a debug message of type 20+)
	# more detailed values can be seen in the documentation
	async def sendstatus(self, level, info,
		errorOnCriticalFailure=True, shutdownByCriticalFailure=True, removeOutsideWhitespace = True):
		
		assert type(level) is int
		info = str(info)

		# create structure according to data specification and send it packed by msgpack
		struct = info
		if removeOutsideWhitespace and len(struct) > 0:
			while (struct[-1].isspace()):
				struct = struct[:-1]
			while (struct[0].isspace()):
				struct = struct[1:]
		if setting.FORMAT_OUTPUT.RESPOND_WITH_COLOR_ANSI_CODES:
			struct = beautifulDebug.formatLevel(level, struct, False, self.command)
		else:
			struct = beautifulDebug.removeAnsiEscapeCharacters(struct)
		
		struct = ("STATUS", level, struct)
		sentSuccessfully = await self.send(struct, False)

		if sentSuccessfully:
			loggingFunctions.printlog(beautifulDebug.formatLevel(level,
				f"> Status (lvl {level}) about {self.command}:\n{beautifulDebug.indent(info, 2)}", False, self.command), verbosity = -2)

		# if chosen, automatically generate error message on encountering a critical error
		if errorOnCriticalFailure and level >= 20:
			await self.senddebug(level, info, shutdownByCriticalFailure)

	# Sends a debug message to the client.
	# decreasing level = less important / more verbose debug info
	async def senddebug(self, level, info, autoShutdownOnCriticalError = True, *,
		sendToClient = True, removeOutsideWhitespace = True):

		assert type(level) is int
		info = str(info)

		if sendToClient:
			# create structure according to data specification and send it packed by msgpack
			struct = info
			if removeOutsideWhitespace:
				while (struct[-1].isspace()):
					struct = struct[:-1]
				while (struct[0].isspace()):
					struct = struct[1:]
			if setting.FORMAT_OUTPUT.RESPOND_WITH_COLOR_ANSI_CODES:
				struct = beautifulDebug.formatLevel(level, struct, True, self.command)
			else:
				struct = beautifulDebug.removeAnsiEscapeCharacters(struct)
			
			struct = ("DEBUG", level, struct)
			sentSuccessfully = await self.send(struct, False)
		else:
			sentSuccessfully = True

		# print if user chosen verbosity level demands it
		if sentSuccessfully and (level >= setting.FORMAT_OUTPUT.DESIRED_VERBOSITY or level == 0):
			if level >= 20: # critical error / failure. shuts down the client system
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> CRITICAL ERROR (lvl {level}) with {self.command}!\n{beautifulDebug.indent(info, 'X ')}", True, self.command))
			elif level >= 10: # error / non-critical exception
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> EXCEPTION (lvl {level}) with {self.command}!\n{beautifulDebug.indent(info, 'X ')}", True, self.command))
			elif level >= 1: # warning
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> WARNING (lvl {level}) about {self.command}!\n{beautifulDebug.indent(info, '! ')}", True, self.command))
			elif level == 0: # undefined
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> Undefined debug message with {self.command}:\n{beautifulDebug.indent(info, 2)}", True, self.command))
			else: # debug
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> Debug info (lvl {level}) about {self.command}:\n{beautifulDebug.indent(info, 2)}", True, self.command))

		# if chosen, automatically shutdown server on encountering a critical error
		if autoShutdownOnCriticalError and level >= 20:
			await server.shutdownServer(self.websocket, "Websocket server is being shut down due to encountering " +
				"a critical error or failure! Connection will be closed and asnycio will no longer " +
				"listen for incoming commands.")


	# Checks if command contains the recommended number of arguments
	# and warns user if extra parameters are ignored or if there's too few
	# Without parameters returns if the command has any parameters
	async def checkParams(self, minCount=None, maxCount=0, warnUser=True):
		if minCount is None:
			return await self.checkParams(1, math.inf, warnUser)

		maxCount = max(minCount, maxCount)
		actualCount = len(self.command.split()) - 1 # actual command doesn't count as parameter
		if actualCount >= minCount and actualCount <= maxCount:
			return True # all well
		elif warnUser:
			# uh oh!
			warningMsg = f"WARNING: Command {self.command.split()[0]} takes "
			if maxCount == math.inf:
				warningMsg += f"at least {minCount} arguments"
			elif maxCount > minCount:
				warningMsg += f"between {minCount} and {maxCount} arguments"
			else:
				warningMsg += f"{minCount} arguments"
			warningMsg += f". You provided {actualCount}."
			if actualCount < minCount:
				warningMsg += " Please specify more arguments for this command!"
			else:
				warningMsg += " Additional parameters will be ignored!"
			await self.senddebug(2, warningMsg)
		return False

	# Retrieves parameter at specified position from whitespace-serparated command.
	# Casts it to specified type (or type of specified default value)
	# If parameter was not provided or cannot be casted, will normally use default
	# Only raises exception if parameter not found/not castable and flag is enabled
	# defaultOrType being a type itself would always raise exception if can't be casted
	# for position=-1 (or no position specified) getParam will return the rest of command as str
	async def getParam(self, position=-1, defaultOrType=str, raiseException=False, warnOnEmptyString=True):
		if position == -1:
			assert defaultOrType is str or type(defaultOrType) is str
			if len(self.command.split()) < 2 and type(defaultOrType) is str:
				return defaultOrType
			try:
				return self.command.split(None, 1)[1]
			except:
				if warnOnEmptyString:
					await self.senddebug(5, f"TYPE WARNING! Couldn't return rest of command {self.command}" +
						" as there don't seem to be any more parameters available! " +
						"getParam will return an empty string.")
				return ""

		actualCount = len(self.command.split()) - 1 # actual command doesn't count as parameter

		try:
			# retrieve type of defaultOrType
			if type(defaultOrType) is type:
				castToType = defaultOrType
			else:
				castToType = type(defaultOrType)
		except:
			raise TypeError("Parameter defaultOrType could not be recognized as valid type!\n" +
				f"Command {self.command.split()[0]}, position {position}, " +
				f"defaultOrType {defaultOrType} of type {defaultOrType.type()}")

		if position > actualCount:
			# too few parameters in command arguments
			if type(defaultOrType) is type or raiseException:
				raise RuntimeError("Not enough parameters given for command " +str(self.command.split()[0])+
					f"! Looking for position {position}, but only found {actualCount} arguments.")
			else:
				return defaultOrType

		try:
			# trying to cast the command parameter string to desired type
			paramValue = self.command.split()[position]
			if type(defaultOrType) is bool or defaultOrType is bool:
				if paramValue in setting.COMMANDS.POSITIVE_PARAMETERS:
					result = True
				elif paramValue in setting.COMMANDS.NEGATIVE_PARAMETERS:
					result = False
				elif type(defaultOrType) is bool:
					result = defaultOrType
				else:
					result = False
			else:
				result = castToType(paramValue)
			return result
		except:
			if type(defaultOrType) is type or raiseException:
				raise TypeError(f"Error casting parameter {self.command.split()[position]} to type " +
					f"{castToType}! No default specified or raiseException was flagged.")
			else:
				await self.senddebug(5, f"TYPE WARNING! Cannot cast parameter " +
					f"{self.command.split()[position]} to type " +
					f"{castToType}! Using default value {defaultOrType}.")
				return defaultOrType



	# COMMAND EXECUTION FUNCTIONS specified in 'commandList'-dictionary
	# general structure: async def {name}(self, **kwargs {, more options}):
	# needs async to be called with await,
	# **kwargs = ignore too many parameters (for flexible number of arguments in other functions)
	# return boolean to specify whether connection to client should be closed after execution

	async def commandNotFound(self, **kwargs):
		await self.sendstatus(11, "ERROR! Command " + self.command + " not recognized!")
		return False

	async def displayhelp(self, helpString = None, **kwargs):
		# Note: In main section, structure of all commandList values was automatically changed to
		# (function, verbose_command_with_spaces, explanation, details_about_usage)
		if await self.checkParams(warnUser=False):
			if helpString is None:
				helpString = await self.getParam()

			HELP_VERBOSE = ("verbose", "all")
			HELP_SEARCH = ("search", "description", "search description")
			HELP_DEEP_SEARCH = ("deepsearch", "deep search", "deep", "usage search", "usagesearch",
				"usage", "search deep", "search usage")
			HELP_VERBOSE = tuple(HELP_VERBOSE)
			HELP_SEARCH = tuple(word + " " for word in HELP_SEARCH)
			HELP_DEEP_SEARCH = tuple(word + " " for word in HELP_DEEP_SEARCH)
			if helpString.startswith(HELP_VERBOSE):
				result = {value[1]:value[2] for (key,value) in commandList.items()}
				await self.senddebug(-1, 'Here are all commands recognized by the python interaction ' +
				'server.\nType "help [command]" for a more detailed explanation of a specific command.\n' +
				'All commands can also be typed without spaces in the command name.')
				await self.sendstatus(-30, "LIST OF ALL AVAILABLE COMMANDS:\n" + beautifulDebug.mapToText(result))
			elif helpString.startswith(HELP_SEARCH) or helpString.startswith(HELP_DEEP_SEARCH):
				# Do a search for descriptions containing this word
				deepSearch = helpString.startswith(HELP_DEEP_SEARCH)
				for word in HELP_SEARCH + HELP_DEEP_SEARCH:
					if helpString.startswith(word):
						helpString = helpString[len(word):]

				result = []

				# Normal search
				if not deepSearch:
					result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower() in value[1].lower() or helpString.lower() in value[2].lower()}
				if len(result) > 0:
					await self.senddebug(-1,
					'Here are all commands recognized by the python interaction ' +
					f'server containing "{helpString}" in their description.\n' +
					'Type "help [command]" for a more detailed explanation of a specific ' +
					'command.\nAll commands can also be typed without spaces in the name.')
					await self.sendstatus(-30, f'LIST OF COMMANDS WITH DESCRIPTION CONTAINING "{helpString}"\n' +
						beautifulDebug.mapToText(result))
					return
				else:
					originalCommand = helpString
					# Try without whitespace
					result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower().replace(" ", "") in value[1].lower().replace(" ", "") or
						helpString.lower().replace(" ", "") in value[2].lower().replace(" ", "")}
					if len(result) > 0:
						helpString = helpString.replace(" ", "")
					else:
						result = {value[1]:value[2] for (key,value) in commandList.items()
							if helpString.lower() in value[1].lower() or
							(helpString.lower() in value[2].lower()) # in case deep skipped this
							or ((len(value) > 3) and (helpString.lower() in value[3].lower()))}
					if len(result) < 1:
						originalCommand = helpString
						helpString = helpString.replace(" ", "")
						result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower() in value[1].lower() or
						(len(value) > 3) and (helpString.lower() in value[3].lower())}
					if len(result) < 1:
						result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower() in value[1].lower().replace(" ", "") or
						(len(value) > 3) and (helpString.lower() in value[3].lower().replace(" ", ""))}
					
					if len(result) > 0:
						await self.senddebug(-1,
						'Here are all commands recognized by the python interaction ' +
						f'server mentioning "{helpString}" in their description or usage.\n' +
						'Type "help [command]" for a more detailed explanation of a specific ' +
						'command.\nAll commands can also be typed without spaces in the name.')
						await self.sendstatus(-30, f'LIST OF COMMANDS MENTIONING "{helpString}"\n' +
							beautifulDebug.mapToText(result))
					else:
						await self.sendstatus(12,
							'Command matching or mentioning "' + originalCommand +
							'" could not be found! ' +
							'Please type "help" for a list of all available commands on this server')
						return False
			else: # command contains a search string
				# Search in 'commandList'-dictionary for the first parameter
				result = commandList.get(helpString.split()[0].lower(), None)

				# If command not found, try eliminating whitespaces consecutively and match it
				originalCommand = helpString
				while(result is None and len(helpString.split()) > 1):
					helpString = helpString.split()[0] + helpString.split(None, 1)[1]
					result = commandList.get(helpString.split()[0].lower(), None)

				if result is not None: # Result found. Printing and sending the detailed explanation
					explanation = 'Detailed explanation for command "' + \
						beautifulDebug.underline(result[1]) + '":\n' + result[2]
					if len(result) > 4:
						originalCommand = result[4].replace(" ", "")
						explanation += ":\n" + commandList[originalCommand][2]
						usageDescription = commandList[originalCommand][3]
					elif len(result) > 3:
						usageDescription = result[3]
					# Replacing '§§§§' or '§§§§ ' in usage details with '"verbose command"' and
					usageDescription = usageDescription.replace('§§', f'"{result[1]}"')
					# Replacing '§§§...§' or '§§§...§ ' in usage details with '"verbose command ..."'
					usageDescription = re.sub('§([^§]*)§', f'"{result[1]} \\1"', usageDescription)
					explanation += "\nUsage: " + usageDescription
					await self.sendstatus(-30, explanation)
				else: # No specific command found. Let's try to filter the list
					# If no command could be found, restore it with whitespaces to avoid confusion
					helpString = originalCommand

					# Try to list all commands that start with this string
					result = {value[1]:value[2] for (key,value) in commandList.items()
						if value[1].startswith(helpString)}
					if len(result) > 0:
						await self.senddebug(-1,
						'Here are all commands recognized by the python interaction ' +
						f'server starting with "{helpString}".\n' +
						'Type "help [command]" for a more detailed explanation of a specific command.\n' +
						'All commands can also be typed without spaces in the command name.')
						await self.sendstatus(-30, f'LIST OF COMMANDS STARTING WITH "{helpString}"\n' +
							beautifulDebug.mapToText(result))
					else:
						# Try to list all commands that contain this string
						result = {value[1]:value[2] for (key,value) in commandList.items()
							if helpString.lower() in value[1].lower()}
						if len(result) < 1:
							# Finally let's try eliminating spaces
							helpString = helpString.replace(" ", "")
							result = {value[1]:value[2] for (key,value) in commandList.items()
								if helpString.lower() in value[1].lower().replace(" ", "")}

						if len(result) > 0:
							await self.senddebug(-1,
							'Here are all commands recognized by the python interaction ' +
							f'server containing "{helpString}".\n' +
							'Type "help [command]" for a more detailed explanation of a specific ' +
							'command.\nAll commands can also be typed without spaces in the name.')
							await self.sendstatus(-30, f'LIST OF COMMANDS CONTAINING "{helpString}"\n' +
								beautifulDebug.mapToText(result))
						else: # Still nothing
							# Let's try further searching for these words
							return await self.displayhelp("search " + helpString)
		else:
			result = {}
			allcommands = '\n' + '\n'.join({value[1] for (key,value) in commandList.items()}) + '\n'
			#print(allcommands)
			for (key,value) in commandList.items():
				cmd = value[1]
				description = value[2]
				if ' ' in cmd:
					firstword = cmd.split(' ')[0]
					groupCount = allcommands.count('\n' + firstword + ' ')
					if groupCount > 1:
						# firstWord is a group
						cmd = firstword + " ..."
						description = f'Group of {groupCount} commands. Type "help {firstword}" for a detailed list'
				result[cmd] = description
			await self.senddebug(-1, 'Here is a concise list of all command groups recognized by the ' +
			'python interaction server.\nType "help all" for a complete list of all individual commands.\n' +
			'Type "help [command]" for a more detailed explanation of a specific command.\n' +
			'All commands can also be typed without spaces in the command name.')
			await self.sendstatus(-30, f'GROUPED LIST OF AVAILABLE COMMANDS\n' +
				beautifulDebug.mapToText(result))
			# await self.sendstatus(-30, "Short list of available commands: " + ", ".join(sorted(commandList.keys()))) # don't need that
	commandList["help"] = (displayhelp,
		"Displays available commands or detailed info about a certain command",
		"§§ Without parameters it will return an array of grouped available commands with their explanation.\n" +
		'Type §all§ for a complete list of all individual available commands.\n' +
		'Type §[command]§ to get more detailed information about a specific command.\n' +
		'Use §search [keyword]§ to search for descriptions matching the specified following string\nUse ' +
		'§deep [keyword]§ to search even the explanations for anything matching the following string\n' +
		'(If no command is found with a specific search, it automatically searches deeper, ' +
		'ending up at a deep search in the end.)')


	async def setverbosity(self, **kwargs):
		await self.checkParams(0, 1)
		if not await self.checkParams(1, 1, False):
			# Just display the current verbosity level
			await self.sendstatus(-30, "Current verbosity level: " + str(setting.FORMAT_OUTPUT.DESIRED_VERBOSITY))
		else:
			newVerbosity = await self.getParam(1, setting.FORMAT_OUTPUT.DESIRED_VERBOSITY)
			if setting.FORMAT_OUTPUT.DESIRED_VERBOSITY == newVerbosity:
				await self.senddebug(-5, f"Server verbosity level is already set at {newVerbosity}.")
			else:
				setting.FORMAT_OUTPUT.DESIRED_VERBOSITY = newVerbosity
				infotext = f"Verbosity level of the server has been changed to {newVerbosity}."
				await self.senddebug(-1, infotext)
				if -1 < setting.FORMAT_OUTPUT.DESIRED_VERBOSITY:
					loggingFunctions.log(infotext)
					# To make sure that at least the logfile logs this change to avoid confusion
					# about missing debug info later on
	commandList["set verbosity"] = (setverbosity, "Displays or sets the desired verbosity level",
		'§§ without parameter displays the current verbosity level of the server.\n' +
		'§[new verbosity level]§ ' +
		'changes the servers verbosity level of debug and status information. Will affect which ' +
		'messages are printed in the console and stored in the logfile.\nThe lower you go the ' +
		'more verbose debug info gets printed. -10 = all debug, 0 = only warnings and errors, ' +
		'3 = ignore mild warnings, 10 = ignore all warnings, 13 = ignore mild errors, 20 = ' +
		'don''t print any non-critical errors.')
	commandList["verbosity"] = commandAlias("set verbosity")


	async def clearScreenInSeconds(self, waitSeconds=0):
		await server.sleep(waitSeconds, "Clear screen command")
		beautifulDebug.clearScreen()


	async def cls(self, **kwargs):
		await self.checkParams(0, 1)
		seconds = await self.getParam(1, 0)
		await self.senddebug(-10, "Screen of the server console output is being cleared in " +
			str(seconds) + " seconds.") # To avoid display of command disconnect output in the freshly
			# cleared window, this yields until the processing of the cls-command has been completed
		asyncio.get_event_loop().create_task(self.clearScreenInSeconds(seconds))
	commandList["cls"] = (cls, "Clears the console output screen",
		'First and only parameter can define in how many seconds the screen will be cleared, ' +
		'defaults to 0\nThen sends cls or clear to the server console, depending on the system')
	commandList["clear"] = commandAlias("cls")


	async def space(self, **kwargs):
		await self.checkParams(0, 1)
		lines = await self.getParam(1, 8)
		loggingFunctions.printlog('\n' * lines, allowSmartLineBreaks=False)
	commandList["space"] = (space, "Prints out empty lines in server console and log",
		'This can be used to visually separate output between commands for easier reading.\n' +
		'Does not respond to the client in any way.\n' +
		'Single parameter specifies how many empty lines should be printed (default 8).')


	async def echo(self, **kwargs):
		await self.sendstatus(-30, await self.getParam(-1, "echo"))
	commandList["test echo"] = (echo, "Echos back text",
		'§§ sends the string "echo", otherwise §[text]§ sends back all text as string' +
		'contained in a status message of type successful (level -30)')


	async def sleeptest(self, **kwargs):
		await self.checkParams(1)
		sleepDuration = await self.getParam(1, 2.0)
		await self.senddebug(-10, "Sleeping now for " + str(sleepDuration) + " seconds.")
		#time.sleep(sleepDuration) # blocks whole thread and doesn't allow other async execution
		await server.sleep(sleepDuration, "Test sleep command, sleeping for " + str(sleepDuration) + " seconds.")
		#await asyncio.sleep(sleepDuration) # allows other async operations to run
		await self.senddebug(-9, "Slept successfully for " + str(sleepDuration) + " seconds.")
	commandList["test sleep"] = (sleeptest, "Sleeps for specified number of seconds",
		"§[float:seconds=2]§ First and only parameter should be of type float, defaults to 2\n" +
		"Sleeping is asynchronous and allows for other commands to be processed in the meantime")


	# should be for debug only. deactivated on connections outside of localhost
	# do not rely on this function for production code via unencrypted connections
	async def python(self, **kwargs):
		if not setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION:
			await self.sendstatus(15, f"Cannot execute {await self.getParam()}. " +
				"Remote code execution is disabled by python websocket server.")
			return False
		if(not(await self.checkParams(1, math.inf))):
			return False
		try:
			result = exec(await self.getParam(), globals())
			if result is None:
				await self.sendstatus(-30, f"Successfully executed code {self.command} in python.")
			else:
				await self.sendstatus(-30, str(result))
		except:
			await self.sendstatus(13, f"ERROR executing code {self.command} in python:\n" +
				traceback.format_exc())
			return False
	commandList["python"] = (python, "Executes the specified string as python code" +
		("" if setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION else " (DISABLED)"),
		"Parameters as string specify the code that will be executed by the server\n" +
		"Due to security reasons, this feature is normally disabled when this server is " +
		"active on the internet via unencrypted connections (outside of localhost)\n" +
		"This command is currently " + ("ENABLED" if setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION else "DISABLED"))
	commandList["py"] = commandAlias("python")


	# should be for debug only. deactivated on connections outside of localhost
	# do not rely on this function for production code via unencrypted connections
	async def pythoneval(self, **kwargs):
		if not setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION:
			await self.sendstatus(15, f"Cannot evaluate {await self.getParam()}. " +
				"Remote code execution is disabled by python websocket server.")
			return False
		if(not(await self.checkParams(1, math.inf))):
			return False
		try:
			result = eval(await self.getParam())
			await self.sendstatus(-30, str(result))
		except:
			await self.sendstatus(13, f"ERROR evaluating expression {self.command} in python:\n" +
				traceback.format_exc())
			return False
	commandList["eval"] = (pythoneval, "Evaluates the specified string as python expression and " +
			"responds with the result" + ("" if setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION else " (DISABLED)"),
			"Parameters as string specify the expression that will be evaluated by the server\n" +
			"Due to security reasons, this feature is normally disabled when this server is " +
			"active on the internet via unencrypted connections (outside of localhost)\n" +
			"This command is currently " + ("ENABLED" if setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION else "DISABLED"))
	commandList["evaluate"] = commandAlias("eval")


	def listCoroutines(self, coroutines = None):
		if coroutines is None:
			coroutines = [desc for (_, desc) in server.yieldingCoroutines]
		result = ""
		alreadyVisited = set()
		for desc in coroutines:
			if not desc.startswith("#HIDDEN\n") and desc not in alreadyVisited:
				if coroutines.count(desc) > 1:
					result += f'\n      {coroutines.count(desc)}x {desc}'
					alreadyVisited.add(desc)
				else:
					result += '\n      ' + desc
		return result

	async def serverInfo(self, *, history, **kwargs):
		await self.checkParams(0)
		text = f"You are connected to the python interaction server, " + \
			f"which is located on {setting.SERVER.IP}:{setting.SERVER.PORT}"
		if len([desc for (_, desc) in server.yieldingCoroutines if not desc.startswith("#HIDDEN\n")]) == 0:
			text += f'\n(No other command coroutines are currently running on the server)'
		else:
			text += f'\nCurrently running command coroutines:' + self.listCoroutines()
		finaloutput = text
		#await self.sendstatus(-30, text, False)
		# if len(history) == 0:
			# # This will never get called, as calling "server info" already is a command from a client
			# text = f"This server is running and waiting for a client to connect. So far, in " + \
			# 	"this session, the server has not yet connected to any client or received any " + \
			# 	"commands. Please start the client and make sure that it connects properly to " + \
			# 	"the servers websocket connection via network with matching IP and port."
			# finaloutput += '\n\n' + text
		if not(ai.tfloaded()):
			text = f"A client has successfully connected and communicated with this server in the current server session.\n" + \
				"No neural network has been loaded in this server session yet (or a loaded one has been reset).\n" + \
				'Use the command "nn load ..." to load a neural network. More info available on typing "help nn load"'
			finaloutput += '\n\n' + text
			#await self.sendstatus(1, text, False)
		else:
			text = f"A neural network has been successfully loaded and initialized on this server."
			#await self.sendstatus(-30, text, False)
			if not hasattr(ai.tfnet, "layoutPositions") or ai.tfnet.layoutPositions is None:
				text = f"The layouting of the initialized neural network has not been calculated yet.\n" + \
				'Use the command "tf draw structure" to execute the force-based algorithm and receive drawing instructions.'
				finaloutput += '\n\n' + text
				#await self.sendstatus(1, text, False)
			else:
				text = f"The layouting for the loaded network has already been calculated and drawn."
				finaloutput += '\n\n' + text
				#await self.sendstatus(-30, text, False)
		await self.sendstatus(-30, finaloutput, False)
	commandList["server info"] = (serverInfo, "Returns IP addess and port of this websocket server",
		'Does not take parameters and responds with a verbose text as status level -30 (successful).\n' +
		'IP and port are returned according to the python server settings')
	commandList["server status"] = commandAlias("server info")


	async def serverIP(self, **kwargs):
		if await self.checkParams(warnUser=False):
			param = await self.getParam(1, str)
			if param.lower() == "port":
				return await self.serverIPPort(warnParameters = False)
		await self.checkParams(0)
		await self.sendstatus(-30, "IP address of this websocket server: " + str(setting.SERVER.IP))
	commandList["server ip"] = (serverIP, "Returns IP address of this websocket server",
		'Does not take parameters and responds with a string.\n' +
		'IP is returned according to the python server settings')


	async def serverPort(self, **kwargs):
		await self.checkParams(0)
		await self.sendstatus(-30, "Port of this websocket server: " + str(setting.SERVER.PORT))
	commandList["server ip"] = (serverIP, "Returns port of this websocket server",
		'Does not take parameters and responds with an integer.\n' +
		'Port is returned according to the python server settings')


	async def serverIPPort(self, *, warnParameters = True, **kwargs):
		if warnParameters:
			await self.checkParams(0)
		await self.sendstatus(-30, "IP and port of this websocket server: " +
			str(setting.SERVER.IP) + ":" + str(setting.SERVER.PORT))
	commandList["server address"] = (serverIPPort, "Returns IP address and port of this websocket server",
		'Does not take parameters and responds with a string.\n' +
		'IP and port are returned according to the python server settings')
	commandList["server ipport"] = commandAlias("server address")


	async def shutdown(self, **kwargs):
		await self.checkParams(0)
		await server.shutdownServer(self.websocket, "Websocket server is being shut down due to request by client.\n" +
			"All running processes and active client connections will be forcibly terminated.\n" +
			"Connection will be closed and asyncio will no longer listen for incoming commands.\n" +
			"Cannot be used to chain commands together! All commands after it will be discarded!")
	commandList["server shutdown"] = (shutdown, "Shuts down the server",
		"No parameters. Will not ask for confirmation!\n" +
		"This will terminate all running processes and client connections forcibly")


	async def restart(self, **kwargs):
		await self.checkParams(0, 1)
		await server.shutdownServer(self.websocket, "Websocket server is being restarted due to request by client.\n" +
			"All running processes and active client connections will be forcibly terminated.\n" +
			"The server will unload any neural network and reset its state to the initial server state.\n"+
			"Cannot be used to chain commands together! All commands after it will be discarded!\n"+
			"Please refer to the python server console to see if re-establishing the server is " +
			'successful or test a second later (with a newly established connection) with ' +
			'"send status"')
		os.execl(sys.executable, *([sys.executable]+sys.argv))
	commandList["server restart"] = (restart, "Restarts and resets the server",
		"No parameters. Will not ask for confirmation!\n" +
		"This will terminate all running processes and client connections forcibly and restart " +
		"the python interaction server. Neural networks will be unloaded and the server resets " +
		"its state to the initial server state.")
	commandList["server reset"] = commandAlias("server restart")


	async def reload(self, **kwargs):
		if not setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION:
			await self.senddebug(15, f"Cannot reload modules! " +
				"Remote code execution is disabled by python websocket server.")
			return False
		modules = await self.getParam(warnOnEmptyString=False)
		modules = modules.split(' ')
		modules = [m.strip() for m in modules if len(m) > 0]
		keepVars = True
		if len(modules) > 0 and modules[0] == "vars":
			keepVars = False
			modules = modules[1:]

		excludePathFragments = ["\\site-packages\\", "\\lib\\"]
		globalVarModules = dict()
		for (name, variable) in globals().items():
			if type(variable) is types.ModuleType and \
				hasattr(variable, "__file__") and \
				all(exclude not in variable.__file__ for exclude in excludePathFragments):
					globalVarModules[name] = variable.__file__
		
		if len(modules) == 0: # Display modules available for reload
			availableModules = globalVarModules
			pythonFiles = os.listdir(os.path.dirname(os.path.realpath(__file__)))
			for file in pythonFiles:
				if file.endswith('.py'):
					availableModules[file[:-3]] = importlib.util.find_spec(file[:-3]).origin
			availableModulesCompact = []
			alreadyCovered = []
			for (name, path) in availableModules.items():
				if name not in alreadyCovered:
					aliases = [name]
					for (name2, path2) in availableModules.items():
						if name != name2 and path == path2:
							# Found same module under different names
							aliases.append(name2)
							alreadyCovered.append(name2)
					availableModulesCompact.append(' = '.join(aliases))
			availableModulesCompact = sorted(availableModulesCompact)
			await self.senddebug(-5, "The following modules have been found and can be reloaded:\n" +
				', '.join(availableModulesCompact))
		else: # reload listed modules
			async def reloadByRef(moduleRef, keepVars):
				if keepVars and 'onModuleReloadVars' in dir(moduleRef):
					moduleVars = moduleRef.onModuleReloadVars()
				importlib.reload(moduleRef)
				if 'onModuleReload' in dir(moduleRef):
					moduleRef.onModuleReload()
				if keepVars and 'onModuleReloadVars' in dir(moduleRef):
					moduleRef.onModuleReloadVars(moduleVars)
				await self.sendstatus(-30, f"Successfully reloaded the {module} module.")
			
			errorsEncountered = False
			for module in modules:
				if module in globalVarModules or importlib.util.find_spec(module) is not None:
					try: # using import_module to receive a module reference from a string
						await reloadByRef(importlib.import_module(module), keepVars)
					except ModuleNotFoundError:
						try: # Trying again with the eval method...
							await reloadByRef(eval(module), keepVars)
						except ModuleNotFoundError:
							await self.sendstatus(10, f"Python cannot find any module named {module}! " +
								'Please type "server reload" to see a list of available modules.')
							errorsEncountered = True
					except:
						await self.sendstatus(11, f"ERROR reloading module {module}!\n" +
							traceback.format_exc())
						errorsEncountered = True
				else:
					await self.sendstatus(10, f"Python cannot find any module named {module}! " +
						'Please type "server reload" to see a list of available modules.')
					errorsEncountered = True
			if errorsEncountered:
				return False
	commandList["server reload"] = (reload, "Reloads certain modules on the server",
		"§§ will list all the modules that can be reloaded and their aliases.\n" +
		"§[modules]§ name as many modules as you want, separated by spaces.\n" +
		"These will then be reloaded by importlib. Note that the loaded AI network " +
		'is located in ai, therefore reloading this module requires again the "nn load" command\n' +
		"Note: When reloading the module serverCommands you cannot chain any other commands " +
		"behind the reload with a & due to the nature of command processing checks" +
		"\nPlease be aware that reloading modules this way might lead to undefined behaviour! " +
		'It is recommended to completely reinitialize the server with "server reset"\n' +
		"Due to security reasons, this feature is normally disabled when this server is " +
		"active on the internet via unencrypted connections (outside of localhost)\n" +
		"By default, modules define variables which they want to keep while the module is being" +
		"reloaded. The value of these variables is restored after the reload. " +
		"(This does not work for the module serverCommands.)\n" +
		"Use §vars [modules]§ to force a reset of the variables in the reloaded modules.\n" +
		"This command is currently " + ("ENABLED" if setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION else "DISABLED"))


	async def stopCoroutines(self, **kwargs):
		await self.checkParams(0)
		stopped = await server.stopCoroutines()
		if len(stopped) == 0:
			await self.senddebug(10, f"Nothing to stop. No stoppable coroutines are currently running or yielding to be stopped")
		elif self.listCoroutines(stopped) == "":
			await self.sendstatus(-30, f"Successfullly stopped {len(stopped)} hidden subroutines, nothing major.")
		else:
			await self.sendstatus(-30, f"Successfully interrupted these processes:" +
				self.listCoroutines(stopped) +
				"\n\nPlease be aware that stopping coroutines this way might lead to undefined behaviour! " +
				'It is recommended to reinitialize the server with "server reset"')
	commandList["server stop"] = (stopCoroutines, "Interrupts all running coroutines",
		"Interrupts all running coroutines that yield to be stopped. This can be used " +
		"to stop command processing that has taken much longer than expected.\n" +
		"It might lead to undefined behaviour, therefore " +
		'it is recommended to reinitialize the server afterwards with the command "server reset"')
	
	def verboseFilecacheInfo(self, deleting=False):
		cachepath = setting.FILEPATHS.FILECACHE
		description = "Deleted " if deleting else "The complete filecache contains "
		description += f"{fileHandling.filecount(cachepath)} " + \
			f"files with a total size of {fileHandling.foldersize(cachepath)}"
		description += " from the filecache, including data from these networks:\n" if deleting \
			else ".\nIt has cached information about the following networks:\n"
		return description + beautifulDebug.mapToText({folder:
			f"{fileHandling.filecount(cachepath, folder)} files / " + str(fileHandling.foldersize(cachepath, folder))
			for folder in fileHandling.getSubdirectories(cachepath)})
	
	async def infoFilecache(self, **kwargs):
		await self.checkParams(0, 0)
		await self.sendstatus(-30, self.verboseFilecacheInfo())
	commandList["server cache info"] = (infoFilecache, "Gives information about the files in the servers filecache",
		"Will print out available information about the files stored in the servers filecache.")
	commandList["server filecache info"] = commandAlias("server cache info")
	
	async def deleteFilecache(self, **kwargs):
		if await self.checkParams(warnUser=False): # specific folder
			folder = await self.getParam()
			folderlist = fileHandling.getSubdirectories(setting.FILEPATHS.FILECACHE)
			if folder not in folderlist:
				folder = folder.strip()
			if folder not in folderlist:
				folders = [f for f in folderlist if f.startswith(folder)]
			else:
				folders = [folder]
			if len(folders) == 0:
				await self.sendstatus(10, f'Cannot find any cache-directory for "{folder}"! ' + \
					'Nothing in the cache has been deleted.\nTo clear the cache of a specific network, ' + \
					'select one of the following directories by typing "server cache delete [directory]": ' + \
					', '.join(folderlist))
				return False
			for folder in folders:
				cachepath = setting.FILEPATHS.FILECACHE
				description = f'Deleted the filecache of the network "{folder}", which contained ' + \
					f"{fileHandling.filecount(cachepath, folder)} files / " + \
					f"{fileHandling.foldersize(cachepath, folder)} of data."
				fileHandling.deleteDirectoryContent(setting.FILEPATHS.FILECACHE + os.path.sep + folder)
				await self.sendstatus(-30, description)
		else: # delete whole cache
			description = self.verboseFilecacheInfo(deleting=True)
			fileHandling.deleteDirectoryContent(setting.FILEPATHS.FILECACHE)
			await self.sendstatus(-30, description)
	commandList["server cache delete"] = (deleteFilecache, "Deletes all files in the servers filecache",
		"Will remove any files that have been stored in the servers filecache path.\n" +
		"Any calculations (like kernel texture renderings) need to be done again.\n" +
		"Use this command if you updated your neural network and are still seeing old versions " +
		"of data in the visualization or if you want to ensure that no old information persists.\n" +
		"Does not ask for confirmation and clears the cache for all networks, not just the current one. " +
		'Please execute the command "server cache info" before, to see what you are deleting.\n' +
		"§[network]§ will only delete the cache of that specific network directory. Available networks: " +
		', '.join(fileHandling.getSubdirectories(setting.FILEPATHS.FILECACHE)) +
		"\nIf you type just the beginning of a network, it matches all directories beginning with that string.")
	commandList["server cache del"] = commandAlias("server cache delete")
	commandList["server filecache delete"] = commandAlias("server cache delete")
	
	
	async def serverDraw(self, **kwargs):
		vis.readyToDraw = True
	commandList["server draw next"] = (serverDraw, "Requests the next batch of object draw instructions",
		"Signals to the server that the client is ready to receive the next drawing instruction\n" +
		"This is used as to not overload the client with too many cuboids at the same time, " +
		"as then drawing instructions might be dropped and ignored.\n" +
		"For performance reasons and to reduce connection overload, this command trigerrs no response!")


	async def sendalot(self, **kwargs):
		await self.checkParams(0, 1)
		await self.sendstatus(-30, "#" * await self.getParam(1, 10))
	commandList["send a lot"] = (sendalot, "Responds with a string of specified length",
		"§[length=10]§ returns a string of the symbol '#' repeated length times.\n" +
		"Can be used to test transmission rate of extremely large messages")


	async def sendfiletest(self, **kwargs):
		if not await self.checkParams(warnUser=False):
			await self.senddebug(1, f"No filepath specified for sendfile test. Sending log file.")
			path = setting.FILEPATHS.LOGFILE
		else:
			path = await self.getParam()
		result = await self.sendfile(path)
		# checking if it was successful or file was too large
		if result is False:
			return False
	commandList["send file"] = (sendfiletest, "Transmits a file at specified path as binary data",
		"§[path]§ path refers to the file location on the server. Absolute paths are " +
		'preferred\nResponds with a struct of type ["FILE", filename, binarydata]')


	async def sendstruct(self, **kwargs):
		struct = (1, 'text', 5.234, (1, 'more', 3, ()), ('b', 'a', 'c'), None, {"hi": 1, "there": 2})
		if await self.checkParams(warnUser=False):
			if setting.COMMANDS.ALLOW_REMOTE_CODE_EXECUTION:
				try:
					struct = eval(await self.getParam())
				except:
					await self.senddebug(10, f"Python cannot evaluate {await self.getParam()} " +
						"as valid structure.")
					return False
			else:
				await self.senddebug(1, f"Cannot evalute parameter {await self.getParam()}. " +
					"Remote code execution is disabled by python websocket server. " +
					"Using default structure.")
		await self.send(struct, sendAlsoAsDebugMsg=True)
	commandList["send struct"] = (sendstruct, "Sends a test structure via msgpack",
		"§[custom structure]§ can define a custom structure to send. If no structure is specified (§§)" +
		"or the provided string cannot be parsed into a structure, a default structure is used")


	async def testdebug(self, **kwargs):
		await self.checkParams(0, 1)
		level = await self.getParam(1, -1)
		text = f"This is a fake debug message of level {level} as " + \
			"requested by the client."
		if level >= 20:
			text += "\nRaising an exception and shutting down the system has been suppressed, " + \
				"although this would normally happen on level 20+"
		await self.senddebug(level, text, False)
	commandList["send debug"] = (testdebug, "Sends a test debug message",
		"§[level=-1]§ defines the level (importance) of that debug message")


	async def teststatus(self, **kwargs):
		await self.checkParams(0, 1)
		if await self.checkParams(1, 1, warnUser=False):
			level = await self.getParam(1, -30)
			text = f"This is a fake status message of level {level} as " + \
				"requested by the client."
			if level >= 20:
				text += "\nRaising an exception and shutting down the system has been suppressed, " + \
					"although this would normally happen on level 20+"
			await self.sendstatus(level, text, False)
		else:
			text = f'You are connected to the python interaction server. ' + \
				f'Type the command "server info" for more information.'
			await self.sendstatus(-30, text, False)
	commandList["send status"] = (teststatus, "Sends a test status message",
		"§[level=-30]§ the level (importance) of that debug message. Defaults to -30 (successful)\n" +
		'Not to be confused with the command "server status" which returns the current state of this server.')


	async def add(self, **kwargs):
		await self.checkParams(2)
		await self.send(await self.getParam(1, 2.0) + await self.getParam(2, 3.0), sendAlsoAsDebugMsg=True)
	commandList["test add"] = (add, "Adds two float numbers",
		"§[float:number=2] [float:number=3]§ responds with the result " +
		"as float\nCan be used for testing purposes")


	async def divide(self, **kwargs):
		await self.checkParams(2)
		await self.send(await self.getParam(1, 2.0) / await self.getParam(2, 3.0), sendAlsoAsDebugMsg=True)
	commandList["test divide"] = (divide, "Divides two float numbers",
		"§[float:number=2] [float:number=3]§ responds with the result " +
		"as float\nCan be used for testing purposes")


	async def console(self, *, loadedCommand, **kwargs):
		await self.checkParams(0)
		await self.sendstatus(-20, "Waiting for console input by user on python script execution server.")
		newcommand = await ainput("Enter your desired command here: ")
		await self.sendstatus(-10, f'Console input received. Continuing with command "{beautifulDebug.underline(newcommand)}"')
		loadedCommand.append(newcommand)
		# old implementation:
		#await server.interactiveServer(self.websocket, path, command=newcommand, dontDebugDisconnect=True)
		return True
	commandList["console"] = (console, "Prompts on the server console for a command",
		'This can be used to inject commands into the pipeline that the server then executes. Waits ' +
		'for the user to type the command while asynchronously processing other incoming commands\n' +
		'This request would then be processed on the original thread, so the client that ' +
		'originally sent the §§ command will receive any debug/status messages and other ' +
		'response that is produced by the executing the command that the user typed in\n' +
		'Type help for a list of available commands')


	async def history(self, *, history, **kwargs):
		if len(history) == 0:
			await self.sendstatus(-30, f"No commands have yet been executed during this server session.")
			return
		fancyHistory = []
		for entry in history:
			if entry[1]:
				fancyHistory.append((beautifulDebug.B_GREEN + entry[0], "successful"))
			else:
				fancyHistory.append((beautifulDebug.B_YELLOW + entry[0], "failed"))
		await self.sendstatus(-30, f"Here is the history of all executed commands in this server session:\n" +
			beautifulDebug.mapToText(fancyHistory, spacing=1, key_width=0.8))
	commandList["history"] = (history, "Lists a history of all executed commands in the server session",
		'Takes no arguments. Also lists whether the commands were successful or not.\n' +
		'For more detailed information about the results and timestamps of the command executions ' +
		'please see the server console output or the servers logfile.')


	async def prepareCommand(self, **kwargs):
		global preparedCommands
		if await self.checkParams(0, 0, False):
			await self.sendstatus(-30, "PREPARED COMMANDS:\n    " + '\n    '.join(preparedCommands))
		else:
			param = await self.getParam()
			param = param.strip()
			if param == "clear" or param=="reset":
				if len(preparedCommands) == 0:
					await self.senddebug(-3, f"List of prepared commands is already empty.")
				else:
					preparedCommands = []
					await self.senddebug(-4, f"List of prepared commands was successfully cleared.")
			else:
				preparedCommands.append(param)
				await self.senddebug(-4, f'Command "{param}" was added to the list of prepared ' +
					'commands. Use "prepare" to review the list or "load" to execute commands from it.')
	commandList["prepare"] = (prepareCommand, "Prepares a command to be executed later",
		'The argument passed a string (containing spaces) will be stored and can be executed by ' +
		'the load command. This is useful for injecting commands into the program pipeline from ' +
		'other clients, e.g. for debugging.\nWarning: This command depends on execution order ' +
		'and might lead to unexpected results when multiple prepare and load commands are ' +
		'executed in the wrong order. Take care when using this in parallel with multiple ' +
		'asynchronously threaded clients.\nFirst in, first out system for multiple commands ' +
		'prepared consecutively when loaded.\nWithout parameters, it will return a list of the ' +
		'currently prepared commands.\nUse §clear§ or §reset§ to clear the list ' +
		'from any loaded commands.\nWith chained commands ' +
		('(currently enabled)' if setting.COMMANDS.AMPERSAND_CHAINS_COMMANDS else '(currently disabled)') +
		', a single & will first prepare the command and then execute anything behind it. A ' +
		'double ampersand will be converted into a prepared chained command, that executes its ' +
		'contents consecutively. To use a ampersand in a string within those commands, escape ' +
		'it as &&&&.\nExample: "prepare echo alone & prepare echo and&&&&and & prepare echo ' +
		'one&&echo two & echo successfully prepared &&-chained commands" will prepare "echo ' +
		'alone", then prepare "echo and&&and" (which just prints out "and&and"), then prepare ' +
		'the double command "echo one & echo two" and finally print out "successfully prepared ' +
		'&-chained commands"')
	

	async def loadCommand(self, *, loadedCommand = None, **kwargs):
		if loadedCommand is None:
			raise TypeError("Function loadCommand needs to be given a list as parameter loadedCommands, otherwise it cannot relay the information of the loaded command! Make sure that the function executing commands has a mutable list parameter for loadedCommands.")
		
		global preparedCommands
		await self.checkParams(0, 1)
		if len(preparedCommands) == 0:
			await self.senddebug(10, f"List of prepared commands is empty. Nothing to load!")
			return False
		else:
			if not self.checkParams(1, 1, False) or \
				not (await self.getParam(warnOnEmptyString=False)).lower().strip() == "keep":
					nextCommand = preparedCommands.pop(0)
					await self.sendstatus(-10, f'Command "{beautifulDebug.underline(nextCommand)}" was ' +
					'loaded and removed from the list of prepared commands. Executing it now.')
			else:
				nextCommand = preparedCommands[0]
				await self.sendstatus(-10, f'Command "{beautifulDebug.underline(nextCommand)}" was ' +
				'loaded from the list of prepared commands without removing it from there. Executing it now.')
			loadedCommand.append(nextCommand)
			return True
	commandList["load"] = (loadCommand, "Loads and executes the oldest prepared command",
		'Does not take any arguments. Loads the oldest command from the list of prepared commands, ' +
		'executes it on the current client connection and removes it from the list.\n' +
		'Use §§ to check the list. See more info on the prepare and loading mechanism with "help prepare"\n' +
		'§keep§ loads the oldest prepared command without consuming it. ' +
		'This way you can repeatedly load the same command')
	

	SEVERE_WARNING_LEVEL = 20
	SUPPRESSED_WARNING_LEVEL = 19
	async def checkScriptVersion(self, **kwargs):
		await self.checkParams(1, 2)
		if not await self.checkParams(warnUser=False):
			await self.sendstatus(-30, "SERVER SCRIPT VERSION: " + str(server.PYTHON_INTERACTION_SCRIPT_VERSION))
			return
		criticalWarning = True
		if await self.checkParams(2, math.inf, False):
			criticalWarning = not((await self.getParam(2, "True")) in setting.COMMANDS.NEGATIVE_PARAMETERS)
		if criticalWarning:
			warningLevel = self.SEVERE_WARNING_LEVEL
			shutdownText = "Terminating the connection and shutting down the server."
		else:
			warningLevel = self.SUPPRESSED_WARNING_LEVEL
			shutdownText = "Further code execution is not recommended and " + \
				"might lead to undefined behaviour. Proceed with caution."
		clientVersion = await self.getParam(1, str)
		if re.fullmatch("[\\da-zA-Z]+\\.[\\da-zA-Z]+\\.[\\da-zA-Z]+", clientVersion) is None:
			await self.sendstatus(6, f"Client version {clientVersion} does not match the expected " +
				"version template [major].[minor].[build] Cannot compare versions correctly!")
			return False
		if re.fullmatch("[\\da-zA-Z]+\\.[\\da-zA-Z]+\\.[\\da-zA-Z]+", server.PYTHON_INTERACTION_SCRIPT_VERSION) is None:
			await self.sendstatus(6, f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does not " +
				"match the expected version template [major].[minor].[build] Cannot compare versions " +
				"correctly!")
			return False
		cmajor, cminor, cbuild = clientVersion.split(".")
		smajor, sminor, sbuild = server.PYTHON_INTERACTION_SCRIPT_VERSION.split(".")
		# Compare major version
		if cmajor != smajor:
			if re.fullmatch("\\d+", cmajor) is None or re.fullmatch("\\d+", smajor) is None:
				await self.sendstatus(warningLevel,
					f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does " +
					f"not match major of client version {clientVersion}.\n" +
					f"Commands cannot be executed properly!\n" +
					shutdownText + "\n" +
					f"Please use a similar version on both ends.")
				return False
			else:
				if int(cmajor) > int(smajor):
					await self.sendstatus(warningLevel,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} is " +
						f"too low for client({clientVersion}).\n" +
						f"Commands cannot be executed properly!\n" +
						shutdownText + "\n" +
						f"Please update the server or use a similar client version.")
					return False
				if int(cmajor) < int(smajor):
					await self.sendstatus(warningLevel,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} is " +
						f"too high for client({clientVersion}).\n" +
						f"Major version differences might lead to unexpected behaviour due to varying " +
						f"implementation!\n" +
						shutdownText + "\n" +
						f"Please update the client or use a similar server version.")
					return False
		# Compare minor version
		elif cminor != sminor:
			if re.fullmatch("\\d+", cminor) is None or re.fullmatch("\\d+", sminor) is None:
				await self.sendstatus(warningLevel,
					f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does " +
					f"not match minor of client version {clientVersion}.\n" +
					f"Commands might not be executed properly!\n" +
					shutdownText + "\n" +
					f"Please use a similar version on both ends.\n" +
					f"Note: A higher minor version in the server is accepted. However, as the minor " +
					f"versions are not numerical, they cannot be compared.\n" +
					f"Please use numerical versions if you want to have more flexibility.")
				return False
			else:
				if int(cminor) > int(sminor):
					await self.sendstatus(warningLevel,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} is " +
						f"too low for client({clientVersion}).\n" +
						f"Commands cannot be executed properly!\n" +
						shutdownText + "\n" +
						f"Please update the server or use a similar client version.")
					return False
				if int(cminor) < int(sminor):
					await self.sendstatus(6,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} has " +
						f"higher minor version than client({clientVersion}).\n" +
						f"This should not be an issue, if only minor features have been added. " +
						f"However, it is advised to update the client version to a similar build.")
		# Compare build version
		elif cbuild != sbuild:
			if re.fullmatch("\\d+", cbuild) is None or re.fullmatch("\\d+", sbuild) is None:
				await self.sendstatus(4,
					f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does " +
					f"not match build of client version {clientVersion}.\n" +
					f"This should not be an issue, if only minor details have been changed. " +
					f"However, it is advised to use matching software versions on both ends.")
			else:
				if int(cbuild) > int(sbuild):
					await self.sendstatus(4,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} has " +
						f"a lower build number than client version {clientVersion}.\n" +
						f"This should not be an issue, if only minor details have been changed. " +
						f"However, it is advised to update the server to a matching version.")
				if int(cbuild) < int(sbuild):
					await self.sendstatus(2,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} has " +
						f"a higher build number than client version {clientVersion}.\n" +
						f"This should not be an issue, if only minor details have been changed. " +
						f"However, it is advised to update the client to a matching version.")
		else:
			await self.sendstatus(-30,
				f"Server and client versions {server.PYTHON_INTERACTION_SCRIPT_VERSION} match perfectly.")
	commandList["check version"] = (checkScriptVersion, "Compares and checks server and client versions",
		'§§ returns the version of the server script as a string.'+
		'\n§[version]§ is expected to be the client script version for asserting compatibility.\n' +
		'The version is passed as a string of type major.minor.build\nmajor, minor and build can ' +
		'contain only digits or letters.\nIf major version differs or clients minor version is higher ' +
		'then the servers minor version (or if any minor version contains letters and is different), ' +
		'the check will fail and throw an error of level ' + str(SEVERE_WARNING_LEVEL) +
		', shutting down the server to prohibit ' +
		'undefined behaviour with unexpected errors due to differing implementations in updates.\n' +
		'This check can be overridden with a negative second parameter, which lowers the warning level ' +
		'to ' + str(SUPPRESSED_WARNING_LEVEL) + '. (Negative parameters are: ' +
		', '.join(setting.COMMANDS.NEGATIVE_PARAMETERS) + ')\nLower minor version in the client or differing build ' +
		'will only display a low level warning and pass the check.\n' +
			('If this check is used and fails while chaining commands with ampersand (' +
			('enabled' if setting.COMMANDS.AMPERSAND_CHAINS_COMMANDS else 'disabled') +
			'), execution will carry on regardless due to server settings.'
		if setting.COMMANDS.EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE else
			'This check can be used when chaining commands with ampersand (' +
			('enabled' if setting.COMMANDS.AMPERSAND_CHAINS_COMMANDS else 'disabled') + '), ' +
			'as the chain will only continue if the check is passed.'))
	commandList["assert version"] = commandAlias("check version")
	commandList["verify version"] = commandAlias("check version")



	# NEURAL NETWORK INTERACTION
	async def loadnn(self, **kwargs):
		if ai.nnloaded or ai.nnprepared:
			await self.senddebug(9, f'The server has already loaded another network. It is ' +
			'recommended to use "server reset" before loading another network, to avoid ' +
			'undefined behaviour!')
		if not await self.checkParams(warnUser=False):
			path = setting.FILEPATHS.NN_LOAD_DEFAULT_MODEL
			await self.senddebug(5, f"No custom path for the neural network was specified. " +
			"Using default path specified in python server script: " + path)
		else:
			path = await self.getParam()
		# Try to match with a predefined path from server settings
		path = setting.FILEPATHS.AVAILABLE_MODELS.get(path, path)
		
		try:
			await self.sendstatus(-10, f'Neural network at "{path}" is being loaded. This might ' +
				"take a while. Please view the python console for further information and loading details.")
			await server.sleep(0.1, "Loading neural network")
			# make sure other async tasks have a chance to be executed before blocking main
			# thread for a while (so that the previous status mesage gets send properly)
			result = ai.preparemodule(path, True)
		except asyncio.CancelledError:
			raise asyncio.CancelledError
		except:
			await self.sendstatus(15, f'ERROR finding or loading python script at specified location "{path}":\n' +
				traceback.format_exc())
			return False
		if type(result) is str and len(result):
			await self.sendstatus(15, f'ERROR loading python script at specified location "{path}":\n' + result)
			return False
		
		await server.sleep(0.1, "Initializing neural network")
		# make sure other async tasks have a chance to be executed before blocking main
		# thread for a while (so that the previous status mesage gets send properly)
		try:
			if ai.preparedModuleIsTf():
				ai.importtf()
			await self.sendstatus(-30, f"Neural network at {path} has been successfully loaded and " +
				"executed.")
		except:
			await self.sendstatus(15, f"ERROR loading Neural Network from script {path}:\n" +
				traceback.format_exc())
			return False
	commandList["nn load"] = (loadnn, "Loads a neural network at the given path",
		"§[path]§ specify the location of the python script on the server. " +
		"This script is then imported and loaded by python.\n" +
		"Use a keyword as parameter to load one of the networks specified in server settings.\n" +
		'Available keywords are: "' + '", "'.join(setting.FILEPATHS.AVAILABLE_MODELS.keys()) + '"')


	async def isnnloaded(self, calledDirectlyByCommand=False, **kwargs):
		await self.send(ai.tfloaded(), sendAlsoAsDebugMsg=calledDirectlyByCommand)
		if not(ai.tfloaded()):
			return False
	commandList["nn is loaded"] = (isnnloaded, "Checks if any NN is loaded and initialized",
		"Returns a boolean saying whether any neural network has been " +
		"loaded and initialized successfully, can be used for assertion to chain commands")

	# For internal use, not a command. Use the following code line in any function to only let
	# execution continue if a tf has been loaded and initialized successfully:
	#if not await self.assertTf(): return False
	async def assertTf(self, **kwargs):
		if not ai.nnloaded:
			await self.sendstatus(18, f"Network hasn't been loaded and initialized yet!\n" +
			'Use "nn load" to initialize a network. See "help nn load" for more info.')
			return False
		if not ai.tfloaded:
			await self.sendstatus(18, f"Network is not Tensorflow, tf-specific functions can't be used!")
			return False
		return True

	async def tf_getversion(self, **kwargs):
		if not await self.assertTf(): return False
		try:
			v = ai.tfversion()
			await self.send(v)
			await self.sendstatus(-30, "Using tensorflow version " + str(v))
		except:
			await self.sendstatus(16, f"Couldn't retrieve tensorflow version!\n" +
				traceback.format_exc())
			return False
	commandList["tf get version"] = (tf_getversion, "Gets tensorflow version of loaded neural network",
		"Returns a string with the version number")


	async def tf_getstructure(self, printStructure=True, canUseFakeStructure=None, **kwargs):
		if canUseFakeStructure is None:
			canUseFakeStructure = hasattr(setting, "DEBUG") and getattr(setting.DEBUG, "USE_FAKE_STRUCTURE", False)
		
		if not canUseFakeStructure:
			if not await self.assertTf(): return False
		try:
			if canUseFakeStructure and not ai.tfloaded():
				structure = debugAndTesting.const_fake_structure
			else:
				structure = ai.tfmodelsummary()
				if printStructure:
					await self.senddebug(-8, "Structure of the network:\n" +
						ai.makeModelSummaryReadable(structure))
		except:
			await self.sendstatus(16, f"Couldn't retrieve tensorflow structure!\n" +
				traceback.format_exc())
			return False
		
		try:
			successful = await ai.parsestructure(self, structure)
			if not successful:
				# parestructure couldn't find valid structure. It has already output debug errors
				# Just need to quit this function at this point
				return False
			else:
				if printStructure:
					printText = '("TF STRUCTURE",\n'
					for layer in ai.tfnet.layers:
						printText += '    ' + str(layer) + ',\n'
					printText = printText[:-2]
					printText += ')'
					# Send the whole structure as array
					await self.send(("TF STRUCTURE", ai.tfnet.layers), sendAlsoAsDebugMsg=True, printText = printText)
		except:
			await self.sendstatus(17, f"Couldn't parse tensorflow structure!\n" +
				traceback.format_exc())
			return False
	commandList["tf get structure"] = (tf_getstructure, "Retrieves tensorflow network structure",
		'Response has the following form:\n' +
		'["TF STRUCTURE", [layer_name, type, [dimensions]]*]\n' +
		'* This array is repeated as many times as there are layers in the network, and then ' +
		'packaged into an array of itself\n' +
		'layer_name and type are strings retrieved from tensorflow. dimensions usually have ' +
		'nil/None as their first value due to tensorflow standards with dynamic batch sizes')
	commandList["tf get layers"] = commandAlias("tf get structure")


	async def tf_drawstructure(self, **kwargs):
		if not hasattr(ai.tfnet, "layoutPositions") or ai.tfnet.layoutPositions is None:
			successful = await self.tf_getstructure(printStructure=False)
			if successful == False:
				# parestructure couldn't find valid structure. It has already output debug errors
				# Just need to quit this function at this point
				return False
			await self.sendstatus(-10, f"Layouting for the network structure is being calculated.\n" +
				"This might take a minute... (you can see a progress bar in the python server console)")
			if design.layouting.renderGif.displayPlot * design.layouting.renderGif.framesInAnimation > 0:
				await self.sendstatus(1, "Visualization settings have layouting.renderGif.displayPlot enabled.\n" +
					"That means, the layouting algorithm opens an animated plot on the python server,\n" +
					"which needs to be closed manually after completion, before the layout can be sent via websocket.")
		try:
			await vis.drawstructure(self) # Includes layouting calculations
		except asyncio.CancelledError:
			raise asyncio.CancelledError
		except:
			await self.sendstatus(17, f"Couldn't draw tensorflow structure!\n" +
				traceback.format_exc())
			return False
	commandList["tf draw structure"] = (tf_drawstructure, "Creates quads for tensorflow network structure",
		'Will send a quad drawing instruction for each layer of the neural network to display the ' +
		'DNN in the game engine.\n' +
		'Layers will be layouted with the modified forceatlas2-algorithm using the visualization settings.')
	commandList["tf draw layers"] = commandAlias("tf draw structure")


	async def tf_resetstructure(self, **kwargs):
		if not await self.assertTf(): return False
		await self.checkParams(0)
		ai.tfresetstructure()
		await self.sendstatus(-30, f"Saved structure information of the loaded tf network has been reset.")
	commandList["tf reset structure"] = (tf_getstructure, "Resets the stored tensorflow network structure",
		'Takes no parameters. Just resets the stored structure information of tfnet.')


	async def tf_getvars(self, **kwargs):
		if not await self.assertTf(): return False
		await self.checkParams(0, 1)
		global tfNetwork
		if await self.checkParams(1, 1, False):
			attr = await self.getParam(1, str, True)
			if attr.lower() == "overview":
				return await self.sendstatus(-30, "Available variables in the currently loaded network:\n" +
					beautifulDebug.mapToText(vars(ai.tfnet), 3, treatValues=beautifulDebug.shortenVar))
			try:
				await self.send(getattr(ai.tfnet, attr), sendAlsoAsDebugMsg=True)
			except:
				await self.senddebug(12, f"Attribute {attr} does not (yet) exist in tfNetwork. " +
					f"Sending back None as value for {attr}.")
				await self.send(None)
				return False
		else:
			await self.send(vars(ai.tfnet), sendAlsoAsDebugMsg=True,
				printText=beautifulDebug.mapToText(vars(ai.tfnet), treatValues=beautifulDebug.shortenVar))
	commandList["tf get vars"] = (tf_getvars, "Returns all tf variables and information currently loaded",
		"Retrieves any information already known about the loaded tensorflow network.\n" +
		"Returns a map of the continually expanding class type that stores information about the " +
		"neural network\nThis data is continually expanded by more commands and information requests.\n" +
		"§[varname]§ only gives back the requested variable.\n§OVERVIEW§ returns a list of available vars " +
		"that can be read by humans due to capped output")


	async def tf_refreshtrainablevars(self, returnShapeDict=False, calledDirectlyByCommand=False, **kwargs):
		if not await self.assertTf(): return False
		await self.checkParams(0, 1, warnUser=calledDirectlyByCommand)
		printVars = await self.getParam(1, False, warnOnEmptyString=calledDirectlyByCommand)
		if not hasattr(ai.tfnet, "validstructure") or ai.tfnet.validstructure == False:
			await self.sendstatus(-10, f"Structure of the network hasn't been retrieved yet. Doing that first...")
			success = await self.tf_getstructure(False, False)
			if success == False:
				await self.sendstatus(17, f"Cannot proceed to trainable variables due to invalid parsing of network structure.")
				return False
			
		shapeDict = ai.tfRefreshTrainableVars()
		if printVars:
			debugMsg = "The following trainable variable shapes have been retrieved {{index:layername, kernelshape}}:\n" +\
				beautifulDebug.mapToText(shapeDict, 1)
			await self.sendstatus(-30, debugMsg)
		await self.sendstatus(-30, f"Trainable variables of the loaded tf network have been retrieved and stored.")
		if returnShapeDict:
			return shapeDict
	commandList["tf get train vars"] = (tf_refreshtrainablevars,
		"Retrieves and stores all trainable variables available in the network.",
		"All trainable tensorflow variables are retrieved and stored temporarily.\n" +
		"$[respond=False]$ If respond is positive, the var shapes will be sent as response")
	commandList["tf get trainable vars"] = commandAlias("tf get train vars")
	commandList["tf get trainable variables"] = commandAlias("tf get train vars")


	async def tf_drawkernel(self, **kwargs):
		if not await self.assertTf(): return False
		if not await self.checkParams(0, 2): return False
		precacheAll = (await self.getParam(warnOnEmptyString=False)).lower() == "all"
		if precacheAll:
			index = -1
		else:
			index = await self.getParam(1, -1, warnOnEmptyString=False)
			refresh = await self.getParam(2, False, warnOnEmptyString=False)
		if index == -1: # just printing out all kernel shapes without drawing anything
			await self.sendstatus(-10, f"Refreshing trainable variables of the network...")
			shapeDict = await self.tf_refreshtrainablevars(returnShapeDict=True)
			shapeDict = {name.replace('/kernel:0', ''): str(shape) for (name, shape) in shapeDict.items() if '/kernel:0' in name}
			debugMsg = "The following kernel shapes have been retrieved {{index:layername, kernelshape}}:\n" + \
				beautifulDebug.mapToText(shapeDict, 1)
			await self.sendstatus(-30, debugMsg)
			if precacheAll:
				for key in shapeDict.keys():
					index = int(key.split(':')[0])
					try:
						await vis.drawKernels(self, index, canUseCachedFile=True, draw=False)
						server.sleep(0.1, "Checking and drawing all kernel textures. Currently at layer " + str(index))
					except asyncio.CancelledError:
						raise asyncio.CancelledError
			return
		if refresh or not hasattr(ai.tfnet, "validstructure"):
			if refresh:
				await self.sendstatus(-10, f"Refreshing trainable variables of the network first...")
			else:
				await self.sendstatus(-10, f"Trainable variables of the network haven't been retrieved yet. Doing that first...")
			success = await self.tf_refreshtrainablevars()
			if success == False:
				await self.sendstatus(17, f"Cannot proceed to drawing kernels due to failure of retrieving trainable variables.")
				return False
		if ai.tfnet.validstructure == False or len(vis.Layer.layerList) == 0:
			await self.sendstatus(17, f"The structure of the network hasn't even been drawn yet!\n" +
			'Use "tf draw structure" to render the network itself before any kernels can be visualized.')
			return False
		try:
			await vis.drawKernels(self, index, canUseCachedFile=not refresh)
		except asyncio.CancelledError:
			raise asyncio.CancelledError
		except:
			await self.sendstatus(17, f"Couldn't draw kernel data!\n" +
				traceback.format_exc())
			return False
	commandList["tf draw kernel"] = (tf_drawkernel, "Creates quads for tensorflow network kernels",
		'§§ will just refresh trainable vars print out all kernel shapes without drawing anything.\n' +
		'§[int:index]§ will respond with drawing instructions for all kernel data of the neural ' +
		'network layer with that index to display it in the game engine.\n' +
		'§[int:index] [refresh=False]§ If refresh is true or no kernel data can be found, ' +
		'data of trainable variables will be refreshed first and kernel will be recalculated.\n' +
		"§all§ will recalculate and cache all kernel textures that have not been cached yet without drawing")
	commandList["tf draw kernels"] = commandAlias("tf draw kernel")

	async def tf_drawkernelactivations(self, **kwargs):
		layerIndex = await self.getParam(1, 0)
		selection = await self.getParam(2, -1)
		if selection == -1:
			selection = None
		input = await self.getParam(3, setting.DEBUG.DEFAULT_INPUT_IMAGE)
		await vis.drawKernelActivations(self, layerIndex, selection, input)
	commandList["tf draw activations"] = (tf_drawkernelactivations, "Draws the activations of a certain kernel",
		'TODO')

	async def tf_drawinputprediction(self, **kwargs):
		input = await self.getParam(1, setting.DEBUG.DEFAULT_INPUT_IMAGE)
		await vis.drawInputPrediction(self, input)
	commandList["tf draw prediction"] = (tf_drawinputprediction, "Draws the prediction resulting from a given input",
		'TODO')

	async def tf_drawsaliency(self, **kwargs):
		index = await self.getParam(1, "-1")
		input = await self.getParam(2, setting.DEBUG.DEFAULT_INPUT_IMAGE)
		await vis.drawSaliency(self, input, index)
	commandList["tf draw saliency"] = (tf_drawsaliency, "Draws the saliency map for a certain output",
		'TODO')

	async def tf_drawgradients(self, **kwargs):
		index = await self.getParam(1, "-1")
		input = await self.getParam(2, setting.DEBUG.DEFAULT_INPUT_IMAGE)
		await vis.drawGradients(self, input, index)
	commandList["tf draw gradients"] = (tf_drawgradients, "Draws the integrated gradients for a certain output",
		'TODO')
