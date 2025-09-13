
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int, map<int, multiset<int>>> mp;
        queue<pair<TreeNode*, pair<int, int>>>q;
        q.push({root,{0, 0}});
        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                auto p = q.front();
                q.pop();
                TreeNode* curr = p.first;
                int vd = p.second.first;
                int hd = p.second.second;
                mp[hd][vd].insert(curr->val);
                if(curr->left != NULL) q.push({curr->left, {vd+1, hd-1}});
                if(curr->right != NULL) q.push({curr->right, {vd+1, hd+1}});
            }
        }
        vector<vector<int>>res;
        for(auto x : mp){
            vector<int>temp;
            for(auto y : x.second){
                for(auto itr = y.second.begin(); itr!=y.second.end(); itr++)
                    temp.push_back(*itr);
            }
            res.push_back(temp);
        }
            
        return res;
    }
};



/*
==================== REVISION BLOCK — Binary Tree Vertical Order Traversal (LC 987) ====================

Problem
-------
Return the vertical order traversal of a binary tree. Columns go from left to right (smallest col to largest).
Within a column, nodes are ordered by row (top to bottom). If multiple nodes share the same (row, col),
order them by value ascending.

Pattern
-------
Coordinate the tree: (row, col), with root at (0,0), left child (row+1, col-1), right child (row+1, col+1).
Collect nodes by column, then by row, breaking ties with value.
Two common implementations:
1) Ordered containers: map<col, map<row, multiset<val>>> (insertion O(log n), natural ordering).
2) Collect & sort: store (col,row,val) tuples, sort by (col,row,val), then group by col (simpler & fast).

Algorithm (step-by-step; ordered-containers)
--------------------------------------------
1) If root == nullptr → return {}.
2) BFS (or DFS) from root while carrying (row, col).
3) Insert each node’s value into mp[col][row] (a multiset).
4) Build the result: for col in ascending order, for row in ascending order,
   append all multiset values to that column’s output vector.

Correctness (sketch)
--------------------
- Column key ensures left→right order.
- Row key ensures top→bottom order within a column.
- Multiset enforces ascending values when (row,col) ties occur.
Thus the output satisfies the required ordering.

Complexity
---------
Let n be the number of nodes.
- Time: O(n log n) due to map/multiset insertions.
- Space: O(n) for maps/multisets + O(n) for the result.

Notes / Pitfalls
----------------
- Always guard `root == nullptr`.
- Either BFS or DFS works; order is derived from (row,col) keys, not traversal order.
- Using `pow`/floating math is not involved here; avoid unnecessary level loops: a plain queue is fine.
*/

class Solution {
public:
    std::vector<std::vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};

        // mp[col][row] = multiset of values at (row,col)
        std::map<int, std::map<int, std::multiset<int>>> mp;

        std::queue<std::pair<TreeNode*, std::pair<int,int>>> q; // node, {row, col}
        q.push({root, {0, 0}});

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            TreeNode* node = cur.first;
            int row = cur.second.first;
            int col = cur.second.second;

            mp[col][row].insert(node->val);

            if (node->left)  q.push({node->left,  {row+1, col-1}});
            if (node->right) q.push({node->right, {row+1, col+1}});
        }

        std::vector<std::vector<int>> res;
        res.reserve(mp.size());
        for (auto& [col, rows] : mp) {
            std::vector<int> colVals;
            for (auto& [row, vals] : rows) {
                colVals.insert(colVals.end(), vals.begin(), vals.end());
            }
            res.push_back(std::move(colVals));
        }
        return res;
    }
};

/* ==================== Optional: Collect & Sort (clean and fast) ====================

Idea
----
Store every node as (col, row, val). Sort all nodes by (col asc, row asc, val asc),
then sweep to build columns. Often simpler and with smaller constants.

Time: O(n log n) for the sort. Space: O(n).

std::vector<std::vector<int>> verticalTraversal(TreeNode* root) {
    if (!root) return {};
    std::vector<std::array<int,3>> nodes; // {col, row, val}

    std::queue<std::pair<TreeNode*, std::pair<int,int>>> q;
    q.push({root, {0, 0}});
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        TreeNode* node = cur.first;
        int row = cur.second.first, col = cur.second.second;
        nodes.push_back({col, row, node->val});
        if (node->left)  q.push({node->left,  {row+1, col-1}});
        if (node->right) q.push({node->right, {row+1, col+1}});
    }

    std::sort(nodes.begin(), nodes.end()); // lex order: col, then row, then val

    std::vector<std::vector<int>> res;
    int i = 0, n = nodes.size();
    while (i < n) {
        int curCol = nodes[i][0];
        std::vector<int> colVals;
        while (i < n && nodes[i][0] == curCol) {
            colVals.push_back(nodes[i][2]);
            ++i;
        }
        res.push_back(std::move(colVals));
    }
    return res;
}
*/
