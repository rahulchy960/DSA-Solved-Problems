class Solution {
public:
    void bfs(vector<vector<int>>& isConnected, int s, vector<bool>&visited){
        int n = isConnected.size();
        visited[s] = true;
        queue<int>q;
        q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v=0;v<n;v++){
                if(visited[v]==false && isConnected[u][v]==1){
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int V = isConnected.size();
        vector<bool>visited(V,0);
        int count=0;
        for(int s=0;s<V;s++){
            if(visited[s] == false){
                bfs(isConnected, s, visited);
                count++;
            }
        }
        return count;
    }
};

/*
==================== REVISION BLOCK — Number of Provinces (BFS on adjacency matrix) ====================

Problem
-------
Given an adjacency matrix isConnected (n×n) where isConnected[i][j] == 1 iff city i and j are directly connected,
return the number of **provinces** (connected components) in the undirected graph.

Pattern
-------
- Graph traversal with **BFS** (could use DFS/Union-Find too).
- Since the graph may be disconnected, start a BFS from every **unvisited** node.

Algorithm (step-by-step)
------------------------
1) Let n = isConnected.size(). Make visited[n] = false.
2) For each node s in 0..n-1:
   - If not visited[s], run BFS(s):
     * visited[s] = true; push s to queue.
     * While queue not empty:
         - pop u
         - for v in 0..n-1:
             if isConnected[u][v] == 1 and !visited[v]:
                 visited[v] = true; push v
   - After BFS finishes, we have explored an entire component → provinces++.
3) Return provinces.

Correctness (sketch)
--------------------
- BFS visits exactly the nodes reachable from s; marking on enqueue prevents duplicates.
- Repeating from every unvisited node ensures each connected component is counted once.

Complexity
---------
- Time: O(n^2). For each popped node we scan across its row (0..n-1).
- Space: O(n) for visited + O(n) worst-case queue.

Notes / Pitfalls
----------------
- Matrix is symmetric with 1s on the diagonal (city connected to itself); code handles this naturally.
- Marking visited **when enqueuing** avoids pushing the same node multiple times.

========================================================
*/

class Solution {
public:
    // BFS starting from node s over an adjacency matrix; marks all nodes in s's component
    void bfs(std::vector<std::vector<int>>& isConnected, int s, std::vector<bool>& visited){
        int n = isConnected.size();
        visited[s] = true;
        std::queue<int> q;
        q.push(s);

        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v = 0; v < n; v++){
                // if there is an edge u-v and v is not visited yet, visit it
                if(!visited[v] && isConnected[u][v] == 1){
                    visited[v] = true;     // mark on enqueue to avoid duplicates
                    q.push(v);
                }
            }
        }
    }

    int findCircleNum(std::vector<std::vector<int>>& isConnected) {
        int n = isConnected.size();
        std::vector<bool> visited(n, false);
        int provinces = 0;

        for(int s = 0; s < n; s++){
            if(!visited[s]){
                bfs(isConnected, s, visited);
                provinces++;               // finished one connected component
            }
        }
        return provinces;
    }
};

/*
--- Alternatives for revision ---
1) DFS (recursive/iterative): same O(n^2) time on matrix, O(n) space.
2) Union-Find (DSU): near O(n^2 α(n)) by unioning (i,j) where isConnected[i][j] == 1; count roots at end.
*/
