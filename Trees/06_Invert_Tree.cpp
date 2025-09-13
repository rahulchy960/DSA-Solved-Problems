
class Solution {   
    public:
        TreeNode* invertTree(TreeNode* root) {
            if(root==NULL)
                return NULL;
    
            swap(root->left, root->right);
            
            root->left = invertTree(root->left);
            root->right = invertTree(root->right);
            
            return root;
        }
    };


    /*
==================== REVISION BLOCK — Invert / Mirror a Binary Tree ====================

Problem
-------
Flip a binary tree so that every node’s left and right children are swapped. Return the root.

Pattern
-------
Simple **DFS** (preorder/postorder both work) or **BFS**. At each node: swap its children, then recurse/iterate.

Algorithm (step-by-step, precise)
---------------------------------
invert(u):
1) If u == nullptr → return nullptr.
2) swap(u->left, u->right).
3) invert(u->left).
4) invert(u->right).
5) return u.

Correctness (sketch)
--------------------
Swapping at u exchanges entire left/right subtrees. Recursing ensures the same operation
is applied to all descendants. By induction on subtree size, the whole tree is mirrored.

Complexity
---------
Time: O(n) — visit each node once.  
Space: O(h) recursion stack (h = height; worst O(n) skewed, O(log n) balanced).  
(Iterative BFS/DFS uses O(w) queue/stack where w is max width.)

Edge Cases / Pitfalls
---------------------
- Empty tree → return nullptr.
- Very deep (skewed) trees can overflow recursion → use iterative BFS/DFS.
- Reassigning `root->left = invertTree(root->left)` is unnecessary (the function
  returns the same pointer) but harmless.

========================================================
*/

// Clean recursive DFS (preorder)
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        std::swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

/* ==================== Optional: Iterative BFS (no recursion depth risk) ====================
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    std::queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        TreeNode* u = q.front(); q.pop();
        std::swap(u->left, u->right);
        if (u->left)  q.push(u->left);
        if (u->right) q.push(u->right);
    }
    return root;
}
*/
