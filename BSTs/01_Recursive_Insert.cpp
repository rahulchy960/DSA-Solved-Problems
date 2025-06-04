
/*
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution {
  public:
    Node* insert(Node* root, int key) {

        // Your code goes here
        if(root==NULL)
            return new Node(key);
        else if(root->data < key)
            root->right = insert(root->right, key);
        else if(root->data > key)
            root->left = insert(root->left, key);
         
        return root;  // if linked with if-else chain, it only return a new node if the current subtree is NULL.
    }
};