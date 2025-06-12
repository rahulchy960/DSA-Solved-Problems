/* Structure for tree and linked list

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

// This function should return head to the DLL
class Solution {
  public:
    Node* head = NULL;
    Node *prev = NULL;
    void toDLL(Node* root){
        
        if(root == NULL) return;
        
        toDLL(root->left);
        
        if(prev == NULL)
            head = root;
        else{
            root->left = prev;
            prev->right = root;
        }
        
        prev = root;
        
        toDLL(root->right);
        
    }
    Node* bToDLL(Node* root) {
        // code here
        toDLL(root);
        
        return head;
    }
};


class Solution {
  public:
    Node* head = NULL;  // 🧠 Will point to head of DLL
    Node* prev = NULL;  // ⬅️ Tracks previously visited node (in-order predecessor)

    // 🔄 Recursive in-order traversal to convert to DLL
    void toDLL(Node* root) {
        if(root == NULL) return;

        toDLL(root->left);  // Traverse left subtree

        // 🎯 Process current node
        if(prev == NULL)
            head = root;  // First node becomes head of DLL
        else {
            root->left = prev;   // Connect current ← prev
            prev->right = root;  // Connect prev → current
        }

        prev = root;  // Move prev forward

        toDLL(root->right);  // Traverse right subtree
    }

    // 🧾 Main function to initiate conversion
    Node* bToDLL(Node* root) {
        toDLL(root);   // Start in-order traversal
        return head;   // Return head of the resulting DLL
    }
};
