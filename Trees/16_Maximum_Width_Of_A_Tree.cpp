/*  Structure of a Binary Tree

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};
 */

class Solution {
  public:
    // Function to get the maximum width of a binary tree.
    int getMaxWidth(Node* root) {
        // Your code here
        if(root == NULL) return 0;
        queue<Node*>q;
        q.push(root);
        int res = 0;
        while(!q.empty()){
            int count = q.size();
            res = max(res, count);
            for(int i=0;i<count;i++){
                Node* curr = q.front();
                q.pop();
                if(curr->left != NULL)q.push(curr->left);
                if(curr->right != NULL)q.push(curr->right);
            }
        }
        return res;
    }
};


/*
==================== REVISION BLOCK — Maximum Width of Binary Tree (level-index BFS) ====================

Problem
-------
Given a binary tree, the **width** of a level is the number of nodes between the leftmost
and rightmost non-null nodes at that depth, counting the “gaps” as in a complete tree index.
Return the maximum width over all levels.

Pattern
-------
**Level-order BFS** + complete-binary-tree **indexing**:
- Give root index 0. For a node with index i, its children have indices:
  left = 2*i + 1, right = 2*i + 2.
- The width of a level = (rightmost_index - leftmost_index + 1).

Algorithm (step-by-step, precise)
---------------------------------
1) If root == nullptr → return 0.
2) Use a queue of (node, idx). Start with (root, 0).
3) While queue not empty:
   a) Let `sz = queue.size()`. Let `offset = queue.front().idx` (leftmost index of this level).
   b) Initialize `left = 0`, `right = 0`.
   c) Repeat `sz` times:
      • Pop (u, i). Let `j = i - offset`  // **normalize** to prevent overflow.
      • If first node in level: `left = j`; always set `right = j`.
      • If u->left  exists, push (u->left,  2*j + 1).
      • If u->right exists, push (u->right, 2*j + 2).
   d) Update `ans = max(ans, right - left + 1)`.
4) Return `ans`.

Why normalization?
------------------
Indices grow roughly by ×2 each level. Subtracting the leftmost index per level
keeps them small (0-based within the level), preventing 64-bit overflow and reducing risk.

Correctness (sketch)
--------------------
Complete-tree indexing preserves the relative horizontal positions of nodes, including gaps.
At each depth, the difference between max and min indices + 1 equals that level’s width.
Taking the max across levels yields the answer.

Complexity
---------
Time: O(n) — visit each node once.  
Space: O(n) — queue in the worst case (breadth/width of the tree).

Notes / Pitfalls
----------------
- **Guard null root.**
- Use a 64-bit type for indices (e.g., `unsigned long long`) and **normalize per level**.
- Don’t store indices in `int`; children `2*i+…` will overflow.
- Your original code computed `end = q.back().second` / `start = q.front().second`, but used `int` in the queue,
  causing truncation. Also, compute width **after** normalization.
========================================================
*/

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;

        using ULL = unsigned long long;
        std::queue<std::pair<TreeNode*, ULL>> q;
        q.push({root, 0});

        long long best = 0;

        while (!q.empty()) {
            int sz = (int)q.size();
            ULL offset = q.front().second;   // normalize this level
            ULL left = 0, right = 0;

            for (int k = 0; k < sz; ++k) {
                auto [node, i] = q.front(); q.pop();
                ULL j = i - offset;          // normalized index within level

                if (k == 0) left = j;
                right = j;

                if (node->left)  q.push({node->left,  2*j + 1});
                if (node->right) q.push({node->right, 2*j + 2});
            }
            long long width = (long long)(right - left + 1);
            if (width > best) best = width;
        }
        return (int)best;
    }
};

/* -------- Minimal fixes to your version --------
- Change queue index type to 64-bit.
- Normalize per level (subtract start) before generating children indices.
- Guard root == nullptr.
*/
