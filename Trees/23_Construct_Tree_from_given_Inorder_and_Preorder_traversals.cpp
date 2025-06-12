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





int preIndex = 0;  // 🔁 Global index to track position in preorder array

// 🔧 Recursive function to build tree
TreeNode* CTree(vector<int>& preorder, vector<int>& inorder, int is, int ie) {
    // 🛑 Base Case: No elements to construct subtree
    if(is > ie) return NULL;

    // 🌱 Step 1: Create current root node using preorder
    TreeNode* node = new TreeNode(preorder[preIndex]);
    preIndex++;  // Move to next root in preorder

    // 🔍 Step 2: Find the index of this node in inorder traversal
    int inIndex = -1;
    for(int i = is; i <= ie; i++) {
        if(inorder[i] == node->val) {
            inIndex = i;
            break;
        }
    }

    // 🔄 Step 3: Recursively build left and right subtrees
    node->left = CTree(preorder, inorder, is, inIndex - 1);     // left subtree: elements before inIndex
    node->right = CTree(preorder, inorder, inIndex + 1, ie);    // right subtree: elements after inIndex

    return node;  // 🔁 Return current subtree
}

// 🌳 Wrapper function to start tree construction
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return CTree(preorder, inorder, 0, inorder.size() - 1);
}
