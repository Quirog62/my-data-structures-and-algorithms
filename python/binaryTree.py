class TreeNode:
    
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right 
    def inorder(self,l:list[int], node: Optional[TreeNode]) -> List[int]:
        if node == None:
            return
        self.inorder(l,node.left)
        l.append(node.val)
        self.inorder(l,node.right)
    
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []
        self.inorder(result,root)
        return result
    
    def preorder(self,l:list[int], node: Optional[TreeNode]) -> List[int]:
        if node == None:
            return
        l.append(node.val)
        self.preorder(l,node.left)
        self.preorder(l,node.right)
    
    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []
        self.preorder(result,root)
        return result
    
    def postorder(self,l:list[int], node: Optional[TreeNode]) -> List[int]:
        if node == None:
            return
        self.postorder(l,node.left)
        self.postorder(l,node.right)
        l.append(node.val)
    
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []
        self.postorder(result,root)
        return result
    
    def dfs(self, l:List[int], depth: int, node: Optional[TreeNode]) -> List[List[int]]:
        if node == None:
            return
        if len(l) <= depth:
            l.append([])
        
        l[depth].append(node.val)
        self.dfs(l,depth+1,node.left)
        self.dfs(l,depth+1,node.right)
    
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        result = []
        self.dfs(result,0,root)
        return result
