class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();
        if(m==1) return triangle[0][0];

        vector<vector<int>>dp(m, vector<int>(m,0));
        int n = triangle[m-1].size();
        for(int j=0;j<n;j++)
            dp[m-1][j] = triangle[m-1][j];

        for(int i=m-2;i>=0;i--){
            n = triangle[i].size();
            for(int j=0;j<n;j++){
                dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]);
            }
        }
        return dp[0][0];
        
    }
};

/*
==================== REVISION BLOCK — Triangle (Minimum Path Sum) — LeetCode 120 ====================

Problem
-------
Given a triangle array, return the minimum path sum from top to bottom.
At each step, you may move to adjacent numbers on the row below (i -> i or i+1).

Pattern/ Idea
-------------
Bottom-up Dynamic Programming on the triangle.
Let dp[i][j] be the minimum path sum from cell (i, j) to the bottom.

Algorithm (step-by-step)
------------------------
1) Create dp with same shape (or a square m×m for simplicity).
2) Initialize the base row: dp[lastRow][j] = triangle[lastRow][j] for all j.
3) For i from second-last row up to 0:
   For each j in row i:
     dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]).
4) Answer is dp[0][0].

Correctness (sketch)
--------------------
Any minimal path from (i, j) must choose the better of the two children below:
(j) or (j+1). By computing from the bottom, both subproblems are already optimal,
so dp[i][j] is optimal by local optimal choice + induction.

Complexity
----------
Time: O(m^2) where m = number of rows (total cells ~ m(m+1)/2).  
Space: O(m^2) for the shown dp; can be reduced to O(m) using a 1D array updated in place from bottom.

Edge Cases / Pitfalls
---------------------
- Single-row triangle (answer is the only element).
- Ensure bounds for dp[i+1][j+1] are valid (triangle row lengths grow by 1 each level).
- If using 1D DP, update order must be left-to-right or right-to-left appropriately to avoid overwriting needed states.

Optimization if needed
----------------------
- Use a 1D dp initialized with the last row and update upwards:
  dp[j] = triangle[i][j] + min(dp[j], dp[j+1]) (right-to-left).
========================================================
*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int m = triangle.size();
        if (m == 1) return triangle[0][0]; // Single row case

        // dp as an m x m table (only dp[i][0..i] are used for row i)
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // Initialize base row with the triangle's last row
        int n = triangle[m - 1].size();
        for (int j = 0; j < n; j++)
            dp[m - 1][j] = triangle[m - 1][j];

        // Build from the second-last row up to the top
        for (int i = m - 2; i >= 0; i--) {
            n = triangle[i].size(); // number of elements in current row
            for (int j = 0; j < n; j++) {
                // Choose the cheaper of the two children below (j and j+1)
                dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
            }
        }
        return dp[0][0]; // Minimum path sum from top to bottom
    }
};

/*
--------------------
Space-Optimized Note
--------------------
int minimumTotal(vector<vector<int>>& tri) {
    int m = tri.size();
    vector<int> dp = tri.back();              // start from last row
    for (int i = m - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {        // row i has i+1 elements
            dp[j] = tri[i][j] + min(dp[j], dp[j+1]);
        }
    }
    return dp[0];
}
*/
