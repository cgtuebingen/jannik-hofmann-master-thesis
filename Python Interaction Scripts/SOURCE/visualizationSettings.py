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
	"default": .4,
}

class connections:
	display = True
	strength = 70
	color = .3

class layouting:
	horizontalSpaceBetweenGroupedLayers = 100
	bufferZone = 500
	horizontalSpaceBetweenLayers = 500
	verticalSpaceBetweenLayers = -400

	# SETTINGS FOR THE FORCE ALGORITHM:
	iterations = 1000
	debugDrawPlots = 40 # number of plots to draw
	# You need to close the drawn plot window on the server before the layout can be sent.
	# Put a 0 to not draw any plots

	# Finetune importance of certain rules during force algorithm iterations.
	# importance can be 'increasing' (0 at start), 'decreasing' (0 at end)
	# or 'midway' (0 at start and end, just multiplies increasing * decreasing)
	# exponentialCurveFactor 0 = linear, 1 = slight curve, 5 = really strong curve
	# positive: curved downward, negative: curved upward. example with factor 5:
	# https://www.wolframalpha.com/input/?i=%28e%5E%28+++++5+++++*x%29%2Fe-1%2Fe%29%2F%28e%5E%28+++++5+++++%29%2Fe-1%2Fe%29+in+x%3D%5B0%2C1%5D
	# Use importance = 'none' or strength = 0 to disable a rule
	class overlapRepulsion:
		strength = 3
		importance = 'increasing'
		exponentialCurveFactor = 1
	class gravity:
		strength = 1
		importance = 'decreasing'
		exponentialCurveFactor = 1
	class connectedAttraction:
		strength = 100
		importance = 'decreasing'
		exponentialCurveFactor = 1
	class shiftOnAxisToOrderByIndex:
		strength = 1000
		importance = 'midway'
		exponentialCurveFactor = 1
		




# INITIALIZATIONS

# revert capitalization and spaces, this is done to facilitate a more human-readable specification above.
layerColors = {key.lower().replace(" ", ""):value for (key, value) in layerColors.items()}
