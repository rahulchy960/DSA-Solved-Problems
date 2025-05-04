#include<bits/stdc++.h>
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

vector<int> preorder(Node* root) {
    if(root==NULL)
        return {};
    vector<int>res;
    stack<Node*>s; 
    Node* curr = root;
    while(curr!=NULL || !s.empty()){
        while(curr!=NULL){
            res.push_back(curr->key);
            if(curr->right != NULL){
                s.push(curr->right);
            }
            curr = curr->left;
        }
        if(!s.empty()){
            curr = s.top();
            s.pop();
        }
    }
    return res;

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
    vector<int>res = preorder(root);
    for(auto x: res){
        cout<<x<<" ";
    }
    return 0;
}