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

void printPreorder(Node* root){
    if(root==NULL)
        return;
    cout<<root->key<<" ";
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(Node *root){
    if(root==NULL)
        return;
    printPostorder(root->left);
    printPostorder(root->right);
    cout<<root->key<<" ";
}

void printInorder(Node* root){
    if(root==NULL)
        return;
    printInorder(root->left);
    cout<<root->key<<" ";
    printInorder(root->right);
}

int main(){
    // Contrust the Tree
    //      1
    //     /  \
    //    2    3
    //   / \    
    //  4   5
    
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5); 

    cout << "Preorder traversal of binary tree is \n";
    printPreorder(root);

    cout << "\nInorder traversal of binary tree is \n";
    printInorder(root); 

    cout << "\nPostorder traversal of binary tree is \n";
    printPostorder(root);

    return 0;
}