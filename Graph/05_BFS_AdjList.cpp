class Solution {
  public:
    void bfsHelper(vector<vector<int>> &adj, int s, vector<bool> &visited, vector<int> &res){
        visited[s] = true;
        queue<int>q;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            res.push_back(u);
            for(auto v : adj[u]){
                if(visited[v] == false){
                    visited[v]=true;
                    q.push(v);
                    
                }
                    
            }
        }
    }
    vector<int> bfs(vector<vector<int>> &adj) {
        // Code here
        int v = adj.size();
        vector<bool>visited(v,0);
        vector<int>res;
        for(int s=0;s<v;s++){
            if(visited[s]==false)
                bfsHelper(adj,s,visited,res);
        }
        return res;
    }
};

/*
==================== REVISION BLOCK — Graph BFS (All Components) ====================

Problem
-------
Return the Breadth-First Traversal (BFS) of an undirected/directed graph given as
adjacency list `adj`. The traversal must cover **all connected components**.

Pattern
-------
- BFS with a queue and a `visited` array.
- Restart BFS from every unvisited vertex to cover disconnected components.

Algorithm (step-by-step)
------------------------
1) Create `visited[V]` initialized to false and an empty `res` vector.
2) For each source `s` from 0..V-1:
   - If `visited[s]` is false, run BFS:
     a) Mark `visited[s]=true`, push `s` to queue.
     b) While queue not empty:
        - Pop `u`, append to `res`.
        - For each neighbor `v` in `adj[u]`:
            If not visited, mark visited and push to queue.
3) Return `res`.

Correctness (sketch)
--------------------
- BFS explores vertices in non-decreasing order of distance from the current source,
  visiting each vertex once (guarded by `visited`). Repeating from every unvisited
  source ensures all components are covered.

Complexity
---------
- Time: O(V + E)  
  Each vertex enqueued/dequeued once; each edge examined at most twice (undirected).
- Space: O(V) for `visited` + O(V) worst-case queue.

Notes / Pitfalls
----------------
- The output order depends on the given adjacency ordering.
- Some platforms (e.g., specific GFG tasks) expect BFS **starting only from node 0**.
  If so, remove the outer loop and call BFS just once from `0`.
- Assumes vertices are 0-indexed and `adj.size()` is V.

========================================================
*/

class Solution {
  public:
    // BFS from a single source `s`, appending the visited order into `res`.
    void bfsHelper(std::vector<std::vector<int>> &adj, int s,
                   std::vector<bool> &visited, std::vector<int> &res) {
        visited[s] = true;
        std::queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            res.push_back(u);

            // Push all unvisited neighbors, mark visited upon enqueue to avoid duplicates
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // BFS traversal covering all components.
    std::vector<int> bfs(std::vector<std::vector<int>> &adj) {
        int V = adj.size();
        std::vector<bool> visited(V, false);
        std::vector<int> res;

        // Start BFS from every unvisited node to cover disconnected components
        for (int s = 0; s < V; s++) {
            if (!visited[s]) {
                bfsHelper(adj, s, visited, res);
            }
        }
        return res;
    }
};
