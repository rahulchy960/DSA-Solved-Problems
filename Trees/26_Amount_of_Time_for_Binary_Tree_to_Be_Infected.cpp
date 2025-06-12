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


int amountOfTime(TreeNode* root, int start) {
    // ✅ Step 1: Create a parent mapping for all nodes using BFS
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* target = NULL;  // Will hold the node from where the infection starts
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        int n = q.size();
        for(int i = 0; i < n; i++){
            TreeNode* curr = q.front();
            q.pop();

            // 🎯 Identify the node where infection starts
            if(curr->val == start) target = curr;

            // 🔄 Track parent pointers for all child nodes
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

    // ✅ Step 2: BFS from the 'target' node to simulate infection spread
    unordered_map<TreeNode*, bool> visited;
    int time = -1;  // Starts from -1 because after pushing target, we increment time once
    q.push(target);

    while(!q.empty()){
        int n = q.size();

        for(int i = 0; i < n; i++){
            TreeNode* curr = q.front();
            q.pop();
            visited[curr] = true;

            // Spread to left child if not visited
            if(curr->left != NULL && !visited[curr->left])
                q.push(curr->left);

            // Spread to right child if not visited
            if(curr->right != NULL && !visited[curr->right])
                q.push(curr->right);

            // Spread to parent if not visited
            if(parent[curr] != NULL && !visited[parent[curr]])
                q.push(parent[curr]);
        }

        // Each level = 1 unit of time for infection to spread
        time++;
    }

    return time;
}
