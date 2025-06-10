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
    int amountOfTime(TreeNode* root, int start) {

        unordered_map<TreeNode*, TreeNode*> parent;
        TreeNode* target = NULL;
        queue<TreeNode*>q;
        q.push(root);

        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                TreeNode* curr = q.front();
                q.pop();
                if(curr->val == start) target = curr;
                if(curr->left != NULL) {
                    parent[curr->left] = curr;
                    q.push(curr->left);
                }
                if(curr->right != NULL) {
                    parent[curr->right] = curr;
                    q.push(curr->right);
                }
            }
        }

        unordered_map<TreeNode*, bool>visited;
        int time = -1;
        q.push(target);
        while(!q.empty()){
            int n = q.size();
            
            for(int i=0;i<n;i++){
                TreeNode* curr = q.front();
                q.pop();
                visited[curr] = true;
                if(curr->left != NULL && !visited[curr->left])
                    q.push(curr->left);
                 
                if(curr->right != NULL && !visited[curr->right])
                    q.push(curr->right);
                 
                if(parent[curr] != NULL && !visited[parent[curr]])
                    q.push(parent[curr]);
            }
            time++;
        }

        return time;

    }
};