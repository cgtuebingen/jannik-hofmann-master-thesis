#!/usr/bin/env python

# In this file, the user can specify preferences for the visualization in Unreal Engine.
# This includes color schemes, animations and other properties for visual representation

# LOCAL IMPORTS
import loggingFunctions

def onModuleReload(): checkSettings()

maxDrawWaitTimeout = 0.5 # seconds to wait for the command "server draw next" before resuming drawing
# This avoids getting stuck in infinite loops if the command "server draw next" hasn't been received properly
recheckDrawReadyInterval = .001 # in seconds, how often the algorithm rechecks if "server draw next" was received
# should be much smaller than maxDrawWaitTimeout
objectBatchSize = 1000 # how many objects/cuboids will be sent to the client in one batch via websocket response
checkSentBatchAfter = 120 # checks this number of seconds after the last queueCuboid call, that the batch has been sent
debugWhenDrawingObject = True # accompanies any object draw response (or batch of objects) with a debug msg to client
flipRGBtoBGR = True # Use this if the first activation layer has weird colors to swap red and blue channels

# Colors of different DNN layers, specified by their type as it appears in the model summary
# Spaces and capitalization will be ignored and reversed, also a "2d" at the end can be omitted
# Colors can be defined as tuple / list / single number (grayscale) using ranges 0-1 or 0-255,
# Also accepting strings containing hex code
layerColors = {
	"input layer": (0, .5, .6), # ocean blue
	"zero padding": (.3, .3, .4), # dark gray with a bit of violet

	"conv": (.8, .3, 0), # bright orange
	"batch normalization": (.4, 0, .9), # violet
	"activation": (.2, .3, .2), # dark army gray
	"add": (.5, .1, 0), # dark red
	"max pooling": (.6, .6, .0), # dark yellow

	"global average pooling": (.6, .8, .1), # very light blue
	"dense": (0, .2, .9), # blue
	"flatten": (0, .7, .1), # green

	# For anything unknown / unspecified
	"default": .4, # gray
}

class connections:
	display = True
	displayBetweenGroupedLayers = False
	strength = 70
	color = .3

# If a kernel setting is changed, the cached kernels will not be used by the algorithm,
# therefore new kernel textures will need to be recalculated when drawing them.
# With a few exceptions, this rule applies to a huge majority of the kernel settings.
class kernels:
	defaultPixelDimensions = (50, 50)
	minPixelDimensions = None
	maxPixelDimensions = None
	spacingBetweenKernels = (.5, .5) # if values <= 1, interpreted as percentage of pixel dimensions
	spacingFromLayer = 50 # scalar, horizontal spacing as kernels are to the side of layers
	thickness = .1 # if value <= 1, intepreted as percentage of pixel width
	wrapIfDimLeftover = True # when there are dimensions left over, the algorithm can wrap the kernel groups
	# instead of displaying them in one huge line
	brightness = 45 # default 50, black 0, white 100, changes the color brightness of kernels
	contrast = 70 # default 50, gray 0, black/white 100, changes kernel contrast and saturation at the same time
	spawnIndividualCuboids = False # otherwise spawns a plane with a rendered texture image of all the kernels.
	# Should be set to False
	useAlreadyCachedTextures = False # whether to use the already saved textures when they have been cached.
	# If True, does not recaculate kernels again unless forced to by the command or by spawnIndividualCuboids
	# You might want to deactivate this if the global variables change (e.g. with different checkpoints)
	hideSpacingBetweenSingles = True # When enabled, if each kernel has dims 1 x 1, removes spacing between them
	class renderTexture:
		displayTextureImage = False
		defaultPixelResolution = (100, 100) # determines resolution of each kernel pixel within the final texture image file
		# Basically pixels per one kernel pixel
		maxTextureResolution = 5000 # int defining the maximum pixel resolution at the longer edge of the texture file
		# A too small resolution might lead to aliasing patterns in the texture image
		antiAliasing = True # ensures that every pixel and spacing always has the same image resolution
		# might change the aspect ratio of the texture slightly or even increase the max resolution for huge kernels
		saveToRendersFolder = True # will save a copy of the rendered kernel texture to the renders folder
		opacity = 1

class saliency:
	normalizationFactor = None # normally saliency is always scaled to the max value.
	# Use this factor to specify a maximum number for the saliency scale. If anything
	# higher is encountered, the values will be fitted automatically anyways. None for auto scaling
	colormap = "magma" # see https://matplotlib.org/stable/gallery/color/colormap_reference.html
	brightness = 70 # default 50, lower colors 0, higher colors 100, changes the colormaps ramp up for saliency
	blurRadius = 1.5 # gaussian blur radius of the saliency map, 0 to disable
	opacityMinimum = 0 # opacity of the saliency map when saliency is at minimum
	opacityMaximum = 1 # opacity of the saliency map when saliency is at maximum. recommended to always be 1
	opacityBrightness = 50 # default 50, changes the ramp up of opacity for the saliency map
	# note: when calculating the saliency overlays' opacity, the brightness specified above is already included
	imageOpacity = 0.5 # 0 to deactivate showing the input image. resulting texture will not have any transparency,
	# but will just have more of a black background
	additiveMixing = False # whether the saliency map on top of the input image should be mixed additively
	# instead of classically with opacity mixing

class integratedGradients:
	normalizationFactor = .02 # normally gradients are always scaled to the max value.
	# Use this factor to specify a maximum number for the gradient scale. If anything
	# higher is encountered, the values will be fitted automatically anyways. None for auto scaling
	leaveColored = False # when True, gray (128 on all channels with opacityNeutral) will be used
	# for default and RGB channels become dark or bright depending on the integrated gradient on
	# that specific RGB channel. When set to False, all RGB channels are averaged before applying
	# the colormap and negativeColors defined below
	colormap = "invert" # can also be "invert" if negativeColors is a valid colormap
	negativeColors = "magma" # how to handle negative values. Can be another colormap, "invert" to
	# use the positive colormap with inverted hues or "continuous" to use the main colormap with
	# lowest color = negative gradient, middle color = neutral, highest color = positive gradient
	fuseColormaps = 0.2 # only relevant if opacityNeutral is larger than 0
	# set a float between 0 and 1 to define the area of fusing between color maps, recommended 0.1
	# set to 0 or False for a hard cutoff, do so if both colormaps start with the same color
	# set to "additive" if you want to add up both colormaps with additive color mixing
	brightness = 80 # default 50, lower colors 0, higher colors 100, changes the colormaps ramp up
	blurRadius = 1 # gaussian blur radius of the saliency map, 0 to disable
	# Might lead to undesired results with negativeColor = "continuous" as it shifts neutral middle color
	opacityNeutral = 0 # opacity of the integrated gradient when gradient is at neutral value
	opacityStrongest = 1 # opacity of the integrated gradient at strongest gradient. recommended to always be 1
	opacityBrightness = 50 # default 50, changes the ramp up of opacity for the saliency map
	# note: when calculating the saliency overlays' opacity, the brightness specified above is already included
	imageOpacity = 0.5 # 0 to deactivate showing the input image. resulting texture will not have any transparency,
	# but will just have more of a black background
	additiveMixing = False # whether the saliency map on top of the input image should be mixed additively
	# instead of classically with opacity mixing
	calculateDirectlyOnCpu = True # skips trying to calculate the gradients on GPU with cuda first
	cacheCalculationResults = True # enable if you keep changing the visualization settings and are
	# using the "server reload" command to apply the changes to a running server, to avoid waiting
	# for recalculation of the integrated gradients everytime. In that case you can use the command
	# "python ai.gradientCache = dict()" to empty the cache
	# disable if you are changing the source code of integrated gradient calculations or are loading
	# different NNs or weight configurations on top of each other. recommended to be False if unsure


class layouting:
	# Dimensions as single numbers or tuples: one value = uniform scaling,
	# two values = (xz axes, y axis), three values (x, z, y) in unreal
	# y axis is the horizontal layouting axis, in whose direction the information flows
	scaleLayerSizes = (50, 1)
	addToLayerSizes = (100, 20) # takes place after scaling
	# hard size cutoffs after scaling and adding
	minLayerDimensions = None
	maxLayerDimensions = None
	groupLinearlyConnectedLayers = True
	# specify desired spacing. buffer zone gets added to space between ungrouped layers
	horizontalSpaceBetweenGroupedLayers = 100
	bufferZone = 500
	horizontalSpaceBetweenLayers = 500
	verticalSpaceBetweenLayers = -400
	class renderGif:
		displayPlot = False
		# With this enabled, the layouting cannot run in an async thread and will block the server
		# You need to close the drawn plot window on the server before the layout can be sent
		# If saveAsGif is enabled too, this plot will not be displayed live, but just opens the gif file afterwards
		# (in this case, the server is not blocked from executing more)
		framesInAnimation = 20 # number of plots to draw during layouting iterations
		saveAsGif = False # needs framesInAnimation > 1
		plotSizeInches = (20, 10) # determines the plot size of the plot on your screen and the saved gif
		gifDpi = 100 # determines the resolution of the gif image file (multiplied with gifSizeInches)
		# without affecting the relative size of text and lines, like plotSizeInches would do
		animationLength = 2 # in seconds, determines how fast the gif will play

	# SETTINGS FOR THE FORCE ALGORITHM:
	iterations = 1200 # starting at 0, ending one below

	class classicRepulsion:
		strength = 1
		withinIterations = (0, 0.9)
	class gravity:
		strength = 1
		withinIterations = (0, 0.9)
		importance = 'decreasing'
		exponentialCurveFactor = 1
	class connectedAttraction:
		strength = 1
		withinIterations = (0, 0.9)
		importance = 'decreasing'
		exponentialCurveFactor = 1
	class shiftOnAxisToOrderByIndex:
		strength = 1.4
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
	#     'constant' (default, always strength),
	#     'increasing' (0 to strength, factor positive = curved downward, factor negative = curved upward),
	#     'decreasing' (strength to 0, factor positive = curved downward, factor negative = curved upward),
	#     'midway' (mirrored, 0 at start and end, strength in the middle, recommended with negative factor,
	#         factor = 0: /\, factor higher = strong peak _/\_, negative factor = round, convex shape /°°\)
	#     'outsides' (mirrored exactly opposite to midway, strength at start and end, 0 in the middle,
	#         recommended with positive factor, factor = 0: \/, factor higher = \__/ round in the middle
	#         with strong peaks outside, negative factor = °\/° strong downward peak in the middle)
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
