
class Solution {
public:
    bool isMirrorTree(TreeNode* p, TreeNode* q){
        if(p == NULL && q == NULL)
            return true;
        if(p==NULL || q==NULL)
            return false;
        return (p->val == q->val && isMirrorTree(p->left, q->right) && isMirrorTree(p->right,q->left));
    }
    bool isSymmetric(TreeNode* root) {
        if(root == NULL || (root->left==NULL && root->right==NULL))
            return true;
        if(root->left == NULL || root->right==NULL)
            return false;
        if(isMirrorTree(root->left, root->right))
            return true;
        else 
            return false;
    }
};

/*
==================== REVISION BLOCK — Symmetric (Mirror) Binary Tree ====================

Problem
-------
Check whether a binary tree is **symmetric** around its center:
left subtree must be a **mirror** of the right subtree (both structure and values).

Pattern
-------
Mirror comparison via:
1) **Recursive DFS**: compare (left, right) pairs in mirrored order.
2) **Iterative BFS/queue**: push node pairs (L,R), always expand as (L->left, R->right) and (L->right, R->left).

Algorithm (Recursive, precise)
------------------------------
isMirror(a, b):
1) If a == nullptr or b == nullptr → return a == b          // both null ⇒ match; one null ⇒ mismatch
2) If a->val != b->val → return false
3) Return isMirror(a->left,  b->right)  && 
         isMirror(a->right, b->left)

Main:
- If root == nullptr → true
- Return isMirror(root->left, root->right)

Correctness (sketch)
--------------------
Symmetry requires: roots equal, outer children equal (a->left vs b->right), and inner children
equal (a->right vs b->left). Recursing on mirrored positions ensures both structure and values
match; the base cases handle null structure perfectly.

Complexity
----------
Time: O(n) — each node compared once.  
Space: O(h) recursion stack (worst O(n) skewed, O(log n) balanced).  
(Iterative BFS uses O(w) queue where w = max width.)

Edge Cases / Pitfalls
---------------------
- Empty tree is symmetric (true).
- Avoid redundant top-level checks; the helper handles nulls cleanly.
- Ensure you compare **mirrored** children in the correct order.
- Values may repeat; pointer identity is irrelevant—compare node values and structure.

========================================================
*/

// Clean recursive solution (simplified)
class Solution {
    bool isMirror(TreeNode* a, TreeNode* b) {
        if (!a || !b) return a == b;                 // both null -> true; one null -> false
        if (a->val != b->val) return false;
        return isMirror(a->left,  b->right) &&
               isMirror(a->right, b->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return isMirror(root->left, root->right);
    }
};

/* ==================== Optional: Iterative BFS (queue of pairs) ====================
- Same logic without recursion depth concerns.
*/
bool isSymmetric_iter(TreeNode* root) {
    if (!root) return true;
    std::queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);
    while (!q.empty()) {
        TreeNode* a = q.front(); q.pop();
        TreeNode* b = q.front(); q.pop();
        if (!a && !b) continue;
        if (!a || !b || a->val != b->val) return false;
        q.push(a->left);  q.push(b->right);
        q.push(a->right); q.push(b->left);
    }
    return true;
}
