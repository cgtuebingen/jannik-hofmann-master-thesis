#!/usr/bin/env python

# This module can incorporate and remove ansi escope code sequences in order to format
# the console output for a more legible debugging experience

# USED LIBRARIES
import re
import os
import math

# LOCAL IMPORTS
import serverSettings as setting

# Returns a simple or complicated ansi foreground text color code as str for console formatting
def ansicode(value, simpleCode = True):
	if simpleCode:
		return f'\033[{value}m'
	else:
		return f'\u001b[38;5;{value}m'

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
		r //= 3
		g //= 3
		b //= 3
		bright = r+g+b >= 8
		code = 90 if bright else 30
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
			withintext = withintext.replace(word + text,
				word + underline(text))
		return withintext

# Removes any formatting ansi escape codes applied by this module. Should be used for log files
def removeAnsiEscapeCharacters(text):
	text = re.sub("\033\\[[0-9]*m", "", text)
	text = re.sub("\u001b\\[[0-9\\;]*m", "", text)
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
		colorcode = RED + BOLD if setting.FORMAT_OUTPUT.ONLY_USE_SIMPLE_ANSI_CODES else special(4, 0, 0) + BOLD + NEGATIVE

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
		return os.get_terminal_size()[0]
	except:
		return 80

def getCleanLinebreak(text, width = None, splitAtSpaces = True):
	if width is None:
		width = consoleWidth()
	text = text.strip()
	text_line = text[:width]
	if '\n' in text_line:
		return text.split('\n', 1)
	elif splitAtSpaces and len(text) > len(text_line) and text_line[:-1] != ' ' and \
		text[width] != ' ' and ' ' in text_line:
			text_line = text_line.rsplit(' ', 1)[0]
			return text_line, text[len(text_line)+1:]
	else:
		return text_line, text[len(text_line):]

def printWithLinebreaks(text):
	while len(text):
		text_line, text = getCleanLinebreak(text)
		print(text_line)

def mapToText(map, spacing = 3, line_width = None, key_width = None, splitAtSpaces = True,
	before_key = '', after_key = '', before_value = '', after_value = '', auto_adjust_column_length = True):

	if line_width is None:
		line_width = consoleWidth()

	key_lengths = [len(before_key + after_key + key) for key, value in map.items()]
	value_lengths = [len(before_value + after_value + value) for key, value in map.items()]
	if key_width is None:
		key_width = sum(key_lengths) / sum(value_lengths) # ratio of average lengths
	if type(key_width) is float:
		key_width = int(math.floor((line_width - spacing) * key_width))
	key_width = max(key_width, line_width - spacing - max(value_lengths)) # adapt to short values
	key_width = min(key_width, max(key_lengths)) # adapt to short keys
	output = ""
	for key, value in map.items():
		key = before_key + str(key) + after_key
		value = before_value + str(value) + after_value
		while len(key) or len(value):
			key_line, key = getCleanLinebreak(key, key_width, splitAtSpaces)
			value_line, value = getCleanLinebreak(value,
				line_width - spacing - key_width, splitAtSpaces)
			spaces = ' ' * (spacing + key_width - len(key_line))
			output += key_line + spaces + value_line + '\n'
	return output[:-1] # removing last '\n'
