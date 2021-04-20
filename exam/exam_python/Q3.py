class BST:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def insert(self, value):
        '''
        node.insert(5) is the same as BST.insert(node, 5)
        We use this when recursively calling, e.g. self.left.insert
        '''
        if value < self.value:
            if self.left == None:
                self.left = BST(value)
            else:
                self.left.insert(value)
        else:
            if self.right == None:
                self.right = BST(value)
            else:
                self.right.insert(value)

    def __repr__(self):
        '''The string representation of a node.
        Here, we convert the value of the node to a string and make that
        the representation.
        We can now use
        a = BST(4)
        print(a) # prints 4
        '''
        return str(self.value)

def nth_laregst(node, n, visited):
    #base case and check to avoid uneccesary calls so it stays in O(h)
    if node == None or visited[0] >= n:
        return 
    #recurse in postorder to get the largest element first 
    nth_laregst(node.right, n, visited)
    #backtrack and visit each node by incrementing the counter 
    visited[0] += 1
    #if we visited enough nodes then store the value in the referenced array and return 
    if visited[0] == n:
        visited[1] = node.value
        return 

def third_largest(node):
    visited = [0, 0]
    #array is passed by reference so it can be modified 
    nth_laregst(node, 3, visited)
    return visited[1]


if __name__ == "__main__":
    root = BST(1)
    root.insert(2)
    root.insert(3)
    root.insert(4)
    root.insert(-4)
    print(third_largest(root)) # 1