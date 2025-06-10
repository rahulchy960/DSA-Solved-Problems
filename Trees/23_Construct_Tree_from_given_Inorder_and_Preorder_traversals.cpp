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
    int preIndex = 0;
    TreeNode* CTree(vector<int>& preorder, vector<int>& inorder, int is, int ie){
        // contructing the tree in preorder fasion
        if(is>ie) return NULL;

        TreeNode* node = new TreeNode(preorder[preIndex]);
        preIndex++;
        int inIndex = -1;
        for(int i=is;i<=ie;i++){
            if(inorder[i] == node->val){
                inIndex = i;
                break;
            }
        }

        node->left = CTree(preorder, inorder, is, inIndex-1);
        node->right = CTree(preorder, inorder, inIndex+1, ie);

        return node;


    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return CTree(preorder, inorder, 0, inorder.size()-1);
    }
};