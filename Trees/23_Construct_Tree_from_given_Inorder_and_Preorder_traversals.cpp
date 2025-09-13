class Solution {
public:
    int preIndex = 0;
    TreeNode* CTree(vector<int>& preorder, vector<int>& inorder, int is, int ie){
        if(is>ie) return NULL;

        TreeNode* node = new TreeNode(preorder[preIndex]);
        preIndex++;
        int inIndex = -1;
        for(int i=is;i<=ie;i++){
            if(inorder[i] == node->val){
                inIndex = i;
                break;
            }
        }

        node->left = CTree(preorder, inorder, is, inIndex-1);
        node->right = CTree(preorder, inorder, inIndex+1, ie);

        return node;


    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return CTree(preorder, inorder, 0, inorder.size()-1);
    }
};


/*
==================== REVISION BLOCK — Construct Binary Tree from Preorder & Inorder ====================

Problem
-------
Given two arrays:
- preorder (Root, Left, Right)
- inorder  (Left, Root, Right)
build the original binary tree. Assume all node values are **unique**.

Pattern
-------
Divide & Conquer with an index pointer over preorder:
- The next unused preorder value is always the **root** of the current (sub)tree.
- Find that root’s position in inorder; everything left of it is the left subtree,
  everything right is the right subtree. Recurse on [lo..mid-1] and [mid+1..hi].

Algorithm (step-by-step, precise)
---------------------------------
Let `preIdx` be the index of the next root in `preorder`.
1) Precompute `pos[val] = index of val in inorder` (hash map) to get O(1) splits.
2) Define `build(lo, hi)` (inclusive inorder bounds):
   a) If `lo > hi` → return null (empty subtree).
   b) `val = preorder[preIdx++]`  // consume next root
   c) `mid = pos[val]`            // locate root in inorder
   d) Create node with `val`.
   e) `node->left  = build(lo, mid-1)`
   f) `node->right = build(mid+1, hi)`
   g) Return node.
3) Call `build(0, n-1)` with `preIdx = 0`.

Correctness (sketch)
--------------------
- Preorder guarantees we always pick the current subtree’s root first.
- Inorder uniquely splits that subtree into left and right parts (values unique).
- Recursing on the split intervals reconstructs left and right subtrees exactly.
- By induction on subtree size, the reconstruction is unique and correct.

Complexity
----------
- Precompute map: O(n)
- Each node is created once; each split is O(1) via the map ⇒ **Time: O(n)**
- Space: O(n) for the map + O(h) recursion stack (h = tree height; worst O(n), avg O(log n)).

Edge Cases / Pitfalls
---------------------
- Empty input → return nullptr.
- Arrays must be the same size and contain the same multiset of unique values.
- **Do not** linearly scan inorder each time (that is O(n^2)).
- **Reset** any class member `preIndex` before each build; or pass it by reference.
- Avoid slicing vectors (copies); use indices.
*/

class Solution {
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        int n = (int)preorder.size();
        if (n == 0) return nullptr;

        // value -> index in inorder
        std::unordered_map<int, int> pos;
        pos.reserve(n * 2);
        for (int i = 0; i < n; ++i) pos[inorder[i]] = i;

        int preIdx = 0;  // reset for each call

        std::function<TreeNode*(int,int)> build = [&](int lo, int hi) -> TreeNode* {
            if (lo > hi) return nullptr;
            int val = preorder[preIdx++];          // next root from preorder
            int mid = pos[val];                    // split point in inorder
            TreeNode* node = new TreeNode(val);
            node->left  = build(lo, mid - 1);      // build left subtree
            node->right = build(mid + 1, hi);      // build right subtree
            return node;
        };

        return build(0, n - 1);
    }
};

/* ==================== Notes on Your Version ====================
- Your approach is logically correct but linearly searches inorder to find `inIndex`,
  making it O(n^2) in the worst case. The hashmap above reduces it to O(n).
- Also ensure `preIndex` is reinitialized to 0 inside `buildTree()` before you start,
  otherwise multiple calls on the same Solution object will fail.
- If duplicates can appear, this reconstruction is ambiguous; typical problems assume uniqueness.
*/
