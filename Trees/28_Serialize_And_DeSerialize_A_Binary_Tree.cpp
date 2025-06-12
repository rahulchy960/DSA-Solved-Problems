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




// 🔧 Global constant to represent NULL nodes in serialized array
const int null = -1;

// 🔁 Helper function for serialization (Preorder traversal)
void serializeHelper(Node *root, vector<int>& arr) {
    if(root == NULL) {
        arr.push_back(null);  // Store placeholder for NULL
        return;
    }

    arr.push_back(root->data);          // Add current node value
    serializeHelper(root->left, arr);   // Serialize left subtree
    serializeHelper(root->right, arr);  // Serialize right subtree
}

// ✅ Main serialization function
vector<int> serialize(Node *root) {
    vector<int> arr;
    serializeHelper(root, arr);
    return arr;  // Return the preorder list with nulls
}

// 🔁 Global index for tracking current element in deserialization
int index = 0;

// ✅ Deserialization function: Reconstructs tree from preorder list
Node* deSerialize(vector<int> &arr) {
    if(index == arr.size()) return NULL;

    int val = arr[index];
    index++;

    if(val == null) return NULL;  // Null placeholder → return NULL

    Node* root = new Node(val);             // Rebuild node
    root->left = deSerialize(arr);          // Rebuild left subtree
    root->right = deSerialize(arr);         // Rebuild right subtree

    return root;  // Return reconstructed subtree
}
