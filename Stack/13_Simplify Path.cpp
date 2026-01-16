/*  Mistake I made

This Statement is wrong as it fails for Input: "/../"

if (curr == ".." && !stack.empty())
    stack.pop_back();

When curr == ".." and the stack is empty, the code falls into the else if 
condition and pushes ".." into the stack 

*/


class Solution {
public:
    string simplifyPath(string path) {
        vector<string>stack;
        string curr;
        path += "/";
        for(char c: path){
            if(c == '/'){
                if(curr == ".."){         // 
                    if(!stack.empty())
                        stack.pop_back();
                }    
                else if(curr.empty()==false && curr != ".")
                    stack.push_back(curr);
                
                curr.clear();

            } else {
                curr += c;
            }
        }

        path = "/";
        for(int i=0;i<stack.size();i++){
            if(i>0){
                path += "/";
            }
            path += stack[i];
        }

        return path;
    }
};

/*
==================== REVISION BLOCK — LeetCode 71: Simplify Path ====================

Problem
-------
Given an absolute Unix-style file path, simplify it and return the canonical path.
Rules:
- "." means current directory → ignore.
- ".." means move to parent directory → pop last directory if possible.
- Multiple '/' are treated as a single '/'.
- The result must start with '/' and contain no trailing '/' (except root).

Pattern/ Idea
-------------
Stack-based Directory Traversal.
Idea:
- Split the path by '/'.
- Use a stack to maintain valid directory names.
- Handle ".." by popping, "." by ignoring, and normal directory names by pushing.

Algorithm (step-by-step)
------------------------
1) Append a trailing '/' to the path to process the last directory uniformly.
2) Traverse each character of path, building a current token `curr`.
3) When '/' is encountered:
   a) If curr == "..":
        - Pop from stack if stack is not empty.
   b) Else if curr is non-empty and curr != ".":
        - Push curr onto stack.
   c) Clear curr.
4) After traversal, rebuild the canonical path:
   - Start with "/".
   - Append stack elements separated by '/'.
5) Return the resulting path.

Correctness (sketch)
--------------------
- Each directory token is processed exactly once.
- "." tokens do not change the directory structure.
- ".." correctly moves one level up by removing the last directory (if any).
- Extra slashes produce empty tokens, which are ignored.
- Reconstructing from the stack yields the canonical absolute path.

Complexity
---------
Time: O(n), where n is the length of the input path
Space: O(n) in worst case (stack stores all directory names)

Edge Cases / Pitfalls
---------------------
- Path like "/../" → remains "/".
- Path with multiple slashes: "/a//b///c/".
- Path resolving to root only.
- Directory names like "...", which are valid (only "." and ".." are special).

Optimization if needed
----------------------
Already optimal.
Alternative approach: use stringstream to split by '/'.

========================================================
*/

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;   // acts as directory stack
        string curr;

        path += "/";            // sentinel slash to process last token

        for (char c : path) {
            if (c == '/') {
                if (curr == "..") {
                    if (!stack.empty())
                        stack.pop_back(); // move to parent directory
                } 
                else if (!curr.empty() && curr != ".") {
                    stack.push_back(curr); // valid directory name
                }
                curr.clear();   // reset for next token
            } else {
                curr += c;      // build current directory name
            }
        }

        // Reconstruct canonical path
        path = "/";
        for (int i = 0; i < (int)stack.size(); i++) {
            if (i > 0)
                path += "/";
            path += stack[i];
        }

        return path;
    }
};
