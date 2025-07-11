/*
struct Node
{
    int data;
    Node* left;
    Node* right;
};
*/

class Solution {
  public:
    vector<int> bottomView(Node *root) {
        // Your Code Here
        map<int,int>mp;
        queue<pair<Node*,int>>q;
        q.push({root,0});
        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                auto p = q.front();
                Node* curr = p.first;
                int hd = p.second;
                mp[hd] = curr->data;
                q.pop();
                if(curr->left != NULL) q.push({curr->left, hd-1});
                if(curr->right != NULL) q.push({curr->right, hd+1});
            }
        
        }
        vector<int>res;
        for(auto x : mp)
            res.push_back(x.second);
        return res;
        
    }
};