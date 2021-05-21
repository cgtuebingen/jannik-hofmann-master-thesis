#!/usr/bin/env python

# In this file, the user can specify preferences for the visualization in Unreal Engine.
# This includes color schemes, animations and other properties for visual representation

# LOCAL IMPORTS
import loggingFunctions

def onModuleReload(): checkSettings()

maxDrawWaitTimeout = 60 # seconds to wait for the command "server draw next" before resuming drawing
# This avoids getting stuck in infinite loops if the command "server draw next" hasn't been received properly
objectBatchSize = 1000 # how many objects/cuboids will be sent to the client in one batch via websocket response
checkSentBatchAfter = 120 # checks this number of seconds after the last queueCuboid call, that the batch has been sent

# Colors of different DNN layers, specified by their type as it appears in the model summary
# Spaces and capitalization will be ignored and reversed, also a "2d" at the end can be omitted
# Colors can be defined as tuple / list / single number (grayscale) using ranges 0-1 or 0-255,
# Also accepting strings containing hex code
layerColors = {
	"input layer": (0, .5, .6, .5),
	"zero padding": (.3, .3, .4),

	"conv": (.8, .3, 0),
	"batch normalization": (.4, 0, .9),
	"activation": (.2, .3, .2),
	"add": (.5, .1, 0),
	"max pooling": (.6, .6, .0),

	"global average pooling": (.6, .8, .1),
	"dense": (0, .2, .9),
	"flatten": (0, .7, .1),

	# For anything unknown / unspecified. This "default" value always needs to exist!
	"default": .4,
}

class connections:
	display = True
	displayBetweenGroupedLayers = False
	strength = 70
	color = .3

class kernels:
	defaultPixelDimensions = (50, 50)
	minPixelDimensions = None
	maxPixelDimensions = None
	spacingBetweenKernels = (.5, .5) # if values <= 1, interpreted as percentage of pixel dimensions
	spacingFromLayer = 50 # scalar, horizontal spacing as kernels are to the side of layers
	thickness = .1 # if value <= 1, intepreted as percentage of pixel width
	wrapIfDimLeftover = True # when there are dimensions left over, the algorithm can wrap the kernel groups
	brightness = 45 # default 50, black 0, white 100, changes the color brightness of kernels
	contrast = 70 # default 50, grey 0, black/white 100, changes kernel contrast and saturation at the same time
	debugPlotOnServer = True # After creating drawing instructions to the (UE4) client, plot the 
	# kernels on a matplotlib drawing and open a window on the server
	# (this also blocks other processes from running until the window is closed!)

class layouting:
	# Dimensions as single numbers or tuples: one value = uniform scaling,
	# two values = (xz axes, y axis), three values (x, z, y) in unreal
	# y axis is the horizontal layouting axis, in whose direction the information flows
	scaleLayerSizes = (50, 1)
	addToLayerSizes = (100, 20) # takes place after scaling
	# hard size cutoffs after scaling and adding
	minLayerDimensions = None
	maxLayerDimensions = None
	# specify desired spacing. buffer zone gets added to space between ungrouped layers
	horizontalSpaceBetweenGroupedLayers = 100
	bufferZone = 500
	horizontalSpaceBetweenLayers = 500
	verticalSpaceBetweenLayers = -400

	# SETTINGS FOR THE FORCE ALGORITHM:
	iterations = 1200 # starting at 0, ending one below
	class debug:
		drawPlots = False # If this is False, this whole debug section will be deactivated
		# With this enabled, the layouting cannot run in an async thread and will block the server
		# You need to close the drawn plot window on the server before the layout can be sent
		numberOfPlots = 20 # number of plots to draw during layouting iterations
		saveAsGif = False # needs drawPlots True and numberOfPlots > 1
		gifSizeInches = (20, 10) # determines the resolution of the gif, might depend on your screens dpi
		gifFps = 10 # How fast the gif will play. Also depends on the number of plots defined above

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
		#withinIterations = (0, 0.9)
		importance = 'increasing'
		#importance = 'midway'
		exponentialCurveFactor = -3
	class overlapRepulsion:
		strength = 3
		importance = 'increasing'
		exponentialCurveFactor = 3
	# Finetune importance of certain rules during force algorithm iterations.
	# withinIterations can be a single number or a tuple defining a range ([inclusive start,] exclusive end[, steps])
	#     Also accepts floats, which will automatically multiply with iterations
	# importance can be
	#     'constant' (default, always 1),
	#     'increasing' (0 to 1, factor positive = curved downward, factor negative = curved upward),
	#     'decreasing' (1 to 0, factor positive = curved downward, factor negative = curved upward),
	#     'midway' (mirrored, 0 at start and end, 1 in the middle, recommended with negative factor,
	#         factor = 0: /\, factor higher = strong peak _/\_, negative factor = round, convex shape /°°\)
	#     'outsides' (mirrored exactly opposite to midway, 1 at start and end, 0 in the middle,
	#         factor = 0: \/, factor higher = \__/ round in the middle with strong peaks outside,
	#         negative factor = °\/° strong downward peak in the middle)
	# exponentialCurveFactor 0 = linear, 1 = slight curve, 5 = really strong curve
	#     example with factor 5: https://www.wolframalpha.com/input/?i=%28e%5E%28+++++5+++++*x%29%2Fe-1%2Fe%29%2F%28e%5E%28+++++5+++++%29%2Fe-1%2Fe%29+in+x%3D%5B0%2C1%5D
	# Use importance = 'disabled', strength = 0 or withinIterations = None to disable a rule



# INITIALIZATIONS AND SETTINGS CHECKS

def checkSettings():
	global layerColors
	# revert capitalization and spaces, this is done to facilitate a more human-readable specification above.
	layerColors = {key.lower().replace(" ", ""):value for (key, value) in layerColors.items()}
	# Convert withinIterations from numbers into ranges, and multiply floats with the absolute number of iterations
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
		# Also warn if anything of that range is outside of the number of specified iterations
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