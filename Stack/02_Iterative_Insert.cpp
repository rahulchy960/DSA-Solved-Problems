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
        
        Node* temp = new Node(key);
        Node* curr = root, *parent = NULL;  // // Keep track of the parent node

        while(curr!=NULL){
            parent = curr;
            if(curr->data < key)
                curr = curr->right;
            else if(curr->data > key)
                curr = curr->left;
            else 
                return root;
            
        }
        
        if(parent == NULL) return temp;  // If the tree was empty
        
        if(parent->data < key)     // // Link the new node to the appropriate child of the parent
            parent->right = temp;
        else 
            parent->left = temp;
        
        return root;
        
    }
};