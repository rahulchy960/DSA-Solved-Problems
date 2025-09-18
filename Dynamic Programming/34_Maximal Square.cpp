class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>>dp(m, vector<int>(n, 0));
        int mx = 0;
        for(int i=0;i<m;i++){
            dp[i][0] = matrix[i][0]-'0';
            mx = max(mx, dp[i][0]);
        }
            
        for(int j=1;j<n;j++){
            dp[0][j] = matrix[0][j]-'0';
            mx = max(mx, dp[0][j]);
        }
            
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                if(matrix[i][j] == '1'){
                    dp[i][j] = 1 + min(dp[i][j-1], min(dp[i-1][j-1], dp[i-1][j]));
                    mx = max(mx, dp[i][j]);
                }
            }
            
        }
        return mx*mx;
    }
};

/*
==================== REVISION BLOCK — Maximal Square (LeetCode 221) ====================

Problem
-------
Given a 2D binary matrix filled with '0' and '1', find the area of the largest square
containing only 1's.

Pattern/ Idea
-------------
Dynamic Programming on a grid.
- dp[i][j] = side length of the largest square ending at (i, j).
- If matrix[i][j] == '1', then dp[i][j] = 1 + min(top, left, top-left).
- Otherwise, dp[i][j] = 0.

Algorithm (step-by-step)
------------------------
1) Initialize dp[m][n] with 0.
2) Base cases:
   - First row and first column: dp[i][0] = matrix[i][0], dp[0][j] = matrix[0][j].
   - Track max side length (mx).
3) For each cell (i, j) starting from (1,1):
   - If matrix[i][j] == '1':
       dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]).
       Update mx = max(mx, dp[i][j]).
4) Return mx * mx (area of the largest square).

Correctness (sketch)
--------------------
A square of size k can end at (i,j) iff:
- (i-1,j), (i,j-1), and (i-1,j-1) can each support at least a square of size k-1,
and matrix[i][j] == '1'. This recurrence ensures the largest possible square is built.

Complexity
----------
Time: O(m * n) — each cell processed once.
Space: O(m * n) — dp table; can be optimized to O(n) using rolling arrays.

Edge Cases / Pitfalls
---------------------
- All zeros → answer = 0.
- Single '1' in matrix → answer = 1.
- Ensure conversion from char to int (subtract '0').

Optimization if needed
----------------------
Use a 1D dp array (rolling update) to reduce space to O(n).
========================================================
*/

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> dp(m, vector<int>(n, 0));
        int mx = 0;

        // Initialize first column
        for (int i = 0; i < m; i++) {
            dp[i][0] = matrix[i][0] - '0';
            mx = max(mx, dp[i][0]);
        }

        // Initialize first row
        for (int j = 1; j < n; j++) {
            dp[0][j] = matrix[0][j] - '0';
            mx = max(mx, dp[0][j]);
        }

        // Fill rest of dp
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == '1') {
                    dp[i][j] = 1 + min(dp[i][j-1],
                                   min(dp[i-1][j-1], dp[i-1][j]));
                    mx = max(mx, dp[i][j]);
                }
            }
        }

        return mx * mx; // area of the largest square
    }
};
