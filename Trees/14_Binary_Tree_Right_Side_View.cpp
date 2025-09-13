
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == NULL)return {};
        queue<TreeNode*>q;
        q.push(root);
        vector<int>res;
        while(!q.empty()){
            int level = q.size();
            for(int i=0;i<level;i++){
                TreeNode* temp = q.front();
                q.pop();
                if(i==0) res.push_back(temp->val);
                if(temp->right != NULL)q.push(temp->right);
                if(temp->left != NULL)q.push(temp->left);
            }
        }
        return res;
    }
};


/*
==================== REVISION BLOCK — Binary Tree Right Side View ====================

Problem
-------
Return the list of node values visible when the tree is viewed from the **right** side:
for each depth (level), pick the **rightmost** node.

Pattern
-------
Level-order **BFS** by layers. Two equivalent ways:
1) Push children in order **right, then left** and take the **first** node of each level.
2) Push children in order **left, then right** and take the **last** node of each level.
(Your code uses #1.)

Algorithm (step-by-step; BFS, right-first)
------------------------------------------
1) If root == nullptr → return {}.
2) Initialize queue with root; result = [].
3) While queue not empty:
   a) sz = queue.size()  // number of nodes at current level
   b) For i in [0..sz-1]:
      • u = queue.front(); pop
      • If i == 0, append u->val to result  // the rightmost at this level (since we push right first)
      • If u->right, push u->right
      • If u->left,  push u->left
4) Return result.

Why this works (correctness)
----------------------------
Within a level, visiting **right child first** ensures the node encountered earliest (i=0)
is the rightmost among all nodes at that depth. Level boundaries are preserved by the sz
snapshot, so exactly one value per depth is recorded.

Complexity
---------
Time: O(n) — each node is enqueued/dequeued once.  
Space: O(n) — queue holds up to the tree’s maximum width; output is O(h).

Edge Cases / Pitfalls
---------------------
- Empty tree → return empty vector.
- If you push **left before right**, change the pick to **i == sz-1**.
- DFS alternative: Preorder **root→right→left** recording the **first** visit per depth.
- Extremely skewed trees still run in O(n) and minimal queue size.

========================================================
*/

class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        std::queue<TreeNode*> q;
        q.push(root);
        std::vector<int> res;

        while (!q.empty()) {
            int sz = (int)q.size();
            for (int i = 0; i < sz; ++i) {
                TreeNode* u = q.front(); q.pop();
                if (i == 0) res.push_back(u->val);   // first seen at this level = rightmost
                if (u->right) q.push(u->right);      // push right first
                if (u->left)  q.push(u->left);
            }
        }
        return res;
    }
};

/* ==================== Optional: DFS variant (root→right→left) ====================
Record the first node seen at each depth.
Time O(n), recursion stack O(h).
*/
void dfsRight(TreeNode* u, int depth, std::vector<int>& out) {
    if (!u) return;
    if ((int)out.size() == depth) out.push_back(u->val); // first at this depth
    dfsRight(u->right, depth + 1, out);
    dfsRight(u->left,  depth + 1, out);
}

std::vector<int> rightSideView_DFS(TreeNode* root) {
    std::vector<int> res;
    dfsRight(root, 0, res);
    return res;
}
