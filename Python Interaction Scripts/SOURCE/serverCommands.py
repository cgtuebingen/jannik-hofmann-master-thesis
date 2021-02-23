#!/usr/bin/env python

# This module contains all of the different server command functions that can be executed by a
# connected websocket client (called by websocketServer.py).
# It also contains a few helper functions to manage the commandList, send data, files, debug
# and status messages, and to verify and retrieve parameters sent along with the commands.
# Every command function has a reference stored in the commandList, so that it can be found
# by the websocketServer script.
# This module also contains the interaction of the server with the imported tensorflow and
# pytorch neural networks. It takes care of loading them, calculating predictions, as well as
# retrieving weight data and meta information about the architectures.

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

# LOCAL IMPORTS
import serverSettings as setting
import websocketServer as server
import loggingFunctions
import beautifulDebug
import loggingFunctions
import visualizationSettings


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
nnSuccessfullyLoaded = False
nn_spec = None
nn_module = None
tfNetwork = SimpleNamespace()
pytorchNetwork = SimpleNamespace()
tf = None


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
				newKey = key.replace(" ", "")
				commandList[newKey] = (oldCommand[0], key) + oldCommand[1:]
				# New structure: commandList[command_without_spaces] =
				# 	(function, verbose_command_with_spaces, explanation, details_about_usage)
			
			# replace aliases with references to original functions
			for key in list(commandList.keys()):
				oldCommand = commandList.pop(key)
				functionRef = oldCommand[0]
				if type(functionRef) is str and functionRef.startswith("ALIAS:"):
					tmpAliasKey = functionRef[len("ALIAS:"):].replace(" ", "")
					functionRef = commandList[tmpAliasKey][0]
				commandList[key] = (functionRef,) + oldCommand[1:]
			commandListInitialized = True

			ignoreSameBeginningInTheseKeys = {
				"py": ["python"],
				"eval": ["evaluate"],
				"serverip": ["serveripport"],
			}

			for key in list(commandList.keys()):
				clashingCommands = [matches for matches in list(commandList.keys()) if matches.startswith(key) and matches != key]
				if (len(clashingCommands) > 0):
					if not(ignoreSameBeginningInTheseKeys.get(key, []) == clashingCommands):
						if (len(clashingCommands) == 1):
							warnText = f'Unexpected command clash! Command "{key}" starts in the same way as command "{clashingCommands[0]}"'
						else:
							joinedCommands = '"' + '", "'.join(clashingCommands) + '"'
							warnText = f'Unexpected command clash! Command "{key}" starts in the same way as these commands: {joinedCommands}'
						warnText += "\nPlease make sure that the commands are recognized correctly when the user adds spaces inbetween."
						loggingFunctions.warn(warnText, 2)


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

	# Sends the specified message to the websocket client and prints it in console
	# utilizing messagepack and projects data specification.
	# Returns a boolean that signals whether the message was small enough to be sent properly
	async def send(self, data, printhere=True):
		# check for ints that are too large
		if not self.numbersInRangeOfInt64(data):
			# message contains numbers outside of int64 range
			# Will prevent message from being sent in order to prevent undefined results
			# Caution when changing this debug message! The content of this message should stay
			# below a length of 256 to avoid this message being cut off by the message size checks below
			await self.senddebug(14, f"Error sending message! This message contains numbers outside of " +
				f"the int64 range! Please convert them to float before sending these values!\n" +
				f"Beginning of the message " +
				f"you were trying to send: {str(data)[0:min(256, setting.MAX_MESSAGE_SIZE-248)]}...")
			return False

		message_size_too_large = False
		if (len(str(data)) > setting.MAX_MESSAGE_SIZE):
			# nope, too large to even try packing it. might cause buffer overflow otherwise
			message_size_too_large = len(str(data))
			packed = None
		else:
			# let's try to pack this up with msgpack
			packed = msgpack.packb(data)
			if (len(packed) > setting.MAX_MESSAGE_SIZE):
				# still larger than expected
				message_size_too_large = len(packed)
		
		if (message_size_too_large is False): # message can be sent
			await self.websocket.send(packed) # actually send it via websocket
			if (printhere): # and print it in the console
				loggingFunctions.printlog("> " + str(data), -3)
			return True
		else: # message too large to be sent properly!
			# Caution when changing this debug message! The content of this message needs to stay
			# below a length of 256 to avoid recursive loops for very small MAX_MESSAGE_SIZE setting
			await self.senddebug(14, f"Error sending message! This message is {message_size_too_large} " +
				f"bytes long and exceeds the limit of {setting.MAX_MESSAGE_SIZE} bytes!\n" +
				f"Content has to be shortened before being sent.\nBeginning of the message " +
				f"you were trying to send: {str(data)[0:min(256, setting.MAX_MESSAGE_SIZE-246)]}...")
			return False
	
	# Sends the file specified by path over binary data via msgpack to the websocket client
	# Optionally sends the already specified data and path is only used as the filename
	# File cannot be larger than MAX_MESSAGE_SIZE
	# Todo: chop up large files and send them in chunks to the client
	async def sendfile(self, path, data = None):
		assert type(path) is str
		try:
			if data is None:
				# Try to retrieve data from path
				file = open(path, "rb")
				data = file.read()
				file.close()
			else:
				if (type(data) is str):
					raise NotImplementedError("You need to pass binary data to sendfile, " +
						"strings are not accepted due to unspecified encoding standard!")
		except:
			# Probably a wrong path
			await self.sendstatus(14, f"File {path} could not be found or opened!")
			return False

		assert type(data) is bytes
		# only remember the filename itself. Client doesn't care about the servers folder structure
		filename = re.split(r"[\\/]", path)[-1]
		# Structure of a sent file tuple:
		struct = ("FILE", filename, data)
		sentSuccessfully = await self.send(struct, False)
		if (sentSuccessfully):
			# Some formatting fun
			filename = filename.replace("_",
				beautifulDebug.DISABLE_UNDERLINE + "_" + beautifulDebug.UNDERLINE)
			path = beautifulDebug.special(0, 1, 0) + path.replace(filename, #beautifulDebug.UNDERLINE +
				beautifulDebug.B_GREEN + filename #+ beautifulDebug.DISABLE_UNDERLINE
				)
			msg = beautifulDebug.B_GREEN + "> Sent file " + path + \
				beautifulDebug.special(0,3,0) + " (" + len(data) + " bytes)" + \
				beautifulDebug.B_GREEN + " via msgpack." + beautifulDebug.RESET
			loggingFunctions.printlog(msg, -2)
		
		return sentSuccessfully

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
		assert type(info) is str

		# create structure according to data specification and send it packed by msgpack
		struct = info
		if removeOutsideWhitespace and len(struct) > 0:
			while (struct[-1].isspace()):
				struct = struct[:-1]
			while (struct[0].isspace()):
				struct = struct[1:]
		if (setting.RESPOND_WITH_COLOR_ANSI_CODES):
			struct = beautifulDebug.formatLevel(level, struct, False, self.command)
		else:
			struct = beautifulDebug.removeAnsiEscapeCharacters(struct)
		
		struct = ("STATUS", level, struct)
		sentSuccessfully = await self.send(struct, False)

		if (sentSuccessfully):
			loggingFunctions.printlog(beautifulDebug.formatLevel(level,
				f"> Status (lvl {level}) about {self.command}:\n  {info}", False, self.command), verbosity = -2)

		# if chosen, automatically generate error message on encountering a critical error
		if (errorOnCriticalFailure and level >= 20):
			await self.senddebug(level, info, shutdownByCriticalFailure)

	# Sends a debug message to the client.
	# decreasing level = less important / more verbose debug info
	async def senddebug(self, level, info, autoShutdownOnCriticalError = True, *,
		sendToServer = True, removeOutsideWhitespace = True):
		assert type(level) is int
		assert type(info) is str

		if (sendToServer):
			# create structure according to data specification and send it packed by msgpack
			struct = info
			if (removeOutsideWhitespace):
				while (struct[-1].isspace()):
					struct = struct[:-1]
				while (struct[0].isspace()):
					struct = struct[1:]
			if (setting.RESPOND_WITH_COLOR_ANSI_CODES):
				struct = beautifulDebug.formatLevel(level, struct, True, self.command)
			else:
				struct = beautifulDebug.removeAnsiEscapeCharacters(struct)
			
			struct = ("DEBUG", level, struct)
			sentSuccessfully = await self.send(struct, False)
		else:
			sentSuccessfully = True

		# print if user chosen verbosity level demands it
		if (sentSuccessfully and (level > -setting.DESIRED_VERBOSITY or level == 0)):
			if (level >= 20): # critical error / failure. shuts down the client system
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"\n> CRITICAL ERROR (lvl {level}) with {self.command}!\nX {info}\n", True, self.command))
			elif (level >= 10): # error / non-critical exception
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"\n> EXCEPTION (lvl {level}) with {self.command}!\nX {info}\n", True, self.command))
			elif (level >= 1): # warning
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"\n> WARNING (lvl {level}) about {self.command}!\n! {info}\n", True, self.command))
			elif (level == 0): # undefined
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> Undefined debug message with {self.command}:\n  {info}", True, self.command))
			else: # debug
				loggingFunctions.printlog(beautifulDebug.formatLevel(level,
					f"> Debug info (lvl {level}) about {self.command}:\n  {info}", True, self.command))

		# if chosen, automatically shutdown server on encountering a critical error
		if (autoShutdownOnCriticalError and level >= 20):
			await server.shutdownServer(self.websocket, "Websocket server is being shut down due to encountering " +
				"a critical error or failure! Connection will be closed and asnycio will no longer " +
				"listen for incoming commands.")


	# Checks if command contains the recommended number of arguments
	# and warns user if extra parameters are ignored or if there's too few
	# Without parameters returns if the command has any parameters
	async def checkParams(self, minCount=None, maxCount=0, warnUser=True):
		if (minCount is None):
			return await self.checkParams(1, math.inf, warnUser)

		maxCount = max(minCount, maxCount)
		actualCount = len(self.command.split()) - 1 # actual command doesn't count as parameter
		if (actualCount >= minCount and actualCount <= maxCount):
			return True # all well
		elif (warnUser):
			# uh oh!
			warningMsg = f"WARNING: Command {self.command.split()[0]} takes "
			if (maxCount == math.inf):
				warningMsg += f"at least {minCount} arguments"
			elif (maxCount > minCount):
				warningMsg += f"between {minCount} and {maxCount} arguments"
			else:
				warningMsg += f"{minCount} arguments"
			warningMsg += f". You provided {actualCount}."
			if (actualCount < minCount):
				warningMsg += " Please specify more arguments for this command!"
			else:
				warningMsg += " Additional parameters will be ignored!"
			await self.senddebug(2, warningMsg)
			return False
		else:
			return False

	# Retrieves parameter at specified position from whitespace-serparated command.
	# Casts it to specified type (or type of specified default value)
	# If parameter was not provided or cannot be casted, will normally use default
	# Only raises exception if parameter not found/not castable and flag is enabled
	# defaultOrType being a type itself would always raise exception if can't be casted
	# for position=-1 (or no position specified) getParam will return the rest of command as str
	async def getParam(self, position=-1, defaultOrType=str, raiseException=False):
		if(position == -1):
			assert (defaultOrType is str) or (type(defaultOrType) is str)
			if (len(self.command.split()) < 2) and (type(defaultOrType) is str):
				return defaultOrType
			try:
				return self.command.split(None, 1)[1]
			except:
				await self.senddebug(5, f"TYPE WARNING! Couldn't return rest of command {self.command}" +
				" as there don't seem to be any more parameters available! " +
				"getParam will return an empty string.")
				return ""

		actualCount = len(self.command.split()) - 1 # actual command doesn't count as parameter

		try:
			# retrieve type of defaultOrType
			if (type(defaultOrType) is type):
				castToType = defaultOrType
			else:
				castToType = type(defaultOrType)
		except:
			raise TypeError("Parameter defaultOrType could not be recognized as valid type!\n" +
				f"Command {self.command.split()[0]}, position {position}, " +
				f"defaultOrType {defaultOrType} of type {defaultOrType.type()}")

		if (position > actualCount):
			# too few parameters in command arguments
			if (type(defaultOrType) is type or raiseException):
				raise RuntimeError("Not enough parameters given for command " +str(self.command.split()[0])+
					f"! Looking for position {position}, but only found {actualCount} arguments.")
			else:
				return defaultOrType

		try:
			# trying to cast the command parameter string to desired type
			paramValue = self.command.split()[position]
			if type(defaultOrType) is bool or defaultOrType is bool:
				if paramValue in setting.POSITIVE_PARAMETERS:
					result = True
				elif paramValue in setting.NEGATIVE_PARAMETERS:
					result = False
				elif type(defaultOrType) is bool:
					result = defaultOrType
				else:
					result = False
			else:
				result = castToType(paramValue)
			return result
		except:
			if (type(defaultOrType) is type or raiseException):
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
		await self.senddebug(11, "ERROR! Command " + self.command + " not recognized!")
		return False

	async def displayhelp(self, helpString = None, **kwargs):
		# Note: In main section, structure of all commandList values was automatically changed to
		# (function, verbose_command_with_spaces, explanation, details_about_usage)
		if (await self.checkParams(warnUser=False)):
			if (helpString is None):
				helpString = await self.getParam()

			HELP_VERBOSE = ("verbose", "all")
			HELP_SEARCH = ("search", "description", "search description")
			HELP_DEEP_SEARCH = ("deepsearch", "deep search", "deep", "usage search", "usagesearch",
				"usage", "search deep", "search usage")
			HELP_VERBOSE = tuple(HELP_VERBOSE)
			HELP_SEARCH = tuple(word + " " for word in HELP_SEARCH)
			HELP_DEEP_SEARCH = tuple(word + " " for word in HELP_DEEP_SEARCH)
			if (helpString.startswith(HELP_VERBOSE)):
				result = {value[1]:value[2] for (key,value) in commandList.items()}
				await self.senddebug(-1, 'Here are all commands recognized by the python interaction ' +
				'server.\nType "help [command]" for a more detailed explanation of a specific command.\n' +
				'All commands can also be typed without spaces in the command name.')
				await self.send(("LIST OF ALL AVAILABLE COMMANDS", result))
			elif (helpString.startswith(HELP_SEARCH) or helpString.startswith(HELP_DEEP_SEARCH)):
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
				if (len(result) > 0):
					await self.senddebug(-1,
					'Here are all commands recognized by the python interaction ' +
					f'server containing "{helpString}" in their description.\n' +
					'Type "help [command]" for a more detailed explanation of a specific ' +
					'command.\nAll commands can also be typed without spaces in the name.')
					await self.send((f'LIST OF COMMANDS WITH DESCRIPTION CONTAINING "{helpString}"', result))
					return
				else:
					originalCommand = helpString
					# Try without whitespace
					result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower().replace(" ", "") in value[1].lower().replace(" ", "") or
						helpString.lower().replace(" ", "") in value[2].lower().replace(" ", "")}
					if (len(result) > 0):
						helpString = helpString.replace(" ", "")
					else:
						result = {value[1]:value[2] for (key,value) in commandList.items()
							if helpString.lower() in value[1].lower() or
							(helpString.lower() in value[2].lower()) # in case deep skipped this
							or ((len(value) > 3) and (helpString.lower() in value[3].lower()))}
					if (len(result) < 1):
						originalCommand = helpString
						helpString = helpString.replace(" ", "")
						result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower() in value[1].lower() or
						(len(value) > 3) and (helpString.lower() in value[3].lower())}
					if (len(result) < 1):
						result = {value[1]:value[2] for (key,value) in commandList.items()
						if helpString.lower() in value[1].lower().replace(" ", "") or
						(len(value) > 3) and (helpString.lower() in value[3].lower().replace(" ", ""))}
					
					if (len(result) > 0):
						await self.senddebug(-1,
						'Here are all commands recognized by the python interaction ' +
						f'server mentioning "{helpString}" in their description or usage.\n' +
						'Type "help [command]" for a more detailed explanation of a specific ' +
						'command.\nAll commands can also be typed without spaces in the name.')
						await self.send((f'LIST OF COMMANDS MENTIONING "{helpString}"', result))
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
						beautifulDebug.underlinetext(result[1]) + '":\n' + result[2]
					if (len(result) > 4):
						originalCommand = result[4].replace(" ", "")
						explanation += ":\n" + commandList[originalCommand][2] + \
							"\nUsage: " + commandList[originalCommand][3]
					elif (len(result) > 3):
						explanation += "\nUsage: " + result[3]
					await self.sendstatus(-30, explanation)
				else: # No specific command found. Let's try to filter the list
					# If no command could be found, restore it with whitespaces to avoid confusion
					helpString = originalCommand

					# Try to list all commands that start with this string
					result = {value[1]:value[2] for (key,value) in commandList.items()
						if value[1].startswith(helpString)}
					if (len(result) > 0):
						await self.senddebug(-1,
						'Here are all commands recognized by the python interaction ' +
						f'server starting with "{helpString}".\n' +
						'Type "help [command]" for a more detailed explanation of a specific command.\n' +
						'All commands can also be typed without spaces in the command name.')
						await self.send((f'LIST OF COMMANDS STARTING WITH "{helpString}"', result))
					else:
						# Try to list all commands that contain this string
						result = {value[1]:value[2] for (key,value) in commandList.items()
							if helpString.lower() in value[1].lower()}
						if (len(result) < 1):
							# Finally let's try eliminating spaces
							helpString = helpString.replace(" ", "")
							result = {value[1]:value[2] for (key,value) in commandList.items()
								if helpString.lower() in value[1].lower().replace(" ", "")}

						if (len(result) > 0):
							await self.senddebug(-1,
							'Here are all commands recognized by the python interaction ' +
							f'server containing "{helpString}".\n' +
							'Type "help [command]" for a more detailed explanation of a specific ' +
							'command.\nAll commands can also be typed without spaces in the name.')
							await self.send((f'LIST OF COMMANDS CONTAINING "{helpString}"', result))
						else: # Still nothing
							# Let's try further searching for these words
							return await self.displayhelp("search " + helpString)
		else:
			result = {}
			allcommands = '\n' + '\n'.join({value[1] for (key,value) in commandList.items()}) + '\n'
			print(allcommands)
			for (key,value) in commandList.items():
				cmd = value[1]
				description = value[2]
				if ' ' in cmd:
					firstword = cmd.split(' ')[0]
					groupCount = allcommands.count('\n' + firstword + ' ')
					if (groupCount > 1):
						# firstWord is a group
						cmd = firstword + " ..."
						description = f'Group of {groupCount} commands. Type "help {firstword}" for a detailed list'
				result[cmd] = description
			await self.senddebug(-1, 'Here is a concise list of all command groups recognized by the ' +
			'python interaction server.\nType "help all" for a complete list of all individual commands.\n' +
			'Type "help [command]" for a more detailed explanation of a specific command.\n' +
			'All commands can also be typed without spaces in the command name.')
			await self.send(("GROUPED LIST OF AVAILABLE COMMANDS GROUPED", result))
			# await self.sendstatus(-30, "Short list of available commands: " + ", ".join(sorted(commandList.keys()))) # don't need that
	commandList["help"] = (displayhelp,
		"Displays available commands or detailed info about a certain command",
		"Without parameters it will return an array of grouped available commands with their explanation.\n" +
		'Type "help all" for a complete list of all individual available commands.\n' +
		'Type "help [command]" to get more detailed information about a specific command.\n' +
		'Use "help search ..." to search for descriptions matching the specified following string\nUse ' +
		'"help deep ..." to search even the explanations for anything matching the following string\n' +
		'(If no command is found with a specific search, it automatically searches more broadly, ' +
		'ending up at a deep search in the end.)')


	async def setverbosity(self, **kwargs):
		await self.checkParams(0, 1)
		if not await self.checkParams(1, 1, False):
			# Just display the current verbosity level
			await self.send(setting.DESIRED_VERBOSITY)
		else:
			newVerbosity = await self.getParam(1, setting.DESIRED_VERBOSITY)
			if (setting.DESIRED_VERBOSITY == newVerbosity):
				await self.senddebug(-5, f"Server verbosity level is already set at {newVerbosity}.")
			else:
				setting.DESIRED_VERBOSITY = newVerbosity
				infotext = f"Verbosity level of the server has been changed to {newVerbosity}."
				await self.senddebug(-1, infotext)
				if (-1 <= -setting.DESIRED_VERBOSITY):
					loggingFunctions.log(infotext)
					# To make sure that at least the logfile logs this change to avoid confusion
					# about missing debug info later on
	commandList["set verbosity"] = (setverbosity, "Displays or sets the desired verbosity level",
		'Without parameter, it displays the current verbosity level of the server.\nA parameter ' +
		'changes the servers verbosity level of debug and status information. Will affect which ' +
		'messages are printed in the console and stored in the logfile.\nThe higher you go the ' +
		'more verbose debug info gets printed. 11 = all debug, 0 = only warnings and errors, ' +
		'-1 = ignore mild warnings, -9 = ignore all warnings, -10 = ignore mild errors, -19 = ' +
		'don''t print any non-critical errors.')
	commandList["verbosity"] = commandAlias("set verbosity")


	async def clearScreenInSeconds(self, waitSeconds=0):
		await asyncio.sleep(waitSeconds)
		beautifulDebug.clearScreen()


	async def cls(self, **kwargs):
		await self.checkParams(0, 1)
		seconds = await self.getParam(1, 0)
		await self.senddebug(-10, "Screen of the server console output is being cleared in " +
			str(seconds) + " seconds.") # To avoid display of command disconnect output in the freshly
			# cleared window, this yields until the processing of the cls-command has been completed
		asyncio.get_event_loop().create_task(self.clearScreenInSeconds(seconds))
	commandList["cls"] = (cls, "Clears the console output screen",
		'First and only parameter can defined in how many seconds the screen will be cleared, ' +
		'defaults to 0\nThen sends cls or clear to the server console, depending on the system')
	commandList["clear"] = commandAlias("cls")


	async def echo(self, **kwargs):
		await self.sendstatus(-30, await self.getParam(-1, "echo"))
	commandList["echo"] = (echo, "Echos back with a status message of type successful",
		'Without parameters, it sends the string "echo", otherwise it sends back all parameters as string')


	async def respondtest(self, **kwargs):
		await self.checkParams(0)
		await self.senddebug(-5, "Respond test executed. This is your response.")
	commandList["respond"] = (respondtest, "Responds with a debug message of level -5")


	async def sleeptest(self, **kwargs):
		await self.checkParams(1)
		sleepDuration = await self.getParam(1, 2.0)
		await self.senddebug(-10, "Sleeping now for " + str(sleepDuration) + " seconds.")
		#time.sleep(sleepDuration) # blocks whole thread and doesn't allow other async execution
		await asyncio.sleep(sleepDuration) # allows other async operations to run
		await self.senddebug(-9, "Slept successfully for " + str(sleepDuration) + " seconds.")
	commandList["sleep"] = (sleeptest, "Sleeps for specified number of seconds",
		"First and only parameter should be of type float, defaults to 2\n" +
		"Sleeping is asynchronous and allows for other commands to be processed in the meantime")


	# should be for debug only. deactivated on connections outside of localhost
	# do not rely on this function for production code via unencrypted connections
	async def python(self, **kwargs):
		if (setting.ALLOW_REMOTE_CODE_EXECUTION):
			if(not(await self.checkParams(1, math.inf))):
				return False
			try:
				result = exec(await self.getParam(), globals())
				await self.sendstatus(-30, str(result))
			except:
				await self.sendstatus(13, f"ERROR executing command {self.command} in python:\n" +
					traceback.format_exc())
				return False
		else:
			await self.senddebug(15, f"Cannot execute {await self.getParam()}. " +
				"Remote code execution is disabled by python websocket server.")
			return False
	commandList["python"] = (python, "Executes the specified string as python code" +
		("" if setting.ALLOW_REMOTE_CODE_EXECUTION else " (DISABLED)"),
		"Parameters as string specify the code that will be executed by the server\n" +
		"Due to security reasons, this feature is normally disabled when this server is " +
		"active on the internet via unencrypted connections (outside of localhost)\n" +
		"This command is currently " + ("ENABLED" if setting.ALLOW_REMOTE_CODE_EXECUTION else "DISABLED"))
	commandList["py"] = commandAlias("python")


	# should be for debug only. deactivated on connections outside of localhost
	# do not rely on this function for production code via unencrypted connections
	async def pythoneval(self, **kwargs):
		if (setting.ALLOW_REMOTE_CODE_EXECUTION):
			if(not(await self.checkParams(1, math.inf))):
				return False
			try:
				result = eval(await self.getParam())
				await self.sendstatus(-30, str(result))
			except:
				await self.sendstatus(13, f"ERROR evaluating command {self.command} in python:\n" +
					traceback.format_exc())
				return False
		else:
			await self.senddebug(15, f"Cannot evaluate {await self.getParam()}. " +
				"Remote code execution is disabled by python websocket server.")
			return False
	commandList["eval"] = (pythoneval, "Evaluates the specified string as python expression and " +
			"responds with the result" + ("" if setting.ALLOW_REMOTE_CODE_EXECUTION else " (DISABLED)"),
			"Parameters as string specify the expression that will be evaluated by the server\n" +
			"Due to security reasons, this feature is normally disabled when this server is " +
			"active on the internet via unencrypted connections (outside of localhost)\n" +
			"This command is currently " + ("ENABLED" if setting.ALLOW_REMOTE_CODE_EXECUTION else "DISABLED"))
	commandList["evaluate"] = commandAlias("eval")


	async def serverInfo(self, **kwargs):
		await self.checkParams(0)
		await self.sendstatus(-30, f"According the python server settings, this websocket server is located on {setting.SERVER_IP}:{setting.SERVER_PORT}")
	commandList["server info"] = (serverInfo, "Gives back the IP address and port of the active websocket server as verbose status",
		'Does not take parameters and responds with a verbose text as status level -30 (successful).\n' +
		'IP and port are returned according to the python server settings')


	async def serverIP(self, **kwargs):
		if (await self.checkParams(warnUser=False)):
			param = await self.getParam(1, str)
			if param.lower() == "port":
				return await self.serverIPPort(warnParameters = False)
		await self.checkParams(0)
		await self.send(setting.SERVER_IP)
	commandList["server ip"] = (serverIP, "Gives back the IP address of the active websocket server as string",
		'Does not take parameters and responds with a string.\n' +
		'IP is returned according to the python server settings')


	async def serverPort(self, **kwargs):
		await self.checkParams(0)
		await self.send(setting.SERVER_PORT)
	commandList["server ip"] = (serverIP, "Gives back the port of the active websocket server as integer",
		'Does not take parameters and responds with an integer.\n' +
		'Port is returned according to the python server settings')


	async def serverIPPort(self, *, warnParameters = True, **kwargs):
		if warnParameters:
			await self.checkParams(0)
		await self.send(setting.SERVER_IP + ":" + str(setting.SERVER_PORT))
	commandList["server address"] = (serverIPPort, "Gives back the IP address and port of the active websocket server as string",
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
		await self.checkParams(0)
		await server.shutdownServer(self.websocket, "Websocket server is being restarted due to request by client.\n" +
			"All running processes and active client connections will be forcibly terminated.\n" +
			"The server will unload any neural network and reset its state to the initial server state.\n"+
			"Cannot be used to chain commands together! All commands after it will be discarded!\n"+
			"Please refer to the python server console to see if re-establishing the server is " +
			'successful or test a second later (with a newly established connection) with ' +
			'"send status -30".')
		os.execl(sys.executable, *([sys.executable]+sys.argv))
	commandList["server restart"] = (restart, "Restarts and resets the server",
		"No parameters. Will not ask for confirmation!\n" +
		"This will terminate all running processes and client connections forcibly and restart " +
		"the python interaction server. Neural networks will be unloaded and the server resets " +
		"its state to the initial server state.")
	commandList["server reset"] = commandAlias("server restart")


	async def sendalot(self, **kwargs):
		await self.checkParams(0, 1)
		await self.sendstatus(-30, "#" * await self.getParam(1, 10))
	commandList["send a lot"] = (sendalot, "Responds with a string of the symbol # repeated many times",
		"First and only parameter specifies how often this symbol should be repeated, equaling the " +
		"length of that string. Defaults to 10\nCan be used to test transmission rate of extremely " +
		"large messages")


	async def sendfiletest(self, **kwargs):
		if not await self.checkParams(warnUser=False):
			await self.senddebug(1, f"No filepath specified for sendfile test. Sending log file.")
			path = setting.LOGFILE_PATH
		else:
			path = await self.getParam()
		await self.sendfile(path)
	commandList["send file"] = (sendfiletest, "Transmits the file content at specified path as binary data",
		"Parameters as string determine the path of that file on the server. Absolute paths are " +
		'preferred\nResponds with a struct of type ["FILE", filename, binarydata]')


	async def sendstruct(self, **kwargs):
		struct = (1, 'text', 5.234, (1, 'more', 3, ()), ('b', 'a', 'c'), None, {"hi": 1, "there": 2})
		if (await self.checkParams(warnUser=False)):
			if (setting.ALLOW_REMOTE_CODE_EXECUTION):
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
		await self.send(struct)
	commandList["send struct"] = (sendstruct, "Sends a complicated test structure via msgpack",
		"Parameters as string can define a custom structure to send. If no structure is specified " +
		"or the provided string cannot be parsed into a structure, " +
		"a complicated default structure is used")


	async def testdebug(self, **kwargs):
		await self.checkParams(0, 1)
		level = await self.getParam(1, -1)
		text = f"This is a fake debug message of level {level} as " + \
			"requested by the client."
		if (level >= 20):
			text += "\nRaising an exception and shutting down the system has been suppressed, " + \
				"although this would normally happen on level 20+"
		await self.senddebug(level, text, False)
	commandList["send debug"] = (testdebug, "Sends a test debug message",
		"First and only parameter defines the level (importance) of that debug message. Defaults to -1")


	async def teststatus(self, **kwargs):
		await self.checkParams(0, 1)
		level = await self.getParam(1, -30)
		text = f"This is a fake status message of level {level} as " + \
			"requested by the client."
		if (level >= 20):
			text += "\nRaising an exception and shutting down the system has been suppressed, " + \
				"although this would normally happen on level 20+"
		await self.sendstatus(level, text, False)
	commandList["send status"] = (teststatus, "Sends a test status message",
		"First and only parameter defines the level (importance) of that debug message. " +
		"Defaults to -30 (successful)")


	async def add(self, **kwargs):
		await self.checkParams(2)
		await self.send(await self.getParam(1, 2.0) + await self.getParam(2, 3.0))
	commandList["add"] = (add, "Adds two float numbers",
		"Two parameters specify the two numbers to be added up as floats, responds with the result " +
		"as float\nPar°ameters default to 2 and 3 respectively\nCan be used for testing purposes")


	async def divide(self, **kwargs):
		await self.checkParams(2)
		await self.send(await self.getParam(1, 2.0) / await self.getParam(2, 3.0))
	commandList["divide"] = (divide, "Divides two float numbers",
		"Two parameters specify the two numbers to be added up as floats, responds with the result " +
		"as float\nParameters default to 2 and 3 respectively\nCan be used for testing purposes")


	async def console(self, *, loadedCommand, **kwargs):
		await self.checkParams(0)
		await self.sendstatus(-20, "Waiting for console input by user on python script execution server.")
		newcommand = await ainput("Enter your desired command here: ")
		await self.sendstatus(-10, f'Console input received. Continuing with command "{beautifulDebug.underlinetext(newcommand)}"')
		loadedCommand.append(newcommand)
		return True
		# old implementation:
		#await server.interactiveServer(self.websocket, path, command=newcommand, dontDebugDisconnect=True)
	commandList["console"] = (console, "Prompts on the server console for a command",
		'This can be used to inject commands into the pipeline that the server then executes. Waits ' +
		'for the user to type the command while asynchronously processing other incoming commands\n' +
		'This request would then be processed on the original thread, so the client that ' +
		'originally sent the "console" command will receive any debug/status messages and other ' +
		'response that is produced by the executing the command that the user typed in\n' +
		'Type help for a list of available commands')


	async def prepareCommand(self, **kwargs):
		global preparedCommands
		if await self.checkParams(0, 0, False):
			await self.send(("PREPARED COMMANDS", preparedCommands))
		else:
			param = await self.getParam()
			param = param.strip()
			if (param == "clear" or param=="reset"):
				if (len(preparedCommands) == 0):
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
		'currently prepared commands.\nUse "prepare clear" or "prepare reset" to clear the list ' +
		'from any loaded commands.\nWith chained commands ' +
		('(currently enabled)' if setting.AMPERSAND_CHAINS_COMMANDS else '(currently disabled)') +
		', a single & will first prepare the command and then execute anything behind it. A ' +
		'double ampersand will be converted into a prepared chained command, that executes its ' +
		'contents consecutively. To use a ampersand in a string within those commands, escape ' +
		'it as &&&&.\nExample: "prepare echo alone & prepare echo and&&&&and & prepare echo ' +
		'one&&echo two & echo successfully prepared &&-chained commands" will prepare "echo ' +
		'alone", then prepare "echo and&&and" (which just prints out "and&and"), then prepare ' +
		'the double command "echo one & echo two" and finally print out "successfully prepared ' +
		'&-chained commands"')
	

	async def loadCommand(self, *, loadedCommand = None, **kwargs):
		if (loadedCommand is None):
			raise TypeError("Function loadCommand needs to be given a list as parameter loadedCommands, otherwise it cannot relay the information of the loaded command! Make sure that the function executing commands has a mutable list parameter for loadedCommands.")
		
		global preparedCommands
		await self.checkParams(0, 0)
		if (len(preparedCommands) == 0):
			await self.senddebug(10, f"List of prepared commands is empty. Nothing to load!")
			return False
		else:
			nextCommand = preparedCommands.pop(0)
			await self.sendstatus(-10, f'Command "{beautifulDebug.underlinetext(nextCommand)}" was loaded from the list of prepared commands. Executing it now.')
			loadedCommand.append(nextCommand)
			return True
	commandList["load"] = (loadCommand, "Loads and executes the oldest prepared command",
		'Does not take any arguments. Loads the oldest command from the list of prepared commands, executes it on the current client connection and removes it from the list.\nUse "prepare" to check the list. See more info on the prepare and loading mechanism with "help prepare"')
	

	SEVERE_WARNING_LEVEL = 20
	SUPPRESSED_WARNING_LEVEL = 19
	async def checkScriptVersion(self, **kwargs):
		await self.checkParams(1, 2)
		if (not await self.checkParams(warnUser=False)):
			await self.send(("SERVER SCRIPT VERSION",  server.PYTHON_INTERACTION_SCRIPT_VERSION))
			return
		criticalWarning = True
		if (await self.checkParams(2, math.inf, False)):
			criticalWarning = not((await self.getParam(2, "True")) in setting.NEGATIVE_PARAMETERS)
		if criticalWarning:
			warningLevel = self.SEVERE_WARNING_LEVEL
			shutdownText = "Terminating the connection and shutting down the server."
		else:
			warningLevel = self.SUPPRESSED_WARNING_LEVEL
			shutdownText = "Further code execution is not recommended and " + \
				"might lead to undefined behaviour. Proceed with caution."
		clientVersion = await self.getParam(1, str)
		if (re.fullmatch("[\\da-zA-Z]+\\.[\\da-zA-Z]+\\.[\\da-zA-Z]+", clientVersion) is None):
			await self.sendstatus(6, f"Client version {clientVersion} does not match the expected " +
				"version template [major].[minor].[build] Cannot compare versions correctly!")
			return False
		if (re.fullmatch("[\\da-zA-Z]+\\.[\\da-zA-Z]+\\.[\\da-zA-Z]+", server.PYTHON_INTERACTION_SCRIPT_VERSION)
			is None):
			await self.sendstatus(6, f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does not " +
				"match the expected version template [major].[minor].[build] Cannot compare versions " +
				"correctly!")
			return False
		cmajor, cminor, cbuild = clientVersion.split(".")
		smajor, sminor, sbuild = server.PYTHON_INTERACTION_SCRIPT_VERSION.split(".")
		# Compare major version
		if (cmajor != smajor):
			if (re.fullmatch("\\d+", cmajor) is None) or (re.fullmatch("\\d+", smajor) is None):
				await self.sendstatus(warningLevel,
					f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does " +
					f"not match major of client version {clientVersion}.\n" +
					f"Commands cannot be executed properly!\n" +
					shutdownText + "\n" +
					f"Please use a similar version on both ends.")
				return False
			else:
				if (int(cmajor) > int(smajor)):
					await self.sendstatus(warningLevel,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} is " +
						f"too low for client({clientVersion}).\n" +
						f"Commands cannot be executed properly!\n" +
						shutdownText + "\n" +
						f"Please update the server or use a similar client version.")
					return False
				if (int(cmajor) < int(smajor)):
					await self.sendstatus(warningLevel,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} is " +
						f"too high for client({clientVersion}).\n" +
						f"Major version differences might lead to unexpected behaviour due to varying " +
						f"implementation!\n" +
						shutdownText + "\n" +
						f"Please update the client or use a similar server version.")
					return False
		# Compare minor version
		elif (cminor != sminor):
			if (re.fullmatch("\\d+", cminor) is None) or (re.fullmatch("\\d+", sminor) is None):
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
				if (int(cminor) > int(sminor)):
					await self.sendstatus(warningLevel,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} is " +
						f"too low for client({clientVersion}).\n" +
						f"Commands cannot be executed properly!\n" +
						shutdownText + "\n" +
						f"Please update the server or use a similar client version.")
					return False
				if (int(cminor) < int(sminor)):
					await self.sendstatus(6,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} has " +
						f"higher minor version than client({clientVersion}).\n" +
						f"This should not be an issue, if only minor features have been added. " +
						f"However, it is advised to update the client version to a similar build.")
		# Compare build version
		elif (cbuild != sbuild):
			if (re.fullmatch("\\d+", cbuild) is None) or (re.fullmatch("\\d+", sbuild) is None):
				await self.sendstatus(4,
					f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} does " +
					f"not match build of client version {clientVersion}.\n" +
					f"This should not be an issue, if only minor details have been changed. " +
					f"However, it is advised to use matching software versions on both ends.")
			else:
				if (int(cbuild) > int(sbuild)):
					await self.sendstatus(4,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} has " +
						f"a lower build number than client version {clientVersion}.\n" +
						f"This should not be an issue, if only minor details have been changed. " +
						f"However, it is advised to update the server to a matching version.")
				if (int(cbuild) < int(sbuild)):
					await self.sendstatus(2,
						f"Server version {server.PYTHON_INTERACTION_SCRIPT_VERSION} has " +
						f"a higher build number than client version {clientVersion}.\n" +
						f"This should not be an issue, if only minor details have been changed. " +
						f"However, it is advised to update the client to a matching version.")
		else:
			await self.sendstatus(-30,
				f"Server and client versions {server.PYTHON_INTERACTION_SCRIPT_VERSION} match perfectly.")
	commandList["check version"] = (checkScriptVersion, "Compares and checks server and client versions",
		'If no arguments are passed, this function returns the version of the server script as a string.'+
		'\nFirst argument is expected to be the client script version for asserting compatibility.\n' +
		'The version is passed as a string of type major.minor.build\nmajor, minor and build can ' +
		'contain only digits or letters.\nIf major version differs or clients minor version is higher ' +
		'then the servers minor version (or if any minor version contains letters and is different), ' +
		'the check will fail and throw an error of level ' + str(SEVERE_WARNING_LEVEL) +
		', shutting down the server to prohibit ' +
		'undefined behaviour with unexpected errors due to differing implementations in updates.\n' +
		'This check can be overridden with a negative second parameter, which lowers the warning level ' +
		'to ' + str(SUPPRESSED_WARNING_LEVEL) + '. (Negative parameters are: ' +
		', '.join(setting.NEGATIVE_PARAMETERS) + ')\nLower minor version in the client or differing build ' +
		'will only display a low level warning and pass the check.\n' +
			('If this check is used and fails while chaining commands with ampersand (' +
			('enabled' if setting.AMPERSAND_CHAINS_COMMANDS else 'disabled') +
			'), execution will carry on regardless due to server settings.'
		if setting.EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE else
			'This check can be used when chaining commands with ampersand (' +
			('enabled' if setting.AMPERSAND_CHAINS_COMMANDS else 'disabled') + '), ' +
			'as the chain will only continue if the check is passed.'))
	commandList["assert version"] = commandAlias("check version")
	commandList["verify version"] = commandAlias("check version")



	# NEURAL NETWORK INTERACTION
	async def loadnn(self, **kwargs):
		global nnSuccessfullyLoaded
		if nnSuccessfullyLoaded:
			await self.senddebug(13, f'The server has already loaded another network. It is ' +
			'recommended to use "server reset" before loading another network, to avoid ' +
			'undefined behaviour!')
		if not await self.checkParams(warnUser=False):
			path = setting.DEFAULT_LOAD_NN_PATH
			await self.senddebug(5, f"No custom path for the neural network was specified. " +
			"Using default path specified in python server script:\n" + path)
		else:
			path = await self.getParam()
			path = setting.AVAILABLE_NN_PATHS.get(path, path)
		
		try:
			await self.sendstatus(-10, f"Neural network at {path} is being loaded. This might " +
				"take a while. Please view the python console for further information and loading details.")
			await asyncio.sleep(0.1) # make sure other async tasks have a chance to be executed before
			# blocking main thread for a while (so that the previous status mesage gets send properly)
			global nn_spec
			global nn_module
			nn_spec = importlib.util.spec_from_file_location("", path)
			nn_module = importlib.util.module_from_spec(nn_spec)
			nn_spec.loader.exec_module(nn_module)
		except:
			await self.sendstatus(15, f"ERROR finding or loading python script at specified location {path}:\n" +
				traceback.format_exc())
			return False
		
		try:
			if (True): # TODO: Check if tensorflow or pytorch
				global tfNetwork
				global tf
				import tensorflow as tfref
				tf = tfref
				tfNetwork.loaded = True
			await self.sendstatus(-30, f"Neural network at {path} has been successfully loaded and " +
				"executed.")
			nnSuccessfullyLoaded = True
		except:
			await self.sendstatus(15, f"ERROR loading Neural Network from script {path}:\n" +
				traceback.format_exc())
			return False
	commandList["nn load"] = (loadnn, "Loads a neural network at the given path",
		"Parameters as string specify the location of the python script on the server. " +
		"This script is then imported and loaded by python.\n" +
		"Use a keyword as parameter to load one of the networks specified in server settings.\n" +
		'Available keywords are: "' + '", "'.join(setting.AVAILABLE_NN_PATHS.keys()) + '"')


	async def isnnloaded(self, **kwargs):
		global tfNetwork
		await self.send(hasattr(tfNetwork, 'loaded') and tfNetwork.loaded)
		if not(hasattr(tfNetwork, 'loaded')):
			return False
	commandList["nn is loaded"] = (isnnloaded, "Checks if any neural network has been loaded and " +
		"initialized successfully", "Returns a boolean, can be used for assertion to chain commands")


	async def checkTf(self, **kwargs):
		global nnSuccessfullyLoaded
		if not nnSuccessfullyLoaded:
			await self.sendstatus(18, f"Network hasn't been loaded and initialized yet!")
			return False

		global tfNetwork
		if not hasattr(tfNetwork, 'loaded') or not tfNetwork.loaded:
			await self.sendstatus(18, f"Network is not Tensorflow, tf-specific functions can't be used!")
			return False

		return True

	async def tf_getversion(self, **kwargs):
		if not await self.checkTf(): return False
		try:
			global tf
			global tfNetwork
			v = tf.__version__
			tfNetwork.version = v
			await self.send(v)
		except:
			await self.sendstatus(16, f"Couldn't retrieve tensorflow version!\n" +
				traceback.format_exc())
			return False
	commandList["tf get version"] = (tf_getversion, "Gets tensorflow version of loaded neural network",
		"Returns a string with the version number")


	async def tf_getstructure(self, **kwargs):
		if not await self.checkTf(): return False
		await self.checkParams(0, 1)
		convertToShapeInstructions = await self.getParam(1, False)
		try:
			structure = []
			global nn_module
			nn_module.model.summary(print_fn=lambda x: structure.append(x), line_length=500)
		except:
			await self.sendstatus(16, f"Couldn't retrieve tensorflow structure!\n" +
				traceback.format_exc())
			return False
		try:
			readableStructure = "\n".join(structure)
			readableStructure = re.sub(r" +", " ", readableStructure)
			lineLength = max([len(
				re.sub(r"\-\-+", "", re.sub(r"\=\=+", "", re.sub(r"\_\_+", "", re.sub(r" +", " ", line))))
			) for line in structure])
			readableStructure = re.sub(r"\-\-+", "-" * lineLength, readableStructure)
			readableStructure = re.sub(r"\=\=+", "=" * lineLength, readableStructure)
			readableStructure = re.sub(r"\_\_+", "_" * lineLength, readableStructure)
			await self.senddebug(-8, "Structure of the network:\n" + readableStructure)
			global tfNetwork
			tfNetwork.validstructure = False
			tfNetwork.layers = []
			mainstructure = 0
			layerCount = 0
			for line in structure:
				if (line.startswith("Model: \"")):
					assert mainstructure == 0
					tfNetwork.modelname = line.replace("Model: ", "").replace('"', '')
				elif (re.fullmatch("Layer \\(type\\) *Output Shape *Param \\# *", line) is not None):
					assert mainstructure == 0
					tfNetwork.validstructure = True
				elif (re.fullmatch("Layer \\(type\\) *Output Shape *Param \\# *Connected to *", line) is not None):
					assert mainstructure == 0
					tfNetwork.validstructure = True
				elif (line.startswith("Total param")):
					assert mainstructure == 2
					tfNetwork.totalparams = int(re.sub("[a-zA-Z\\:\\, ]", "", line))
				elif (line.startswith("Trainable param")):
					assert mainstructure == 2
					tfNetwork.trainableparams = int(re.sub("[a-zA-Z\\:\\, ]", "", line))
				elif (line.startswith("Non-trainable param")):
					assert mainstructure == 2
					tfNetwork.nontrainableparams = int(re.sub("[a-zA-Z\\:\\, ]", "", line))
				elif (re.fullmatch("\\=*", line) is not None):
					mainstructure += 1
				elif (re.fullmatch("\\_*", line) is not None):
					pass
				elif (re.fullmatch(r"[a-z0-9\_]* \([A-Za-z0-9 ]*\)   *" +
					r"\[?\((None|[0-9]*|\, )*\)\]?   *[0-9]* *", line) is not None):
					# Layer (type)      Output      Shape      Param #
					assert mainstructure == 1
					line = re.sub("   *", "\n", line).strip()
					layertype, shape, params = line.split("\n")
					layername, ltype = layertype.split("(")
					layername = layername.strip()
					ltype = ltype.replace(")", "")
					if (shape.startswith("[") and shape.endswith("]")):
						shape = shape[1:-1]
					shape = ast.literal_eval(shape)
					params = int(params)
					layer = layername, ltype, shape, params
					tfNetwork.layers.append(layer)
					layerCount += 1
				elif (re.fullmatch(r"[a-z0-9\_]* \([A-Za-z0-9 ]*\)?   *" +
					r"\[?\((None|[0-9]*|\, )*\)\]?   *[0-9]*   *[a-z0-9\_]*(\[0\])* *", line) is not None):
					# Layer (type)      Output      Shape      Param #      Connected to
					assert mainstructure == 1
					line = re.sub("   *", "\n", line).strip()
					layertype, shape, params, connectedTo = line.split("\n")
					layername, ltype = layertype.split("(")
					layername = layername.strip()
					ltype = ltype.replace(")", "")
					if (shape.startswith("[") and shape.endswith("]")):
						shape = shape[1:-1]
					shape = ast.literal_eval(shape)
					params = int(params)
					while(connectedTo.endswith("[0]")):
						connectedTo = connectedTo[:-3]
					layer = layername, ltype, shape, params, [connectedTo]
					tfNetwork.layers.append(layer)
					layerCount += 1
				elif (re.fullmatch(r"   *[a-z0-9\_]*(\[0\])* *", line) is not None):
					connectedTo = line.strip()
					while(connectedTo.endswith("[0]")):
						connectedTo = connectedTo[:-3]
					tfNetwork.layers[-1][4].append(connectedTo)
				else:
					await self.senddebug(14, f'Line "{line}" in tf network structure is unexpected ' + \
						f"and cannot be parsed! Integrity of the architecture data cannot be guaranteed.")
				tfNetwork.layerCount = layerCount
			if (tfNetwork.validstructure):
				if not convertToShapeInstructions:
					await self.send(("TF STRUCTURE", tfNetwork.layers))
				else:
					pos = [0, 0, 0] # center position of each cube
					for layer in tfNetwork.layers:
						xyz = [] # size of each cube
						for dim in layer[2]:
							if dim is not None and dim > 0 and len(xyz) < 3:
								xyz.append(dim)
						while (len(xyz) < 3):
							xyz = [1] + xyz
						pos[2] += xyz[2]/2
						color = visualizationSettings.layerColors.get(layer[1].lower(),
							visualizationSettings.layerColors.get("default"))
						if (type(color) is not tuple) and (type(color) is not list):
							color = [color]
						color = list(color)
						while (len(color) < 3):
							color.append(color[0])
						coordinates = [float(i) for i in pos + xyz + color]
						await self.send(("SPAWN CUBOID pos size color", coordinates))
						await asyncio.sleep(0.1)
						pos[2] += xyz[2]/2 + 1000
			else:
				await self.sendstatus(17, f"Tensorflow network structure does not adhere to expected " +
					f"format!\nReceived structure: {structure[2]}\nExpected structure: Layer (type)\t" +
					f"Output Shape\tParam #\nAlternative expected structure: Layer (type)\t" +
					f"Output Shape\tParam #\tConnected to")
				return False
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


	async def tf_getvars(self, **kwargs):
		if not await self.checkTf(): return False
		await self.checkParams(0, 1)
		global tfNetwork
		if (await self.checkParams(1, 1, False)):
			attr = await self.getParam(1, str, True)
			try:
				await self.send(getattr(tfNetwork, attr))
			except:
				await self.senddebug(12, f"Attribute {attr} does not (yet) exist in tfNetwork. " +
					f"Sending back None as value for {attr}.")
				await self.send(None)
				return False
		else:
			await self.send(vars(tfNetwork))
	commandList["tf get vars"] = (tf_getvars, "Returns all variables and information currently loaded and " +
		"known about the tensorflow network",
		"Returns a map of the continually expanding class type that stores information about the " +
		"neural network\nThis data is continually expanded by more commands and information requests")

