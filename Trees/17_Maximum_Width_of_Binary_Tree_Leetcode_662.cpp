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