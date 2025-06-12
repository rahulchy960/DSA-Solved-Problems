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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>res;
        if(root == NULL) return res;
        deque<TreeNode*> dq;
        dq.push_back(root);
        bool reverse = false;
        while(!dq.empty()){
            int n = dq.size();
            vector<int>temp;
            for(int i=0;i<n;i++){
                
                if(reverse){
                    TreeNode* curr = dq.back();
                    dq.pop_back();
                    temp.push_back(curr->val);
                    if(curr->right != NULL) dq.push_front(curr->right);
                    if(curr->left != NULL) dq.push_front(curr->left);  
                }
                else{
                    TreeNode* curr = dq.front();
                    dq.pop_front();
                    temp.push_back(curr->val);
                    if(curr->left != NULL) dq.push_back(curr->left);
                    if(curr->right != NULL) dq.push_back(curr->right);
                }
            }
            reverse = !reverse;
            res.push_back(temp);
        }
        return res;

    }
};






vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;  // 🔲 Final result: list of levels
    if(root == NULL) return res;

    deque<TreeNode*> dq;  // 🟦 Deque for flexible popping from both ends
    dq.push_back(root);
    bool reverse = false;  // 🔁 Flag to switch direction at each level

    while(!dq.empty()) {
        int n = dq.size();         // Number of nodes at current level
        vector<int> temp;          // ⏳ To store current level values

        for(int i = 0; i < n; i++) {
            if(reverse) {
                // ↩ Right-to-left traversal
                TreeNode* curr = dq.back();  // Take from back
                dq.pop_back();
                temp.push_back(curr->val);

                // Add children in reverse order for next level
                if(curr->right != NULL) dq.push_front(curr->right);
                if(curr->left != NULL) dq.push_front(curr->left);
            }
            else {
                // ➡ Left-to-right traversal
                TreeNode* curr = dq.front();  // Take from front
                dq.pop_front();
                temp.push_back(curr->val);

                // Add children in natural order for next level
                if(curr->left != NULL) dq.push_back(curr->left);
                if(curr->right != NULL) dq.push_back(curr->right);
            }
        }

        reverse = !reverse;         // Toggle direction for next level
        res.push_back(temp);        // Save current level
    }

    return res;
}
