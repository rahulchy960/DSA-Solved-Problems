
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
int count = 0;
    void kSmall(TreeNode* root, int k, int &res){
        if(root == NULL) return;
        kSmall(root->left, k, res);
        count++;
        if(count == k){
            res = root->val;
            return;
        }
        kSmall(root->right, k, res);
    }
    int kthSmallest(TreeNode* root, int k) {
        int res = -1;
        kSmall(root,k,res);
        return res;
    }
};



int count = 0;  // 🔢 Global counter to track how many nodes have been visited

// 🔁 In-order traversal to find the kth smallest element
void kSmall(TreeNode* root, int k, int &res) {
    if(root == NULL) return;

    kSmall(root->left, k, res);  // Traverse left subtree (smaller values)

    count++;  // 🧮 Increment count when visiting a node
    if(count == k) {
        res = root->val;  // 🎯 Found kth smallest element
        return;
    }

    kSmall(root->right, k, res);  // Traverse right subtree (larger values)
}

// 🚪 Entry point
int kthSmallest(TreeNode* root, int k) {
    int res = -1;  // Will hold the result
    kSmall(root, k, res);  // Run in-order traversal
    return res;
}
