
void bfs(vector<vector<bool>> &mat, int s, vector<bool> &visited){
    queue<int>q;
    q.push(s);
    visited[s] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout<<u<<" ";
        for(int v=0; v<mat[u].size();v++){
            if(mat[u][v]==1 && visited[v] == false){
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void bfsMatrix(vector<vector<bool>> &mat){
    int V = mat.size();
    vector<bool>visited(V,0);
    for(int s=0;s<V;s++){
        if(visited[s]==false)
            bfs(mat, s, visited);
    }
}

/*
==================== REVISION BLOCK — BFS on Adjacency Matrix (All Components) ====================

Problem
-------
Given a graph as an adjacency **matrix** `mat` (mat[u][v] is true/1 iff there is an edge u→v),
perform a Breadth-First Search traversal that **covers all connected components**, printing
the visit order.

Pattern
-------
- Standard BFS with a queue and a `visited` array.
- Since we use an **adjacency matrix**, scanning neighbors of u is O(V) (check every v).

Algorithm (step-by-step)
------------------------
bfs(mat, s, visited):
1) Mark s visited, push s into a queue.
2) While queue not empty:
   a) Pop u, print u.
   b) For every vertex v = 0..V-1:
        If mat[u][v] is true AND v not visited:
           mark visited[v] = true, push v.

bfsMatrix(mat):
1) Initialize visited[V] = false.
2) For every vertex s in 0..V-1:
     If not visited[s], call bfs(mat, s, visited) to cover that component.

Correctness (sketch)
--------------------
- Each vertex is enqueued at most once (we mark visited on enqueue).
- BFS explores vertices in non-decreasing distance from the current source.
- Restarting from every unvisited vertex ensures all components are traversed.

Complexity
----------
Let V = number of vertices, E = number of edges.
- Using an **adjacency matrix**: neighbor scan for each pop is O(V), and we pop up to V times
  → **Time = O(V^2)** (regardless of E).
- Space = O(V) for `visited` + O(V) worst-case queue.

Notes / Pitfalls
----------------
- Since `mat` is `vector<vector<bool>>`, you can test `if (mat[u][v])` instead of `== 1`.
- Output order depends on vertex numbering and matrix row order.
- For undirected graphs, `mat` is symmetric; for directed graphs, it need not be.
- If the platform wants BFS **only from node 0**, drop the outer loop and call `bfs(mat, 0, visited)`.

========================================================
*/

void bfs(vector<vector<bool>> &mat, int s, vector<bool> &visited){
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while(!q.empty()){
        int u = q.front(); q.pop();
        cout << u << " ";

        // Scan all possible neighbors v (matrix row u)
        for(int v = 0; v < (int)mat[u].size(); v++){
            if (mat[u][v] && !visited[v]) {   // mat[u][v] == true means edge u->v exists
                visited[v] = true;            // mark on enqueue to avoid duplicates
                q.push(v);
            }
        }
    }
}

void bfsMatrix(vector<vector<bool>> &mat){
    int V = (int)mat.size();
    vector<bool> visited(V, false);

    // Run BFS from every unvisited vertex to cover all components
    for(int s = 0; s < V; s++){
        if(!visited[s])
            bfs(mat, s, visited);
    }
    // (Optional) cout << '\n';
}
