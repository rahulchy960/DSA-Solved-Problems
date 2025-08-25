void dfs(vector<vector<bool>> &mat, int u, vector<bool> &visited){
    visited[u] = true;
    cout<<u<<" ";
    for(int v=0;v<mat[u].size();v++){
        if(mat[u][v]==1 && visited[v]==false){
            dfs(mat, v, visited);
        }
   }
}

void dfsMatrix(vector<vector<bool>> &mat){
    int V = mat.size();
    vector<bool>visited(V,0);
    for(int s=0;s<V;s++){
        if(visited[s] == false)
            dfs(mat, s, visited);
    }
}


/*
==================== REVISION BLOCK — DFS on Adjacency Matrix (All Components) ====================

Problem
-------
Given a graph as an adjacency **matrix** mat (mat[u][v] is true/1 iff edge u→v exists),
perform a Depth-First Search that **visits every vertex** (i.e., covers all components)
and prints the visitation order.

Core Idea
---------
- Standard recursive DFS with a `visited` array to avoid revisiting nodes.
- Since the graph may be disconnected, start DFS from every unvisited vertex.

Algorithm (step-by-step)
------------------------
dfs(mat, u, visited):
1) Mark u as visited, output u.
2) For each vertex v = 0..V-1:
   - If mat[u][v] is 1/true and v is not visited, recurse into v.

dfsMatrix(mat):
1) Initialize visited[V] = false.
2) For each s in 0..V-1:
   - If not visited[s], call dfs(mat, s, visited).

Correctness (why it works)
--------------------------
- Each vertex is visited exactly once due to the `visited` guard.
- Starting from every unvisited vertex ensures every connected component is explored.

Complexity
----------
Let V be the number of vertices, E the number of edges.
- Using an **adjacency matrix**, checking neighbors of a node costs O(V).
- DFS touches each vertex once → overall **Time = O(V^2)** with a matrix (independent of E).
- Space = O(V) for `visited` plus recursion stack depth O(V) in the worst case.

Pitfalls / Notes
----------------
- `vector<vector<bool>>` stores bits; comparisons like `mat[u][v] == 1` work, but `if (mat[u][v])`
  is more idiomatic.
- Output order depends on matrix row order; different orders are still valid DFS traversals.
- If recursion depth is a concern (very large V), switch to an explicit stack (iterative DFS).
- Some platforms expect starting DFS from node 0 only—remove the outer loop in that case.

========================================================
*/

void dfs(std::vector<std::vector<bool>> &mat, int u, std::vector<bool> &visited){
    visited[u] = true;                 // mark upon entry to prevent re-visits
    std::cout << u << " ";             // preorder output

    // Explore all possible neighbors v of u
    for (int v = 0; v < (int)mat[u].size(); v++){
        if (mat[u][v] == 1 && visited[v] == false){
            dfs(mat, v, visited);
        }
    }
}

void dfsMatrix(std::vector<std::vector<bool>> &mat){
    int V = (int)mat.size();
    std::vector<bool> visited(V, false);

    // Cover all components: start DFS from every unvisited vertex
    for (int s = 0; s < V; s++){
        if (visited[s] == false)
            dfs(mat, s, visited);
    }
    // (Optional) std::cout << '\n';
}




