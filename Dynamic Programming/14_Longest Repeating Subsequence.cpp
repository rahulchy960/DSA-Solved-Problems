class Solution {
  public:
    
    int LRS(string &s, string &ss, int n, int m){
        if(n==0 || m==0)
            return 0;
        if(s[n-1] == s[m-1] && (n-1 != m-1))
            return 1 + LRS(s,ss,n-1,m-1);
        return max(LRS(s,ss,n-1,m), LRS(s,ss,n,m-1));
    }
  
    int LongestRepeatingSubsequence(string &s) {
        // Code here
        return LRS(s,s,s.length(),s.length());

    }
};

class Solution {
  public:
  
    int LongestRepeatingSubsequence(string &s) {
       
        int n = s.length();
        vector<vector<int>>dp(n+1, vector<int>(n+1,0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(s[i-1] == s[j-1] && (i-1 != j-1))
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

Problem (Longest Repeating Subsequence, LRS):
- Given a string s, find the length of the longest subsequence that appears at least twice in s,
  with the two occurrences using different indices (i != j for matched characters).

Key Idea:
- LRS is equivalent to LCS(s, s) with the constraint that we never match the same index.
- Recurrence mirrors LCS:
  f(n, m) = 1 + f(n-1, m-1)        if s[n-1] == s[m-1] and n != m
          = max(f(n-1, m), f(n, m-1)) otherwise
  Base: f(0, m) = f(n, 0) = 0

Algorithm (this implementation — pure recursion):
1) If n == 0 or m == 0 → return 0.
2) If last characters match AND indices differ (n != m), take 1 + recurse on (n-1, m-1).
3) Else, return max of skipping one char from either side: max(f(n-1, m), f(n, m-1)).
4) Answer = f(|s|, |s|).

Correctness (sketch):
- Tries all ways to build two equal subsequences under i != j.
- When characters equal and indices differ, we extend the repeating subsequence by 1.
- Otherwise we optimally skip on one side, just like LCS.

Complexity (THIS recursive version):
- Time: Exponential (≈ O(2^(n+m)) → O(2^n) when both dimensions are n) due to overlapping subproblems.
- Space: O(n + m) = O(n) recursion depth (call stack).
  Tip: Memoization/Tabulation reduces to O(n^2) time and O(n^2) space.

Edge Notes:
- Using the same string twice is fine; just ensure indices differ (n != m).
- Parameter `ss` is unused here (the code compares `s` with itself).

========================================================
*/

class Solution {
public:
    // f(n, m): LRS length between s[0..n-1] and s[0..m-1] with index-inequality constraint
    int LRS(string &s, string &ss, int n, int m){
        // Base: one string empty -> no repeating subsequence
        if(n == 0 || m == 0)
            return 0;

        // If characters match and indices are different (n!=m), we can extend by 1
        if(s[n-1] == s[m-1] && (n-1 != m-1))   // equivalent to (n != m)
            return 1 + LRS(s, ss, n-1, m-1);

        // Otherwise, skip a character from one side (classic LCS move)
        return max(LRS(s, ss, n-1, m), LRS(s, ss, n, m-1));
    }

    int LongestRepeatingSubsequence(string &s) {
        // Time: exponential (recursive). For O(n^2), use memoized/tabulated DP.
        return LRS(s, s, (int)s.length(), (int)s.length());
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Longest Repeating Subsequence - LRS):
- Given a string s, find the length of the longest subsequence that appears
  at least twice in s, using different indices for matching characters.

Key Idea:
- LRS ≡ LCS(s, s) with the extra constraint that we never match the same index.
- Define dp[i][j] = LCS length between s[0..i-1] and s[0..j-1] where matches require i != j.

Transition:
- If s[i-1] == s[j-1] and i != j  → dp[i][j] = 1 + dp[i-1][j-1]
- Else                             → dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Initialization:
- dp[0][*] = dp[*][0] = 0  (empty prefix has LCS 0)

Answer:
- dp[n][n]

Correctness (sketch):
- This is standard LCS on (s, s) while forbidding matching the same occurrence (i != j),
  which exactly enforces “repeating” with disjoint positions.

Complexity:
- Time:  O(n^2) — fill (n+1)×(n+1) table.
- Space: O(n^2) — DP table.
  (Space can be optimized to O(n) with two rolling rows.)

Edge Notes / Pitfalls:
- Be careful to enforce i != j (this code does via (i-1 != j-1)).
- Don’t confuse with Longest Palindromic Subsequence (different problem).

Dry Run:
- s = "aab"
  LRS = "a" (appears twice) → length 1.

========================================================
*/

class Solution {
  public:
    int LongestRepeatingSubsequence(string &s) {
        int n = s.length();
        // dp[i][j] = LRS length for s[0..i-1] vs s[0..j-1] with i != j on matches
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // If characters match and are from different indices, extend by 1
                if (s[i - 1] == s[j - 1] && (i - 1 != j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // Otherwise, skip one side (classic LCS move)
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n][n];
    }
};
