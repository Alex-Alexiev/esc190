/*
3 a)

DFS #1: ABCDFG
DFS #2: ABDFGC

BFS #1: ABCDFG
BFS #2: ABDCFG

3 b)

if the graph is implemented using an adjacency list (linked list of adjacent nodes for each node)
then the node that is visited first will depend on the order that nodes are initially inserted into the graph. 
This is because they will be in a different order in the linked list so certain nodes will be visited
before others.

For example, in the graph from part a) 

   A--B--C
      |
      |
      D-F-G 

When creating it, if C was added to B before D was added to B, then the adjacency list for B would look like (B: C->D)
This means the DFS would go to C first, and then go back out and into D. (ABCDFG)

However, if D was added to B before C was added to B, then the adjacency list for B would look like (B: D->C)
in which case D (along with F and G) would be visited before C. (ABDFGC)

Regardless of the implementation though, you can choose which connections to visit in an arbitrary order so 
in general you can have different DFS results. 
*/