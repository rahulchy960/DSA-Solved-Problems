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
    bool isMirrorTree(TreeNode* p, TreeNode* q){
        if(p == NULL && q == NULL)
            return true;
        if(p==NULL || q==NULL)
            return false;
        return (p->val == q->val && isMirrorTree(p->left, q->right) && isMirrorTree(p->right,q->left));
    }
    bool isSymmetric(TreeNode* root) {
        if(root == NULL || (root->left==NULL && root->right==NULL))
            return true;
        if(root->left == NULL || root->right==NULL)
            return false;
        if(isMirrorTree(root->left, root->right))
            return true;
        else 
            return false;
    }
};