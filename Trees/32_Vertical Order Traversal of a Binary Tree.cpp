/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
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



vector<vector<int>> verticalTraversal(TreeNode* root) {
    // 🌐 Map to hold nodes by horizontal distance (hd) and level (depth)
    // Structure: hd → depth → multiset of node values (to maintain sorted order)
    map<int, map<int, multiset<int>>> nodes;

    // 🧭 Queue for BFS traversal
    // Each item holds: {node, {depth (row), hd (column)}}
    queue<pair<TreeNode*, pair<int, int>>> q;
    q.push({root, {0, 0}}); // root is at hd = 0, depth = 0

    // 🔁 Perform level-order traversal with coordinate tracking
    while (!q.empty()) {
        auto [curr, pos] = q.front(); q.pop();
        int depth = pos.first;
        int hd = pos.second;

        // 🗂 Insert node's value into its correct vertical & level slot
        nodes[hd][depth].insert(curr->val);

        // 👈 Traverse left child: hd - 1, depth + 1
        if (curr->left)
            q.push({curr->left, {depth + 1, hd - 1}});

        // 👉 Traverse right child: hd + 1, depth + 1
        if (curr->right)
            q.push({curr->right, {depth + 1, hd + 1}});
    }

    // 📦 Prepare the final result by flattening the map
    vector<vector<int>> result;
    for (auto& [hd, levelMap] : nodes) {
        vector<int> col;
        for (auto& [depth, values] : levelMap) {
            // Add all node values in sorted order
            col.insert(col.end(), values.begin(), values.end());
        }
        result.push_back(col);
    }

    return result;
}
