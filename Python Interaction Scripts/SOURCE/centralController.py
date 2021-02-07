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

# LOCAL IMPORTS
import serverSettings as setting
import websocketServer as server
import loggingFunctions
import beautifulDebug


# so other modules can access the current script location
def SCRIPT_PATH():
    return os.path.dirname(os.path.realpath(__file__))

# Clearing screen for the start of this new session
beautifulDebug.clearScreen()

# verify user settings and check for warnings / recommendations
setting.checkSettings()

# run websocket server with specified settings
server.startServer()


# enable this to warn of script end:
#logging.warn("Websocket server has been shut down! " +
#	"Asyncio is no longer waiting for client connections. End of program reached.", 19)
 