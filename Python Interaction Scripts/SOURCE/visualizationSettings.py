#!/usr/bin/env python

# In this file, the user can specify preferences for the visualization in Unreal Engine.
# This includes color schemes, animations and other properties for visual representation

# Colors of different DNN layers, specified by their type as it appears in the model summary
# (spaces and capitalization will be ignored and reversed)
layerColors = {
	"input layer": (0, .5, .6),
	"zero padding 2d": (.3, .3, .4),

	"conv 2d": (.8, .3, 0),
	"batch normalization": (.4, 0, .9),
	"activation": (.2, .3, .2),
	"add": (.5, .1, 0),
	"max pooling 2d": (.6, .6, .0),

	"global average pooling 2d": (.6, .8, .1),
	"dense": (0, .2, .9),
	"flatten": (0, .7, .1),

	# For anything unknown / unspecified. This "default" value always needs to be kept!
	"default": (.4),
}

drawConnections = True
connectionColor = .3
connectionStrength = 70
additionalDistanceBetweenUnconnectedLayers = True

# INITIALIZATIONS

# revert capitalization and spaces, this is done for a more human-readable specification above.
layerColors = {key.lower().replace(" ", ""):value for (key, value) in layerColors.items()}
