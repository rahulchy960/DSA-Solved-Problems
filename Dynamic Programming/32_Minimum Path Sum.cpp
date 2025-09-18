class Solution {
public:
    int res = INT_MAX;
    void dfs(vector<vector<int>>& grid, int i=0, int j=0, int sum = 0){
        if(i<0 || j<0 || i>=grid.size() || j>=grid.size())
            return;
        if(i==grid.size()-1 && j==grid[0].size()-1){
            sum += grid[i][j];
            res = min(res, sum);
            return;
        }
        sum += grid[i][j];
        dfs(grid, i+1, j, sum);
        dfs(grid, i, j+1, sum);
        sum -= grid[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        dfs(grid);
        return res;
    }
};

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>>dp(m, vector<int>(n,0));
        dp[0][0] = grid[0][0];
        for(int i=1;i<m;i++)
            dp[i][0] = dp[i-1][0] + grid[i][0];
        for(int j=1;j<n;j++)
            dp[0][j] = dp[0][j-1] + grid[0][j];

        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m-1][n-1];
    }
};

/*
==================== REVISION BLOCK — Minimum Path Sum (LeetCode 64) ====================

Problem
-------
Given a m x n grid filled with non-negative numbers, find a path from top-left to bottom-right 
that minimizes the sum of all numbers along the path. You can only move down or right at any point.

Pattern/ Idea
-------------
Dynamic Programming on grid.
- dp[i][j] = minimum path sum to reach cell (i, j).
- Transition: dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]).

Algorithm (step-by-step)
------------------------
1) Initialize dp[m][n].
2) Base case:
   - dp[0][0] = grid[0][0].
   - Fill first column: dp[i][0] = dp[i-1][0] + grid[i][0].
   - Fill first row:    dp[0][j] = dp[0][j-1] + grid[0][j].
3) For i=1..m-1 and j=1..n-1:
   - dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]).
4) Return dp[m-1][n-1].

Correctness (sketch)
--------------------
Each cell (i, j) can only be reached from top (i-1, j) or left (i, j-1).
Thus, the optimal path to (i, j) is its value plus the min of the optimal paths to its two predecessors.
Fills DP row-by-row ensures all subproblems are solved before being used.

Complexity
----------
Time: O(m * n) — fill the entire dp table once.
Space: O(m * n) — dp array, can be optimized to O(n) using rolling row.

Edge Cases / Pitfalls
---------------------
- Single row or single column grid (works due to initialization).
- Large grids may need space optimization.
- Ensure non-negative assumption holds (else algorithm still works, but interpretation changes).

Optimization if needed
----------------------
- Space reduce dp to O(n) by keeping only the current and previous row.
- Alternatively, modify grid in-place to store dp values if allowed.
========================================================
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j] stores min path sum to reach (i,j)
        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = grid[0][0]; // start at top-left

        // Fill first column (can only come from above)
        for (int i = 1; i < m; i++)
            dp[i][0] = dp[i - 1][0] + grid[i][0];

        // Fill first row (can only come from left)
        for (int j = 1; j < n; j++)
            dp[0][j] = dp[0][j - 1] + grid[0][j];

        // Fill remaining cells
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[m - 1][n - 1]; // minimum path sum to bottom-right
    }
};
