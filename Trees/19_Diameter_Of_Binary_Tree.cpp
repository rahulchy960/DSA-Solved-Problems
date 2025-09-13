

class Solution {
public:
    int diameter(TreeNode* root, int &res){
        if(root == NULL) 
            return 0;
        int d1 = diameter(root->left, res);
        int d2 = diameter(root->right, res);
        res = max(res, d1 + d2);
        return max(d1,d2)+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;
        int res = 0;
        int h = diameter(root, res);
        return res;
    }
};


/*
==================== REVISION BLOCK — Diameter of a Binary Tree (longest path) ====================

Problem
-------
Return the **diameter** of a binary tree: the length (in **edges**) of the longest path
between any two nodes in the tree (the path may or may not pass through the root).

Pattern
-------
Single-pass **post-order DFS** computing:
- `height(u)` of each node (max edges from `u` down to a leaf), and
- updating a global / reference `best` with `height(left) + height(right)` (the longest path
  that passes through `u`).

Precise Recurrence (heights in **edges**)
-----------------------------------------
Let `h(u)` be the height in edges (empty subtree has height -1, leaf has height 0):
  h(u) = 1 + max(h(u->L), h(u->R))
Diameter candidate through `u`:  h(u->L) + 1 + h(u->R)  =  (hL + hR + 2) edges total,
but if we return subtree heights as **node counts** instead (empty = 0, leaf = 1),
then the diameter in **edges** at `u` is  (hL + hR) with those node-count heights.

Algorithm (step-by-step)
------------------------
1) If root == nullptr → diameter is 0.
2) Do a post-order DFS that returns a **height** and updates a shared `best`:
   a) Recurse to left and right to get `hL` and `hR` (using the same height convention).
   b) Update `best = max(best, hL + hR)`  (when heights are **node counts**, this equals edges).
   c) Return `max(hL, hR) + 1` as the height of the current subtree.
3) After DFS, `best` holds the diameter in edges.

Correctness (sketch)
--------------------
Every simple path’s highest node is some LCA `u`. The path length is exactly the sum of the
longest downward paths in `u`’s left and right subtrees. DFS computes those heights bottom-up
and takes the maximum over all `u`, thus capturing the global longest path.

Complexity
---------
Time: O(n) — each node visited once.  
Space: O(h) — recursion stack (h = tree height; worst O(n) skewed, O(log n) balanced).

Edge Cases / Pitfalls
---------------------
- **Edges vs nodes**: be consistent. With your current helper (empty→0, leaf→1),
  `res` should be `hL + hR` to count **edges** (correct in your code).
- If you choose edge-height convention (empty→-1, leaf→0), then the through-node
  diameter is `(hL + hR + 2)`.
- Don’t compute extra values you don’t use (your `h` in `diameterOfBinaryTree`).
- For an empty tree, define diameter as 0.

========================================================
*/

// Cleaned version of your approach (heights as node-counts; diameter in edges)
class Solution {
    int dfs(TreeNode* u, int& best) {
        if (!u) return 0;                      // empty subtree has 0 nodes height
        int hL = dfs(u->left,  best);
        int hR = dfs(u->right, best);
        best = std::max(best, hL + hR);        // edges = (hL-1) + 1 + (hR-1) = hL + hR - 1 + 1 = hL + hR
        return std::max(hL, hR) + 1;           // node-count height
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int best = 0;
        (void)dfs(root, best);
        return best;
    }
};
