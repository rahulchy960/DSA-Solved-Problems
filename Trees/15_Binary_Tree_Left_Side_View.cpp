/* A binary tree node

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

class Solution { //if we do a preOrder traversal of the tree, we will always going to visit the leftmost node first in that level.
  public:
    int maxLevel = 0; 
    void leftViewRec(Node* root, vector<int>&res, int level = 1){
        if(root == NULL) return;
        if(maxLevel<level){
            res.push_back(root->data);
            maxLevel = level;
        }
            
        leftViewRec(root->left, res, level+1);
        leftViewRec(root->right, res, level+1);
    }
    vector<int> leftView(Node *root) {
        // code here
        if(root == NULL) return {};
        vector<int>res;
        leftViewRec(root, res);
        return res;
    }
};