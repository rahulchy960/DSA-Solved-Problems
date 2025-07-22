class Solution {
public:

    int eD(string word1, string word2, int m, int n){
        if(m==0) return n;
        if(n==0) return m;
        if(word1[m-1] == word2[n-1])
            return eD(word1, word2, m-1,n-1);
        return 1 + min(eD(word1, word2, m-1, n), min(eD(word1, word2,m,n-1), eD(word1, word2,m-1, n-1)));
    }
    int minDistance(string word1, string word2) {
        return eD(word1, word2, word1.length(), word2.length());
    }
};

// Algorithm: Edit Distance (Recursive Approach)
// --------------------------------------------
// Problem:
//   - Given two strings word1 and word2, return the minimum number of operations
//     required to convert word1 to word2.
//   - Allowed operations: Insert, Delete, Replace (each costs 1)
//
// Approach:
//   - Use recursion to compare characters from the end of both strings.
//   - At each step:
//       - If characters match: no operation needed → move diagonally (m-1, n-1)
//       - If characters differ: try all 3 operations and choose the minimum:
//           1. Insert (m, n-1)
//           2. Delete (m-1, n)
//           3. Replace (m-1, n-1)
//   - Base Cases:
//       - If word1 is empty (m == 0): insert all remaining characters of word2
//       - If word2 is empty (n == 0): delete all remaining characters of word1
//
// Time Complexity: O(3^min(m, n))
//   - Exponential due to overlapping subproblems and branching factor of 3
//
// Space Complexity: O(min(m, n)) for recursion stack depth
//   - No extra DP table used

class Solution {
public:
/*
    int eD(string word1, string word2, int m, int n){
        if(m==0) return n;
        if(n==0) return m;
        if(word1[m-1] == word2[n-1])
            return eD(word1, word2, m-1,n-1);
        return 1 + min(eD(word1, word2, m-1, n), min(eD(word1, word2,m,n-1), eD(word1, word2,m-1, n-1)));
    }
*/
    int minDistance(string word1, string word2) {
        // return eD(word1, word2, word1.length(), word2.length());
        int m = word1.length();
        int n = word2.length();
        vector<vector<int>>dp(m+1, vector<int>(n+1));
        for(int i=0;i<=m;i++)
            dp[i][0] = i;
        for(int j=0;j<=n;j++)
            dp[0][j] = j;

        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = 1 + min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]));
            }
        }
        return dp[m][n];

    }
};


// Approach (Tabulation):
//   1. Create a 2D DP table `dp[m+1][n+1]` where:
//         - dp[i][j] represents the minimum number of operations to convert
//           word1[0..i-1] to word2[0..j-1]
//   2. Initialize base cases:
//         - dp[i][0] = i → converting i characters to empty string (delete all)
//         - dp[0][j] = j → converting empty string to j characters (insert all)
//   3. Fill the table using the following rules:
//         - If word1[i-1] == word2[j-1]:
//             dp[i][j] = dp[i-1][j-1] (no cost)
//         - Else:
//             dp[i][j] = 1 + min(
//                            dp[i-1][j],   // delete
//                            dp[i][j-1],   // insert
//                            dp[i-1][j-1]  // replace
//                        )
//
// Time Complexity: O(m × n)
//   - where m = length of word1, n = length of word2
//
// Space Complexity: O(m × n)
//   - for the 2D DP table

