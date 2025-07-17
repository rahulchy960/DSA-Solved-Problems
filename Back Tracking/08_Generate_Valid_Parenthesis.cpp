class Solution {
public:
    vector<string>res;
    /*
    bool isSafe(int open, int close, int n){   // this is aslo correct
        return (open<=n && close<=open);
    }
    void helper(int n, string curr, int open=0, int close=0){
        if(curr.length()==2*n && open==close){
            res.push_back(curr);
            return;
        }
        if(isSafe(open, close, n)){
            helper(n, curr+"(", open+1, close);
            helper(n, curr+")", open, close+1);
        }
            
    }
    */
    void helper(int n, string curr, int open=0, int close=0){
        if(curr.length()==2*n && open==close){
            res.push_back(curr);
            return;
        }

        
        if(open<n){
            curr.push_back('(');
            helper(n, curr, open+1, close);
            curr.pop_back();
        } 
        
        if(close<open){
            curr.push_back(')');
            helper(n, curr, open, close+1);
            curr.pop_back();
        }
        
    }
    vector<string> generateParenthesis(int n) {
        string curr="";
        helper(n, curr);
        return res;
    }
};



class Solution {
public:
    vector<string> res;

    /*
    Algorithm:
    - We are generating all combinations of well-formed (balanced) parentheses for a given number 'n'.
    - Use backtracking to add '(' and ')' as long as they maintain valid pairing:
        - Only add '(' if the count of '(' added so far is less than n.
        - Only add ')' if the count of ')' is less than the count of '('.
    - When the current string length reaches 2*n and the number of '(' equals the number of ')',
      we add the string to the result.
    - Backtracking ensures we explore all valid paths and remove invalid ones.

    Time Complexity:
    - O(2^2n) in the worst case due to the binary tree recursion structure,
      but the actual number of valid combinations is the nth Catalan number: C(n) = (1 / (n+1)) * (2n choose n)
    - So, Time Complexity is O(C(n)), which is asymptotically O(4^n / sqrt(n))

    Space Complexity:
    - O(2n) for the recursion stack (maximum depth is 2n)
    - O(C(n) * 2n) for storing all valid combinations in the result vector,
      where each string is of length 2n and there are C(n) such strings
    */

    void helper(int n, string curr, int open = 0, int close = 0) {
        // Base case: if the current string is complete and valid
        if (curr.length() == 2 * n && open == close) {
            res.push_back(curr);
            return;
        }

        // Try to add '(' if we haven't reached the limit
        if (open < n) {
            curr.push_back('(');
            helper(n, curr, open + 1, close);
            curr.pop_back();  // backtrack
        }

        // Try to add ')' if it won't make the string invalid
        if (close < open) {
            curr.push_back(')');
            helper(n, curr, open, close + 1);
            curr.pop_back();  // backtrack
        }
    }

    vector<string> generateParenthesis(int n) {
        string curr = "";
        helper(n, curr);
        return res;
    }
};
