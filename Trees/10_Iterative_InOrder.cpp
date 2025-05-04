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

vector<int> inOrder(Node* root) {
    if(root==NULL)
        return {};
    vector<int>res;
    stack<Node*>s; 
    Node* curr = root;
    while(curr!=NULL || !s.empty()){
        while(curr!=NULL){
            s.push(curr);
            curr = curr->left;
        }
        Node* temp = s.top();
        s.pop();
        res.push_back(temp->key);
        curr = temp->right;
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
    vector<int>res = inOrder(root);
    for(auto x: res){
        cout<<x<<" ";
    }
    return 0;
}