class Solution {
public:
    int countNodes(TreeNode* root) {
        if(root == NULL) return 0;
        int lh = 0, rh =0;

        TreeNode* curr = root;
        while(curr!=NULL){
            lh++;
            curr = curr->left;
        }

        curr = root;
        while(curr!=NULL){
            rh++;
            curr = curr->right;
        }

        if(lh == rh) return pow(2, lh)-1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

/*
==================== REVISION BLOCK — Count Complete Tree Nodes (height trick) ====================

Problem
-------
Given the root of a **complete** binary tree, return the total number of nodes.

Pattern
-------
Use the **height equality test**:
- For a perfect tree (all levels full), the node count is 2^h - 1.
- For a complete but not perfect tree, **one** subtree is perfect; recurse on subtrees.

Algorithm (step-by-step)
------------------------
1) If root == nullptr → return 0.
2) Compute:
   - lh = height going **left** from root (count nodes on the left spine).
   - rh = height going **right** from root (count nodes on the right spine).
3) If lh == rh:
   - Tree is **perfect** → answer = 2^lh - 1  (compute via bit shift, not `pow`).
4) Else:
   - return 1 + countNodes(root->left) + countNodes(root->right)

Correctness (sketch)
--------------------
In a complete tree, if the left height equals the right height, every level is full
(i.e., the tree is perfect). Otherwise, the last level is partially filled on exactly
one side. Recursing splits off a perfect subtree each time and sums the rest.

Complexity
---------
Let h = tree height = O(log n).
- Each call computes two heights in O(h) and recurses to at most **one level deeper**
  on both sides but effectively shrinks the problem size by ~half.
- T(n) = T(n/2) + O(h) ⇒ **O((log n)^2)** time.
- Space: O(h) recursion stack.

Edge Cases / Pitfalls
---------------------
- Use bit shifts for 2^h: `(1LL << lh) - 1` (avoids floating `pow` truncation issues).
- Height definition: here `lh`/`rh` count **levels** (root-only tree has height 1).
- Works for any complete tree (single node, skewed last level, etc.).
*/

class Solution {
public:
    int countNodes(TreeNode* root) {
        if (!root) return 0;

        // compute left spine height
        int lh = 0;
        for (TreeNode* p = root; p; p = p->left) ++lh;

        // compute right spine height
        int rh = 0;
        for (TreeNode* p = root; p; p = p->right) ++rh;

        if (lh == rh) {
            // perfect tree of height lh: nodes = 2^lh - 1
            return static_cast<int>((1LL << lh) - 1);
        }
        // otherwise, sum recursively
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

/* ==================== Optional: Binary Search on Last Level (also O((log n)^2)) ====================

Idea
----
For height h (levels, 1-based), nodes above the last level = (1 << (h-1)) - 1.
The last level has up to (1 << (h-1)) nodes indexed [0 .. 2^(h-1)-1].
Binary-search how many exist by walking bits from the root (left=0, right=1).

Why it can be nicer
-------------------
It does O(log n) height work once, then O(log n) steps to check existence per
binary-search probe → O((log n)^2) overall, with good constants.

Code
----
int leftHeight(TreeNode* p){ int h=0; while(p){ ++h; p=p->left; } return h; }

bool exists(TreeNode* root, int idx, int depth){ // depth = h-1 moves
    int lo = 0, hi = (1 << depth) - 1;
    TreeNode* node = root;
    for (int d = depth - 1; d >= 0 && node; --d) {
        int mid = (lo + hi) >> 1;
        if (idx <= mid) { node = node->left;  hi = mid; }
        else            { node = node->right; lo = mid + 1; }
    }
    return node != nullptr;
}

int countNodes(TreeNode* root) {
    if (!root) return 0;
    int h = leftHeight(root);
    if (h == 1) return 1;
    int fullAbove = (1 << (h - 1)) - 1;
    int lo = 0, hi = (1 << (h - 1)) - 1; // last-level range
    while (lo <= hi) {
        int mid = lo + ((hi - lo) >> 1);
        if (exists(root, mid, h - 1)) lo = mid + 1; // search higher indices
        else                          hi = mid - 1;
    }
    // lo = count of existing nodes on last level
    return fullAbove + lo + 1; // +1? No. Nodes = fullAbove + lastLevelCount
}
*/
