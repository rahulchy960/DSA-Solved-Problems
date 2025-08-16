#include<bits/stdc++.h>
using namespace std;

void printLCS(string s1, string s2){
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
    
    int i=m, j=n;
    string str = "";
    while(i>0 && j>0){
        if(s1[i-1] == s2[j-1]){
            str+=s1[i-1];
            i--;
            j--;
        }
        else{
            if(dp[i-1][j] > dp[i][j-1])
                i--;
            else
                j--;
        }
    }
    reverse(str.begin(), str.end());
    cout<<"LCS : "<<str<<endl;

}


int main(){

    string s1 = "abc";
    string s2 = "acd";

    printLCS(s1, s2);

}


/*
==================== REVISION BLOCK ====================

Problem (Print LCS — Longest Common Subsequence string):
- Given strings s1 (length m) and s2 (length n), print one actual LCS string.

Pattern:
- Classic DP (tabulation) + path reconstruction.

State:
- dp[i][j] = length of LCS of s1[0..i-1] and s2[0..j-1].

Transitions:
- If s1[i-1] == s2[j-1]  → dp[i][j] = 1 + dp[i-1][j-1]  (take matching char)
- Else                   → dp[i][j] = max(dp[i-1][j], dp[i][j-1])  (skip one)

Reconstruction (build LCS string from dp):
- Start at (i=m, j=n):
  * If chars match → append s1[i-1], move (i-1, j-1).
  * Else move to the neighbor with larger dp value:
      - if dp[i-1][j] > dp[i][j-1] → i--;
      - else → j--;
- Reverse the collected characters at the end.

Correctness (sketch):
- dp fills optimal LCS lengths for all prefixes (induction on i,j).
- Backtracking always follows an optimal parent (either diagonal on match, or toward the larger subproblem),
  reconstructing one valid optimal LCS.

Complexity:
- Time: O(m * n) for table fill + O(m + n) for backtrack.
- Space: O(m * n) for the dp table.
  (Space can be reduced to O(n) to get only the length, but reconstruction then needs extra bookkeeping.)

Edge cases:
- If either string is empty → LCS is "".
- Multiple valid LCS strings may exist; this prints one of them.
- Note: `int dp[m+1][n+1];` uses a VLA (non-standard in C++). Prefer `vector<vector<int>>` for portability.

Tiny dry run:
- s1="abcde", s2="bdgek"
  LCS length = 3, one LCS = "bde".

========================================================
*/

void printLCS(std::string s1, std::string s2) {
    int m = s1.length();
    int n = s2.length();

    // DP table: dp[i][j] = LCS length of s1[0..i-1] and s2[0..j-1]
    int dp[m+1][n+1];                 // VLA; replace with vector for strict C++ compliance

    // Base: any LCS with an empty prefix has length 0
    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;

    // Fill table bottom-up
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];       // take the matching character
            } else {
                dp[i][j] = std::max(dp[i-1][j],    // skip s1[i-1]
                                    dp[i][j-1]);   // or skip s2[j-1]
            }
        }
    }

    // Reconstruct one LCS by walking back from (m,n)
    int i = m, j = n;
    std::string str;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            str += s1[i-1];     // match contributes to LCS
            i--; j--;
        } else {
            // Move toward the direction that gave the optimal length
            if (dp[i-1][j] > dp[i][j-1]) i--;
            else                         j--;
        }
    }

    std::reverse(str.begin(), str.end());
    std::cout << "LCS : " << str << std::endl;  // prints one optimal LCS
}
