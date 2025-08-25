class Solution {
  public:
    void dfsRec(vector<vector<int>>& adj, int u, vector<bool>&visited, vector<int>&res){
        visited[u] = true;
        res.push_back(u);
        for(auto v: adj[u]){
            if(visited[v] == false)
                dfsRec(adj, v, visited, res);
        }
    }
    vector<int> dfs(vector<vector<int>>& adj) {
        // Code here
        int v = adj.size();
        vector<bool>visited(v, 0);
        vector<int>res;
        for(int s=0;s<v;s++){
            if(visited[s]==false)
                dfsRec(adj, s, visited, res);
        }
        return res;
        
    }
};

/*
==================== REVISION BLOCK — Graph DFS (All Components) ====================

Problem
-------
Given a graph as an adjacency list `adj` (0..V-1), return a **depth-first traversal**
that covers **all connected components**.

Pattern
-------
- Recursive DFS with a `visited` array.
- Start DFS from every unvisited vertex to ensure disconnected components are included.

Algorithm (clear steps)
-----------------------
1) Create `visited[V] = {false}` and an empty `res`.
2) For each vertex s in [0..V-1]:
   - If not visited[s], call dfsRec(s):
     • Mark visited[u] = true, push u to res.
     • Recurse on each neighbor v of u that is not visited.
3) Return `res`.

Correctness (invariant)
-----------------------
- When dfsRec(u) begins, all vertices already in `res` are reachable from some earlier start.
- dfsRec(u) visits **exactly** the vertices reachable from u that were not visited yet,
  marking them before recursing to avoid cycles and duplicates.
- The outer loop guarantees every component is explored.

Complexity
---------
- Time: O(V + E). Each vertex is processed once; each edge is examined at most twice (undirected) / once (directed).
- Space: O(V) for `visited` + O(H) recursion stack (H ≤ V in worst case).
  ⚠ If V can be very large / recursion depth is a concern, use an explicit stack (iterative DFS).

Notes / Pitfalls
----------------
- The order in `res` depends on the adjacency list ordering.
- Some platforms want DFS **starting only from node 0**; remove the outer loop if required.
- Works for directed or undirected graphs; for undirected, `adj` should list both directions.

========================================================
*/

class Solution {
  public:
    // DFS from a single source `u`, appending visit order into `res`.
    void dfsRec(std::vector<std::vector<int>>& adj, int u,
                std::vector<bool>& visited, std::vector<int>& res) {
        visited[u] = true;      // mark upon entry to prevent revisits
        res.push_back(u);       // record preorder

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsRec(adj, v, visited, res);
            }
        }
    }

    // DFS traversal covering all components.
    std::vector<int> dfs(std::vector<std::vector<int>>& adj) {
        int V = adj.size();
        std::vector<bool> visited(V, false);
        std::vector<int> res;

        for (int s = 0; s < V; ++s) {
            if (!visited[s]) {
                dfsRec(adj, s, visited, res);
            }
        }
        return res;
    }
};

/* -------- Optional: Iterative DFS to avoid recursion depth --------
std::vector<int> dfs_iterative(std::vector<std::vector<int>>& adj) {
    int V = adj.size();
    std::vector<bool> visited(V,false);
    std::vector<int> res;

    for (int s = 0; s < V; ++s) if (!visited[s]) {
        std::stack<int> st;
        st.push(s);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (visited[u]) continue;
            visited[u] = true;
            res.push_back(u);
            // Push neighbors; to mimic recursive order, iterate in reverse if desired.
            for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                if (!visited[*it]) st.push(*it);
            }
        }
    }
    return res;
}
*/
 