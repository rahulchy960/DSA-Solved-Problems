class Solution {
public:
    bool isMatching(char a, char b){
        return (a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']') ;
    }
    bool isValid(string str) {
        stack<char>s;
        for(int i=0; i<str.length(); i++){
            if(str[i] == '(' || str[i] == '{' || str[i] == '[')
                s.push(str[i]);
            else{
                if(s.empty())
                    return false;
                else if(isMatching(s.top(), str[i]))
                    s.pop();
                else
                    return false;
            }
        }

        return s.empty();
    }
};


/*
==================== REVISION BLOCK — LeetCode 20: Valid Parentheses ====================

Problem
-------
Given a string str containing only the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.
A string is valid if:
1) Open brackets are closed by the same type of brackets.
2) Open brackets are closed in the correct order.
3) Every closing bracket has a corresponding open bracket.

Pattern/ Idea
-------------
Stack-based Matching (LIFO).
Idea:
- Use a stack to store opening brackets.
- When a closing bracket appears, it must match the most recent opening bracket
  (top of the stack).

Algorithm (step-by-step)
------------------------
1) Initialize an empty stack of characters.
2) Traverse the string character by character:
   a) If current character is an opening bracket, push it onto the stack.
   b) Else (it is a closing bracket):
      - If stack is empty → invalid (no opening bracket).
      - If top of stack matches the closing bracket → pop stack.
      - Otherwise → invalid.
3) After traversal, return true only if the stack is empty.

Correctness (sketch)
--------------------
- The stack ensures Last-In-First-Out order, which matches the nesting requirement
  of parentheses.
- Every closing bracket is matched with the most recent unmatched opening bracket.
- If a mismatch occurs or a closing bracket appears with an empty stack, the string
  is invalid.
- If the stack is empty at the end, all brackets were matched correctly.

Complexity
---------
Time: O(n), where n is the length of the string
Space: O(n) in worst case (all opening brackets)

Edge Cases / Pitfalls
---------------------
- Empty string → valid.
- String starting with a closing bracket.
- Odd length strings cannot be valid.
- Mixing different bracket types incorrectly.

Optimization if needed
----------------------
Already optimal.
Can also be solved by mapping closing → opening brackets using a hash map.

========================================================
*/
