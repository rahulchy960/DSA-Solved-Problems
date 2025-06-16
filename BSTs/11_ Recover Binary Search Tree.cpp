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
    TreeNode *prev = NULL, *first = NULL, *second = NULL;
    void fixBST(TreeNode* root){
        if(root == NULL) return;
        fixBST(root->left);
        if(prev == NULL) prev = root;
        else{
            if(prev->val > root->val){
                if(first == NULL)
                    first = prev;
                second = root;
            }
        }
        prev = root;
        fixBST(root->right);
    }
    void recoverTree(TreeNode* root) {
        fixBST(root);
        swap(first->val, second->val);
    }
};








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
    // These three pointers will help us identify the two misplaced nodes
    TreeNode *prev = NULL;   // Tracks the previous node in in-order traversal
    TreeNode *first = NULL;  // First misplaced node
    TreeNode *second = NULL; // Second misplaced node

    // Helper function: In-order traversal to detect swapped nodes
    void fixBST(TreeNode* root) {
        if(root == NULL) return;

        // Traverse left subtree
        fixBST(root->left);

        // Check for violation of in-order property
        if(prev && prev->val > root->val) {
            // First time the violation is found — store the previous node
            if(first == NULL)
                first = prev;

            // Always update second to the current node (might update twice)
            second = root;
        }

        // Update the previous node to current
        prev = root;

        // Traverse right subtree
        fixBST(root->right);
    }

    // Main function to recover the tree
    void recoverTree(TreeNode* root) {
        // Step 1: Find the two incorrect nodes using in-order traversal
        fixBST(root);

        // Step 2: Swap their values to correct the BST
        swap(first->val, second->val);
    }
};
