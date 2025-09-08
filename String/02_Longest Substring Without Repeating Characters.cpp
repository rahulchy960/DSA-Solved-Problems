class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLen = 0;
        vector<int>map(256, -1);
        int i=0;
        for(int j=0;j<n;j++){
            i = max(i, map[s[j]]+1);
            maxLen = max(maxLen, j-i+1);
            map[s[j]]=j;
        }
        return maxLen;
    }
};

/*
==================== REVISION BLOCK — Longest Substring Without Repeating Characters ====================

Problem
-------
Given a string s, find the length of the longest substring that contains **no repeated characters**.

Pattern
-------
Sliding window with last-seen index:
- Keep a window [i..j] with all unique chars.
- When s[j] repeats a character already in the window, move the left bound `i`
  to one position right of that character’s **last seen index**.

Key Invariant
-------------
At any time, substring s[i..j] has all unique characters.  
For each new j:
- If s[j] hasn't been seen in s[i..j-1], expand the window (just update best length).
- Else, set `i = max(i, lastIndex[s[j]] + 1)` to jump past the previous occurrence.

Algorithm (this code)
---------------------
1) lastIndex[c] = last index of character c seen so far, initialized to -1.
2) i = 0 (left bound), ans = 0.
3) For j from 0..n-1:
   - i = max(i, lastIndex[s[j]] + 1)   // shrink left if s[j] repeats inside window
   - ans = max(ans, j - i + 1)         // update best window length
   - lastIndex[s[j]] = j               // record current index
4) Return ans.

Complexity
----------
- Time: O(n) — each index moves forward at most once.
- Space: O(Σ) where Σ is the alphabet size (256 here).

Notes / Pitfalls
----------------
- If `char` is signed on your platform and `s[j]` can be non-ASCII, prefer indexing with
  `(unsigned char)s[j]` or use an `unordered_map<char,int>`/`array<int,256>`.
- For pure ASCII, `vector<int> last(256, -1)` is fine.
- Empty string returns 0.

Tiny Dry Run
------------
s = "abba"
j=0:'a' → i=0 → ans=1 → last['a']=0
j=1:'b' → i=0 → ans=2 → last['b']=1
j=2:'b' → i=max(0,1+1)=2 → ans=max(2, 2-2+1)=2 → last['b']=2
j=3:'a' → i=max(2,0+1)=2 → ans=max(2, 3-2+1)=2 → last['a']=3
Answer = 2 ("ab" or "ba")

========================================================
*/

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        int n = s.length();
        int maxLen = 0;
        std::vector<int> last(256, -1);  // last seen index for each char
        int i = 0;                       // left bound of window

        for (int j = 0; j < n; j++) {
            // If s[j] seen inside current window, jump i past its last occurrence
            i = std::max(i, last[(unsigned char)s[j]] + 1);
            maxLen = std::max(maxLen, j - i + 1);      // update best length
            last[(unsigned char)s[j]] = j;             // record current index
        }
        return maxLen;
    }
};
