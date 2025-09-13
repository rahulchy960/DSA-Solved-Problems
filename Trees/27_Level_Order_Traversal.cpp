
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>>res;
        if(root==NULL)return res;
        queue<TreeNode*>q;
        q.push(root);
        
        while(!q.empty()){
            int n = q.size();
            vector<int>v;
            for(int i=0;i<n;i++){
                TreeNode *temp = q.front();
                q.pop();
                if(temp->left != NULL) q.push(temp->left);
                if(temp->right != NULL) q.push(temp->right);
                v.push_back(temp->val);
            }
            res.push_back(v);
        }
        return res;
        
    }
};


/*
==================== REVISION BLOCK — Binary Tree Level Order Traversal (BFS) ====================

Problem
-------
Return the node values of a binary tree level by level (top to bottom, left to right).

Pattern
-------
Classic **BFS (level-order)** using a queue. Process nodes in layers:
grab current queue size = nodes in this level, pop them, push their children.

Algorithm (step-by-step)
------------------------
1) If root == nullptr → return {}.
2) Push root into a queue.
3) While the queue is not empty:
   a) Let `sz = queue.size()` (number of nodes in this level).
   b) Create an empty array `level` (reserve `sz`).
   c) Repeat `sz` times:
      • pop node `u`, append `u->val` to `level`
      • if `u->left`  push it
      • if `u->right` push it
   d) Append `level` to the answer.
4) Return the collected levels.

Correctness (sketch)
--------------------
BFS visits nodes by distance (depth) from the root. Capturing the queue size at each
iteration isolates exactly one depth level, so values pushed in that pass correspond
to that level.

Complexity
----------
- Time: O(n) — each node enqueued/dequeued once.
- Space: O(n) — queue holds up to a level’s worth of nodes; output also O(n).

Edge Cases
----------
- Empty tree → return empty vector.
- Skewed tree (all left or all right) → each level has one node.
- Very large tree → BFS is iterative (no recursion depth risk).

Pitfalls
--------
- Don’t recompute `queue.size()` inside the for-loop; take a snapshot before processing the level.
- Push children **after** popping the current node; else level boundaries blur.

Variants
--------
- **DFS by depth**: collect in `ans[depth]` (O(n) time, O(h) stack).
- **Zigzag level order**: alternate reversing every other level or fill from both ends using deque.
========================================================
*/

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> res;
        if (!root) return res;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            std::vector<int> level;
            level.reserve(sz);

            for (int i = 0; i < sz; ++i) {
                TreeNode* u = q.front(); q.pop();
                level.push_back(u->val);
                if (u->left)  q.push(u->left);
                if (u->right) q.push(u->right);
            }
            res.push_back(std::move(level));
        }
        return res;
    }
};

