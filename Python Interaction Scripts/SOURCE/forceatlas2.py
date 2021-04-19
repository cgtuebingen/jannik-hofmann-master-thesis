# This is the fastest python implementation of the ForceAtlas2 plugin from Gephi
# intended to be used with networkx, but is in theory independent of
# it since it only relies on the adjacency matrix.  This
# implementation is based directly on the Gephi plugin:
#
# https://github.com/gephi/gephi/blob/master/modules/LayoutPlugin/src/main/java/org/gephi/layout/plugin/forceAtlas2/ForceAtlas2.java
#
# For simplicity and for keeping code in sync with upstream, I have
# reused as many of the variable/function names as possible, even when
# they are in a more java-like style (e.g. camelcase)
#
# I wrote this because I wanted an almost feature complete and fast implementation
# of ForceAtlas2 algorithm in python
#
# NOTES: Currently, this only works for weighted undirected graphs.
#
# Copyright (C) 2017 Bhargav Chippada <bhargavchippada19@gmail.com>
#
# Available under the GPLv3

import random
from sys import version_info
import time

import numpy
import scipy
from tqdm import tqdm

#from . import fa2util
import fa2util

class Timer:
    def __init__(self, name="Timer"):
        self.name = name
        self.start_time = 0.0
        self.total_time = 0.0

    def start(self):
        self.start_time = time.time()

    def stop(self):
        self.total_time += (time.time() - self.start_time)

    def display(self):
        print(self.name, " took ", "%.2f" % self.total_time, " seconds")


class ForceAtlas2:
    def __init__(self,
        # Behavior alternatives
        outboundAttractionDistribution=False,  # Dissuade hubs
        linLogMode=False,  # NOT IMPLEMENTED
        adjustSizes=False,  # Prevent overlap (NOT IMPLEMENTED)
        edgeWeightInfluence=1.0,
        orderconnectedQuadsOnXaxis=False, # orders connected nodes by their index on x axis
        desiredHorizontalSpacing=50, # spacing between the nodes
        desiredVerticalSpacing=0, # spacing between the nodes
        bufferZone=50,

        # Performance
        jitterTolerance=1.0,  # Tolerance
        barnesHutOptimize=True,
        barnesHutTheta=1.2,
        multiThreaded=False,  # NOT IMPLEMENTED

        # Tuning
        scalingRatio=2.0,
        strongGravityMode=False,
        gravity=1.0,

        # Log
        verbose=True,
        debugDisplayPlot=False,
        addedMsPerFrame=0
    ):
        assert linLogMode == adjustSizes == multiThreaded == False, "You selected a feature that has not been implemented yet..."
        self.outboundAttractionDistribution = outboundAttractionDistribution
        self.linLogMode = linLogMode
        self.adjustSizes = adjustSizes
        self.edgeWeightInfluence = edgeWeightInfluence
        self.orderconnectedQuadsOnXaxis = orderconnectedQuadsOnXaxis
        self.desiredHorizontalSpacing = desiredHorizontalSpacing
        self.desiredVerticalSpacing = desiredVerticalSpacing
        self.bufferZone = bufferZone
        self.jitterTolerance = jitterTolerance
        self.barnesHutOptimize = barnesHutOptimize
        self.barnesHutTheta = barnesHutTheta
        self.scalingRatio = scalingRatio
        self.strongGravityMode = strongGravityMode
        self.gravity = gravity
        self.verbose = verbose
        self.debugDisplayPlot = debugDisplayPlot
        self.addedMsPerFrame = addedMsPerFrame

    def init(self,
             G,  # a graph in 2D numpy ndarray format (or) scipy sparse matrix format
             pos=None,  # Array of initial positions
             quadsizes=None # Array of rectangular node sizes
             ):
        isSparse = False
        if isinstance(G, numpy.ndarray):
            # Check our assumptions
            assert G.shape == (G.shape[0], G.shape[0]), "G is not 2D square"
            assert numpy.all(G.T == G), "G is not symmetric.  Currently only undirected graphs are supported"
            assert isinstance(pos, numpy.ndarray) or (pos is None), "Invalid node positions"
        elif scipy.sparse.issparse(G):
            # Check our assumptions
            assert G.shape == (G.shape[0], G.shape[0]), "G is not 2D square"
            assert isinstance(pos, numpy.ndarray) or (pos is None), "Invalid node positions"
            G = G.tolil()
            isSparse = True
        else:
            assert False, "G is not numpy ndarray or scipy sparse matrix"

        # Put nodes into a data structure we can understand
        nodes = []
        for i in range(0, G.shape[0]):
            n = fa2util.QuadNode()
            if isSparse:
                n.mass = 1 + len(G.rows[i])
            else:
                n.mass = 1 + numpy.count_nonzero(G[i])
            n.old_dx = 0
            n.old_dy = 0
            n.dx = 0
            n.dy = 0
            if pos is None:
                n.x = random.random()
                n.y = random.random()
            else:
                n.x = pos[i][0]
                n.y = pos[i][1]
            n.id = i
            if quadsizes is not None:
                n.width = quadsizes[i][0]
                n.height = quadsizes[i][1]
            nodes.append(n)

        # Put edges into a data structure we can understand
        edges = []
        es = numpy.asarray(G.nonzero()).T
        for e in es:  # Iterate through edges
            if e[1] <= e[0]: continue  # Avoid duplicate edges
            edge = fa2util.Edge()
            edge.node1 = e[0]  # The index of the first node in `nodes`
            edge.node2 = e[1]  # The index of the second node in `nodes`
            edge.weight = G[tuple(e)]
            edges.append(edge)

        return nodes, edges

    # Given an adjacency matrix, this function computes the node positions
    # according to the ForceAtlas2 layout algorithm.  It takes the same
    # arguments that one would give to the ForceAtlas2 algorithm in Gephi.
    # Not all of them are implemented.  See below for a description of
    # each parameter and whether or not it has been implemented.
    #
    # This function will return a list of X-Y coordinate tuples, ordered
    # in the same way as the rows/columns in the input matrix.
    #
    # The only reason you would want to run this directly is if you don't
    # use networkx.  In this case, you'll likely need to convert the
    # output to a more usable format.  If you do use networkx, use the
    # "forceatlas2_networkx_layout" function below.
    #
    # Currently, only undirected graphs are supported so the adjacency matrix
    # should be symmetric.
    def forceatlas2(self,
                    G,  # a graph in 2D numpy ndarray format (or) scipy sparse matrix format
                    pos=None,  # Array of initial positions
                    quadsizes=None, # List of sizes of the graph nodes [(width, height)]
                    iterations=100,  # Number of times to iterate the main loop
                    ):
        # Initializing, initAlgo()
        # ================================================================

        # speed and speedEfficiency describe a scaling factor of dx and dy
        # before x and y are adjusted.  These are modified as the
        # algorithm runs to help ensure convergence.
        speed = 1.0
        speedEfficiency = 1.0
        nodes, edges = self.init(G, pos, quadsizes)
        outboundAttCompensation = 1.0
        if self.outboundAttractionDistribution:
            outboundAttCompensation = numpy.mean([n.mass for n in nodes])
        # ================================================================

        # Main loop, i.e. goAlgo()
        # ================================================================

        barneshut_timer = Timer(name="BarnesHut Approximation")
        repulsion_timer = Timer(name="Repulsion forces")
        overlap_repulsion_timer = Timer(name="Overlap repulsion forces")
        gravity_timer = Timer(name="Gravitational forces")
        attraction_timer = Timer(name="Attraction forces")
        applyforces_timer = Timer(name="AdjustSpeedAndApplyForces step")
        draw_timer = Timer(name="Drawing the plot")

        #for _i in niters:
        def execute_once(i):
            nonlocal speed, speedEfficiency, nodes, edges, outboundAttCompensation, barneshut_timer, repulsion_timer, overlap_repulsion_timer, gravity_timer, attraction_timer, applyforces_timer, quadsizes

            for n in nodes:
                n.old_dx = n.dx
                n.old_dy = n.dy
                n.dx = 0
                n.dy = 0

            # Barnes Hut optimization
            if self.barnesHutOptimize:
                barneshut_timer.start()
                rootRegion = fa2util.Region(nodes)
                rootRegion.buildSubRegions()
                barneshut_timer.stop()

            # Charge repulsion forces
            repulsion_timer.start()
            # parallelization should be implemented here
            if self.barnesHutOptimize:
                rootRegion.applyForceOnNodes(nodes, self.barnesHutTheta, self.scalingRatio)
            else:
                fa2util.apply_repulsion_fast(nodes, self.scalingRatio)

            repulsion_timer.stop()
            overlap_repulsion_timer.start()
            if quadsizes is not None:
                CONS2 = 3 * i / iterations # linearly become more important

                fa2util.apply_overlap_repulsion(nodes, self.scalingRatio*CONS2, self.desiredHorizontalSpacing, self.desiredVerticalSpacing, self.bufferZone)

            overlap_repulsion_timer.stop()

            # Gravitational forces
            gravity_timer.start()

            scalingFactor = self.scalingRatio * (1 - i / iterations) # linearly become less important
            fa2util.apply_gravity(nodes, self.gravity, scalingRatio=scalingFactor, useStrongGravity=self.strongGravityMode)

            gravity_timer.stop()

            # If other forms of attraction were implemented they would be selected here.
            attraction_timer.start()
            if self.orderconnectedQuadsOnXaxis:
                CONS1 = 100 * (1 - i / iterations) # linearly become less important to the end

                fa2util.apply_attraction_to_sides(nodes, edges, self.outboundAttractionDistribution, outboundAttCompensation*CONS1, self.edgeWeightInfluence, self.desiredHorizontalSpacing)

            else:
                fa2util.apply_attraction(nodes, edges, self.outboundAttractionDistribution, outboundAttCompensation, self.edgeWeightInfluence)
            # order along x axis: directional attraction
            if self.orderconnectedQuadsOnXaxis:
                CONS0 = 100 * i / iterations * (1 - i / iterations) # linearly become more and then less important

                fa2util.apply_directional_attraction(nodes, edges, self.outboundAttractionDistribution, CONS0, self.edgeWeightInfluence, self.desiredHorizontalSpacing)
                
            attraction_timer.stop()

            # Adjust speeds and apply forces
            applyforces_timer.start()
            values = fa2util.adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, self.jitterTolerance)
            speed = values['speed']
            speedEfficiency = values['speedEfficiency']
            applyforces_timer.stop()

        if self.debugDisplayPlot == True:
            self.debugDisplayPlot = 1
        if self.debugDisplayPlot == 0:
            self.debugDisplayPlot = False
        if type(self.debugDisplayPlot) is int or type(self.debugDisplayPlot) is float :
            def draw(i):
                nonlocal draw_timer, ax, fig
                draw_timer.start()
                import networkx as nx
                ax.clear()
                oldG = nx.from_scipy_sparse_matrix(G)
                positions = dict(zip(oldG.nodes(), [(n.x, n.y) for n in nodes]))
                labels = dict(zip(oldG.nodes(), range(G.shape[0])))
                nx.draw_networkx_nodes(oldG, positions, node_size=50, label=None, node_color="white", alpha=0.94)
                if quadsizes is not None:
                    for n in nodes:
                        from matplotlib import patches
                        rect = patches.Rectangle((n.x-quadsizes[n.id][0]/2, n.y-quadsizes[n.id][1]/2),
                            quadsizes[n.id][0], quadsizes[n.id][1], edgecolor=(.5,0,0,.3), fill=False)
                        ax.add_patch(rect)
                nx.draw_networkx_edges(oldG, positions, edge_color="blue", alpha=0.505)
                nx.draw_networkx_labels(oldG, positions, labels, font_size=11, font_weight='bold', font_color='white')
                nx.draw_networkx_labels(oldG, positions, labels, font_size=10)
                ax.set_xticks([])
                ax.set_yticks([])
                fig.suptitle(f'Iteration {i} of {iterations}', fontsize=15, va='top')
                # if (i > 0):
                #     from time import sleep
                #     initialFrameTime = 1 # seconds
                #     accelerationFactor = 0.2
                #     if accelerationFactor == 0:
                #         sleeptime = initialFrameTime
                #     else:
                #         accelerationFactor = 1 / accelerationFactor
                #         sleeptime=initialFrameTime * accelerationFactor/(i+accelerationFactor)
                #     sleep(sleeptime)
                draw_timer.stop()
            
            if self.verbose: pbar = tqdm(total=iterations)
            iterationCounter = 0
            def update(i):
                nonlocal iterationCounter
                goUntil = int(i * iterations / self.debugDisplayPlot)
                goUntil = min(goUntil, iterations)
                while iterationCounter < goUntil:
                    iterationCounter += 1
                    execute_once(iterationCounter)
                    if self.verbose: nonlocal pbar
                    if self.verbose: pbar.update(1)
                draw(iterationCounter)
                #print("gountil " + str(goUntil))
                #print("drawing " + str(iterationCounter))
            
            import matplotlib.pyplot as plt
            from matplotlib.animation import FuncAnimation
            fig, ax = plt.subplots(figsize=(6,4))
            draw(0)
            anim = FuncAnimation(fig, update, frames=self.debugDisplayPlot+1,
                interval=max(self.addedMsPerFrame, 10), repeat=False)
            #anim.save('most_recent_animation.gif', writer='imagemagick')
            plt.show()
            if self.verbose: pbar.close()

        else: # no debugDisplayPlot
            # Each iteration of this loop represents a call to goAlgo().
            niters = range(iterations)
            if self.verbose:
                niters = tqdm(niters)
            for i in niters:
                execute_once(i)
        
        if self.verbose:
            if self.barnesHutOptimize:
                barneshut_timer.display()
            repulsion_timer.display()
            overlap_repulsion_timer.display()
            gravity_timer.display()
            attraction_timer.display()
            applyforces_timer.display()
            draw_timer.display()
        # ================================================================
        return [(n.x, n.y) for n in nodes]

    # A layout for NetworkX.
    #
    # This function returns a NetworkX layout, which is really just a
    # dictionary of node positions (2D X-Y tuples) indexed by the node name.
    def forceatlas2_networkx_layout(self, G, pos=None, quadsizes=None, iterations=100, weight_attr=None):
        import networkx
        try:
            import cynetworkx
        except ImportError:
            cynetworkx = None

        assert (
            isinstance(G, networkx.classes.graph.Graph)
            or (cynetworkx and isinstance(G, cynetworkx.classes.graph.Graph))
        ), "Not a networkx graph"
        assert isinstance(pos, dict) or (pos is None), "pos must be specified as a dictionary, as in networkx"
        M = networkx.to_scipy_sparse_matrix(G, dtype='f', format='lil', weight=weight_attr)
        if quadsizes is not None:
            if not isinstance(quadsizes, numpy.ndarray):
                quadsizes = numpy.array(quadsizes)
            assert (quadsizes.shape[0] == M.shape[0]), \
                "quadsizes has the wrong length. It must have exactly as many entries as there are nodes"
            assert (quadsizes.shape[1] == 2), \
                "quadsizes has the wrong dimensions. Each node entry must have exactly two float values: width and height"
        if pos is None:
            l = self.forceatlas2(M, pos=None, quadsizes=quadsizes, iterations=iterations)
        else:
            poslist = numpy.asarray([pos[i] for i in G.nodes()])
            l = self.forceatlas2(M, pos=poslist, quadsizes=quadsizes, iterations=iterations)
        return dict(zip(G.nodes(), l))

    # A layout for igraph.
    #
    # This function returns an igraph layout
    def forceatlas2_igraph_layout(self, G, pos=None, quadsizes=None, iterations=100, weight_attr=None):
        from scipy.sparse import csr_matrix
        import igraph

        def to_sparse(graph, weight_attr=None):
            edges = graph.get_edgelist()
            if weight_attr is None:
                weights = [1] * len(edges)
            else:
                weights = graph.es[weight_attr]

            if not graph.is_directed():
                edges.extend([(v, u) for u, v in edges])
                weights.extend(weights)

            return csr_matrix((weights, zip(*edges)))

        assert isinstance(G, igraph.Graph), "Not a igraph graph"
        if isinstance(pos, list):
            pos = numpy.array(pos)
        assert isinstance(pos, numpy.ndarray) or (pos is None), "pos must be a list or numpy array"

        if quadsizes is not None:
            if not isinstance(quadsizes, numpy.ndarray):
                quadsizes = numpy.array(quadsizes)
            assert (quadsizes.shape[0] == G.shape[0]), \
                "quadsizes has the wrong length. It must have exactly as many entries as there are nodes"
            assert (quadsizes.shape[1] == 2), \
                "quadsizes has the wrong dimensions. Each node entry must have exactly two float values: width and height"

        adj = to_sparse(G, weight_attr)
        coords = self.forceatlas2(adj, pos=pos, quadsizes=quadsizes, iterations=iterations)

        return igraph.layout.Layout(coords, 2)
