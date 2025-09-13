
class Solution {  
    public:
        bool isSameTree(TreeNode* p, TreeNode* q) {
            if(p==NULL && q==NULL) 
                return true;
            else if(p==NULL || q==NULL) 
                return false;
            else
                return (p->val == q->val) && (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
        }
    };


    /*
==================== REVISION BLOCK — Same Tree (structure + values) ====================

Problem
-------
Given two binary trees p and q, determine whether they are **identical**:
- same **shape** (nulls in the same places), and
- same **values** at corresponding nodes.

Pattern
-------
Recursive **DFS** (preorder or postorder) comparing the pair (p, q) at each step.
Alternatively, iterative BFS/DFS over pairs.

Algorithm (precise)
-------------------
same(p, q):
1) If both null  → true.                 // same empty subtree
2) If exactly one null → false.          // shapes differ
3) If p->val != q->val → false.          // values differ
4) Return same(p->left,  q->left) &&
           same(p->right, q->right).

Correctness (sketch)
--------------------
We enforce equality of both structure (by null checks) and values at every node.
By structural induction, if roots match and both left and right subtrees match,
the whole trees are identical.

Complexity
---------
Time: O(n) where n = number of nodes compared (min size of the two trees if they match early).  
Space: O(h) recursion stack (h = tree height; worst O(n) for skewed trees, O(log n) for balanced).

Edge Cases / Pitfalls
---------------------
- One tree empty, one not → false.
- Early exit on first mismatch saves work.
- If recursion depth is a concern (very skewed), use an **iterative** pairwise traversal.

========================================================
*/

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;           // both null
        if (!p || !q) return false;          // one null, one not
        if (p->val != q->val) return false;  // values differ
        return isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
    }
};

/* ==================== Optional: Iterative BFS over pairs ====================
- Avoids recursion depth issues. Same O(n) time / O(w) space (w = max width).
*/
bool isSameTree_iter(TreeNode* p, TreeNode* q) {
    std::queue<std::pair<TreeNode*, TreeNode*>> qu;
    qu.push({p, q});
    while (!qu.empty()) {
        auto [a, b] = qu.front(); qu.pop();
        if (!a && !b) continue;
        if (!a || !b) return false;
        if (a->val != b->val) return false;
        qu.push({a->left,  b->left});
        qu.push({a->right, b->right});
    }
    return true;
}

/* ==================== Optional: Iterative DFS with stack ====================
bool isSameTree_dfs(TreeNode* p, TreeNode* q) {
    std::stack<std::pair<TreeNode*, TreeNode*>> st;
    st.push({p, q});
    while (!st.empty()) {
        auto [a, b] = st.top(); st.pop();
        if (!a && !b) continue;
        if (!a || !b || a->val != b->val) return false;
        st.push({a->left,  b->left});
        st.push({a->right, b->right});
    }
    return true;
}
*/
