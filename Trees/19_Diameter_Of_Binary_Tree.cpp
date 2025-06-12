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


public:
    // 🔁 Recursive function to compute height and update diameter
    int diameter(TreeNode* root, int &res) {
        if(root == NULL) 
            return 0;

        // 🧱 Compute height of left and right subtrees
        int d1 = diameter(root->left, res);
        int d2 = diameter(root->right, res);

        // 🎯 Update max diameter found so far
        // Diameter at current node = d1 (left height) + d2 (right height)
        res = max(res, d1 + d2);

        // ⬆ Return height of subtree rooted at current node
        return max(d1, d2) + 1;
    }

    // 🚪 Entry point
    int diameterOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;

        int res = 0;
        diameter(root, res);  // Run DFS and update res
        return res;
    }
