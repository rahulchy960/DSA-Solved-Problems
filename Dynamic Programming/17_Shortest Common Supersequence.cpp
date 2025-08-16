class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.length();
        int n = str2.length();
        vector<vector<int>>dp(m+1, vector<int>(n+1, 0));
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(str1[i-1] == str2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        int i = m, j = n;
        string str = "";
        while(i>0 && j>0){
            if(str1[i-1] == str2[j-1]){
                str += str1[i-1];
                i--;
                j--;
            }
            else{
                if(dp[i-1][j] > dp[i][j-1]){
                    str += str1[i-1];
                    i--;
                }
                else{
                    str += str2[j-1];
                    j--;
                }
            }
        }
        while(i>0){
            str += str1[i-1];
            i--;
        }
        while(j>0){
            str += str2[j-1];
            j--;
        }

        reverse(str.begin(), str.end());

        return str;

        // the length of SCS is => str1.length() + str2.length() - lengthOf(LCS)
        
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Shortest Common Supersequence, SCS):
- Given strings str1 (len m) and str2 (len n), return the shortest string that contains both str1 and str2 as subsequences.

Key Fact:
- |SCS| = m + n − |LCS(str1, str2)|.

Pattern:
- Compute LCS length table (dp), then reconstruct the SCS by walking backward:
  * If characters match → include it once and move diagonally (i-1, j-1).
  * Else → move toward the larger LCS neighbor; append the corresponding character.
  * After one string exhausts, append the remaining prefix of the other string.
  * Reverse at the end (since we build from back to front).

Algorithm (step-by-step):
1) Build LCS length table dp[m+1][n+1]:
   - dp[i][j] = 0 for i==0 or j==0.
   - If str1[i-1] == str2[j-1]: dp[i][j] = 1 + dp[i-1][j-1]
     else: dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
2) Reconstruct SCS from (i=m, j=n):
   - If chars match: push that char; i--, j--.
   - Else if dp[i-1][j] > dp[i][j-1]: push str1[i-1]; i--.
          else: push str2[j-1]; j--.
3) Append leftovers from str1 (i>0) or str2 (j>0).
4) Reverse the built string and return.

Correctness (sketch):
- The LCS table ensures we never drop characters needed to keep both as subsequences.
- Taking the larger neighbor preserves maximal common-subsequence length, yielding minimal SCS.
- Matches are added once, preventing duplication and achieving shortest length.

Complexity:
- Time: O(m·n) to fill dp + O(m+n) to backtrack → O(m·n).
- Space: O(m·n) for dp (can be optimized with careful reconstruction bookkeeping).

Edge cases:
- One string empty → SCS is the other string.
- Multiple valid SCS exist; this returns one of them (tie-breaking when dp values equal prefers str2 in this code).

========================================================
*/

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.length();
        int n = str2.length();

        // 1) LCS length table
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];         // take match
                else
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]); // skip one side
            }
        }

        // 2) Reconstruct SCS by walking back through dp
        int i = m, j = n;
        std::string str;
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                str += str1[i - 1];   // common char appears once
                i--; j--;
            } else {
                // Move toward the side with larger LCS; append that side's char
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    str += str1[i - 1];
                    i--;
                } else {
                    str += str2[j - 1];
                    j--;
                }
            }
        }

        // 3) Append remaining characters from either string
        while (i > 0) {
            str += str1[i - 1];
            i--;
        }
        while (j > 0) {
            str += str2[j - 1];
            j--;
        }

        // Built from back to front → reverse
        std::reverse(str.begin(), str.end());
        return str;
    }
};
