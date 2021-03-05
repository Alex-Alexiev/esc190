import numpy as np

class Node:
    def __init__(self, name):
        self.name = name
        self.connections = []
        self.visited = False


def connect(node1, node2, weight):
    node1.connections.append({"node": node2, "weight": weight})
    node2.connections.append({"node": node1, "weight": weight})

def BFS(node):
    q = [node]
    node.visited = True
    while q:
        curr = q.pop(0)
        print(curr.name)
        for conn in curr.connections:
            if conn["node"].visited:
                continue
            q.append(conn["node"])
            conn["node"].visited = True
    
    unvisit_all(node)


################################################################################

def get_all_nodes(node):
    '''Return a list of the nodes in the graph of nodes connected to node
    (N.B., the nodes can be indirectly connected as well)'''
    q = [node]
    ret = []
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        ret.append(cur)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True
    
    return ret


################################################################################

def unvisit_all(node):
    '''Change all n.visited to False in all the nodes in the graph of nodes
    connected to node. Use BFS to find all the nodes'''
    q = [node]
    node.visited = False
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        for con in cur.connections:
            if con["node"].visited:
                q.append(con["node"])
                con["node"].visited = False
    


###############################################################################

def DFS_rec(node):
    '''Print out the names of all nodes connected to node using a
    recursive version of DFS'''
    node.visited = True
    print(node.name)
    for conn in node.connections:
        if not conn["node"].visited:
            DFS_rec(conn["node"])
    

################################################################################

def DFS_nonrec(node):
    '''Print out the names of all nodes connected to node using a non-recursive
    version of DFS. Make it so that the nodes are printed in the same order
    as in DFS_rec'''
    s = [node]
    node.visited = True
    while s:
        curr = s.pop()
        print(curr.name)
        for conn in curr.connections[::-1]:
            if conn["node"].visited: 
                continue
            s.push(conn["node"])
            conn["node"].visited = True


################################################################################
#
# OPTIONAL
#

    """Initialize all the distances to infinity, then while there
    are unvisited nodes, go to the closest unvisited node and 
    check all the distances to its unvisited neighbours 
    """
def dijsktra_slowish_1(node):
    '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
    need to use a priority queue'''
    visited = [node]
    unvisit_all(node)

    unvisited = get_all_nodes(node)

    d = {}
    for n in unvisited:
        d[n] = float('inf')
    d[node] = 0

    while unvisited:
        closest = unvisited[0]
        for n in unvisited:
            if d[n] < d[closest]:
                closest = n
        
        for conn in closest.connections:
            if conn["node"] in visited:
                continue
            distance = d[closest] + conn["weight"]
            d[conn["node"]] = min(d[conn["node"]], distance)
        
        visited.append(closest)
        unvisited.remove(closest)
    
    return d


def dijsktra_slowish_2(node):
    '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
    need to use a priority queue'''
    S = [node] 
    d = {node: 0}

    unvisit_all(node)
    unexplored = get_all_nodes(node)
    unexplored.remove(node)  

    while unexplored:
        min_dist = float('inf')
        min_node = None
        for n in S:
            for conn in n.connections:
                if conn["node"] in S:
                    continue
                if conn["node"] not in d:
                    d[conn["node"]] = float('inf')
                distance = d[n] + conn["weight"]
                if distance < min_dist:
                    min_dist = distance
                    min_node = conn["node"]
        S.append(min_node)
        unexplored.remove(min_node)
        d[min_node] = min_dist

    return d

# def dijsktra_slowish_2(node):
#     '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
#     need to use a priority queue'''
#     S = [node] 
#     d = {node.name: 0}

#     unvisit_all(node)
#     unexplored = get_all_nodes(node)
#     unexplored.remove(node)  

#     while len(unexplored) > 0:
#         min = float('inf')
#         for n in S:
#             for conn in n.connections:
#                 if (conn["weight"] + d[n.name] < min and conn["node"] not in unexplored):
#                     min = conn["weight"] + d[n.name]
#                     min_id = conn["node"]
#         d[min_id.name] = min
#         S.append(min_id)
#         min_id.visited = True
#         unexplored.remove(min_id)

#     return d




if __name__ == '__main__':
    TO = Node("A")
    NYC = Node("B")
    DC = Node("C")
    CDMX = Node("D")
    SF = Node("E")

    connect(TO, NYC, 3)
    connect(TO, SF, 6)
    connect(TO, CDMX, 7)
    connect(NYC, DC, 2)
    connect(SF, DC, 5)

    #BFS(TO)
    #DFS_rec(TO)
    #DFS_nonrec(TO)

    for node, distance in dijsktra_slowish_2(TO).items():
        print(node.name, " ", distance)