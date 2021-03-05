import numpy as np
import heapq as pq

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

def dijsktra_pq(node):
    S = []
    d = {node:0}

    count = 0
    _pq = []
    pq.heappush(_pq, (0, count, node))
    
    curr = node

    while _pq:
        dist, _, curr = pq.heappop(_pq)
        if curr in S:
            continue
        S.append(curr)
        d[curr] = dist
        for conn in curr.connections:
            pq.heappush(_pq, (d[curr]+conn["weight"],  count, conn["node"]))
            count += 1
        
    return d 
        

        



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
    prev = {}

    unvisit_all(node)
    unexplored = get_all_nodes(node)
    unexplored.remove(node)  

    while unexplored:
        min_dist = float('inf')
        min_node = None
        min_prev = None
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
                    min_prev = n
        S.append(min_node)
        unexplored.remove(min_node)
        d[min_node] = min_dist
        prev[min_node] = min_prev

    return d, prev

def get_shortest_path_dj(start, end):
    d, prev = dijsktra_slowish_2(start)
    path = []
    curr = end
    while curr in prev:
        path.append(curr)
        curr = prev[curr]
        
    path.append(start)
    return path[::-1]

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

    d = dijsktra_pq(TO)
    for key, val in d.items():
        print(key.name, " ", val)

    # path = get_shortest_path_dj(TO, DC)
    # for node in path:
    #     print(node.name, end=" ")
