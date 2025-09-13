
class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        int level = 1;
        int maxSum = root->val;
        int res = 1;
        while(!q.empty()){
            int sum = 0;
            int n = q.size();
            for(int i=0;i<n;i++){
                TreeNode* curr = q.front();
                q.pop();
                sum += curr->val;
                if(curr->left != NULL) q.push(curr->left);
                if(curr->right != NULL) q.push(curr->right);
            }
            if(sum>maxSum) {
                res = level;
                maxSum = sum;
            }
            level++;
        }
        return res;
    }
};


/*
==================== REVISION BLOCK — Maximum Level Sum of a Binary Tree (BFS) ====================

Problem
-------
Find the (1-indexed) level of a binary tree whose **sum of node values** is maximum.
If multiple levels tie, return the **smallest** level index.

Pattern
-------
**Level-order BFS**: process nodes level by level, accumulate a sum for each level,
track the best (maxSum, level).

Algorithm (step-by-step)
------------------------
1) If root == nullptr → return 0 (or problem-defined default).
2) Push root into a queue, set level = 1.
3) While queue not empty:
   a) sz = queue.size(), sum = 0
   b) Repeat sz times: pop node u, add u->val to sum, push u->left/right if non-null
   c) If sum > maxSum: update maxSum = sum, ans = level   // strict '>' keeps the smallest level on ties
   d) ++level
4) Return ans.

Correctness (sketch)
--------------------
BFS isolates nodes by depth; each loop computes the exact sum of one level.
Keeping the maximum (with strict comparison) yields the smallest index among ties.

Complexity
---------
Time: O(n) — each node enqueued/dequeued once.  
Space: O(w) — queue holds at most the tree’s maximum width.

Edge Cases
----------
- Empty tree.
- All negative values (initializing maxSum from the first level preserves correctness).
- Large sums: use 64-bit accumulator for safety.

Pitfalls
--------
- Don’t access root->val before checking root != nullptr.
- Use strict '>' for tie-breaking to favor the smallest level.
- Beware 32-bit overflow when summing many nodes → prefer long long for `sum`.

========================================================
*/

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        if (!root) return 0;

        std::queue<TreeNode*> q;
        q.push(root);

        int level = 1, bestLevel = 1;
        long long maxSum = root->val; // works even if all values are negative

        while (!q.empty()) {
            int sz = (int)q.size();
            long long sum = 0;

            for (int i = 0; i < sz; ++i) {
                TreeNode* u = q.front(); q.pop();
                sum += u->val;
                if (u->left)  q.push(u->left);
                if (u->right) q.push(u->right);
            }

            if (sum > maxSum) {
                maxSum = sum;
                bestLevel = level;
            }
            ++level;
        }
        return bestLevel;
    }
};

/* ==================== Optional: DFS depth-sums (same O(n)) ====================
- Accumulate sums by depth via DFS, then scan for the max with smallest index.
*/
void dfsSum(TreeNode* u, int d, std::vector<long long>& sums) {
    if (!u) return;
    if ((int)sums.size() <= d) sums.resize(d + 1, 0);
    sums[d] += u->val;
    dfsSum(u->left,  d + 1, sums);
    dfsSum(u->right, d + 1, sums);
}

int maxLevelSum_DFS(TreeNode* root) {
    if (!root) return 0;
    std::vector<long long> sums; // sums[d] = sum of level (d), with d=0 for level 1
    dfsSum(root, 0, sums);
    int ans = 1; long long best = sums[0];
    for (int d = 1; d < (int)sums.size(); ++d) {
        if (sums[d] > best) { best = sums[d]; ans = d + 1; }
    }
    return ans;
}
