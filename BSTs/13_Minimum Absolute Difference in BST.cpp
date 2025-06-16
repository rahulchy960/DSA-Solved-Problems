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
    
    TreeNode* prev = NULL;
    int res = INT_MAX;
    
    void getMin(TreeNode* root){
        if(root == NULL) return;
        getMin(root->left);
        if(prev != NULL)
            res = min(res, (root->val - prev->val));
        prev = root;
        getMin(root->right);
    }
    int getMinimumDifference(TreeNode* root) {
        getMin(root);
        return res;
    }
};