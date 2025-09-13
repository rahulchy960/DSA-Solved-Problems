class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if(root == NULL) return NULL; // case 1
        if(root->val == p->val || root->val == q->val) return root; // case 2

        TreeNode* LCA1 = lowestCommonAncestor(root->left,p ,q);
        TreeNode* LCA2 = lowestCommonAncestor(root->right,p ,q);

        if(LCA1 != NULL && LCA2!= NULL) return root; // case 3;

        if(LCA1 != NULL) return LCA1;
        else return LCA2;
    }
};

/*
==================== REVISION BLOCK — Lowest Common Ancestor in a Binary Tree (general) ====================

Problem
-------
Given a binary tree (not necessarily a BST) and two nodes p and q, return their Lowest Common Ancestor (LCA):
the lowest node that has both p and q as descendants (a node can be a descendant of itself).

Pattern
-------
Post-order **DFS (divide & conquer)**:
- Ask left and right subtrees for p/q.
- Combine results at the current node.

Algorithm (step-by-step, precise)
---------------------------------
We define `LCA(u)` which returns:
- `u` itself if `u` equals `p` or `q`,
- the found node (either `p`, `q`, or an LCA) from its subtree,
- `nullptr` if neither target is in that subtree.

For each node `u`:
1) **Base cases**
   - If `u == nullptr` → return `nullptr`.
   - If `u == p || u == q` → return `u`.  // node is ancestor of itself
2) **Recurse**
   - `left  = LCA(u->left)`
   - `right = LCA(u->right)`
3) **Combine / Decide**
   - If `left != nullptr` **and** `right != nullptr` → `u` is the split point ⇒ **return `u`**.
   - Else if exactly one side is non-null → **return that side** (it bubbles up the found target or LCA).
   - Else (both null) → **return `nullptr`**.

Decision table (summarizes step 3)
----------------------------------
left    right   → return
null    null    → null
node    null    → node
null    node    → node
node    node    → current `u` (LCA)

Correctness (sketch)
--------------------
- If `u` is the true LCA, one target lies in each subtree (or `u` equals one target and the other lies below),
  making both recursive calls non-null → we return `u`.
- If both targets lie strictly in one subtree, only that subtree returns non-null and we bubble it up.
- Lowestness follows from post-order: a lower LCA is returned before its ancestors can claim it.

Complexity
----------
Time: O(n) — each node is visited once.  
Space: O(h) — recursion stack, h = tree height (worst O(n) skewed, O(log n) balanced).

Edge Cases / Pitfalls
---------------------
- **Compare pointers** (`u == p` / `u == q`), not values; duplicates may exist.
- If one of {p,q} is missing from the tree, the routine returns the one that exists (or null if both absent).
  If you must ensure **both** exist, use a presence-check variant below.
- Works for general binary trees; see BST-optimized version for ordered trees.

==================== Optional: Ensure BOTH p and q exist ====================
Idea: return a tuple {lca, hasP, hasQ}. Only accept `lca` if hasP && hasQ.

==================== Optional: BST-specialized walk ====================
In a BST, walk down once:
- If p->val and q->val are both < u->val → go left.
- If both > u->val → go right.
- Else `u` is the LCA.

========================================================
*/

// General binary tree (pointer comparisons)
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;

        TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right) return root;      // split point
        return left ? left : right;          // bubble up found node or null
    }
};


