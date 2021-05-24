#!/usr/bin/env python

# This module defines the behaviour of the websocket server itself. It contains functions to
# start the server or shut it down, and controls the looped asyncio interface that asynchronously
# waits and listens for new commands by a client. It will find functions from the serverCommands.py
# script and execute them when a client sends the corresponding command.

# USED LIBRARIES
import asyncio
from logging import error
from msgpack.exceptions import FormatError
import websockets
import sys
import time
import traceback

# LOCAL IMPORTS
import beautifulDebug
import serverCommands
import serverSettings as setting
import loggingFunctions


# allows the client to check its version against the server to guarantee feature parity
# Minor version difference will result in a warning
# Major version difference will result in refusal to interact with neural network
PYTHON_INTERACTION_SCRIPT_VERSION = "0.1.0"

# WEBSOCKET SERVER THAT INTERACTS WITH COMMANDS
async def interactiveServer(websocket, path, *, initialCommand=None, debugDisconnect=True):
	# Create a new command instance for this client connection and store the websocket connection,
	# as well as the command string
	commandInstance = serverCommands.Request(websocket, initialCommand)
	
	# Default function for commands if it can't be matched
	COMMAND_NOT_FOUND_FUNCTION = serverCommands.Request.commandNotFound

	# check that the modules have been connected well
	assert(callable(loggingFunctions.printlog))
	assert(callable(commandInstance.senddebug))
	assert(callable(COMMAND_NOT_FOUND_FUNCTION))
	assert(type(serverCommands.commandList) is dict)
	assert(len(serverCommands.commandList) > 0)

	# loop while the client stays connected,
	# so that this server does not prematurely close the connection
	while True:
		if commandInstance.command is None:
			# No command was given. Wait and listen for an incoming command
			try:
				# Wait for next command by client
				commandInstance.command = await websocket.recv()
				# Print out received command
				loggingFunctions.printlog(beautifulDebug.B_CYAN + "< " +
					f"{commandInstance.command}" + beautifulDebug.RESET,
					verbosity = -2)

			# If client is disconnected, recv will raise an exception.
			# This would be printed and returns the function. (alternatively, break could be used too)
			# Then asyncio's run_forever (in main program section at the bottom)
			# would call this function again, so the server waits for a new client connection
			except websockets.ConnectionClosedOK:
				if debugDisconnect:
					formattedWarning = beautifulDebug.special(5,1,5, f"x DISCONNECT: Client has disconnected ok.\n\n")
					loggingFunctions.printlog(formattedWarning, verbosity = -4)
				return True

			except websockets.ConnectionClosedError:
				formattedWarning = beautifulDebug.special(5,0,4, f"x DISCONNECT: Client has disconnected unexpectedly!\n\n")
				loggingFunctions.printlog(formattedWarning, verbosity = -3)
				return False

			except: # any other error while trying to listen for a command
				formattedWarning = beautifulDebug.special(5,0,2, f"ERROR! Unexpected error ocurred " +
					"while trying to listen for a websocket command.\n" + traceback.format_exc() + "\n\n")
				loggingFunctions.printlog(formattedWarning, verbosity = 10)
				return False


		try:
			# Send confirmation of received command back to client
			#await serverCommands.senddebug(w, c, -10, f"Received command {command}")

			# check if command is empty
			if len(commandInstance.command) == 0 or \
				commandInstance.command == " " or \
				len(commandInstance.command.split()) == 0:
				
				await commandInstance.senddebug(10, "Empty command is invalid, cannot be processed")
				if debugDisconnect:
					loggingFunctions.printlog(beautifulDebug.B_BLUE +
						f"x End of command processing. Disconnecting client on purpose.\n\n" +
						beautifulDebug.RESET, verbosity = -3)
				await websocket.close()
				return True

			# TRYING TO FIND AND MATCH THE COMMAND

			# This nested function tries to match the command from
			# the server commandList and returns the corresponding function
			def findCommand(firstCommandWord):
				return serverCommands.commandList.get(firstCommandWord.lower(),
					[COMMAND_NOT_FOUND_FUNCTION])[0]

			# Search in 'serverCommands.commandList'-dictionary for the first word of command by client
			func = findCommand(commandInstance.command.split()[0])

			# If command not found, try eliminating whitespaces consecutively and match it
			originalCommand = commandInstance.command
			while(func is COMMAND_NOT_FOUND_FUNCTION and len(commandInstance.command.split()) > 1):
				commandInstance.command = commandInstance.command.split()[0] + commandInstance.command.split(None, 1)[1]
				func = findCommand(commandInstance.command.split()[0])
			
			# If no command could be found, restore it with whitespaces to avoid user confusion
			if func is COMMAND_NOT_FOUND_FUNCTION:
				commandInstance.command = originalCommand

			# Now check for chained commands
			if setting.AMPERSAND_CHAINS_COMMANDS:
				# Matching single ampersands near you
				if "&" in commandInstance.command.replace("&&", ""):
					# Temporarily replace escaped double ampersands before splitting the commands
					tmpReplaceString = "\n\t!#DOUBLE_ESCAPED_AMPERSAND #+*~\n\t"
					commandInstance.command = commandInstance.command.replace("&&", tmpReplaceString)
					# Split command into first command and all the rest of the chain
					commandInstance.command, chainedCommands = commandInstance.command.split("&", 1)
					# Eliminating leading and trailing whitespaces with the first command
					if commandInstance.command.endswith(" "):
						commandInstance.command = commandInstance.command[:-1]
					if chainedCommands.startswith(" "):
						chainedCommands = chainedCommands[1:]
					# And restore the escaped && to a single & in the first command
					commandInstance.command = commandInstance.command.replace(tmpReplaceString, "&")
					# Restore && to && in the rest of the chain, as it will be split again later
					chainedCommands = chainedCommands.replace(tmpReplaceString, "&&")
				else:
					# No single & for splitting. So we only replace the escaped && with a normal &
					commandInstance.command = commandInstance.command.replace("&&", "&")
					chainedCommands = ""
			else:
				chainedCommands = ""

			# Mutable list will be passed to func. Commands "load" and "console" will
			# fill the first list entry with the command that should be executed now
			loadedCommand=[]

			# Execute corresponding function, relaying websocket connection and command
			# Functions returns whether it wants the connection to be kept open after execution
			shouldBeKeptOpen = await commandInstance.func(
				# Defining additional parameters needed for certain command functions
				loadedCommand=loadedCommand, # for console and load
			)

			# Just making sure that func can only returns bool or None:
			assert(shouldBeKeptOpen is None or type(shouldBeKeptOpen) is bool)

			# If the load function returned any prepared commands, put them into chainedCommands
			if len(loadedCommand) > 0:
				assert(type(loadedCommand[0]) is str)
				if chainedCommands.strip() == "":
					chainedCommands = loadedCommand[0]
				else:
					chainedCommands = loadedCommand[0] + " & " + chainedCommands
				# Just making sure, that the connection will definitely stay open
				shouldBeKeptOpen = True

			# If more chained commands are left over for processing, but func returned False and
			# settings require to close the connection in that case, print a debug message and
			# clear chained commands
			if setting.AMPERSAND_CHAINS_COMMANDS and len(chainedCommands) > 0:
				if shouldBeKeptOpen is False and \
					not setting.EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE:
					# Executed server command function returned False
					# and the settings specified to close the connection in this case
					msg = beautifulDebug.underline(chainedCommands)
					msg = 'Further chained commands ' + msg + \
						' will not be executed, because the command ' + commandInstance.command + \
						" provided a negative result, failed or threw an error!"
					# Tell the user why the commands will be ignored
					await commandInstance.senddebug(7, msg)
					# Clear chained commands list, so they won't be executed
					chainedCommands = ""
			
			# We have more chained (or loaded) commands to be executed:
			if len(chainedCommands) > 0:
				commandInstance.command = chainedCommands
				shouldBeKeptOpen = True

			# Check if executed function specified to close connection in return type
			if shouldBeKeptOpen is None:
				# Default. Set to True if normally should be kept open to wait for more commands
				# on the same client connection (this depends on the client implementation,
				# whether it opens new connections for each command)
				shouldBeKeptOpen = False
			
			if not shouldBeKeptOpen:
				if debugDisconnect:
					# Notifying the user of closing connection
					loggingFunctions.printlog(beautifulDebug.B_BLUE +
						f"x End of command processing. Disconnecting client on purpose.\n\n" +
						beautifulDebug.RESET, verbosity = -5)
				
				# Actively closing the connection
				await websocket.close()
				return True
			#else:
				# keep open, stay in the while(True) loop
			
			# Give other threads a chance to pass through. This should have a negligible effect
			# on performance exclusively on &-chained commands.
			if not setting.EXECUTE_REST_OF_CHAINED_COMMANDS_AFTER_FORCE_CLOSE:
				if len(chainedCommands) > 0:
					await sleep(0.001, "Chained commands " + str(chainedCommands))
				else:
					await sleep(0.001, "websocket connection that has been left open")

		except asyncio.CancelledError:
			# Command thread has been interrupted from outside, probably by command "server stop"
			errormsg = f"The coroutine of command " + commandInstance.command + \
				" has been interrupted from the outside! Command execution could not be finished properly."
			# Trying to at least transfer error message to client
			try:
				await commandInstance.senddebug(5, errormsg)
			except:
				# No chance, then just print and log it on the server
				loggingFunctions.printlog(beautifulDebug.B_RED + beautifulDebug.BOLD + errormsg + beautifulDebug.RESET,
				verbosity = 12)
			
			# Closing the current connection to the client
			loggingFunctions.printlog(beautifulDebug.special(5,0,3) +
				f"x Terminating connection due to outside interruption.\n\n" + beautifulDebug.RESET, verbosity = -3)
			await websocket.close()
			return False
		except websockets.exceptions.ConnectionClosedError:
			# Command thread has been interrupted from outside, probably by command "server stop"
			errormsg = f"ERROR responding to command " + commandInstance.command + \
				"! The connection has been closed by the client and is no longer available."
			# Trying to at least transfer error message to client
			try:
				await commandInstance.senddebug(7, errormsg)
			except:
				# No chance, then just print and log it on the server
				loggingFunctions.printlog(beautifulDebug.B_RED + beautifulDebug.BOLD + errormsg + beautifulDebug.RESET,
				verbosity = 12)
			
			# Closing the current connection to the client
			loggingFunctions.printlog(beautifulDebug.special(5,0,3) +
				f"x Terminating connection due to disconnected client.\n\n" + beautifulDebug.RESET, verbosity = -3)
			await websocket.close()
			return False
		except Exception:
			#if str(traceback.format_exc()).contains("The specified network name is no longer available")
			# If command execution failed somewhere, the server will print the exception,
			# close the current connection (so the client does not reach unspecified states)
			# and asyncio's run forever (in main program section at the bottom)
			# would continue listening for new connections
			errormsg = f"ERROR executing command " + commandInstance.command + \
				"! The following EXCEPTION was raised:\n" + traceback.format_exc()
			# Trying to at least transfer error message to client
			try:
				await commandInstance.senddebug(12, errormsg)
			except:
				# No chance, then just print and log it on the server
				loggingFunctions.printlog(beautifulDebug.B_RED + beautifulDebug.BOLD + errormsg + beautifulDebug.RESET,
				verbosity = 12)
			
			# Closing the current connection to the client anyways
			loggingFunctions.printlog(beautifulDebug.special(5,0,3) +
				f"x Terminating connection due to erroneous execution.\n\n" + beautifulDebug.RESET, verbosity = -3)
			await websocket.close()
			return False


# Starts the websocket server on the asyncio loop according to settings
def startServer():
	# Try to establish the server as often as the settings tell us
	# For example it might take a few tries on server restart, when the ip/port connection is still
	# being closed and the server wants to immediately open a new connection on the same address
	triesLeft = setting.TIMES_TO_RETRY_ESTABLISHING_SERVER
	while (triesLeft > 0):
		triesLeft -= 1
		
		errorMsg = None
		try:
			# Specify the server function and address
			newServer = websockets.serve(interactiveServer, setting.SERVER_IP, setting.SERVER_PORT)
			# asyncio: start specified server
			asyncio.get_event_loop().run_until_complete(newServer)
			# Great, print the success
			loggingFunctions.printlog(beautifulDebug.B_GREEN + "Websocket server has been started. " +
				"Listening for incoming connection requests...\n" +
				'From the corresponding websocket client, send the command "server info" '+
				'for a current status and a hint on what to do next ' +
				'or "help" for a list of available commands on this server.\n' +
				beautifulDebug.RESET, verbosity = -1)
			# Set triesLeft to 0 to avoid restarts after server shutdown
			triesLeft = 0

			# asyncio: listen forever for new websocket client connections to this server
			asyncio.get_event_loop().run_forever()
			
		except OSError:
			# OSError means probably that the server couldn't bind to the specified address
			errorMsg = beautifulDebug.special(5, 3, 0) + \
				"Cannot bind websocket server to desired address and port!\n"
			if errorMsg.find("OSError: ") > -1:
				# Generate a shorter error message with only the relevant parts
				errorMsg += errorMsg[errorMsg.find("OSError: "):]
			else:
				errorMsg += traceback.format_exc()
		except KeyboardInterrupt:
			# User interrupted server with keyboard
			loggingFunctions.printlog(beautifulDebug.special(4, 3, 0,
				"User interrupted server execution with keyboard interrupt." +
				" Server has been shut down unexpectedly."), verbosity = 5)
			triesLeft = 0
			sys.exit()
		except:
			# other unspecified error occured
			errorMsg = beautifulDebug.special(5, 3, 0) + \
				"Unexpected error occurred trying to establish the server!\n" + traceback.format_exc()
		
		if errorMsg is not None and len(errorMsg) > 0:
			errorMsg += "\n"
			# Telling the user how often we try again or that we give up:
			if triesLeft > 0:
				errorMsg += f"Trying {triesLeft} more times in " + \
				f"{setting.SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER} seconds.\n" + beautifulDebug.RESET
			else:
				errorMsg += beautifulDebug.RED + \
					"Address and port for the desired websocket connection are blocked!\n" + \
					"Giving up and shutting down the server.\n(It might help to terminate all " + \
					"running python tasks if the server was just running and has crashed)" + \
					beautifulDebug.RESET
			
			# Print and log this error message on high, almost critical error level
			loggingFunctions.printlog(errorMsg, verbosity = 19)

			if triesLeft == 0:
				# If out of tries, shut down the whole script before unspecified behaviour occurs
				sys.exit()
			else:
				# Otherwise, wait specified time before trying again
				time.sleep(setting.SECONDS_BETWEEN_TRIES_TO_ESTABLISH_SERVER)


yieldingCoroutines = set()

# Sleeps in an asynchronous manner while yielding other threads, can be cancelled with stopCoroutines
async def sleep(delay, description, hideInServerInfo = False):
	if hideInServerInfo:
		description = "#HIDDEN\n" + description
	global yieldingCoroutines
	task = asyncio.ensure_future(asyncio.sleep(delay))
	yieldingCoroutines.add((task, description))
	try:
		await task
	except asyncio.CancelledError:
		raise asyncio.CancelledError
	finally:
		yieldingCoroutines.remove((task, description))

# Stops and interrupts all ongoing coroutines
# Returns a list of descriptions of all the cancelled tasks
async def cancelYieldingCoroutines():
	global yieldingCoroutines
	if len(yieldingCoroutines) == 0:
		return []
	cancelledCoroutines = set()
	justTasks = set()
	for (task, description) in yieldingCoroutines:
		if task.cancel():
			cancelledCoroutines.add((task, description))
		justTasks.add(task)
	await asyncio.wait(justTasks)
	yieldingCoroutines -= cancelledCoroutines
	return [description for (_, description) in cancelledCoroutines]

# Stops and interrupts all ongoing coroutines
# Returns a list of descriptions of all the cancelled tasks
async def stopCoroutines():
	return await asyncio.create_task(cancelYieldingCoroutines())


# Shuts down the server after optionally displaying and sending the specified message
async def shutdownServer(websocket, text = None):
	if text is not None and len(text) > 0:
		await serverCommands.Request(websocket, "SERVER").senddebug(-1, "\n" + text, False)

	await stopCoroutines()

	# Interrupt all coroutines now before waiting for them to finish
	asyncio.get_event_loop().stop()
	
	# Slower, safer alternative:
	# Close the connection and stop all asyncio loop execution
	# This might take some times and wait for threads to finish
	#await websocket.close()
	#asyncio.get_event_loop().stop()
