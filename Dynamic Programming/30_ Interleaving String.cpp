class Solution {
public:
    bool helper(string s1, string s2, string s3, int n1, int n2){
        if(n1+n2 == s3.length()) 
            return true;
        if(n1 < s1.length() && s1[n1] == s3[n1+n2])
            if(helper(s1, s2, s3, n1+1, n2))
                return true;
        if(n2 < s2.length() && s2[n2] == s3[n1+n2])
            if(helper(s1, s2, s3, n1, n2+1))
                return true;
        
        return false;
        
    }
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.length() + s2.length() != s3.length())
            return false;
        return helper(s1, s2, s3, 0, 0);
    }
};

/*
==================== REVISION BLOCK — Interleaving String (LeetCode 97) ====================

Problem
-------
Given strings s1, s2, s3, determine whether s3 is formed by an interleaving of s1 and s2.
Interleaving keeps the left-to-right order of characters from each string.

Pattern/ Idea
-------------
Recursive choice at each step: if s3[idx] equals next of s1 and/or s2, try advancing.
This is a classic DP (2D) problem due to heavy overlap → recursion + memoization or bottom-up DP.

Algorithm (step-by-step)
------------------------
1) Quick length check: if |s1| + |s2| != |s3| → false.
2) Define a helper(s1, s2, s3, i, j):
   - If i + j == |s3| → true (all matched).
   - If i < |s1| and s1[i] == s3[i+j], try helper(i+1, j).
   - If j < |s2| and s2[j] == s3[i+j], try helper(i, j+1).
   - If neither path succeeds → false.
3) Start with helper(0, 0).

Correctness (sketch)
--------------------
At each (i, j), we match s3[i+j] with the next available char from s1 or s2 while preserving order.
Exhaustively exploring feasible choices ensures we accept iff a valid interleaving exists.

Complexity
----------
Current code (plain recursion):
- Time: Exponential in the worst case (overlapping subproblems).
- Space: O(|s1| + |s2|) recursion depth in worst case.

Edge Cases / Pitfalls
---------------------
- Empty strings: s1="", s2="" → s3 must be "".
- Prefix ties where both branches seem valid (requires memoization to avoid rework).
- Mismatched lengths immediately return false.

Optimization if needed
----------------------
- Add memoization on (i, j) → O(|s1| * |s2|) time, O(|s1| * |s2|) space.
- Bottom-up DP: dp[i][j] true if dp[i-1][j] and s1[i-1]==s3[i+j-1], or dp[i][j-1] and s2[j-1]==s3[i+j-1].
========================================================
*/

class Solution {
public:
    // Helper checks if s3[0..i+j-1] can be formed by interleaving s1[0..i-1] and s2[0..j-1].
    bool helper(string s1, string s2, string s3, int n1, int n2) {
        // If we've consumed exactly all chars of s3, success.
        if (n1 + n2 == (int)s3.length())
            return true;

        // Try to take next char from s1 if it matches s3 at position n1+n2
        if (n1 < (int)s1.length() && s1[n1] == s3[n1 + n2])
            if (helper(s1, s2, s3, n1 + 1, n2))
                return true;

        // Otherwise, try to take next char from s2 if it matches s3 at position n1+n2
        if (n2 < (int)s2.length() && s2[n2] == s3[n1 + n2])
            if (helper(s1, s2, s3, n1, n2 + 1))
                return true;

        // No valid interleaving from this state
        return false;
    }

    bool isInterleave(string s1, string s2, string s3) {
        // Length mismatch → cannot be an interleaving
        if (s1.length() + s2.length() != s3.length())
            return false;

        // Plain recursion (may TLE on large inputs)
        return helper(s1, s2, s3, 0, 0);
    }
};



class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.length() + s2.length() != s3.length())
            return false;
        int n1 = s1.length(), n2 = s2.length();

        vector<vector<bool>>dp(n1+1, vector<bool>(n2+1, false));
        dp[0][0] = true;
        for(int i=1;i<=n1;i++)
            dp[i][0] = s3[i-1] == s1[i-1] && dp[i-1][0];
        for(int j=1;j<=n2;j++)
            dp[0][j] = s3[j-1] == s2[j-1] && dp[0][j-1];

        for(int i=1;i<=n1;i++){
            for(int j=1;j<=n2;j++){
                int k = i+j;
                bool s1Match = 0, s2Match = 0;
                if(s3[k-1] == s1[i-1])
                    s1Match = dp[i-1][j];
                if(s3[k-1] == s2[j-1])
                    s2Match = dp[i][j-1];
                dp[i][j] = s1Match || s2Match;
            }
        }

        return dp[n1][n2];
        
    }
};


/*
==================== REVISION BLOCK — Interleaving String (LeetCode 97) ====================

Problem
-------
Given strings s1, s2, s3, decide if s3 is a merge of s1 and s2 that preserves the
left-to-right order within each source string.

Pattern/ Idea
-------------
Think of a **grid walk** on an (|s1|+1) × (|s2|+1) lattice:
- State (i, j) means we've taken i chars from s1 and j chars from s2 to form s3[0..i+j-1].
- A **right move** consumes s1[i-1]; a **down move** consumes s2[j-1].
- s3 is a valid interleaving iff there exists a monotone path from (0,0) to (|s1|,|s2|)
  whose step label always matches the next character of s3.

This naturally yields DP:
dp[i][j] = true iff (s3[i+j-1] == s1[i-1] && dp[i-1][j]) OR
                         (s3[i+j-1] == s2[j-1] && dp[i][j-1]).

Algorithm (step-by-step)
------------------------
1) Length gate: if |s1| + |s2| != |s3| → return false.
2) Create dp of size (n1+1)×(n2+1), dp[0][0] = true (empty + empty = empty).
3) Initialize first column (only right moves allowed):
   dp[i][0] = dp[i-1][0] && (s1[i-1] == s3[i-1]).
4) Initialize first row (only down moves allowed):
   dp[0][j] = dp[0][j-1] && (s2[j-1] == s3[j-1]).
5) For i = 1..n1, j = 1..n2:
   - Let k = i + j be the length of the prefix we try to match in s3.
   - fromS1 = (s1[i-1] == s3[k-1]) && dp[i-1][j]
   - fromS2 = (s2[j-1] == s3[k-1]) && dp[i][j-1]
   - dp[i][j] = fromS1 || fromS2
6) Return dp[n1][n2].

Correctness (sketch)
--------------------
**Invariant:** dp[i][j] is true ⇔ s3[0..i+j-1] can be formed by interleaving s1[0..i-1] and s2[0..j-1].
Base case holds at (0,0). Inductively, any valid prefix must end by consuming either s1[i-1]
or s2[j-1]. If that last char matches s3’s last of the prefix and the preceding state is true,
then dp[i][j] is true. Conversely, any interleaving path to (i,j) must have come from one of
the two predecessors, so the recurrence is both necessary and sufficient.

Complexity
----------
Time: O(n1 * n2)  
Space: O(n1 * n2)  (optimizable to O(n2) with a rolling 1D array)

Edge Cases / Pitfalls
---------------------
- One of s1 or s2 empty (handled by first row/column initialization).
- Repeated characters across s1/s2 require considering **both** transitions (don’t short-circuit one).
- Early length mismatch must return false.

Optimization if needed
----------------------
- Space optimize: keep a 1D dp over j; update left-to-right:
  dp[j] = (dp[j] && s1[i-1]==s3[k-1]) || (dp[j-1] && s2[j-1]==s3[k-1]).
========================================================
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // Gate on total length
        if (s1.length() + s2.length() != s3.length())
            return false;

        int n1 = s1.length(), n2 = s2.length();

        // dp[i][j] ⇒ s3[0..i+j-1] is an interleaving of s1[0..i-1] and s2[0..j-1]
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;  // empty + empty = empty

        // Only consume from s1 (first column)
        for (int i = 1; i <= n1; i++)
            dp[i][0] = (s3[i - 1] == s1[i - 1]) && dp[i - 1][0];

        // Only consume from s2 (first row)
        for (int j = 1; j <= n2; j++)
            dp[0][j] = (s3[j - 1] == s2[j - 1]) && dp[0][j - 1];

        // Fill the interior of the DP table
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                int k = i + j;                 // total chars matched in s3 so far
                bool fromS1 = false, fromS2 = false;

                // If we take next from s1, the previous state must be dp[i-1][j]
                if (s3[k - 1] == s1[i - 1])
                    fromS1 = dp[i - 1][j];

                // If we take next from s2, the previous state must be dp[i][j-1]
                if (s3[k - 1] == s2[j - 1])
                    fromS2 = dp[i][j - 1];

                dp[i][j] = fromS1 || fromS2;
            }
        }
        return dp[n1][n2];
    }
};

