#!/usr/bin/env python

# In this file, the user can specify preferences for the visualization in Unreal Engine.
# This includes color schemes, animations and other properties for visual representation

# LOCAL IMPORTS
import loggingFunctions

# Colors of different DNN layers, specified by their type as it appears in the model summary
# (spaces and capitalization will be ignored and reversed)
# Colors can be defined as tuple / list / single number (grayscale) using ranges 0-1 or 0-255, or as string containing hex code
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

ITERATIONS = 1200

class layouting:
	scaleLayerSizes = (50, 50, 1)
	horizontalSpaceBetweenGroupedLayers = 100
	bufferZone = 500
	horizontalSpaceBetweenLayers = 500
	verticalSpaceBetweenLayers = -400

	# SETTINGS FOR THE FORCE ALGORITHM:
	iterations = ITERATIONS # exclusive this one, starting at 0, ending one below
	debugDrawPlots = 12 # number of plots to draw
	# You need to close the drawn plot window on the server before the layout can be sent. Put a 0 to not draw any plots

	class classicRepulsion:
		strength = 1
		withinIterations = (0, 0.9)
	class gravity:
		strength = 1
		withinIterations = (0, 0.9)
		importance = 'decreasing'
		exponentialCurveFactor = 1
	class connectedAttraction:
		strength = 100
		withinIterations = (0, 0.9)
		importance = 'decreasing'
		exponentialCurveFactor = 1
	class shiftOnAxisToOrderByIndex:
		strength = 140
		importance = 'increasing'
		#importance = 'midway'
		#withinIterations = (0, 0.9)
		exponentialCurveFactor = -3
	class overlapRepulsion:
		strength = 3
		importance = 'increasing'
		exponentialCurveFactor = 3
	# Finetune importance of certain rules during force algorithm iterations.
	# withinIterations can be a single number or a tuple defining a range ([inclusive start,] exclusive end[, steps])
	# Also accepts floats, which will automatically multiply with iterations
	# importance can be 'constant' (default, always 1), 'increasing' (0 to 1), 'decreasing' (1 to 0),
	# 'midway' (0 at start and end, 1 in the middle, mirrored, recommended with negative factor,
	# factor = 0: /\, factor higher = strong peak _/\_, negative factor = round, convex shape /°°\)
	# 'outsides' (mirrored exactly opposite to midway, 1 at start and end, 0 in the middle,
	# factor = 0: \/, factor higher = \__/ round in the middle with strong peaks outside,
	# negative factor = °\/° strong downward peak in the middle)
	# exponentialCurveFactor 0 = linear, 1 = slight curve, 5 = really strong curve
	# positive: curved downward, negative: curved upward. example with factor 5:
	# https://www.wolframalpha.com/input/?i=%28e%5E%28+++++5+++++*x%29%2Fe-1%2Fe%29%2F%28e%5E%28+++++5+++++%29%2Fe-1%2Fe%29+in+x%3D%5B0%2C1%5D
	# Use importance = 'disabled', strength = 0 or withinIterations = None to disable a rule



# INITIALIZATIONS

def checkSettings():
	global layerColors
	# revert capitalization and spaces, this is done to facilitate a more human-readable specification above.
	layerColors = {key.lower().replace(" ", ""):value for (key, value) in layerColors.items()}
	def fixAndCheckWithinIterations(rule):
		if not hasattr(rule, 'withinIterations'):
			return
		if type(rule.withinIterations) is int:
			rule.withinIterations = [rule.withinIterations]
		if type(rule.withinIterations) is float:
			rule.withinIterations = [round(rule.withinIterations * layouting.iterations, 0)]
		if type(rule.withinIterations) is tuple:
			if any(type(value) is float for value in rule.withinIterations):
				rule.withinIterations = tuple(int(round(value * layouting.iterations, 0)) for value in rule.withinIterations)
			if len(rule.withinIterations) == 1:
				rule.withinIterations = [rule.withinIterations[0]]
			elif len(rule.withinIterations) == 2:
				rule.withinIterations = range(rule.withinIterations[0], rule.withinIterations[1])
			elif len(rule.withinIterations) > 2:
				rule.withinIterations = range(rule.withinIterations[0], rule.withinIterations[1],
					rule.withinIterations[2])
		if min(rule.withinIterations) < 0 or max(rule.withinIterations) > layouting.iterations:
				loggingFunctions.warn("Visualization settings, layouting: withinIterations of " +
					f'{rule=}'.split('=')[0] + " contains values outside of the iterations range, " +
					"layouting might not be executed properly. Please note that iterations start " +
					"at 0 and end one before the number of iterations.", 5)
	fixAndCheckWithinIterations(layouting.classicRepulsion)
	fixAndCheckWithinIterations(layouting.overlapRepulsion)
	fixAndCheckWithinIterations(layouting.gravity)
	fixAndCheckWithinIterations(layouting.connectedAttraction)
	fixAndCheckWithinIterations(layouting.shiftOnAxisToOrderByIndex)
