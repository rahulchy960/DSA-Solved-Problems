
class Solution {
public:
    bool checkTree(TreeNode* root) {
        if(root == NULL)return true;
        if(root->left == NULL && root->right == NULL)return true;
        int sum = 0;
        if(root->left != NULL) sum += root->left->val;
        if(root->right != NULL) sum += root->right->val;
        return (root->val == sum  && checkTree(root->left) && checkTree(root->right));
    }
};


/*
==================== REVISION BLOCK — Children Sum Property (check only) ====================

Problem
-------
Determine whether a binary tree satisfies the **children-sum property**:
for every non-leaf node `u`, `u->val == (val of left child if any) + (val of right child if any)`.
Leaves vacuously satisfy the property.

Pattern
-------
**Post-order DFS** (or BFS) with a local check at each node:
- Compute/collect the immediate children values (use 0 if missing).
- Verify equality at the current node and recurse into children.

Algorithm (step-by-step, precise)
---------------------------------
check(u):
1) If u == null → return true.                 // empty subtree is valid
2) If u is a leaf → return true.               // no constraint beyond itself
3) Let sum = (u->left ? u->left->val : 0) + (u->right ? u->right->val : 0).
4) If u->val != sum → return false.
5) Return check(u->left) && check(u->right).

Correctness (sketch)
--------------------
The property is local to each node. By verifying it at every internal node and ensuring
both subtrees also satisfy it (via recursion), the entire tree satisfies the property.

Complexity
---------
Time: O(n) — each node visited once.  
Space: O(h) recursion stack (h = height; worst O(n), balanced O(log n)).

Edge Cases / Pitfalls
---------------------
- A node with exactly one child must have `val == child->val` (since the other child contributes 0).
- Large values: if node values can overflow 32-bit when added, compute `sum` in 64-bit.
- This checks only **immediate** children sums, not the sum of all descendants.

Variants
--------
- **Iterative BFS**: level-order traversal, apply the same local check per node.
*/

class Solution {
public:
    bool checkTree(TreeNode* root) {
        if (!root) return true;
        if (!root->left && !root->right) return true; // leaf

        long long sum = 0;
        if (root->left)  sum += root->left->val;
        if (root->right) sum += root->right->val;

        if (sum != root->val) return false;
        return checkTree(root->left) && checkTree(root->right);
    }
};

/* ==================== Optional: Iterative BFS ====================
bool checkTree_BFS(TreeNode* root) {
    if (!root) return true;
    std::queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        TreeNode* u = q.front(); q.pop();
        if (u->left || u->right) {
            long long sum = (u->left ? u->left->val : 0) + (u->right ? u->right->val : 0);
            if (sum != u->val) return false;
        }
        if (u->left)  q.push(u->left);
        if (u->right) q.push(u->right);
    }
    return true;
}
*/
