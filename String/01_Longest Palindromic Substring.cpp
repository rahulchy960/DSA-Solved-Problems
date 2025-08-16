class Solution {
public:
    bool isPalindrome(string &str, int left, int right){
        while(left<=right){
            if(str[left] != str[right])
                return false;
            left++;
            right--;
        }
        return true;
    }
    string longestPalindrome(string s) {
        int n = s.length();
        int pLen = 0;
        int start = - 1, end = - 1;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(isPalindrome(s,i,j) && (j-i+1 > pLen)){
                    pLen = j-i+1;
                    start = i;
                    end = j+1;
                }
            }
        }
        return s.substr(start, pLen);
    }
};

class Solution {
public:
    bool isPalindrome(string &str, int left, int right){
        while(left<=right){
            if(str[left] != str[right])
                return false;
            left++;
            right--;
        }
        return true;
    }
    string longestPalindrome(string s) {
        int n = s.length();
        int pLen = 0;
        int start = - 1, end = - 1;
        for(int i=0;i<n;i++){

            // for odd length substring
            int left = i, right = i;
            while(left>=0 && right<n && s[left]==s[right]){
                if(pLen < right-left+1){
                    pLen = right - left + 1;
                    start = left;
                    end = right+1;
                }
                left--;
                right++;
            }

            // for even length substring 
            left = i;
            right = i+1;
            while(left>=0 && right<n && s[left]==s[right]){
                if(pLen < right-left+1){
                    pLen = right - left + 1;
                    start = left;
                    end = right+1;
                }
                left--;
                right++;
            }
        }
        return s.substr(start, pLen);
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Longest Palindromic Substring):
- Given a string s, return the longest substring of s that is a palindrome.

Pattern:
- Expand Around Center (two-pointer growth from each center).

Intuition:
- Any palindrome is defined by a center:
  * Odd length: single center at i → expand (i-1, i+1).
  * Even length: double center between i and i+1 → expand (i, i+1).
- Expanding while s[left] == s[right] explores the maximal palindrome for that center.
- Track the longest length and its starting index.

Algorithm:
1) Initialize best length (pLen=0) and best start index.
2) For each i in [0..n-1]:
   a) Odd center: left=i, right=i; expand while equal; update best.
   b) Even center: left=i, right=i+1; expand while equal; update best.
3) Return s.substr(start, pLen).

Correctness (sketch):
- For any optimal palindrome P, its center must be checked at some i (odd or even case).
- Expansion returns the maximal palindrome for that center; global maximum across all centers is found.

Complexity:
- Time: O(n^2) in the worst case (e.g., all identical characters cause maximal expansions).
- Space: O(1) extra.

Edge cases:
- Empty string → returns "" (here pLen starts at 0; loop won’t update; start stays -1; but in LeetCode input n≥1. If needed, guard n==0).
- All unique chars → any single char is the answer.
- Multiple answers with same length → first encountered by the scan is returned.

Notes:
- `end` is tracked but not required for the final return (kept to match your code).
- `isPalindrome` helper is unused by this optimal approach (kept for completeness).

========================================================
*/

class Solution {
public:
    bool isPalindrome(std::string &str, int left, int right){
        // Helper for brute-force checking (unused in the final approach).
        while (left <= right) {
            if (str[left] != str[right]) return false;
            left++; right--;
        }
        return true;
    }

    std::string longestPalindrome(std::string s) {
        int n = s.length();
        int pLen = 0;                  // best palindrome length so far
        int start = -1, end = -1;      // start index (used for substr), end is not strictly needed

        for (int i = 0; i < n; i++) {

            // ---- Odd-length center at i ----
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (pLen < right - left + 1) {
                    pLen = right - left + 1;
                    start = left;
                    end = right + 1;   // not used later; kept from your code
                }
                left--; right++;
            }

            // ---- Even-length center between i and i+1 ----
            left = i;
            right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (pLen < right - left + 1) {
                    pLen = right - left + 1;
                    start = left;
                    end = right + 1;   // not used later; kept from your code
                }
                left--; right++;
            }
        }

        return s.substr(start, pLen);   // longest palindromic substring
    }
};
