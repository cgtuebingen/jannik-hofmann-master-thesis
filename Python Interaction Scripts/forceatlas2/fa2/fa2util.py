# This file allows separating the most CPU intensive routines from the
# main code.  This allows them to be optimized with Cython.  If you
# don't have Cython, this will run normally.  However, if you use
# Cython, you'll get speed boosts from 10-100x automatically.
#
# THE ONLY CATCH IS THAT IF YOU MODIFY THIS FILE, YOU MUST ALSO MODIFY
# fa2util.pxd TO REFLECT ANY CHANGES IN FUNCTION DEFINITIONS!
#
# Copyright (C) 2017 Bhargav Chippada <bhargavchippada19@gmail.com>
#
# Available under the GPLv3

from math import factorial, sqrt
import numpy as np
import math

# This will substitute for the nLayout object
class Node:
    def __init__(self):
        self.mass = 0.0
        self.old_dx = 0.0
        self.old_dy = 0.0
        self.dx = 0.0
        self.dy = 0.0
        self.x = 0.0
        self.y = 0.0

# This will substitute for the nLayout object
class QuadNode:
    def __init__(self):
        self.mass = 0.0
        self.old_dx = 0.0
        self.old_dy = 0.0
        self.dx = 0.0
        self.dy = 0.0
        self.x = 0.0
        self.y = 0.0
        self.id = 0
        self.width = 0.0
        self.height = 0.0


# This is not in the original java code, but it makes it easier to deal with edges
class Edge:
    def __init__(self):
        self.node1 = -1
        self.node2 = -1
        self.weight = 0.0


# Here are some functions from ForceFactory.java
# =============================================

# Repulsion function.  `n1` and `n2` should be nodes.  This will
# adjust the dx and dy values of `n1`  `n2`
def linRepulsion(n1, n2, coefficient=0):
    xDist = n1.x - n2.x
    yDist = n1.y - n2.y
    distance2 = xDist * xDist + yDist * yDist  # Distance squared

    if distance2 > 0:
        factor = coefficient * n1.mass * n2.mass / distance2
        n1.dx += xDist * factor
        n1.dy += yDist * factor
        n2.dx -= xDist * factor
        n2.dy -= yDist * factor


def sign(x):
    if x > 0:
        return 1
    if x < 0:
        return -1
    return 0

# Repulsion function.  `n1` and `n2` should be nodes.  This will
# adjust the dx and dy values of `n1`  `n2`
def linOverlapRepulsion(n1, n2, coefficient=0, xspacing=0, yspacing=0, bufferZone=0):
    xDist = n1.x - n2.x
    bigxspacing = xspacing + bufferZone + n1.width/2 + n2.width/2
    if abs(xDist) > bigxspacing:
        return
    
    yDist = n1.y - n2.y
    bigyspacing = yspacing + bufferZone + n1.height/2 + n2.height/2
    if abs(yDist) > bigyspacing:
        return

    xDist = sign(xDist) * bigxspacing - xDist
    yDist = sign(yDist) * bigyspacing - yDist

    factor = coefficient * n1.mass * n2.mass #* abs(xDist) * abs(yDist)
    import math
    def sigmoid(x):
        return 1 / (1 + math.exp(-x))
    factor *= sigmoid(min(xDist, yDist)/bufferZone/6+1)
    
    #if xDist < yDist:
    #    n1.dx += xDist * xDist * factor
    #    n2.dx -= xDist * xDist * factor
    #else:
    #    n1.dy += yDist * yDist * factor
    #    n2.dy -= yDist * yDist * factor
        
    n1.dx += sign(xDist) * abs(yDist) * factor
    n2.dx -= sign(xDist) * abs(yDist) * factor
    n1.dy += sign(yDist) * abs(xDist) * factor
    n2.dy -= sign(yDist) * abs(xDist) * factor


# Repulsion function. 'n' is node and 'r' is region
def linRepulsion_region(n, r, coefficient=0):
    xDist = n.x - r.massCenterX
    yDist = n.y - r.massCenterY
    distance2 = xDist * xDist + yDist * yDist

    if distance2 > 0:
        factor = coefficient * n.mass * r.mass / distance2
        n.dx += xDist * factor
        n.dy += yDist * factor


# Gravity repulsion function.  For some reason, gravity was included
# within the linRepulsion function in the original gephi java code,
# which doesn't make any sense (considering a. gravity is unrelated to
# nodes repelling each other, and b. gravity is actually an
# attraction)
def linGravity(n, g):
    xDist = n.x
    yDist = n.y
    distance = sqrt(xDist * xDist + yDist * yDist)

    if distance > 0:
        factor = n.mass * g / distance
        n.dx -= xDist * factor
        n.dy -= yDist * factor




# Strong gravity force function. `n` should be a node, and `g`
# should be a constant by which to apply the force.
def strongGravity(n, g, coefficient=0):
    xDist = n.x
    yDist = n.y

    if xDist != 0 and yDist != 0:
        factor = coefficient * n.mass * g
        n.dx -= xDist * factor
        n.dy -= yDist * factor


# Attraction function.  `n1` and `n2` should be nodes.  This will
# adjust the dx and dy values of `n1` and `n2`.  It does
# not return anything.
def linAttraction(n1, n2, e, distributedAttraction, coefficient=0, onlyAlongXaxis=False, xspacing=0, yspacing=0):
    xDist = n1.x - n2.x - xspacing
    if not distributedAttraction:
        factor = -coefficient * e
    else:
        factor = -coefficient * e / n1.mass
    n1.dx += xDist * factor
    n2.dx -= xDist * factor
    if not onlyAlongXaxis:
        yDist = n1.y - n2.y
        n1.dy += yDist * factor
        n2.dy -= yDist * factor


# Attraction function.  `n1` and `n2` should be nodes.  This will
# adjust the dx and dy values of `n1` and `n2`.  It does
# not return anything.
def linAttractionSides(n1, n2, e, distributedAttraction, coefficient=0, xspacing=0, yspacing=0):
    if n1.id < n2.id:
        nleft, nright = n1, n2
    else:
        nleft, nright = n2, n1
    xDist = nright.x - nleft.x - xspacing - nleft.width/2 - nright.width/2
    yDist = nright.y - nleft.y
    # if yDist > 0:
    #     yDist -= yspacing + nleft.height/2 + nright.height/2
    # else:
    #     yDist += yspacing + nleft.height/2 + nright.height/2
    # commented out because we actually want strong attraction. otherwise they stop when just the diagonals are touching which would be too soon
    if not distributedAttraction:
        factor = -coefficient * e
    else:
        factor = -coefficient * e / nleft.mass
    nleft.dx -= xDist * factor
    nleft.dy -= yDist * factor
    nright.dx += xDist * factor
    nright.dy += yDist * factor


# The following functions iterate through the nodes or edges and apply
# the forces directly to the node objects.  These iterations are here
# instead of the main file because Python is slow with loops.
def apply_repulsion(nodes, coefficient):
    i = 0
    for n1 in nodes:
        j = i
        for n2 in nodes:
            if j == 0:
                break
            linRepulsion(n1, n2, coefficient)
            j -= 1
        i += 1


# The following functions iterate through the nodes or edges and apply
# the forces directly to the node objects.  These iterations are here
# instead of the main file because Python is slow with loops.
def apply_repulsion_fast(nodes, coefficient, debugAlgorithm = False):
    if (debugAlgorithm):
        i = 0
        for n1 in nodes:
            j = i
            for n2 in nodes:
                if j == 0:
                    break
                xDist = n1.x - n2.x
                yDist = n1.y - n2.y
                distance2 = xDist * xDist + yDist * yDist  # Distance squared

                if distance2 > 0:
                    factor = coefficient * n1.mass * n2.mass / distance2
                    n1.dx += xDist * factor
                    n1.dy += yDist * factor
                    n2.dx -= xDist * factor
                    n2.dy -= yDist * factor
                j -= 1
            i += 1
    x = np.array([n.x for n in nodes])
    y = np.array([n.y for n in nodes])
    mass = np.array([n.mass for n in nodes])
    deltax = x[None, :] - x[:, None]
    deltax = np.tril(deltax, -1)
    deltay = y[None, :] - y[:, None]
    deltay = np.tril(deltay, -1)
    massmult = mass[None, :] * mass[:, None]
    massmult = np.tril(massmult, -1)
    distance2 = deltax * deltax + deltay * deltay
    onesOnDiagAndAbove = np.triu(np.ones_like(deltax), 0)
    factor = massmult * coefficient / (distance2 + onesOnDiagAndAbove)
    deltax = deltax * factor
    deltay = deltay * factor
    n1x = deltax.sum(axis=0)
    n2x = deltax.sum(axis=1)
    n1y = deltay.sum(axis=0)
    n2y = deltay.sum(axis=1)
    dx = n1x - n2x
    dy = n1y - n2y
    for i, n in enumerate(nodes):
        if (debugAlgorithm):
            reltol = 0.000001
            abstol = reltol
            if not math.isclose(n.dx, dx[i], rel_tol=reltol, abs_tol=abstol):
                print(f"\nindex {i} got {dx[i]}, expected {n.dx}")
            if not math.isclose(n.dy, dy[i], rel_tol=reltol, abs_tol=abstol):
                print(f"\nindex {i} got {dy[i]}, expected {n.dy}")
        n.dx = dx[i]
        n.dy = dy[i]
    
    

# The following functions iterate through the nodes or edges and apply
# the forces directly to the node objects.  These iterations are here
# instead of the main file because Python is slow with loops.
def apply_overlap_repulsion(nodes, coefficient, xspacing=0, yspacing=0, bufferZone=0):
    maxdistx = max([n.width for n in nodes]) + xspacing + bufferZone
    maxdisty = max([n.height for n in nodes]) + yspacing + bufferZone
    i = 0
    for n1 in nodes:
        j = i
        for n2 in nodes:
            if j == 0:
                break
            if abs(n1.x - n2.x) < maxdistx:
                if abs(n1.y - n2.y) < maxdisty:
                    linOverlapRepulsion(n1, n2,
                        coefficient, xspacing, yspacing, bufferZone)
            j -= 1
        i += 1


# The following functions iterate through the nodes or edges and apply
# the forces directly to the node objects.  These iterations are here
# instead of the main file because Python is slow with loops.

# not really faster as it's too complicated, so not recommended to be used
def apply_overlap_repulsion_fast(nodes, coefficient, xspacing=0, yspacing=0, bufferZone=0):
    maxdistx = max([n.width for n in nodes]) + xspacing + bufferZone
    maxdisty = max([n.height for n in nodes]) + yspacing + bufferZone
    x = np.array([n.x for n in nodes])
    y = np.array([n.y for n in nodes])
    deltax = x[None, :] - x[:, None]
    deltay = y[None, :] - y[:, None]
    deltax = np.tril(deltax, -1)
    deltay = np.tril(deltay, -1)
    deltax = np.abs(deltax)
    deltay = np.abs(deltay)
    
    inrange = np.where((deltax < maxdistx) & (deltay < maxdisty),
        np.ones_like(deltax), np.zeros_like(deltax))
    applyto = np.transpose(np.nonzero(inrange)).tolist()

    for pair in applyto:
        linOverlapRepulsion(nodes[pair[0]], nodes[pair[1]],
            coefficient, xspacing, yspacing, bufferZone)


def apply_gravity(nodes, gravity, scalingRatio, useStrongGravity=False):
    if not useStrongGravity:
        for n in nodes:
            linGravity(n, gravity)
    else:
        for n in nodes:
            strongGravity(n, gravity, scalingRatio)


def apply_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence):
    # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
    if edgeWeightInfluence == 0:
        for edge in edges:
            linAttraction(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient)
    elif edgeWeightInfluence == 1:
        for edge in edges:
            linAttraction(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient)
    else:
        for edge in edges:
            linAttraction(nodes[edge.node1], nodes[edge.node2], pow(edge.weight, edgeWeightInfluence),
                          distributedAttraction, coefficient)

def apply_attraction_to_sides(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence, desiredHorizontalSpacing):
    # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
    if edgeWeightInfluence == 0:
        for edge in edges:
            linAttractionSides(nodes[edge.node1], nodes[edge.node2], 1, distributedAttraction, coefficient, xspacing=desiredHorizontalSpacing)
    elif edgeWeightInfluence == 1:
        for edge in edges:
            linAttractionSides(nodes[edge.node1], nodes[edge.node2], edge.weight, distributedAttraction, coefficient, xspacing=desiredHorizontalSpacing)
    else:
        for edge in edges:
            linAttractionSides(nodes[edge.node1], nodes[edge.node2], pow(edge.weight, edgeWeightInfluence),
                          distributedAttraction, coefficient, xspacing=desiredHorizontalSpacing)

def apply_directional_attraction(nodes, edges, distributedAttraction, coefficient, edgeWeightInfluence, desiredHorizontalSpacing):
    # Optimization, since usually edgeWeightInfluence is 0 or 1, and pow is slow
    if edgeWeightInfluence == 0:
        for edge in edges:
            nleft, nright = nodes[edge.node1], nodes[edge.node2]
            if nleft.id > nright.id:
                nleft, nright = nright, nleft
            spacing = desiredHorizontalSpacing + nleft.width/2 + nright.width/2
            if nleft.x + spacing > nright.x:
                linAttraction(nleft, nright, 1, distributedAttraction, coefficient, onlyAlongXaxis=True, xspacing=-spacing)
            # negative spacing because they are overlapping and being pulled back further
    elif edgeWeightInfluence == 1:
        for edge in edges:
            nleft, nright = nodes[edge.node1], nodes[edge.node2]
            if nleft.id > nright.id:
                nleft, nright = nright, nleft
            spacing = desiredHorizontalSpacing + nleft.width/2 + nright.width/2
            if nleft.x + spacing > nright.x:
                linAttraction(nleft, nright, edge.weight, distributedAttraction, coefficient, onlyAlongXaxis=True, xspacing=-spacing)
    else:
        for edge in edges:
            nleft, nright = nodes[edge.node1], nodes[edge.node2]
            if nleft.id > nright.id:
                nleft, nright = nright, nleft
            spacing = desiredHorizontalSpacing + nleft.width/2 + nright.width/2
            if nleft.x + spacing > nright.x:
                linAttraction(nleft, nright, pow(edge.weight, edgeWeightInfluence),
                          distributedAttraction, coefficient, onlyAlongXaxis=True, xspacing=-spacing)


# For Barnes Hut Optimization
class Region:
    def __init__(self, nodes):
        self.mass = 0.0
        self.massCenterX = 0.0
        self.massCenterY = 0.0
        self.size = 0.0
        self.nodes = nodes
        self.subregions = []
        self.updateMassAndGeometry()

    def updateMassAndGeometry(self):
        if len(self.nodes) > 1:
            self.mass = 0
            massSumX = 0
            massSumY = 0
            for n in self.nodes:
                self.mass += n.mass
                massSumX += n.x * n.mass
                massSumY += n.y * n.mass
            self.massCenterX = massSumX / self.mass
            self.massCenterY = massSumY / self.mass

            self.size = 0.0
            for n in self.nodes:
                distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
                self.size = max(self.size, 2 * distance)

    def buildSubRegions(self):
        if len(self.nodes) > 1:
            topleftNodes = []
            bottomleftNodes = []
            toprightNodes = []
            bottomrightNodes = []
            # Optimization: The distribution of self.nodes into 
            # subregions now requires only one for loop. Removed 
            # topNodes and bottomNodes arrays: memory space saving.
            for n in self.nodes:
                if n.x < self.massCenterX:
                    if n.y < self.massCenterY:
                        bottomleftNodes.append(n)
                    else:
                        topleftNodes.append(n)
                else:
                    if n.y < self.massCenterY:
                        bottomrightNodes.append(n)
                    else:
                        toprightNodes.append(n)      

            if len(topleftNodes) > 0:
                if len(topleftNodes) < len(self.nodes):
                    subregion = Region(topleftNodes)
                    self.subregions.append(subregion)
                else:
                    for n in topleftNodes:
                        subregion = Region([n])
                        self.subregions.append(subregion)

            if len(bottomleftNodes) > 0:
                if len(bottomleftNodes) < len(self.nodes):
                    subregion = Region(bottomleftNodes)
                    self.subregions.append(subregion)
                else:
                    for n in bottomleftNodes:
                        subregion = Region([n])
                        self.subregions.append(subregion)

            if len(toprightNodes) > 0:
                if len(toprightNodes) < len(self.nodes):
                    subregion = Region(toprightNodes)
                    self.subregions.append(subregion)
                else:
                    for n in toprightNodes:
                        subregion = Region([n])
                        self.subregions.append(subregion)

            if len(bottomrightNodes) > 0:
                if len(bottomrightNodes) < len(self.nodes):
                    subregion = Region(bottomrightNodes)
                    self.subregions.append(subregion)
                else:
                    for n in bottomrightNodes:
                        subregion = Region([n])
                        self.subregions.append(subregion)

            for subregion in self.subregions:
                subregion.buildSubRegions()

    def applyForce(self, n, theta, coefficient=0):
        if len(self.nodes) < 2:
            linRepulsion(n, self.nodes[0], coefficient)
        else:
            distance = sqrt((n.x - self.massCenterX) ** 2 + (n.y - self.massCenterY) ** 2)
            if distance * theta > self.size:
                linRepulsion_region(n, self, coefficient)
            else:
                for subregion in self.subregions:
                    subregion.applyForce(n, theta, coefficient)

    def applyForceOnNodes(self, nodes, theta, coefficient=0):
        for n in nodes:
            self.applyForce(n, theta, coefficient)


# Adjust speed and apply forces step
def adjustSpeedAndApplyForces(nodes, speed, speedEfficiency, jitterTolerance):
    # Auto adjust speed.
    totalSwinging = 0.0  # How much irregular movement
    totalEffectiveTraction = 0.0  # How much useful movement
    for n in nodes:
        swinging = sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
        totalSwinging += n.mass * swinging
        totalEffectiveTraction += .5 * n.mass * sqrt(
            (n.old_dx + n.dx) * (n.old_dx + n.dx) + (n.old_dy + n.dy) * (n.old_dy + n.dy))

    # Optimize jitter tolerance.  The 'right' jitter tolerance for
    # this network. Bigger networks need more tolerance. Denser
    # networks need less tolerance. Totally empiric.
    estimatedOptimalJitterTolerance = .05 * sqrt(len(nodes))
    minJT = sqrt(estimatedOptimalJitterTolerance)
    maxJT = 10
    jt = jitterTolerance * max(minJT,
                               min(maxJT, estimatedOptimalJitterTolerance * totalEffectiveTraction / (
                                   len(nodes) * len(nodes))))

    minSpeedEfficiency = 0.05

    # Protective against erratic behavior
    if totalEffectiveTraction and totalSwinging / totalEffectiveTraction > 2.0:
        if speedEfficiency > minSpeedEfficiency:
            speedEfficiency *= .5
        jt = max(jt, jitterTolerance)

    if totalSwinging == 0:
        targetSpeed = float('inf')
    else:
        targetSpeed = jt * speedEfficiency * totalEffectiveTraction / totalSwinging

    if totalSwinging > jt * totalEffectiveTraction:
        if speedEfficiency > minSpeedEfficiency:
            speedEfficiency *= .7
    elif speed < 1000:
        speedEfficiency *= 1.3

    # But the speed shoudn't rise too much too quickly, since it would
    # make the convergence drop dramatically.
    maxRise = .5
    speed = speed + min(targetSpeed - speed, maxRise * speed)

    # Apply forces.
    #
    # Need to add a case if adjustSizes ("prevent overlap") is
    # implemented.
    for n in nodes:
        swinging = n.mass * sqrt((n.old_dx - n.dx) * (n.old_dx - n.dx) + (n.old_dy - n.dy) * (n.old_dy - n.dy))
        factor = speed / (1.0 + sqrt(speed * swinging))
        n.x = n.x + (n.dx * factor)
        n.y = n.y + (n.dy * factor)

    values = {}
    values['speed'] = speed
    values['speedEfficiency'] = speedEfficiency

    return values


try:
    import cython

    if not cython.compiled:
        print("Warning: uncompiled fa2util module.  Compile with cython for a 10-100x speed boost.")
except:
    print("No cython detected.  Install cython and compile the fa2util module for a 10-100x speed boost.")
