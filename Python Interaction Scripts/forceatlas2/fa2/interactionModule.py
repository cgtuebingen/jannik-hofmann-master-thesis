"""
 This file interactionModule.py is part of NeuralVisUAL.
 
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

import networkx as nx
from forceatlas2 import ForceAtlas2
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation

NUMBER_OF_NODES = 100
MAX_NODE_SIZE = 50
CONNECTION_RATIO = 0.1
G = nx.random_geometric_graph(NUMBER_OF_NODES, CONNECTION_RATIO)
SIZES = None
SIZES = np.random.random_sample((NUMBER_OF_NODES, 2)) * MAX_NODE_SIZE
NUMBER_OF_ITERATIONS = 1000
NUMBER_OF_PLOTS = 20

#print(f"Selected settings: {NUMBER_OF_NODES} nodes, connection ratio of {CONNECTION_RATIO} and max size {MAX_NODE_SIZE}. Calculating {NUMBER_OF_ITERATIONS} iterations and drawing {NUMBER_OF_PLOTS} plots.")

forceatlas2 = ForceAtlas2(
                        # Behavior alternatives
                        outboundAttractionDistribution=True,  # Dissuade hubs
                        linLogMode=False,  # NOT IMPLEMENTED
                        adjustSizes=False,  # Prevent overlap (NOT IMPLEMENTED)
                        edgeWeightInfluence=1.0,
                        orderconnectedQuadsOnXaxis=True, # orders connected nodes by their index on x axis
                        desiredHorizontalSpacing=0, # spacing between the nodes
                        desiredVerticalSpacing=0, # spacing between the nodes
                        bufferZone=10,

                        # Performance
                        jitterTolerance=1.0,  # Tolerance
                        barnesHutOptimize=False,
                        barnesHutTheta=1.2,
                        multiThreaded=False,  # NOT IMPLEMENTED

                        # Tuning
                        scalingRatio=2.0,
                        strongGravityMode=False,
                        gravity=1.0,

                        # Log
                        verbose=False,
                        debugDisplayPlot=NUMBER_OF_PLOTS,
                        addedMsPerFrame=0)


positions = forceatlas2.forceatlas2_networkx_layout(G, pos=None, quadsizes=SIZES, iterations=NUMBER_OF_ITERATIONS)
