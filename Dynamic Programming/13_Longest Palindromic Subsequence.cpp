class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string ss = s;
        reverse(ss.begin(), ss.end());
        int n = s.length();

        vector<vector<int>>dp(n+1, vector<int>(n+1, 0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(s[i-1] == ss[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[n][n];
    }
};




/*
==================== REVISION BLOCK ====================

Problem (Longest Palindromic Subsequence, LPS):
- Given a string s, find the length of the longest subsequence of s that is a palindrome.

Key Trick:
- LPS(s) == LCS(s, reverse(s)).
  Any palindromic subsequence in s reads the same forward/backward → it appears as a common subsequence
  between s and its reverse.

Pattern:
- Classic Dynamic Programming via LCS on s and rev(s).

State:
- dp[i][j] = length of LCS between s[0..i-1] and rev(s)[0..j-1].

Transition:
- If s[i-1] == rev[j-1] → dp[i][j] = 1 + dp[i-1][j-1]
- Else                → dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Init:
- dp[0][*] = dp[*][0] = 0  (empty string has LCS length 0)

Answer:
- dp[n][n]

Correctness (sketch):
- LCS DP is standard and correct by induction on prefixes.
- Since every palindromic subsequence of s is a common subsequence of s and reverse(s),
  the LCS length equals the LPS length; conversely, any common subsequence corresponds
  to a subsequence that reads the same forward/backward.

Complexity:
- Time: O(n^2) — fill an (n+1) x (n+1) table.
- Space: O(n^2) — DP table.
  (Can optimize to O(n) using two 1D rows since each row depends only on the previous row.)

Edge Cases:
- n = 0 → answer 0.
- All identical chars → answer n.
- No repeating chars → answer 1.

Pitfalls:
- Don’t confuse with Longest Palindromic Substring (contiguous vs subsequence).
- Ensure indices align with 1-based DP table.

========================================================
*/

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string ss = s;
        reverse(ss.begin(), ss.end());     // build reverse(s)
        int n = s.length();

        // dp[i][j] = LCS length of s[0..i-1] and ss[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Fill LCS table bottom-up
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == ss[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];      // characters match → extend LCS
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // skip one side
                }
            }
        }
        return dp[n][n]; // LPS length
    }
};
