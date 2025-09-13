
class Solution {
  public:
  
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

/*
==================== REVISION BLOCK — Top View of Binary Tree ====================

Problem
-------
Given the root of a binary tree, return its **top view**: for each vertical line
(horizontal distance, HD) from the root, pick the node that is *highest/closest to root*
(smallest depth). Output from leftmost HD to rightmost HD. Convention: root has HD = 0,
left child HD-1, right child HD+1.

Pattern
-------
**BFS with Horizontal Distance**:
Traverse level-by-level carrying each node’s HD. For each HD, record the **first**
node seen (it’s the topmost due to BFS order).

Algorithm (step-by-step, BFS)
-----------------------------
1) If root == nullptr → return {}.
2) Use a queue of (node, hd). Push (root, 0).
3) Maintain an ordered map `mp<hd, value>`.
4) While queue not empty:
   a) Pop (node, hd).
   b) If `mp` has no entry for `hd`, set `mp[hd] = node->data` (first seen at this HD).
   c) Push children with updated HD: (left, hd-1), (right, hd+1).
5) Iterate `mp` in ascending `hd` and collect the values into the result vector.

Correctness (sketch)
--------------------
BFS explores nodes in non-decreasing depth. The **first** node encountered for an HD
is necessarily the topmost for that vertical; later nodes at the same HD are deeper
and should not overwrite.

Complexity
---------
Let n be the number of nodes and D the number of distinct HDs (D ≤ n).
- Time: O(n log D) due to ordered map operations (log D per first-visit; overwrites are skipped).
- Space: O(n) for queue + map.

Notes / Pitfalls
----------------
- Guard `root == nullptr`.
- No need for a per-level loop; a simple queue loop suffices (ordering comes from BFS).
- For **O(n)** average time, use `unordered_map<int,int>` and track min/max HDs to output in order.
*/

class Solution {
public:
    std::vector<int> topView(Node *root) {
        if (!root) return {};

        std::map<int, int> mp;                          // hd -> first (topmost) value
        std::queue<std::pair<Node*, int>> q;            // node, hd
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front(); q.pop();

            if (mp.find(hd) == mp.end()) {              // first time we see this hd
                mp[hd] = node->data;
            }
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
Use unordered_map for O(1) average inserts. Still BFS, still record only the **first**
node per HD. Track minHD and maxHD to output in order.

Time: O(n) average; Space: O(n)
*/
std::vector<int> topView_fast(Node *root) {
    if (!root) return {};
    std::unordered_map<int,int> firstAtHd;
    std::queue<std::pair<Node*,int>> q;
    q.push({root,0});
    int minHD = 0, maxHD = 0;

    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        if (!firstAtHd.count(hd)) firstAtHd[hd] = node->data; // first/topmost
        minHD = std::min(minHD, hd);
        maxHD = std::max(maxHD, hd);
        if (node->left)  q.push({node->left,  hd-1});
        if (node->right) q.push({node->right, hd+1});
    }

    std::vector<int> res;
    res.reserve(maxHD - minHD + 1);
    for (int hd = minHD; hd <= maxHD; ++hd)
        res.push_back(firstAtHd[hd]);                   // each hd seen at least once
    return res;
}

/* ==================== Optional: DFS variant (explicit depth tracking) ====================

Idea
----
DFS with (hd, depth). For each hd, keep the (minDepth, value); update only if depth is smaller.

Time: O(n log D) with std::map (or O(n) avg with unordered_map), Space: O(n) recursion/structures.
*/
void dfsTop(Node* node, int hd, int depth, std::map<int, std::pair<int,int>>& best) {
    if (!node) return;
    auto it = best.find(hd);
    if (it == best.end() || depth < it->second.first) {
        best[hd] = {depth, node->data};
    }
    dfsTop(node->left,  hd - 1, depth + 1, best);
    dfsTop(node->right, hd + 1, depth + 1, best);
}

std::vector<int> topView_dfs(Node* root) {
    if (!root) return {};
    std::map<int, std::pair<int,int>> best; // hd -> {minDepth, value}
    dfsTop(root, 0, 0, best);
    std::vector<int> res;
    res.reserve(best.size());
    for (auto &kv : best) res.push_back(kv.second.second);
    return res;
}
