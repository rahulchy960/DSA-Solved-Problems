class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {

        unordered_map<TreeNode*, TreeNode*> parent;
        TreeNode* target = NULL;
        queue<TreeNode*>q;
        q.push(root);

        while(!q.empty()){
            int n = q.size();
            for(int i=0;i<n;i++){
                TreeNode* curr = q.front();
                q.pop();
                if(curr->val == start) target = curr;
                if(curr->left != NULL) {
                    parent[curr->left] = curr;
                    q.push(curr->left);
                }
                if(curr->right != NULL) {
                    parent[curr->right] = curr;
                    q.push(curr->right);
                }
            }
        }

        unordered_map<TreeNode*, bool>visited;
        int time = -1;
        q.push(target);
        while(!q.empty()){
            int n = q.size();
            
            for(int i=0;i<n;i++){
                TreeNode* curr = q.front();
                q.pop();
                visited[curr] = true;
                if(curr->left != NULL && !visited[curr->left])
                    q.push(curr->left);
                 
                if(curr->right != NULL && !visited[curr->right])
                    q.push(curr->right);
                 
                if(parent[curr] != NULL && !visited[parent[curr]])
                    q.push(parent[curr]);
            }
            time++;
        }

        return time;

    }
};


/*
==================== REVISION BLOCK — Amount of Time for Binary Tree to Be Infected ====================

Problem
-------
A virus starts at the node with value `start` in a binary tree. Each minute it spreads
to adjacent nodes (parent/left/right). Return the minutes needed to infect the entire tree.

Pattern
-------
Two BFS passes:
1) **Parent mapping BFS**: record each node’s parent and locate the `start` node.
2) **Infection BFS** from `start` over the implicit **undirected** graph (left, right, parent).

Algorithm (step-by-step)
------------------------
1) If root == null → return 0.
2) BFS from root:
   • For each node, if node->val == start, remember it as `target`.
   • Record parent for left/right children in `parent` map.
3) If `target` not found → return 0 (or problem-defined behavior).
4) BFS from `target`:
   • Use a queue and a `visited` set.
   • Push `target` and mark visited.
   • While queue not empty (each loop = 1 minute):
       - For all nodes of current minute, try to push their 0–3 neighbors:
         left, right, and parent (if exist and not visited).
       - Increment `minutes`.
5) Return `minutes`.

Correctness (sketch)
--------------------
The infection front expands in discrete layers of graph distance from `target`.
BFS layers correspond to minutes. Visiting every node exactly once yields the
time equal to the **maximum distance** from `target` to any node.

Complexity
---------
Let n = number of nodes.
- Time: O(n) (each node enqueued/processed at most once in each phase).
- Space: O(n) for the parent map, visited set, and queues.

Notes / Pitfalls
----------------
- Use a **visited set and mark on push** to avoid multi-enqueue of the same node from
  different neighbors in the undirected graph.
- Guard null root; handle case when `start` value isn’t present.
- Using node pointers as keys in unordered_map/set is fine (stable identity).
- Counting minutes: initialize `minutes = -1` and increment per level, or use a
  sentinel/size-based level loop as below.
*/

class Solution {
public:
    int amountOfTime(TreeNode* root, int start) {
        if (!root) return 0;

        // 1) Build parent map and find target node
        std::unordered_map<TreeNode*, TreeNode*> parent;
        TreeNode* target = nullptr;

        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();
            if (cur->val == start) target = cur;
            if (cur->left)  { parent[cur->left]  = cur; q.push(cur->left); }
            if (cur->right) { parent[cur->right] = cur; q.push(cur->right); }
        }

        if (!target) return 0; // start not found; define as 0 minutes

        // 2) BFS infection from target (undirected edges: left, right, parent)
        std::unordered_set<TreeNode*> visited;
        std::queue<TreeNode*> inf;
        visited.insert(target);
        inf.push(target);

        int minutes = -1;
        while (!inf.empty()) {
            int sz = (int)inf.size();
            while (sz--) {
                TreeNode* u = inf.front(); inf.pop();

                if (u->left && !visited.count(u->left)) {
                    visited.insert(u->left);
                    inf.push(u->left);
                }
                if (u->right && !visited.count(u->right)) {
                    visited.insert(u->right);
                    inf.push(u->right);
                }
                auto it = parent.find(u);
                if (it != parent.end() && !visited.count(it->second)) {
                    visited.insert(it->second);
                    inf.push(it->second);
                }
            }
            ++minutes; // one minute per BFS layer
        }
        return minutes;
    }
};

