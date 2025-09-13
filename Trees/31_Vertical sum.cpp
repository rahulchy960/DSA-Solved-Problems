class Solution {
  public:
    vector<int> verticalSum(Node *root) {
        // add code here.
        map<int,int>mp;
        queue<pair<Node*,int>>q;
        q.push({root,0});
        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                auto p = q.front();
                Node* curr = p.first;
                int hd = p.second;
                mp[hd] += curr->data;
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
==================== REVISION BLOCK — Vertical Sum of a Binary Tree ====================

Problem
-------
Given the root of a binary tree, compute the **vertical sums**:
nodes with the same horizontal distance (HD) from the root are in the same vertical line.
Return sums ordered from leftmost (smallest HD) to rightmost (largest HD).
(Conventions: root has HD = 0; left child HD-1; right child HD+1.)

Pattern
-------
Level-order (BFS) or DFS while carrying HD, accumulate sums in a map keyed by HD.
Use an ordered map to emit results left→right.

Algorithm (BFS, ordered map)
----------------------------
1) If root is null → return {}.
2) Push (root, 0) into a queue.
3) While queue not empty:
   - Pop (node, hd); add node->data to sum[hd].
   - If node->left  → push (left,  hd-1)
   - If node->right → push (right, hd+1)
4) Iterate `sum` (ordered by hd) and collect values into the answer vector.

Correctness (sketch)
--------------------
Every node contributes exactly once to the sum of its vertical line (its HD).
Ordering by HD yields left-to-right vertical sums.

Complexity
---------
Let n = number of nodes, D = number of distinct HDs.
- Time: O(n log D) using std::map (log factor per insertion); D ≤ n ⇒ O(n log n) worst-case.
- Space: O(n) for queue + map.

Edge Cases
----------
- Empty tree → [].
- Single node → [root->data].
- Skewed trees (all left or all right) → a single-element per vertical.
- Very large values → consider using `long long` to store sums.

Pitfalls
--------
- Don’t forget to handle `root == nullptr`.
- No need to group by BFS levels—HD alone determines verticals.
- Using `unordered_map` speeds updates but you must track min/max HD to output in order.

========================================================
*/

class Solution {
public:
    std::vector<int> verticalSum(Node *root) {
        if (!root) return {};

        std::map<int, long long> sum;                       // HD -> sum (use long long if sums can grow)
        std::queue<std::pair<Node*, int>> q;                // node, HD
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front(); q.pop();
            sum[hd] += node->data;
            if (node->left)  q.push({node->left,  hd - 1});
            if (node->right) q.push({node->right, hd + 1});
        }

        std::vector<int> res;
        res.reserve(sum.size());
        for (auto &kv : sum) res.push_back(static_cast<int>(kv.second));
        return res;
    }
};

/* ==================== Optional: O(n) average with unordered_map ====================
Idea:
- Use unordered_map<int,long long> for O(1) average updates.
- Track minHD and maxHD during traversal.
- Build output vector of size (maxHD - minHD + 1) and fill by offset.

Time: O(n) average (hash), Space: O(n)
*/

std::vector<int> verticalSum_fast(Node *root) {
    if (!root) return {};
    std::unordered_map<int, long long> sum;
    std::queue<std::pair<Node*, int>> q;
    q.push({root, 0});
    int minHD = 0, maxHD = 0;

    while (!q.empty()) {
        auto [node, hd] = q.front(); q.pop();
        sum[hd] += node->data;
        minHD = std::min(minHD, hd);
        maxHD = std::max(maxHD, hd);
        if (node->left)  q.push({node->left,  hd - 1});
        if (node->right) q.push({node->right, hd + 1});
    }

    std::vector<int> res(maxHD - minHD + 1);
    for (int hd = minHD; hd <= maxHD; ++hd) {
        res[hd - minHD] = static_cast<int>(sum[hd]); // sum[hd] defaults to 0 if absent
    }
    return res;
}
