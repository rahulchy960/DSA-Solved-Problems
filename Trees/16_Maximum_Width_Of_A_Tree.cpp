/*  Structure of a Binary Tree

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};
 */

class Solution {
  public:
    // Function to get the maximum width of a binary tree.
    int getMaxWidth(Node* root) {
        // Your code here
        if(root == NULL) return 0;
        queue<Node*>q;
        q.push(root);
        int res = 0;
        while(!q.empty()){
            int count = q.size();
            res = max(res, count);
            for(int i=0;i<count;i++){
                Node* curr = q.front();
                q.pop();
                if(curr->left != NULL)q.push(curr->left);
                if(curr->right != NULL)q.push(curr->right);
            }
        }
        return res;
    }
};