#include<iostream>
using namespace std;

struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    Node(int k){
        key = k;
        left = right = NULL;
    }
};

int getMax(Node *root){
    if(root==NULL)
        return INT_MIN;
    int x = getMax(root->left);
    int y = getMax(root->right);
    return max(root->key, max(x, y));
}

int main(){
    // Contrust the Tree
    //      1
    //     /  \
    //    2    3
    //   / \    
    //  4   5
    
    Node *root = new Node(1);
    root->left = new Node(21);
    root->right = new Node(30);
    root->left->left = new Node(84);
    root->left->right = new Node(51); 

    cout << "Maximum in the binary tree is = " << getMax(root);
    return 0;
}