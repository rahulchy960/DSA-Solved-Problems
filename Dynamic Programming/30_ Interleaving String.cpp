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
Given strings s1, s2, s3, determine if s3 can be formed by interleaving s1 and s2,
preserving the left-to-right order of characters from each string.

Pattern/ Idea
-------------
2D Dynamic Programming on prefixes.
Let dp[i][j] = true iff s3[0..i+j-1] is an interleaving of s1[0..i-1] and s2[0..j-1].

Algorithm (step-by-step)
------------------------
1) If |s1| + |s2| != |s3| → return false.
2) Initialize dp of size (n1+1) x (n2+1) to false; set dp[0][0] = true.
3) Fill first row/col:
   - dp[i][0] = dp[i-1][0] && (s1[i-1] == s3[i-1])
   - dp[0][j] = dp[0][j-1] && (s2[j-1] == s3[j-1])
4) For i=1..n1, j=1..n2:
   - k = i + j
   - From s1: if s1[i-1] == s3[k-1] and dp[i-1][j] → possible
   - From s2: if s2[j-1] == s3[k-1] and dp[i][j-1] → possible
   - dp[i][j] = (from s1) || (from s2)
5) Return dp[n1][n2].

Correctness (sketch)
--------------------
Every prefix of s3 must end with either s1[i-1] or s2[j-1].
If that last char matches and the remaining prefix is a valid interleave,
we can build dp[i][j] from dp[i-1][j] or dp[i][j-1]. Induction on i+j proves correctness.

Complexity
----------
Time: O(n1 * n2)
Space: O(n1 * n2) (can be optimized to O(n2))

Edge Cases / Pitfalls
---------------------
- One of s1 or s2 empty.
- Early length mismatch.
- Consecutive identical chars across s1 and s2 (ensure both transitions are considered).

Optimization if needed
----------------------
- Space optimize to O(n2) with a rolling 1D dp over j (update right-to-left or carefully left-to-right).
========================================================
*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        // Length check: necessary condition
        if (s1.length() + s2.length() != s3.length())
            return false;

        int n1 = s1.length(), n2 = s2.length();

        // dp[i][j] ⇒ s3[0..i+j-1] formed by interleaving s1[0..i-1] and s2[0..j-1]
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));

        dp[0][0] = true; // empty + empty = empty

        // Fill first column: only s1 contributes
        for (int i = 1; i <= n1; i++)
            dp[i][0] = (s3[i - 1] == s1[i - 1]) && dp[i - 1][0];

        // Fill first row: only s2 contributes
        for (int j = 1; j <= n2; j++)
            dp[0][j] = (s3[j - 1] == s2[j - 1]) && dp[0][j - 1];

        // Fill the rest
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                int k = i + j;              // length of prefix in s3 we must match
                bool fromS1 = false, fromS2 = false;

                // If next of s1 matches s3, we can come from dp[i-1][j]
                if (s3[k - 1] == s1[i - 1])
                    fromS1 = dp[i - 1][j];

                // If next of s2 matches s3, we can come from dp[i][j-1]
                if (s3[k - 1] == s2[j - 1])
                    fromS2 = dp[i][j - 1];

                dp[i][j] = fromS1 || fromS2;
            }
        }

        return dp[n1][n2];
    }
};
