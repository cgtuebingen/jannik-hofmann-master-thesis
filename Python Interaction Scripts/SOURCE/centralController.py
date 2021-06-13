#!/usr/bin/env python

# This module is the central controller of the python websocket server.
# It takes care of initializations after verifying user settings and setting the script path
# Most of work is done by the locally imported modules

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

if __name__ == '__main__':
	# Clearing screen for the start of this new session before the imports can display warnings
	if os.name == 'nt': # windows
		os.system('cls')
	else: # os.name == 'posix' # linux or mac
		os.system('clear')

# LOCAL IMPORTS
import serverCommands
import beautifulDebug
import serverSettings as setting
import loggingFunctions
import websocketServer as server
import visualizationSettings as design


# so other modules can access the current script location
def SCRIPT_PATH():
	return os.path.dirname(os.path.realpath(__file__))
	
# MAIN SECTION THAT CALLS EVERYTHING ELSE
if __name__ == '__main__':
	# verify user settings and check for warnings / recommendations
	setting.checkSettings()
	design.checkSettings()

	# initialize command list
	serverCommands.Request(None, None)

	# run websocket server with specified settings
	server.startServer()


	# enable this to warn of script end:
	#logging.warn("Websocket server has been shut down! " +
	#	"Asyncio is no longer waiting for client connections. End of program reached.", 19)
	