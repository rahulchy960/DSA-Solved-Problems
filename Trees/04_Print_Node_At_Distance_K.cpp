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

void distanceAtK(Node* root, int k){
    if(root==NULL)
        return;
    if(k==0){
        cout<<root->key<<" ";
        return;
    }
    distanceAtK(root->left, k-1);
    distanceAtK(root->right,k-1);
    
}

int main(){
    Node *root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30); 
    root->left->left = new Node(40);
    root->left->right = new Node(45);
    root->right->left = new Node(50); 
    root->right->right = new Node(55);
    root->left->left->left = new Node(60); 
    distanceAtK(root, 2);
}