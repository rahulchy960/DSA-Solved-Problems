int floor(Node* root, int key) {
    // Your code goes here
    int res = -1;
    while(root!=NULL){
        if(root->data == key)
            return root->data;
        else if(root->data > key)
            root = root->left;
        else{
            res = root->data;
            root = root->right;
        }
    }
    return res;
}