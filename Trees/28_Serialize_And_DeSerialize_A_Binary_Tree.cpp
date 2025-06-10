/* A binary tree node has data, pointer to left child
   and a pointer to right child
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

class Solution {
  public:
    // Function to serialize a tree and return a list containing nodes of tree.
    const int null = -1;
    
    void serializeHelper(Node *root, vector<int>&arr){
        if(root == NULL){
            arr.push_back(null);
            return;
        }
        arr.push_back(root->data);
        serializeHelper(root->left, arr);
        serializeHelper(root->right, arr);
    }
    
    vector<int> serialize(Node *root) {
        // Your code here
        vector<int>arr;
        serializeHelper(root, arr);
        return arr;
    }

    // Function to deserialize a list and construct the tree.
    int index = 0;
    Node *deSerialize(vector<int> &arr) {
        
        // Your code here
        if(index == arr.size()) return NULL;
        
        int val = arr[index];
        index++;
        if(val == null) return NULL;
        
        Node* root = new Node(val);
        root->left = deSerialize(arr);
        root->right = deSerialize(arr);
        
        return root;
        
    }
};