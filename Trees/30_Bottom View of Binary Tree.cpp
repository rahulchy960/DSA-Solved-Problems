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

/*
==================== REVISION BLOCK — Bottom View of Binary Tree ====================

Problem
-------
Given the root of a binary tree, return its **bottom view**: for each vertical line
(horizontal distance HD from root, where root has HD=0, left HD-1, right HD+1),
pick the node that is **lowest (maximum depth)** and list results from leftmost HD
to rightmost HD.

Pattern
-------
BFS with **horizontal distance (HD)**:
- Traverse level by level carrying each node’s HD.
- For each HD, keep the *latest* node seen (BFS ensures deeper levels overwrite shallower ones).

Algorithm (step-by-step)
------------------------
1) If root == nullptr → return {}.
2) Use a queue of (node, hd). Push (root, 0).
3) Maintain an ordered map `mp<hd, value>`.
4) While queue not empty:
   a) Pop (node, hd).
   b) Set `mp[hd] = node->data`  // overwrite so deeper nodes win.
   c) If node->left  → push (left,  hd-1)
      If node->right → push (right, hd+1)
5) Iterate `mp` in ascending hd and collect values into the answer vector.

Correctness (sketch)
--------------------
At any HD, BFS visits nodes from top to bottom; the **last** value written to `mp[hd]`
corresponds to the deepest node in that vertical line. Ordered map iteration yields
left-to-right output.

Complexity
---------
Let n be the number of nodes and D the number of distinct HDs (D ≤ n).
- Time: O(n log D) (map insert/overwrite per visited node).
- Space: O(n) for queue + map.

Notes / Pitfalls
----------------
- Guard `root == nullptr`.
- A per-level loop (`int n = q.size()`) is **not required**; simple while-loop works,
  but keeping it is harmless.
- If you want **O(n)** average time, use `unordered_map<int,int>` and track min/max HDs,
  then emit results in a vector using an offset.

========================================================
*/

class Solution {
public:
    std::vector<int> bottomView(Node *root) {
        if (!root) return {};

        std::map<int, int> mp;                       // hd -> bottom-most value
        std::queue<std::pair<Node*, int>> q;         // node, hd
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front(); q.pop();
            mp[hd] = node->data;                     // overwrite: deeper nodes win

            if (node->left)  q.push({node->left,  hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        std::vector<int> res;
        res.reserve(mp.size());
        for (auto &kv : mp) res.push_back(kv.second);
        return res;
    }
};

/* ==================== Optional: O(n) average with unordered_map ====================

Idea
----
Use unordered_map for O(1) average updates and track the min/max HD observed to output
in order without a tree map.

Time: O(n) average; Space: O(n)

std::vector<int> bottomView_fast(Node *root) {
    if (!root) return {};
    std::unordered_map<int,int> valAtHd;
    std::queue<std::pair<Node*,int>> q;
    q.push({root,0});
    int minHD = 0, maxHD = 0;

    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        valAtHd[hd] = node->data;             // overwrite bottom-most
        minHD = std::min(minHD, hd);
        maxHD = std::max(maxHD, hd);
        if (node->left)  q.push({node->left,  hd-1});
        if (node->right) q.push({node->right, hd+1});
    }

    std::vector<int> res(maxHD - minHD + 1);
    for (int hd = minHD; hd <= maxHD; ++hd)
        res[hd - minHD] = valAtHd[hd];        // missing keys default to 0 if absent in map; here all hds present
    return res;
}
*/
