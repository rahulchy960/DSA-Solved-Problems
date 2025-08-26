class Solution {
public:
    vector<vector<int>>dir = {{-1,0}, {0,-1},{1,0},{0,1}};
    void dfs(vector<vector<char>>& grid, int r, int c){
        if(r<0 || c<0 || r>=grid.size() || c>=grid[0].size() || grid[r][c] == '0')
            return;
        grid[r][c] = '0';
        for(int i=0;i<4;i++){
            dfs(grid, r + dir[i][0], c + dir[i][1]);
        }

    }
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for(int r=0;r<m;r++){
            for(int c=0;c<n;c++){
                if(grid[r][c]=='1'){
                    dfs(grid, r, c);
                    count++;
                }
            }
        }
        return count;
    }
};

/*
==================== REVISION BLOCK — Number of Islands (DFS flood-fill) ====================

Problem
-------
Given an m×n grid of '1' (land) and '0' (water), count the number of **islands**.
An island is a maximal group of horizontally/vertically connected '1's.

Pattern
-------
- Classic **DFS flood-fill**: when you see a '1', start a DFS that "sinks" (marks) the
  entire connected component to avoid recounting it. Each time you start a new DFS, you
  found a new island.

Algorithm (step-by-step)
------------------------
1) Initialize count = 0.
2) For each cell (r, c):
   - If grid[r][c] == '1':
       a) Run DFS(r, c) that:
          • returns immediately if out of bounds or on '0'
          • marks current cell as '0' (visited/sunk)
          • recurses to 4 neighbors (up, left, down, right)
       b) After DFS returns, increment count (finished one island).
3) Return count.

Correctness (sketch)
--------------------
- Each DFS fully explores exactly one connected component of land and marks it as '0'.
- No cell is counted twice, since marked cells are never revisited.
- Number of DFS launches equals the number of connected components ⇒ islands.

Complexity
---------
- Time: O(m·n). Every cell is visited at most once and each edge (adjacency) checked O(1) times.
- Space: O(m·n) in the worst case due to recursion stack (e.g., one huge island).  
  Average cases are smaller, but if stack depth is a concern, use an explicit stack/BFS.

Notes / Pitfalls
----------------
- This implementation **modifies the grid in place** by turning visited '1's to '0'.
  If mutation isn’t allowed, maintain a visited[m][n] array instead.
- 4-direction connectivity only; diagonals don’t connect islands.
- Optional micro-opt: store `m = grid.size()`, `n = grid[0].size()` once and pass them to DFS.

========================================================
*/

class Solution {
public:
    // 4-neighborhood: up, left, down, right
    std::vector<std::vector<int>> dir = {{-1,0}, {0,-1}, {1,0}, {0,1}};

    // DFS "sinks" a connected component of '1's starting at (r,c)
    void dfs(std::vector<std::vector<char>>& grid, int r, int c){
        // stop if out of bounds or on water/already visited
        if (r < 0 || c < 0 || r >= (int)grid.size() || c >= (int)grid[0].size() || grid[r][c] == '0')
            return;

        grid[r][c] = '0'; // mark visited by converting to water

        // explore 4 neighbors
        for (int k = 0; k < 4; k++){
            dfs(grid, r + dir[k][0], c + dir[k][1]);
        }
    }

    int numIslands(std::vector<std::vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int count = 0;
        for (int r = 0; r < m; r++){
            for (int c = 0; c < n; c++){
                if (grid[r][c] == '1'){
                    dfs(grid, r, c); // sink this island
                    count++;         // finished one island
                }
            }
        }
        return count;
    }
};
