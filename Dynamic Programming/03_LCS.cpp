#include<bits/stdc++.h>
using namespace std;

int LCS(string s1, string s2, int m, int n){
    if(n==0 || m==0) return 0;
    if(s1[m-1] == s2[n-1]) 
        return 1 + LCS(s1,s2,m-1,n-1);
    return max(LCS(s1,s2,m-1,n), LCS(s1,s2,m,n-1));
}



    /*
    Algorithm (Recursive):
    - Base Case: If either string is empty, LCS is 0
    - If last characters match: 
        → Include it in LCS and recurse on remaining strings
    - Else:
        → LCS is the max of removing one char from either string

    Time Complexity:
    - Exponential: O(2^min(m, n)) due to overlapping subproblems

    Space Complexity:
    - O(m + n) recursion stack depth
    */



/*  Memorization based solution

int LCS(string &s1, string &s2,int m, int n, vector<vector<int>>&memo){
    if(memo[m][n]==-1){
        if(m==0 || n==0)
            return 0;
        else if(s1[m-1] == s2[n-1])
            memo[m][n] = 1 + LCS(s1,s2,m-1,n-1,memo);
        else
            memo[m][n] = max(LCS(s1,s2,m-1,n,memo), LCS(s1,s2,m,n-1,memo));
    }
    return memo[m][n]; 
}

*/


// LCS tabulation based solution
int LCS(string s1, string s2){
    int m = s1.length();
    int n = s2.length();
    int dp[m+1][n+1];
    for(int i=0;i<=m;i++)dp[i][0] = 0;
    for(int j=0;j<=n;j++)dp[0][j] = 0;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}



// Algorithm: Longest Common Subsequence (Tabulation - Bottom-Up DP)
// ------------------------------------------------------------------
// Problem:
//   - Given two strings s1 and s2, find the length of their longest common subsequence.
//   - A subsequence is a sequence that appears in the same relative order,
//     but not necessarily contiguous.
//
// Approach:
//   - Use dynamic programming with a 2D table `dp[m+1][n+1]` where:
//       - dp[i][j] = length of LCS of s1[0...i-1] and s2[0...j-1]
//   - Initialize the first row and first column with 0s (base case: empty subsequence).
//   - Transition:
//       - If characters match: dp[i][j] = 1 + dp[i-1][j-1]
//       - If not match: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
//
// Time Complexity: O(m × n)
//   - Where m = length of s1, n = length of s2
//
// Space Complexity: O(m × n)
//   - 2D DP table of size (m+1) × (n+1)


