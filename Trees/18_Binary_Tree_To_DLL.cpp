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