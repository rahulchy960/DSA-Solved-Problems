

class Solution { //if we do a preOrder traversal of the tree, we will always going to visit the leftmost node first in that level.
  public:
    int maxLevel = 0; 
    void leftViewRec(Node* root, vector<int>&res, int level = 1){
        if(root == NULL) return;
        if(maxLevel<level){
            res.push_back(root->data);
            maxLevel = level;
        }
            
        leftViewRec(root->left, res, level+1);
        leftViewRec(root->right, res, level+1);
    }
    vector<int> leftView(Node *root) {
        // code here
        if(root == NULL) return {};
        vector<int>res;
        leftViewRec(root, res);
        return res;
    }
};


/*
==================== REVISION BLOCK — Left View of Binary Tree ====================

Problem
-------
Return the **left view** of a binary tree: for each depth, output the first node visible
when looking from the left (i.e., the leftmost node on that level).

Pattern
-------
Two classic ways:
1) **DFS (preorder: root → left → right)** while tracking the deepest level seen so far.
   The first time we *enter* a level, the current node is the leftmost for that level.
2) **BFS (level-order)** and take the first node in the queue for each level.

Algorithm (DFS, root→left→right; 1-based levels)
-------------------------------------------------
We maintain a vector `res` and an integer `maxLevel` (deepest level already recorded).

leftViewDFS(u, level):
1) If u == nullptr → return.
2) If level > maxLevel:
   • push u->data into res
   • set maxLevel = level
3) Recurse left:  leftViewDFS(u->left,  level+1)
4) Recurse right: leftViewDFS(u->right, level+1)

Call with leftViewDFS(root, 1) and return `res`.

Correctness (sketch)
--------------------
Preorder visits a level’s leftmost node **before** any other node at that level.
We record exactly the first node encountered at each level, hence the left view.

Complexity
---------
- Time: O(n) — every node visited once.
- Space: O(h) recursion stack (h = tree height; worst O(n), avg O(log n)); plus O(L) output.

Edge Cases / Pitfalls
---------------------
- Guard root == nullptr.
- If you store `maxLevel` as a member, **reset it** for each new call; or avoid globals.
- DFS must be **root→left→right**; flipping left/right will produce a right view instead.
- For very deep trees, use BFS to avoid recursion depth issues.

========================================================
*/

// Re-entrant DFS solution (no stale state across calls)
class Solution {
public:
    std::vector<int> leftView(Node *root) {
        std::vector<int> res;
        int maxLevel = 0; // deepest level recorded
        std::function<void(Node*, int)> dfs = [&](Node* u, int lvl) {
            if (!u) return;
            if (lvl > maxLevel) {
                res.push_back(u->data);
                maxLevel = lvl;
            }
            dfs(u->left,  lvl + 1);
            dfs(u->right, lvl + 1);
        };
        dfs(root, 1);
        return res;
    }
};

/* ==================== Optional: BFS (level-order) variant ====================
- For each level, the first node popped is the leftmost.
*/
std::vector<int> leftView_BFS(Node* root) {
    if (!root) return {};
    std::queue<Node*> q; q.push(root);
    std::vector<int> res;
    while (!q.empty()) {
        int sz = (int)q.size();
        for (int i = 0; i < sz; ++i) {
            Node* u = q.front(); q.pop();
            if (i == 0) res.push_back(u->data); // first node at this level
            if (u->left)  q.push(u->left);
            if (u->right) q.push(u->right);
        }
    }
    return res;
}
