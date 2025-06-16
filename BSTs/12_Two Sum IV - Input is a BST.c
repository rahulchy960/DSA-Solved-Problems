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
    unordered_set<int>s;
    bool findTarget(TreeNode* root, int k) {

        if(root == NULL) return false;

        if(findTarget(root->left, k) == true) return true;

        if(s.find(k-root->val) != s.end())
            return true;
        s.insert(root->val);

        return findTarget(root->right, k);
        
    }
};




unordered_set<int> s; // stores values we've seen during in-order traversal

    bool findTarget(TreeNode* root, int k) {
        // Base case: empty node
        if (root == NULL) return false;

        // Recurse into left subtree
        if (findTarget(root->left, k)) return true;

        // Check if (k - current value) exists in set
        // This means there exists another value that sums to k with root->val
        if (s.find(k - root->val) != s.end())
            return true;

        // Otherwise, store the current node's value in the set
        s.insert(root->val);

        // Recurse into right subtree
        return findTarget(root->right, k);
    }