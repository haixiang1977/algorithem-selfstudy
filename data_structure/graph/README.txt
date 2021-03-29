graph basics
A Graph is a non-linear data structure consisting of nodes and edges.
The nodes are sometimes also referred to as vertices and the edges are lines or arcs that connect any two nodes in the graph.

Graph definitions
    G = (V, E)
    A graph consists of a set of vertices V, along with a set of Edges E that connect pairs of vertices.
    An edge e = (v(i), v(j)) connects vertices v(i) and v(j)
    A self loop is an edge that connects a vertex to itself.

Representation of Graph
    directed graph
        suppose v(i) -> v(j), then E = (v(i), v(j))
    undirected graph
        suppose v(i) - v(j), then E1 = (v(i), v(j)) and E2 = (v(j), v(i))
    So undirected graph can use directed graph to represent and just add one more pair.
    So all the code here in this chapter only consider this directed graph. For un-directed graph, it is also easy to expand.

Graph flavour
    undirected vs directed
    weighted vs unweighted
    simple vs non-simple
        simple means no self loop
    sparse vs dense
    cyclic vs acyclic
        acyclic means no any loop
    embedded vs topological
    implicit vs explicit
    labeled vs unlabeled

property: (https://www.geeksforgeeks.org/basic-properties-of-a-graph/)
. Distance between two Vertices
    If there is more than one edge which is used two connect two vertices then we basically considered the shortest path as the distance between these two vertices.
. Eccentricity of a Vertex
    Maximum distance from a vertex to all other vertices is considered as the Eccentricity of that vertex.
. Radius of a Connected Graph
    The minimum value of eccentricity from all vertices is basically considered as the radius of connected graph.
. Diameter of A Connected Graph
    we basically used the maximum value of eccentricity from all vertices to determine the diameter of the graph
. Central Point and Centre
    The vertex having minimum eccentricity is considered as the central point of the graph.And the sets of all central point is considered as the centre of Graph.

https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/

loop find
https://www.geeksforgeeks.org/detect-cycle-in-a-graph/



