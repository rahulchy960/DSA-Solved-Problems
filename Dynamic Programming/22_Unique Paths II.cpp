class Solution {
public:
    int helper(vector<vector<int>>& obstacleGrid, int i, int j, int m, int n){
        if(i==m-1 && j==n-1 && obstacleGrid[i][j]==0)
            return 1;
        if(i>=m || j>= n || obstacleGrid[i][j]==1)
            return 0;

        return helper(obstacleGrid, i+1,j,m,n) + helper(obstacleGrid,i,j+1,m,n);

    }

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return helper(obstacleGrid, 0, 0, obstacleGrid.size(), obstacleGrid[0].size());
    }
};

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1) return 0;
        vector<vector<int>>dp(m, vector<int>(n, 0));
        dp[0][0] = 1;
        for(int i=1;i<m;i++)
            dp[i][0] = (obstacleGrid[i][0]==0 && dp[i-1][0]==1) ? 1 : 0;
        for(int j=1;j<n;j++)
            dp[0][j] = (obstacleGrid[0][j]==0 && dp[0][j-1]==1) ? 1 : 0;

        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                if(obstacleGrid[i][j] != 1)
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                else
                    dp[i][j] = 0;
            }
        }
        

        return dp[m-1][n-1];

    }
};

/*
==================== REVISION BLOCK ====================

Problem (Unique Paths II — with Obstacles):
- Grid obstacleGrid of size m×n, where 1 = obstacle, 0 = free.
- Robot starts at (0,0), moves only Right or Down, must reach (m-1,n-1).
- Return the number of distinct valid paths.

Pattern:
- Pure recursion with branching (down/right) + obstacle/out-of-bounds guards.

Recurrence:
- Let f(i, j) = number of paths from (i, j) to (m-1, n-1).
  Base:
    • If (i, j) is exactly the destination and it's free → 1.
    • If (i, j) is outside grid OR obstacleGrid[i][j] == 1 → 0.
  Transition:
    • f(i, j) = f(i+1, j) + f(i, j+1).

Correctness (sketch):
- Each path is a sequence of Right/Down moves that never steps onto obstacles.
- Recurrence enumerates all such sequences; invalid moves contribute 0, destination contributes 1.

Complexity (of THIS naive recursion):
- Time: Exponential (≈ Θ(2^(m+n))) due to overlapping subproblems.
- Space: O(m+n) recursion depth (call stack).
  ⚠️ Will TLE for typical constraints (e.g., 100×100).

Faster alternatives (for later):
- Memoization: cache f(i,j) → Time O(m·n), Space O(m·n).
- Tabulation DP: dp[i][j] = (obstacle? 0 : dp[i-1][j] + dp[i][j-1]) → O(m·n) time, O(n) space with 1D rolling.
- Edge pre-checks: if start or end is blocked, answer = 0 (already implied by the base guards).

========================================================
*/

class Solution {
public:
    // Count paths from (i,j) to bottom-right, avoiding obstacles.
    int helper(std::vector<std::vector<int>>& obstacleGrid, int i, int j, int m, int n){
        // Reached destination and it's free → one valid path
        if (i == m-1 && j == n-1 && obstacleGrid[i][j] == 0)
            return 1;

        // Outside grid or on an obstacle → no path
        if (i >= m || j >= n || obstacleGrid[i][j] == 1)
            return 0;

        // Sum of paths by moving down and right
        return helper(obstacleGrid, i+1, j, m, n) +
               helper(obstacleGrid, i, j+1, m, n);
    }

    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        return helper(obstacleGrid, 0, 0,
                      (int)obstacleGrid.size(),
                      (int)obstacleGrid[0].size());
    }
};



/*
==================== REVISION BLOCK (Upgraded) ====================

Problem
-------
Unique Paths II (with obstacles):
- Grid obstacleGrid (m×n), where 1 = obstacle, 0 = free.
- Start at (0,0); you can move only Right or Down.
- Count the number of valid paths to (m-1, n-1).

Core Idea
---------
Dynamic Programming. Let dp[i][j] be the number of ways to reach cell (i, j) from (0,0)
without stepping on obstacles.

Meaning of dp[i][j]
-------------------
- If obstacleGrid[i][j] == 1  → cell blocked → dp[i][j] = 0.
- Otherwise                    → number of ways coming from TOP and LEFT:
    dp[i][j] = (i>0 ? dp[i-1][j] : 0) + (j>0 ? dp[i][j-1] : 0)

Base / Initialization
---------------------
- If the start is blocked (obstacleGrid[0][0] == 1) → answer is 0 immediately.
- dp[0][0] = 1 (one way to “be” at the start, if it’s free).
- First column: dp[i][0] = 1 for all i until you hit an obstacle (after that → 0s).
- First row:    dp[0][j] = 1 for all j until you hit an obstacle (after that → 0s).

Why this is correct (Invariant)
-------------------------------
At each free cell (i, j), every valid path must arrive either from (i-1, j) (moving down)
or from (i, j-1) (moving right). The subproblems dp[i-1][j] and dp[i][j-1] already count
all valid ways to get to those cells. Summing them counts *all* ways to reach (i, j).

Edge Cases / Pitfalls
---------------------
- Start blocked or end blocked → answer 0 (end blocked is handled naturally by dp).
- Ensure the first row/column propagation stops after encountering an obstacle.
- Use 64-bit if counts could overflow (typical LeetCode constraints fit in 32-bit int).

Complexity
----------
Time  : O(m·n)  (each cell computed once)
Space : O(m·n)  (can be reduced to O(n) with a 1D rolling array; see below)

Tiny Dry Run
------------
Grid:
0 0 0
0 1 0
0 0 0
dp table (1 = ways):
1 1 1
1 0 1
1 1 2   → answer = 2 (two routes around the obstacle)

1D Optimization (for later)
---------------------------
We can keep only a single row `dp[j]` (number of ways to current row’s column j):
- Initialize dp[0] = 1 if start is free, else 0.
- For each cell in row-major order:
    if obstacleGrid[i][j] == 1 → dp[j] = 0;
    else                        → dp[j] += (j>0 ? dp[j-1] : 0);
This works because:
- dp[j] before update is ways from the top (previous row),
- dp[j-1] is ways from the left (current row).

========================================================
*/

class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // If the start is blocked, no paths exist.
        if (obstacleGrid[0][0] == 1) return 0;

        // dp[i][j] = number of ways to reach (i, j) from (0,0) avoiding obstacles
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
        dp[0][0] = 1; // one way to stand at the start (since it’s free)

        // First column: can only come from above; stop propagating once an obstacle appears.
        for (int i = 1; i < m; i++)
            dp[i][0] = (obstacleGrid[i][0] == 0 && dp[i-1][0] == 1) ? 1 : 0;

        // First row: can only come from the left; stop propagating once an obstacle appears.
        for (int j = 1; j < n; j++)
            dp[0][j] = (obstacleGrid[0][j] == 0 && dp[0][j-1] == 1) ? 1 : 0;

        // Fill remaining cells: ways = from top + from left (if current cell is not an obstacle)
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0; // blocked
                } else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }
        return dp[m-1][n-1];
    }
};

