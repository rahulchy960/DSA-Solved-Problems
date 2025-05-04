#include <bits/stdc++.h>
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

int maxDepth(Node* root){
    if(root==NULL)
        return 0;
    int x = maxDepth(root->left);
    int y = maxDepth(root->right);
    return 1 + max(x, y);
}

int main(){
    Node *root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30); 
    root->left->left = new Node(40);
    root->left->right = new Node(50); 

    cout<<"Max Depth: "<<maxDepth(root);
}