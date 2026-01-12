class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for (int i=0;i<n; i++) {
            for (int j=0; j<m; j++) {
                if (s1[i] == s2[j])
                    dp[i+1][j+1] = dp[i][j] + s1[i];
                else
                    dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
            }
        }

        int total = 0;
        for (char c : s1) total += c;
        for (char c : s2) total += c;

        return total - 2 * dp[n][m];
    }
};

/*
==================== REVISION BLOCK — LeetCode 712: Minimum ASCII Delete Sum for Two Strings ====================

Problem
-------
Given two strings s1 and s2, delete characters from either string so that the two strings become equal.
Return the minimum possible sum of ASCII values of deleted characters.

Pattern/ Idea
-------------
DP via "Maximum ASCII-sum Common Subsequence" (weighted LCS).
Instead of directly minimizing deletions, maximize the ASCII sum of characters we KEEP in both strings.
If we keep a common subsequence with maximum ASCII sum = bestKeep,
then deleted sum = (sumASCII(s1) + sumASCII(s2)) - 2 * bestKeep.

Algorithm (step-by-step)
------------------------
1) Let n = len(s1), m = len(s2).
2) dp[i][j] = maximum ASCII sum of a common subsequence between:
      s1[0..i-1] and s2[0..j-1].
3) Transition:
   - If s1[i-1] == s2[j-1]:
       dp[i][j] = dp[i-1][j-1] + ASCII(s1[i-1])
   - Else:
       dp[i][j] = max(dp[i-1][j], dp[i][j-1])
4) Compute total = sumASCII(s1) + sumASCII(s2).
5) Answer = total - 2 * dp[n][m].

Correctness (sketch)
--------------------
dp is a classic LCS-style DP but "weighted" by ASCII values:
- When characters match, we can extend the best common subsequence from prefixes and add that character's ASCII value.
- When they don't match, the best must come from dropping one character from either prefix, hence max of the two subproblems.
dp[n][m] thus equals the maximum ASCII sum we can keep in both strings while making them equal.
Deleting everything else from both strings costs total - 2*keptSum, which is minimal when keptSum is maximal.

Complexity
---------
Time: O(n * m)
Space: O(n * m)

Edge Cases / Pitfalls
---------------------
- One string empty: answer is sumASCII(other string).
- ASCII sum uses char codes; in C++ be careful about signed char issues:
  prefer (int)(unsigned char)c when summing for full safety.
- Works for lowercase/uppercase/any ASCII characters.

Optimization if needed
----------------------
Space can be optimized to O(m) using 1D DP (rolling row), since dp[i][*] depends only on dp[i-1][*] and current row.

========================================================
*/

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = (int)s1.size(), m = (int)s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // dp[i+1][j+1] stores max ASCII sum of common subsequence for s1[0..i], s2[0..j]
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s1[i] == s2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + (int)(unsigned char)s1[i]; // keep this matching char
                } else {
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]); // skip one side
                }
            }
        }

        int total = 0;
        for (char c : s1) total += (int)(unsigned char)c; // sum ASCII of s1
        for (char c : s2) total += (int)(unsigned char)c; // sum ASCII of s2

        // delete everything except the best common subsequence (counted twice in total)
        return total - 2 * dp[n][m];
    }
};
