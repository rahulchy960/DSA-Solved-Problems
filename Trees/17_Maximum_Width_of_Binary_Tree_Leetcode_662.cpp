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
    int widthOfBinaryTree(TreeNode* root) {
        queue<pair<TreeNode*, int>>dq;
        long long res = 1;
        dq.push({root, 0});
        while(!dq.empty()){
            long long end = dq.back().second ;
            long long start = dq.front().second ;
            long long width = end - start + 1; 
            res = max(res, width);
            int n = dq.size();
            for(int i=0;i<n;i++){
                
                TreeNode* curr = dq.front().first;
                int idx = dq.front().second;
                
                dq.pop();
                
                long long indexLeft = 2*(long long)idx + 1;
                long long indexRight = 2*(long long)idx + 2;
                
                if(curr->left != NULL) dq.push({curr->left, indexLeft});
                if(curr->right != NULL) dq.push({curr->right, indexRight});
            }
        }
        return res;
    }
};




int widthOfBinaryTree(TreeNode* root) {
    // ⏳ Queue stores {node, index} simulating positions in a complete binary tree
    queue<pair<TreeNode*, int>> dq;
    long long res = 1;  // 📏 Max width of the binary tree

    dq.push({root, 0});

    while(!dq.empty()) {
        long long start = dq.front().second;      // Leftmost node's index at current level
        long long end = dq.back().second;         // Rightmost node's index at current level
        long long width = end - start + 1;        // 🧮 Width of the current level
        res = max(res, width);                    // 🔄 Update max width

        int n = dq.size();  // Number of nodes at current level
        for(int i = 0; i < n; i++) {
            TreeNode* curr = dq.front().first;
            int idx = dq.front().second;
            dq.pop();

            // 🔢 Normalize the index using complete binary tree logic:
            // Left child index = 2 * idx + 1
            // Right child index = 2 * idx + 2
            long long indexLeft = 2LL * idx + 1;
            long long indexRight = 2LL * idx + 2;

            if(curr->left != NULL) dq.push({curr->left, indexLeft});
            if(curr->right != NULL) dq.push({curr->right, indexRight});
        }
    }

    return res;
}
