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
    int diameter(TreeNode* root, int &res){
        if(root == NULL) 
            return 0;
        int d1 = diameter(root->left, res);
        int d2 = diameter(root->right, res);
        res = max(res, d1 + d2);
        return max(d1,d2)+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;
        int res = 0;
        int h = diameter(root, res);
        return res;
    }
};