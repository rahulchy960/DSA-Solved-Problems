class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>res;
        if(root == NULL) return res;
        deque<TreeNode*> dq;
        dq.push_back(root);
        bool reverse = false;
        while(!dq.empty()){
            int n = dq.size();
            vector<int>temp;
            for(int i=0;i<n;i++){
                
                if(reverse){
                    TreeNode* curr = dq.back();
                    dq.pop_back();
                    temp.push_back(curr->val);
                    if(curr->right != NULL) dq.push_front(curr->right);
                    if(curr->left != NULL) dq.push_front(curr->left);  
                }
                else{
                    TreeNode* curr = dq.front();
                    dq.pop_front();
                    temp.push_back(curr->val);
                    if(curr->left != NULL) dq.push_back(curr->left);
                    if(curr->right != NULL) dq.push_back(curr->right);
                }
            }
            reverse = !reverse;
            res.push_back(temp);
        }
        return res;

    }
};


/*
==================== REVISION BLOCK — Binary Tree Zigzag Level Order Traversal ====================

Problem
-------
Return the level order of a binary tree, but alternate the direction each level:
Level 0 → left→right, Level 1 → right→left, Level 2 → left→right, and so on.

Pattern
-------
Level-order **BFS** with a direction toggle.
Two common ways:
1) **Deque method** (your approach): pop from one end and push children on the other end depending on direction.
2) **Queue + index fill** (clean & popular): always pop left-to-right, but write values into a vector at
   either index i (LTR) or index (n-1-i) (RTL).

Algorithm (Queue + index fill — precise & simple)
-------------------------------------------------
1) If root == nullptr → return {}.
2) Push root into a queue; set `leftToRight = true`.
3) While queue not empty:
   a) Let `sz = queue.size()`; create `level` vector of size `sz`.
   b) Repeat `i = 0..sz-1`:
        - Pop node `u` from queue.
        - `pos = (leftToRight ? i : sz-1-i)`; set `level[pos] = u->val`.
        - If `u->left`  push it; if `u->right` push it.
   c) Append `level` to result and flip `leftToRight`.
4) Return result.

Correctness (sketch)
--------------------
BFS guarantees nodes are processed level by level. Filling indices from the front or the back implements
the zigzag ordering without changing the traversal order or child push order. Alternating `leftToRight`
per level enforces the required pattern.

Complexity
----------
Time: O(n) — each node enqueued/dequeued once, O(1) work per node.  
Space: O(n) — queue + output; the per-level vector is O(width) and reused each level.

Edge Cases / Pitfalls
---------------------
- Empty tree → return empty vector.
- Very skewed tree → still O(n).
- If using the **deque method**, push children in the mirrored order on reverse levels:
  when popping from back, **push right then left to the front**; when popping front, **push left then right to back**.
- Avoid naming a boolean `reverse` since it can shadow `std::reverse`; use `leftToRight`.

========================================================
*/

class Solution {
public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::vector<std::vector<int>> res;
        if (!root) return res;

        std::queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;

        while (!q.empty()) {
            int sz = (int)q.size();
            std::vector<int> level(sz);

            for (int i = 0; i < sz; ++i) {
                TreeNode* u = q.front(); q.pop();
                int pos = leftToRight ? i : (sz - 1 - i);
                level[pos] = u->val;

                if (u->left)  q.push(u->left);
                if (u->right) q.push(u->right);
            }
            res.push_back(std::move(level));
            leftToRight = !leftToRight;
        }
        return res;
    }
};

/* ==================== Optional: Your Deque Method (tidied) ====================
- Works well; just rename the flag and keep child-push ordering mirrored.
*/
std::vector<std::vector<int>> zigzagLevelOrder_deque(TreeNode* root) {
    std::vector<std::vector<int>> res;
    if (!root) return res;

    std::deque<TreeNode*> dq;
    dq.push_back(root);
    bool leftToRight = true;

    while (!dq.empty()) {
        int sz = (int)dq.size();
        std::vector<int> level; level.reserve(sz);

        for (int i = 0; i < sz; ++i) {
            if (leftToRight) {
                TreeNode* u = dq.front(); dq.pop_front();
                level.push_back(u->val);
                if (u->left)  dq.push_back(u->left);
                if (u->right) dq.push_back(u->right);
            } else {
                TreeNode* u = dq.back(); dq.pop_back();
                level.push_back(u->val);
                // push children in reversed order to the opposite end
                if (u->right) dq.push_front(u->right);
                if (u->left)  dq.push_front(u->left);
            }
        }
        res.push_back(std::move(level));
        leftToRight = !leftToRight;
    }
    return res;
}
