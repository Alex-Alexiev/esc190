class Node:
    def __init__(self, val):
        self.left = None
        self.right = None
        self.val = val
        self.height = 1

class AVL_Tree: 
    def insert(self, root, val):
        if not root: 
            return Node(val)
        if val < root.val:
            root.left = self.insert(root.left, val)
        else:
            root.right = self.insert(root.right, val)

        self.update_height(root)

        root = self.balance(root)

        return root 

    def delete(self, root, val):
        if not root: 
            return None 
        elif val > root.val:
            root.right = self.delete(root.right, val)
        elif val < root.val:
            root.left = self.delete(root.left, val)
        else:
            if root.left is None:
                return root.right
            if root.right is None:
                return root.left
            min = self.min_node(root.right)
            root.val = min.val
            root.right = self.delete(root.right, min.val)
        
        self.update_height(root)
        self.balance(root)

        return root 
    
    def min_node(self, root):
        if not root or not root.left:
            return root 
        return self.min_node(root.left)
        
    
    def balance(self, root):
        balance_factor = self.get_height(root.left) - self.get_height(root.right)

        if balance_factor > 1:
            root = self.left_balance(root)
        elif balance_factor < -1:
            root = self.right_balance(root)

        return root 

    def left_balance(self, root):
        if self.get_height(root.left.left) < self.get_height(root.left.right):
            root.left = self.rotate_left(root.left)
        root = self.rotate_right(root)
        self.update_height(root)
        return root 
    
    def right_balance(self, root):
        if self.get_height(root.right.right) < self.get_height(root.right.left):
            root.right = self.rotate_right(root.right)
        root = self.rotate_left(root)
        self.update_height(root)
        return root 
    
    def rotate_left(self, z):
        y = z.right 
        T = y.left 

        z.right = T 
        y.left = z

        self.update_height(z)
        self.update_height(y) 

        return y 

    def rotate_right(self, z):
        y = z.left
        T = y.right 

        y.right = z 
        z.left = T

        self.update_height(z)
        self.update_height(y)
        
        return y 
    
    def update_height(self, root):
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))
    
    def get_height(self, root):
        return root.height if root else 0
        
    def preorder(self, root):
        if root == None: 
            return 
        print(root.val, root.height)
        self.preorder(root.left)
        self.preorder(root.right)



avl = AVL_Tree()
root = None 
root = avl.insert(root, 10)
root = avl.insert(root, 20)
root = avl.insert(root, 30)
root = avl.insert(root, 40)
root = avl.insert(root, 50)
root = avl.insert(root, 25)
root = avl.insert(root, 24)
root = avl.insert(root, 26)
root = avl.delete(root, 20)
avl.preorder(root)

