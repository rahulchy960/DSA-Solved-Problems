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
    void flatten(TreeNode* root) {
        if(root == NULL) return;

        TreeNode *head = root;
        stack<TreeNode*>s;
        TreeNode *curr = root;
        while(!s.empty() || curr!=NULL){
            TreeNode* curr = s.top();
            s.pop();
            while(curr->left != NULL){
                while(curr->left != NULL){
                    root->right = curr->left;
                    root->left = NULL;
                    root = curr->left;
                    if(curr->right != NULL)
                        s.push(curr->right);
                    curr = curr->left;
                }
                if(!s.empty()){
                    curr = s.top();
                    s.pop();
                }      
            }
        }
        root = head;
    }
};