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

    int prev = INT_MIN;
    bool isValidBST(TreeNode* root, long long min = LONG_MIN, long long max = LONG_MAX) {
        if(root == NULL) return true;

        return  (root->val > min) && 
                (root->val < max) &&
                isValidBST(root->left, min, root->val) &&
                isValidBST(root->right, root->val, max);
    }


    long long prev = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if(root == NULL) return true;

        if(isValidBST(root->left) == false) return false; // if we return true then the right side will not checked

        if(prev >= root->val) return false;
        prev = root->val;

        return isValidBST(root->right);
    }
};




    // ✅ Method 1: Recursive Range Validation
    bool isValidBST(TreeNode* root, long long min = LONG_MIN, long long max = LONG_MAX) {
        if(root == NULL) return true;

        // 🧠 For each node, ensure:
        // value must lie strictly between min and max
        return  (root->val > min) && 
                (root->val < max) &&
                isValidBST(root->left, min, root->val) &&
                isValidBST(root->right, root->val, max);
    }

    // ✅ Method 2: In-order Traversal Check
    long long prev = LONG_MIN;  // used for method 2

    bool isValidBST_Inorder(TreeNode* root) {
        if(root == NULL) return true;

        // ⬅️ Check left subtree first
        if(isValidBST_Inorder(root->left) == false) return false;

        // 🔁 BST property: in-order traversal must be strictly increasing
        if(prev >= root->val) return false;
        prev = root->val;

        // ➡️ Check right subtree
        return isValidBST_Inorder(root->right);
    }
};
