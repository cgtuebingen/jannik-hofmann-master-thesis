#!/usr/bin/env python

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

	"default": (.4),
}
layerColors = {key.lower().replace(" ", ""):value for (key, value) in layerColors.items()}
