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



// Algorithm for Vertical Order Traversal of a Binary Tree:
//
// 1. We need to return the vertical order traversal of the binary tree.
//    Vertical traversal means:
//      - Nodes that fall in the same vertical line from top to bottom.
//      - If two nodes are at the same position, sort them by their value.
//
// 2. We use a BFS approach and store (node, vertical distance, horizontal distance) in a queue.
//      - Vertical distance (vd): Level (top-down)
//      - Horizontal distance (hd): Column (left-right), root is at hd=0
//
// 3. To maintain order:
//      - We use a nested map structure: map<hd, map<vd, multiset<int>>>
//        - `hd` → horizontal distance (column)
//        - `vd` → vertical level (depth)
//        - `multiset` → to store multiple values in sorted order if they exist at the same (hd, vd)
//
// 4. BFS Traversal:
//      - Start with root at (0, 0)
//      - For each node, push left child at (vd+1, hd-1), right child at (vd+1, hd+1)
//      - Insert current node's value into the map using its hd and vd
//
// 5. After traversal, extract the values from the map:
//      - Traverse `mp` in order of increasing `hd` (left to right)
//      - For each `hd`, traverse in increasing `vd` (top to bottom)
//      - Append all values in the multiset to a temporary vector
//      - Add this temporary vector to the result

vector<vector<int>> verticalTraversal(TreeNode* root) {
    // Nested map: hd -> vd -> multiset of node values
    map<int, map<int, multiset<int>>> mp;

    // BFS queue storing node and its (vd, hd)
    queue<pair<TreeNode*, pair<int, int>>> q;
    q.push({root, {0, 0}}); // root at vd=0, hd=0

    // Perform level-order traversal (BFS)
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            auto p = q.front(); q.pop();
            TreeNode* curr = p.first;
            int vd = p.second.first;  // vertical depth
            int hd = p.second.second; // horizontal distance

            // Insert value into map
            mp[hd][vd].insert(curr->val);

            // Add left and right children with updated coordinates
            if (curr->left != NULL) q.push({curr->left, {vd + 1, hd - 1}});
            if (curr->right != NULL) q.push({curr->right, {vd + 1, hd + 1}});
        }
    }

    // Prepare the final result
    vector<vector<int>> res;
    for (auto x : mp) {
        vector<int> temp;
        for (auto y : x.second) {
            // Insert all values from multiset into temp
            for (auto itr = y.second.begin(); itr != y.second.end(); itr++)
                temp.push_back(*itr);
        }
        res.push_back(temp); // Add vertical column to result
    }

    return res;
}
