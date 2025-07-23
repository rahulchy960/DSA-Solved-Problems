class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>>dp;
        for(int i=0;i<numRows;i++){
            vector<int>row(i+1,1);
            for(int j=1;j<i;j++){
                row[j] = dp[i-1][j-1] + dp[i-1][j]; 
            }
            dp.push_back(row);
        }
        return dp;
    }
};


// Algorithm: Generate Pascal's Triangle (DP - Bottom-Up Construction)
// --------------------------------------------------------------------
// Problem:
//   - Given an integer `numRows`, return the first `numRows` of Pascal's Triangle.
//   - Each row starts and ends with 1.
//   - Each element at position `j` in row `i` is the sum of:
//       → element at position `j-1` and `j` in previous row (i-1).
//
// Approach:
//   - Initialize an empty 2D vector `dp` to hold the triangle.
//   - For each row `i` from 0 to numRows - 1:
//       - Create a new row of size (i+1) filled with 1.
//       - For each index `j` from 1 to i-1:
//           - row[j] = dp[i-1][j-1] + dp[i-1][j]  (Pascal's property)
//       - Push the row into the result vector.
//
// Time Complexity: O(numRows^2)
//   - Each row has up to `i` elements, summing to a triangular number: (n*(n+1))/2
//
// Space Complexity: O(numRows^2)
//   - Required to store all rows
