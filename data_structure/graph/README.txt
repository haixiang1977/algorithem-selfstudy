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

Graph glossary
    http://www-math.ucdenver.edu/~wcherowi/courses/m4408/glossary.html
    Acyclic Graph
        A graph is acyclic if it contains no cycles
    Cycle
        A closed path with at least one edge
    Path
        A path is a trail with no repeated vertices (except possibly the first and last).
    Adjacent
        Two vertices are adjacent if they are connected by an edge. We often call these two vertices neighbors. 
    Ancestor
        In a rooted tree, a vertex on the path from the root to the vertex. Vertex v is an ancestor of vertex w if and only if w is a descendant of v.
    Descendant
        In a rooted tree, a descendant of vertex v is any vertex w whose path from the root contains v.
    Child
        In a rooted tree, a vertex v is a child of vertex w if v immediately succeeds w on the path from the root to v. Vertex v is a child of w if and only if w is the parent of v.
    Loop
        An edge or arc from a vertex to itself is called a loop. Loops are not allowed in simple graphs or digraphs. Also called self-loops.
    Parent
        In a rooted tree, vertex w is the parent of vertex v if w immediately precedes v on the path from the root to v. Vertex w is the parent of v if and only if v is a child of w.
    
Graphic traverse
    there are 2 algorithms for graphic traverse (or search).
    breadth-first search (queue based)
    depth-first search (stack based)

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



