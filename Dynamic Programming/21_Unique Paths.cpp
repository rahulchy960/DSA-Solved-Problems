class Solution {
public:
    int helper(int i, int j, int m, int n){
        if(i==m-1 && j == n-1)
            return 1;
        if(i>m-1 || j > n-1)
            return 0;
        return helper(i+1, j, m, n) + helper(i, j+1, m ,n);

    }
    int uniquePaths(int m, int n) {  
        return helper(0, 0, m, n);
    }
};

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>>dp(m, vector<int>(n,0));
        for(int i=0;i<m;i++) dp[i][0] = 1;
        for(int j=0;j<n;j++) dp[0][j] = 1;
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
       
    }
};

/*
==================== REVISION BLOCK ====================

Problem (Unique Paths):
- Robot at (0,0) in an m×n grid moves only Right or Down. Count paths to (m-1,n-1).

Pattern:
- 2D Dynamic Programming.

State:
- dp[i][j] = number of ways to reach cell (i, j).

Transitions:
- First row/column: only 1 way each (all rights or all downs).
- For others: dp[i][j] = dp[i-1][j] + dp[i][j-1].

Algorithm:
1) Initialize dp[m][n] with zeros.
2) Set dp[i][0] = 1 for all i, dp[0][j] = 1 for all j.
3) For i=1..m-1, j=1..n-1: dp[i][j] = dp[i-1][j] + dp[i][j-1].
4) Return dp[m-1][n-1].

Complexity:
- Time: O(m·n)
- Space: O(m·n)  (can optimize to O(n) using a single row)

Notes:
- Values can grow large; if m,n can be big, consider using 64-bit (long long),
  or compute combinatorially C(m+n-2, m-1) with 64-bit / big integer as needed.

========================================================
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

        // Base: first column and first row have exactly one way to reach
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int j = 0; j < n; j++) dp[0][j] = 1;

        // Fill the rest: ways to (i,j) = from top + from left
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Unique Paths):
- A robot starts at (0,0) in an m×n grid and can only move **right** or **down**.
- Count how many distinct paths reach (m-1, n-1).

Pattern:
- Pure recursion on choices (go down or go right).

Recurrence:
- Let f(i, j) = number of paths from cell (i, j) to (m-1, n-1).
  Base:
    • If (i == m-1 && j == n-1) → 1 path (already at destination).
    • If (i ≥ m or j ≥ n)      → 0 paths (out of grid).
  Transition:
    • f(i, j) = f(i+1, j) + f(i, j+1)

Algorithm (this code):
1) Recurse from (0,0).
2) When you step outside the grid, return 0.
3) When you hit the target, return 1.
4) Otherwise sum paths from moving down and right.

Correctness (sketch):
- Every valid path is a unique sequence of “down/right” decisions; recursion enumerates all such sequences, counting exactly those that land on the target.

Complexity (of THIS naive recursion):
- Time: Exponential — Θ(2^(m+n)) in the worst case due to heavy overlapping subproblems.
- Space: O(m+n) recursion depth (call stack).

Pitfalls / Notes:
- This solution TLEs for moderate m,n (e.g., ≥ 20–30). Use memoization/tabulation for O(m·n).
- A combinatorial closed-form exists: C(m+n-2, m-1) (or C(m+n-2, n-1)).
- Watch for overflow with large grids; prefer 64-bit (long long) for combinatorics/DP.

========================================================
*/

class Solution {
public:
    // Count paths from (i, j) to (m-1, n-1) by trying both moves.
    int helper(int i, int j, int m, int n){
        if (i == m-1 && j == n-1) return 1;  // reached destination
        if (i >  m-1 || j >  n-1)  return 0; // out of bounds -> no path

        // Sum of paths by moving down and right
        return helper(i+1, j, m, n) + helper(i, j+1, m, n);
    }

    int uniquePaths(int m, int n) {
        return helper(0, 0, m, n);
    }
};


