class Solution {
public:
    vector<vector<int>>dir = {{-1,0}, {0,-1},{1,0},{0,1}}; 
    int dfs( vector<vector<int>>& grid, int i, int j, vector<vector<bool>>&vis){
        if(i<0 || j<0 || i>=grid.size() || j>= grid[0].size() || grid[i][j]==0)
            return 1;
        if(vis[i][j] == true) return 0;

        vis[i][j] = true;

        int peri = 0;
        for(int d=0;d<4;d++){
            int row = i + dir[d][0];
            int col = j + dir[d][1];
            peri += dfs(grid, row, col, vis);
        }
        return peri;
    }
    int islandPerimeter(vector<vector<int>>& grid) {
        int i=0, j=0;
        vector<vector<bool>>vis(grid.size(), vector<bool>(grid[0].size()));
        for(i=0;i<grid.size();i++){
            bool flag = false;
            for(j=0;j<grid[0].size();j++){
                if(grid[i][j] == 1){
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
        
        return dfs(grid, i, j, vis);
    }
};


/*
==================== REVISION BLOCK — Island Perimeter (DFS flood-fill) ====================

Problem
-------
Given a binary grid (1 = land, 0 = water), return the perimeter of the island.
LeetCode 463 guarantees exactly one island with no lakes (holes).
(If your data may have no land, answer should be 0.)

Core Idea (DFS perimeter contribution)
--------------------------------------
From a land cell (i,j), look at its 4 neighbors:
- If a neighbor is **out of bounds** or **water (0)** → that side contributes **+1** to perimeter.
- If the neighbor is **land (1)** → recurse to it (once), and add its contributions.

We mark cells as visited so each land cell is processed once.

Why base cases return 1/0?
--------------------------
- Out-of-bounds / water: that side is an **exposed edge** → contributes **1**.
- Already visited land: its edges were already counted via another path → contributes **0**.

Algorithm
---------
1) Find any land cell (first 1). If none exists, return 0.
2) DFS from that cell; for each step:
   - If out of bounds or water → return 1
   - If visited → return 0
   - Mark visited; sum recursive results over 4 directions
3) Return the accumulated perimeter.

Complexity
----------
Time: O(m·n) — each land cell visited once (constant 4-neighbor work).
Space: O(m·n) for visited + recursion stack O(#land) in worst case.

Pitfalls fixed
--------------
- Original code would return 1 when there is **no land** (because dfs was called out-of-bounds).
  Now we explicitly check and return 0 if no land is found.

========================================================
*/

class Solution {
public:
    std::vector<std::vector<int>> dir = {{-1,0}, {0,-1}, {1,0}, {0,1}}; 

    int dfs(std::vector<std::vector<int>>& grid, int i, int j,
            std::vector<std::vector<bool>>& vis) {
        // If outside or on water, this border contributes 1 to perimeter
        if (i < 0 || j < 0 || i >= (int)grid.size() || j >= (int)grid[0].size() || grid[i][j] == 0)
            return 1;

        // If we've already counted this cell, no additional perimeter from this path
        if (vis[i][j]) return 0;

        vis[i][j] = true;

        int peri = 0;
        for (int d = 0; d < 4; d++) {
            int ni = i + dir[d][0];
            int nj = j + dir[d][1];
            peri += dfs(grid, ni, nj, vis);
        }
        return peri;
    }

    int islandPerimeter(std::vector<std::vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // Find a starting land cell
        int si = -1, sj = -1;
        for (int i = 0; i < m && si == -1; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) { si = i; sj = j; break; }
            }
        }
        if (si == -1) return 0; // no land

        std::vector<std::vector<bool>> vis(m, std::vector<bool>(n, false));
        return dfs(grid, si, sj, vis);
    }
};
