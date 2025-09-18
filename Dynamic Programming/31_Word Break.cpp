class Solution {
public:
    bool helper(string s, int start, unordered_set<string>&set){
        if(start == s.length()){
            return true;
        }
        string str = "";
        for(int i = start; i<s.length(); i++){
            str += s[i];
            if(set.find(str) != set.end()){
                if(helper(s, i+1, set))
                    return true;
            }
        }
        return false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>set(wordDict.begin(), wordDict.end());
        return helper(s, 0, set);
    }
};

/*
==================== REVISION BLOCK — Word Break (LeetCode 139) ====================

Problem
-------
Given a string s and a dictionary of strings wordDict, return true if s can be segmented
into a space-separated sequence of one or more dictionary words.

Pattern/ Idea
-------------
DFS on prefixes (try-all-cuts). At index `start`, greedily extend a prefix s[start..i]
and if it exists in the dictionary, recurse from i+1. This is a classic DP problem due to
overlapping subproblems → add memoization or do bottom-up DP.

Algorithm (step-by-step)
------------------------
1) Put all words from wordDict into a hash set for O(1) membership checks.
2) Define helper(s, start):
   - If start == |s| → true (we segmented the whole string).
   - For i from start to |s|-1:
       • Let cur = s[start..i].
       • If cur in dict and helper(i+1) is true → return true.
   - If no cut works → return false.
3) Call helper(0).

Correctness (sketch)
--------------------
Every valid segmentation corresponds to a series of cuts (indices) where each cut piece
is in the dictionary. DFS explores all feasible cuts; if any path reaches the end, s is segmentable.
Memoizing start-indices preserves correctness while pruning repeated states.

Complexity
----------
Current code (plain recursion without memoization):
- Time: Exponential in worst-case (re-explores same suffixes many times).
- Space: O(n) recursion depth (n = |s|).

With memoization on `start`:
- Time: O(n^2) average (each start tries at most n extensions; string slices can be optimized).
- Space: O(n) for memo + recursion depth.

Edge Cases / Pitfalls
---------------------
- s empty → true.
- wordDict empty → s must be empty to return true.
- Many overlapping prefixes (e.g., "aaaa...") cause TLE without memoization.
- Repeated string concatenation can be costly; prefer indices or substring views.

Optimization if needed
----------------------
- Add memoization: dp[start] ∈ { -1 unknown, 0 false, 1 true }.
- Precompute min/max word lengths to bound the inner loop.
- Bottom-up DP: dp[i] = can break first i chars; for each j<i, if dp[j] && s[j..i-1]∈dict → dp[i]=true.
========================================================
*/

class Solution {
public:
    // DFS without memoization (may TLE on adversarial cases)
    bool helper(string s, int start, unordered_set<string>& set) {
        // If we've consumed the whole string, it's a valid segmentation
        if (start == (int)s.length()) return true;

        string cur;
        // Try all prefixes starting at 'start'
        for (int i = start; i < (int)s.length(); ++i) {
            cur += s[i];                         // build s[start..i]
            if (set.find(cur) != set.end()) {    // if current piece is a word
                if (helper(s, i + 1, set))       // try to break the remaining suffix
                    return true;
            }
        }
        // No valid cut from 'start'
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // Put words in hash set for O(1) lookup
        unordered_set<string> set(wordDict.begin(), wordDict.end());
        return helper(s, 0, set);
    }
};


/*
-----------------------------------------
Optional: Memoized Top-Down (recommended)
Time: ~O(n^2), Space: O(n)
-----------------------------------------

class Solution {
public:
    bool dfs(const string& s, int start, const unordered_set<string>& dict, vector<int>& memo,
             int minLen, int maxLen) {
        if (start == (int)s.size()) return true;
        int& m = memo[start];
        if (m != -1) return m;

        // Only try word lengths within [minLen, maxLen] and within bounds
        for (int len = minLen; len <= maxLen && start + len <= (int)s.size(); ++len) {
            if (dict.count(s.substr(start, len)) && dfs(s, start + len, dict, memo, minLen, maxLen))
                return m = 1;
        }
        return m = 0;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) return true;
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        if (dict.empty()) return false;

        // Bound the branching with min/max word lengths
        int minLen = INT_MAX, maxLen = 0;
        for (auto& w : wordDict) {
            minLen = min(minLen, (int)w.size());
            maxLen = max(maxLen, (int)w.size());
        }

        vector<int> memo(s.size(), -1); // -1 unknown, 0 false, 1 true
        return dfs(s, 0, dict, memo, minLen, maxLen);
    }
};
*/



class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<bool>dp(n+1, 0);
        dp[0] = true;
        for(int i=1;i<=n;i++){
            for(const string &w: wordDict){
                int start = i-w.size();
                if(start >= 0 && s.substr(start, w.size()) == w && dp[start]){
                    dp[i] = 1;
                    break;
                }
            }
        }
        return dp[n];
    }
};


/*
==================== REVISION BLOCK — Word Break (LeetCode 139) ====================

Problem
-------
Given a string s and a dictionary wordDict, return true if s can be segmented into 
a sequence of one or more dictionary words.

Pattern/ Idea
-------------
1D Dynamic Programming.
- dp[i] = true if s[0..i-1] can be segmented using wordDict.

Algorithm (step-by-step)
------------------------
1) Initialize dp array of size n+1 to false. dp[0] = true (empty prefix is valid).
2) For i = 1..n:
   - For each word w in wordDict:
     • Let start = i - |w|.
     • If start >= 0 and s.substr(start, |w|) == w and dp[start] == true:
         → mark dp[i] = true and break inner loop.
3) Return dp[n].

Correctness (sketch)
--------------------
If dp[start] is true, then s[0..start-1] can be segmented.
If s[start..i-1] ∈ wordDict, then s[0..i-1] can also be segmented → dp[i] = true.
By induction, dp[n] is true iff the entire string is segmentable.

Complexity
----------
Time: O(n * m * L)  
- n = |s|, m = number of words in wordDict, L = average word length (for substring comparison).
Space: O(n) for the dp array.

Edge Cases / Pitfalls
---------------------
- Empty string s: dp[0] = true → result true.
- Empty dictionary → result false unless s is empty.
- Very large s with overlapping prefixes (need DP for efficiency).
- substring() can be costly; optimization possible.

Optimization if needed
----------------------
- Precompute minLen/maxLen of words to limit checks.
- Use trie-based matching to avoid repeated substring operations.
- Space optimization is already O(n); can’t reduce further without changing approach.
========================================================
*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true; // empty prefix is valid

        for (int i = 1; i <= n; i++) {
            for (const string &w : wordDict) {
                int start = i - (int)w.size();
                // Check if the last |w| chars of s[0..i-1] match w
                if (start >= 0 && s.substr(start, w.size()) == w && dp[start]) {
                    dp[i] = true;
                    break; // no need to check further words for this i
                }
            }
        }

        return dp[n]; // true if full string can be segmented
    }
};
