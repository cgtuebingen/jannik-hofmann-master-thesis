#!/usr/bin/env python

"""
 This file beautifulDebug.py is part of NeuralVisUAL.
 
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

# This module can incorporate and remove ansi escope code sequences in order to format
# the console output for a more legible debugging experience

# USED LIBRARIES
from posixpath import split
import re
import os
import math
import numpy as np

# LOCAL IMPORTS
import serverSettings as setting
import fileHandling

# Returns a simple or complicated ansi foreground text color code as str for console formatting
def ansicode(value, simpleCode = True):
	prefix = ' ' if setting.FORMAT_OUTPUT.USE_ALTERNATIVE_ANSI_CODE_WORKAROUND else ''
	prefix += '\033[' if simpleCode else '\u001b['
	if setting.FORMAT_OUTPUT.USE_ALTERNATIVE_ANSI_CODE_WORKAROUND: prefix += '\b'
	if not simpleCode: prefix += '38;5;'
	return prefix + str(value) + 'm'

# Ansi Colors for nice formatting of console output
RED = ansicode(31)
GREEN = ansicode(32)
YELLOW = ansicode(33)
BLUE = ansicode(34)
MAGENTA = ansicode(35)
CYAN = ansicode(36)
GREY = ansicode(90)
GRAY = ansicode(90)
B_RED = ansicode(91)
B_GREEN = ansicode(92)
B_YELLOW = ansicode(93)
B_BLUE = ansicode(94)
B_MAGENTA = ansicode(95)
B_CYAN = ansicode(96)
WHITE = ansicode(97)
BOLD = ansicode(1)
UNDERLINE = ansicode(4)
DISABLE_UNDERLINE = ansicode(24)
NEGATIVE = ansicode(7)
RESET = ansicode(0) #+ '\u001b[48;5;235m' + '\u001b[38;5;252m'
	# last two parts specify an almost black background with almost white text

# applies r/b/g text colors, values for r, g, b range from 0 to 5
# if a text is given, the formatting will be applied, followed by a reset code
def special(r, g, b, text = None):
	if text is not None:
		return special(r, g, b) + text + RESET
	if not setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES:
		return ansicode(16 + 36*r + 6*g + b, False)
	else:
		r //= 3; g //= 3; b //= 3
		code = 90 if r+g+b >= 8 else 30
		code += r + 2*g + 4*b
		if r==g==b:
			if r+g+b < 8:
				code = 90
			elif r+g+b < 12:
				code = 37
			else:
				code = 97
		return ansicode(code)
		
# applied grayscale text colors, value ranges from 0 (almost black) to 23 (almost white)
# if a text is given, the formatting will be applied, followed by a reset code
def grayscale(w, text = None):
	if text is None:
		return ansicode(232 + w, False)
	else:
		return grayscale(w) + text + RESET


# underlines the specified text.
# optionally underlines all occurences within another text.
# and optionally only if preceding by any of an array of specified words
def underline(text, withintext = None, precedingWords = None, dontUnderlineUnderscores = True):
	if withintext is None:
		if dontUnderlineUnderscores:
			text = text.replace('_', DISABLE_UNDERLINE + '_' + UNDERLINE)
		return UNDERLINE + text + DISABLE_UNDERLINE
	elif precedingWords is None or len(precedingWords) == 0:
		return withintext.replace(text, underline(text))
	else:
		if type(precedingWords) is str:
			precedingWords = [precedingWords]
		for word in precedingWords:
			if not word.endswith(" "):
				word += " "
			withintext = withintext.replace(word + text, word + underline(text))
		return withintext

# Removes any formatting ansi escape codes applied by this module. Should be used for log files
def removeAnsiEscapeCharacters(text):
	text = re.sub("\033\\[[0-9]*m", "", text)
	text = re.sub(" \033\\[\b[0-9]*m", "", text)
	text = re.sub("\u001b\\[[0-9\\;]*m", "", text)
	text = re.sub(" \u001b\\[\b[0-9\\;]*m", "", text)
	return text


# Formats a text according to the debug/status level given and optionally underlines a command
# that follows the specified preceding words (if any are given)
# If no text is specified, this function will return the level-specific ansi colorcode as string
# to be used for formatting
def formatLevel(level, text = "", levelIsDebugLevel = True, commandToUnderline = ""):
	# debug info from dark gray to bright gray
	if levelIsDebugLevel and level < 0:
		colorcode = grayscale(max(14 + level, 4))
	# negative status values
	elif level == -30: # success / completd
		colorcode = B_GREEN
	elif level == -20: # idle / waiting for inpt
		colorcode = CYAN
	elif level == -10: # processig
		colorcode = B_BLUE

	# undefined for debug level 0 and status values <= 0 (except -10, -20, -30)
	elif level <= 0:
		colorcode = B_YELLOW + NEGATIVE

	# warning rgb value from 2,2,0 via 5,5,3 via 5,5,0 to 5,3,0 (5 is max.)
	elif level <= 4:
		colorcode = YELLOW + BOLD if setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES else special(level+1, level+1, level-1) + BOLD
	elif level <= 7:
		colorcode = YELLOW + BOLD if setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES else special(5, 5, 7-level) + BOLD
	elif level <= 9:
		colorcode = YELLOW + BOLD if setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES else special(5, 12-level, 0) + BOLD

	# error rgb value from 2,0,0 to 5,0,0 (5 is max.)
	elif level < 20:
		colorcode = RED + BOLD if setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES else special(int(round(2 + (level-10)/3, 0)), 0, 0) + BOLD
	
	# critical failure
	else: # level >= 20
		colorcode = RED + BOLD if setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES else special(5, 0, 0) + BOLD + NEGATIVE

	# If no text has been specified, just return the colorcode corresponding to that level
	if text == "":
		return colorcode
	
	# Underline the command if there was one given and it's not just whitespace
	if commandToUnderline is not None and \
		len(commandToUnderline) > 0 and \
		len(commandToUnderline.split()) > 0:

		text = underline(commandToUnderline, text, [" about", " with", "command", "Command"])
		# The replace function might underline parts of the text that contain the command in a
		# sentence. However, this is negligible as it's just for formatting purposes.

	# Return the formatted text, followed by a reset signal for default future output
	return colorcode + text + RESET


def clearScreen():
	if os.name == 'nt': # windows
		os.system('cls')
	else: # os.name == 'posix' # linux or mac
		os.system('clear')


def consoleWidth():
	try:
		return int(os.get_terminal_size()[0])
	except:
		return 80

# negative width or width 0 will be relative to consoleWidth
def getCleanLinebreak(text, width = 0, splitAt = ' '):
	if width < 1: # automatic width from console
		width += consoleWidth()
	if len(text) <= width: # text smaller than width, doesn't need to be split
		return text, ""
	text_line = text[:width]
	if '\n' in text_line: # split at first \n
		return text.split('\n', 1)
	if splitAt is True:
		splitAt = ' '
	if splitAt in [False, None, ""] or not any(d in text_line for d in splitAt):
		# no delimiter applies for a split within width, just splitting at width
		return text_line, text[len(text_line):]
	if text[width] in [d for d in splitAt if d.isspace()]:
		# space directly after width, so split at whole width and remove space in next line
		return text_line, text[len(text_line)+1:]
	if text_line[-1] in splitAt:
		# directly at end of text_line (of length width) we have a delimiter
		# split there, and remove it if it's a space
		if text_line[-1].isspace():
			return text_line[:-1], text[len(text_line):]
		else:
			return text_line, text[len(text_line):]
	# search for a valid delimiter in text_line, starting at the end
	for i in range(width-1, 0, -1):
		if text_line[i] in splitAt:
			# split there, and if it's a space, remove it
			if text_line[i].isspace():
				return text[:i], text[i+1:]
			else:
				return text[:i+1], text[i+1:]
	# code shouldn't reach here, but if it does, fall back to simply splitting at width
	return text_line, text[len(text_line):]

def printWithLinebreaks(text, delimiters=' ', autoDetectIndent=True):
	if '\n' in text:
		for line in text.split('\n'):
			printWithLinebreaks(line, delimiters)
	else:
		indent = 0
		while autoDetectIndent and text.startswith(' '):
			text = text[1:]
			indent += 1
		while text:
			text_line, text = getCleanLinebreak(text, splitAt=delimiters, width=-indent)
			print(' '*indent + text_line)

def indent(text, prefix=2, prefixOnlyInFirstLine=True):
	if type(prefix) is int:
		prefix = ' ' * prefix
	indent = ' ' * len(prefix) if prefixOnlyInFirstLine else prefix
	return prefix + text.replace('\n', '\n' + indent)

def shortenVar(var, shortenOverLen=300, previewLen=200):
	vartype = str(type(var)).split("'")[1]
	vartype = vartype.replace("numpy.ndarray", "ndarray")
	if len(str(var)) <= shortenOverLen:
		if type(var) is str:
			return f'{vartype}: "{var}"'
		if type(var) is chr:
			return f"{vartype}: '{var}'"
		return vartype + ": " + str(var)
	if type(var) is np.ndarray:
		return f'{vartype} ({var.shape})'
	output = vartype
	try: output += " of length " + str(len(var))
	except: pass
	output += f" ({fileHandling.formatFilesize(var)})"
	output += ':\n' + str(var)[:previewLen] + '...'
	return output

# prints out a 2-dimensional list as a table
def listToMap(two_dim_list):
	map = {}
	for index, entry in enumerate(two_dim_list):
		if type(entry) in [list, tuple]:
			key, *value = entry
		key = str(index) + '%' + key
		if len(value) == 1:
			value = value[0]
		value = str(value)
		map[key] = value
	return map

# Also accepts lists instead of map
def mapToText(map, spacing = 3, line_width = -2, key_width = .25, splitAtSpaces = True,
	before_key = '', after_key = '', before_value = '', after_value = '',
	treatKeys = lambda x: x, treatValues = lambda x: x):

	if len(map) == 0:
		return ""
	
	if type(map) is list:
		map = listToMap(map)
		def newTreatKeys(key):
			return treatKeys(key.split('%', 1)[1])
	else:
		newTreatKeys = treatKeys

	if line_width < 1:
		line_width += consoleWidth()

	# treating values
	map = {key: treatValues(value) for (key, value) in map.items()}

	key_lengths = [len(before_key + newTreatKeys(str(key)) + after_key) for key, _ in map.items()]
	value_lengths = [len(before_value + str(value) + after_value) for _, value in map.items()]
	if key_width is None:
		key_width = sum(key_lengths) / sum(value_lengths) # ratio of average lengths
	if type(key_width) is float:
		key_width = int(math.floor((line_width - spacing) * key_width))
	key_width = max(key_width, line_width - spacing - max(value_lengths)) # adapt to short values
	key_width = min(key_width, max(key_lengths)) # adapt to short keys
	output = ""
	for key, value in map.items():
		key = before_key + newTreatKeys(str(key)) + after_key
		value = before_value + str(value) + after_value
		while len(str(key)) or len(str(value)):
			key_line, key = getCleanLinebreak(str(key), key_width, splitAtSpaces)
			value_line, value = getCleanLinebreak(str(value),
				line_width - spacing - key_width, splitAtSpaces)
			spaces = ' ' * (spacing + key_width - len(key_line))
			output += key_line + spaces + value_line + '\n'
	return output[:-1] # removing last '\n'

def roundNonZeroDigits(number, relevantDigits):
	assert type(number) in [int, float, np.float64, np.float32]
	assert relevantDigits > 0
	return eval(f"%.{relevantDigits-1}e" % number)

def floatToShortStr(number, significantDigits=4):
	def noend(result):
		result = str(result)
		return result[:-2] if result.endswith(".0") else result
	if len(noend(number)) <= significantDigits:
		result = noend(number)
	else:
		order = int(("%e" % number).replace('-','+-').split('+')[1]) + 1
		if -4 < order <= significantDigits + 4:
			digits = significantDigits
			result = noend(roundNonZeroDigits(number, digits))
			while len(noend(roundNonZeroDigits(number, digits+1))) <= len(result) and not math.isclose(eval(result), number):
				digits += 1
				result = noend(roundNonZeroDigits(number, digits))
		else:
			result = f"%.{significantDigits-1}e" % number
	if 'e' not in result and '.' in result:
		while result.endswith("0"): result = result[:-1]
		if result.endswith("."): result = result[:-1]
	result = result.replace("e+0", "e+").replace("e-0", "e-").replace(".e", "e")
	if len(result) > significantDigits:
		while '.' in result and "0e" in result: result = result.replace("0e", "e")
		result = result.replace(".e", "e")
	if len(result) > significantDigits:
		if result.startswith("0."): result = result[1:]
	return result
