#!/usr/bin/env python

# This module handles files, os paths and everything related to it

# USED LIBRARIES
import os
import shutil

# Counts files in this directory and all subdirectories
def filecount(path, pathjoin=None):
	if pathjoin is not None:
		path = os.path.join(path, pathjoin)
	return sum([len(files) for _, _, files in os.walk(path)])

# Calculates the size of the folder (sum of all contained files in this directory and all subdirectories)
def foldersize(path, pathjoin=None):
	if pathjoin is not None:
		path = os.path.join(path, pathjoin)
	return formatFilesize(sum([
		sum([os.stat(os.path.join(root, file)).st_size for file in files])
		for root, _, files in os.walk(path)
	]))

def getSubdirectories(path):
	return os.listdir(path)

def deleteDirectoryContent(path):
	for filename in os.listdir(path):
		filepath = os.path.join(path, filename)
		try:
			shutil.rmtree(filepath)
		except OSError:
			os.remove(filepath)
	try:
		shutil.rmtree(path)
	except OSError:
		os.remove(path)

def formatFilesize(data):
	if type(data) is int:
		filesize = data
	elif type(data) is bin:
		filesize = len(data)
	else:
		filesize = len(str(data))
	units = "B KB MB GB TB PB EB ZB YB".split(' ')
	while filesize > 1000 and len(units) > 1:
		filesize /= 1000
		units.pop(0)
	return str(round(filesize, 2)) + ' ' + units[0]

# Adds the server script path to a given path if it starts with / or \
def addServerScriptPath(filepath):
	import centralController
	# to be able to retrieve SCRIPT_PATH()
	# needs to be in this function to avoid circular module imports
	assert type(filepath) is str
	if filepath.startswith(('\\', '/')):
		return centralController.SCRIPT_PATH() + filepath
	else:
		return filepath

# Ensures that this path ends in a folder path separator
def ensureFolderEnding(filepath, remove=False):
	if type(filepath) is list and len(filepath) == 2:
		return [ensureFolderEnding(filepath[0], remove), filepath[1]]
	assert type(filepath) is str
	if filepath.endswith(('\\', '/')):
		if remove:
			return filepath[:-1]
		return filepath
	else:
		if remove:
			return filepath
		return filepath + os.path.sep

# Returns a tuple of path and filename
def separateFilename(filepath):
	result = filepath.rsplit('/', 1)
	if len(result) == 2:
		return ensureFolderEnding(result, remove=True)
	result = filepath.rsplit('\\', 1)
	if len(result) == 2:
		return ensureFolderEnding(result, remove=True)
	return ensureFolderEnding(filepath, remove=True)

# Checks that the file path exists and creates the dir structure if not
def createFilepath(filepath):
	assert type(filepath) is str
	if '.' in separateFilename(filepath)[1]:
		# path ends with a file name, not with a folder
		filepath = separateFilename(filepath)[0]
	filepath = ensureFolderEnding(filepath, remove=True)
	if not os.path.exists(filepath):
		os.makedirs(filepath)
