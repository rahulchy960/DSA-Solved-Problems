/* struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};  */

int findCeil(Node* root, int input) {
    // Your code here
    int res = -1;
    while(root!=NULL){
        if(root->data == input)
            return root->data;
        else if(root->data < input)
            root = root->right;
        else{
            res = root->data;
            root = root->left;
        }
    }
    return res;
}