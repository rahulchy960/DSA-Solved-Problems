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
        stack<TreeNode*>s;
        s.push(root);
        while(!s.empty()){
            TreeNode *curr = s.top();
            s.pop();
            if(curr->right != NULL) s.push(curr->right);
            if(curr->left != NULL) s.push(curr->left);

            if(!s.empty()){
                curr->right = s.top();
            }  
            curr->left = NULL;
        }
        
    }
};



void flatten(TreeNode* root) {
    if(root == NULL) return;  // 🛑 Edge case: Empty tree

    stack<TreeNode*> s;       // 🧱 Stack to simulate preorder traversal
    s.push(root);

    while(!s.empty()) {
        TreeNode* curr = s.top();  // 🧭 Current node
        s.pop();

        // ✅ Push right child first so that left is processed first (preorder: root → left → right)
        if(curr->right != NULL)
            s.push(curr->right);

        // ✅ Then push left child
        if(curr->left != NULL)
            s.push(curr->left);

        // 🔗 Connect current node's right pointer to the next node in preorder
        if(!s.empty())
            curr->right = s.top();

        // ❌ Make sure left is always NULL as we're forming a right-skewed "linked list"
        curr->left = NULL;
    }
}
