// C++ program to find LCA using Arrays to Store 
// Paths of Nodes from Root
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// Function to find path from root to given node.
bool findPath(Node* root, vector<Node*>& path, int k) {
  
    // base case
    if (root == nullptr)
        return false;

    // Store current node value in the path.
    path.push_back(root);

    // If node value is equal to k, or
    // if node exist in left subtree or
    // if node exist in right subtree return true
    if (root->data == k || 
            findPath(root->left, path, k) ||
                 findPath(root->right, path, k))
        return true;

    // else remove root from path and return false
    path.pop_back();
    return false;
}

// Returns LCA of two nodes.
Node* lca(Node* root, int n1, int n2) {
  
    // to store paths to n1 and n2 from the root
    vector<Node*> path1, path2;

    // Find paths from root to n1 and 
    // root to n2. If either
    // n1 or n2 is not present, return nullptr
    if (!findPath(root, path1, n1) || 
        !findPath(root, path2, n2))
        return nullptr;

    // Compare the paths to get the first
    // different value
    for (int i=0; i<path1.size()-1 && i<path2.size()-1; i++) {
        if (path1[i+1] != path2[i+1])
           	return path1[i];
    }
  	
  	// if both the datas are same, return last node
    return NULL;
}

int main() {
  
  	// construct the binary tree
  	//			   1
    //           /   \
    //          2     3
    //         / \   / \
    //        4  5  6   7 
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Node* ans = lca(root, 4, 5);
  	if(ans == nullptr)
      	cout<<"No common ancestor found";
	else
      	cout<< ans->data;
    return 0;
}