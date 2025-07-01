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
    // Function to return a list of nodes visible from the top view
    // from left to right in Binary Tree.
    vector<int> topView(Node *root) {
        // code here
        map<int,int>mp;
        queue<pair<Node*,int>>q;
        q.push({root,0});
        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                auto p = q.front();
                Node* curr = p.first;
                int hd = p.second;
                if(mp.find(hd) == mp.end())
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





vector<int> topView(Node *root) {
    // Map to store the first node's value at each horizontal distance (hd)
    map<int, int> mp;

    // Queue for BFS traversal: stores {node, horizontal distance}
    queue<pair<Node*, int>> q;
    q.push({root, 0});  // Root has horizontal distance = 0

    // 🔁 Level-order traversal to cover all levels top-down
    while (!q.empty()) {
        auto [curr, hd] = q.front();
        q.pop();

        // Insert the node only if this hd hasn't been recorded before
        // Ensures only the topmost node at each hd is stored
        if (mp.find(hd) == mp.end())
            mp[hd] = curr->data;

        // 👈 Go left: hd - 1
        if (curr->left)
            q.push({curr->left, hd - 1});

        // 👉 Go right: hd + 1
        if (curr->right)
            q.push({curr->right, hd + 1});
    }

    // 📦 Extract top view values from the map in order (sorted by hd)
    vector<int> res;
    for (auto& [hd, val] : mp)
        res.push_back(val);

    return res;
}
