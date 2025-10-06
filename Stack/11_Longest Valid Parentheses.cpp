class Solution {
public:
    // test case that clears the concept
    //Input: "()(()"  Output: 4  Expected :2

    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);    // -1 for "()()" whole string valid and ease of calculation
        int res = 0;

        for (int i = 0; i < s.length(); i++) {
            if(s[i] == '(')
                stk.push(i);
            else{
                stk.pop();
                if(stk.empty())
                    stk.push(i);
                else
                    res = max(res, i - stk.top());
            }
        }
        
        return res;
    }
};


/*
==================== REVISION BLOCK — Longest Valid Parentheses (LeetCode 32) ====================

Problem
-------
Given a string s consisting of '(' and ')', return the length of the longest valid 
(well-formed) parentheses substring.

Pattern/ Idea
-------------
Stack-based approach:
- Use a stack to store **indices** of unmatched parentheses.
- Push `-1` initially as a "base index" for calculating valid lengths easily.
- Every time you find a closing bracket ')', pop from the stack:
  - If the stack becomes empty, push the current index (to reset base).
  - Otherwise, valid length = i - top_of_stack (difference between current index and
    last unmatched index).

Algorithm (step-by-step)
------------------------
1) Initialize stack with -1 and res = 0.
2) For each index i in s:
   - If s[i] == '(' → push i.
   - Else (s[i] == ')'):
       • Pop top (try to match last '(').
       • If stack becomes empty → push i (reset base).
       • Else → update res = max(res, i - stack.top()).
3) Return res.

Correctness (sketch)
--------------------
The stack always holds indices of unmatched '(' and the last unmatched ')'.
When we pop after a match, the top of the stack points to the index before
the start of the valid substring, so (i - stack.top()) gives the valid length.

Complexity
----------
Time: O(n)
Space: O(n)

Edge Cases / Pitfalls
---------------------
- Empty string → result 0.
- All '(' or all ')' handled by resetting base.
- Works for nested and sequential valid groups.

Optimization if needed
----------------------
Alternative O(1) space two-pass DP:
- Left-to-right and right-to-left scans counting '(' and ')'.
========================================================
*/

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);        // base index for valid substring
        int res = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stk.push(i); // store index of '('
            } else {
                stk.pop();   // try to match a '('
                if (stk.empty()) {
                    stk.push(i); // reset base if no unmatched '('
                } else {
                    res = max(res, i - stk.top()); // length of valid substring
                }
            }
        }

        return res;
    }
};
