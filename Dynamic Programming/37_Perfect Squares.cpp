class Solution {
public:
    int dfs(int num){
        if(num == 0)
            return 0;
        int res = INT_MAX;
        for(int i=1; i*i <= num; i++ ){
            res = min(res, 1 + dfs(num - (i*i)));
        }

        return res;
    }
    int numSquares(int n) {
        return dfs(n);
    }
};

/*
==================== REVISION BLOCK — Perfect Squares (LeetCode 279) ====================

Problem
-------
Given an integer n, return the minimum number of perfect square numbers whose sum is n.

Pattern/ Idea
-------------
Unbounded Coin Change on the set of perfect squares ≤ n.
State f(x): minimum number of squares to form x.
Transition: f(x) = 1 + min_{s ∈ Squares, s ≤ x} f(x - s).

Algorithm (step-by-step)
------------------------
1) Generate all squares s = i*i ≤ n (implicit in your loop).
2) Recursive relation: for each square s ≤ num, try taking it once and solve subproblem (num - s).
3) Answer is f(n). 
   (Your code does this via DFS; adding memoization or bottom-up DP makes it O(n√n).)

Correctness (sketch)
--------------------
Any optimal decomposition of x into squares starts with some square s and then optimally
decomposes the remainder x - s. Taking the minimum over all valid s yields the optimal count.

Complexity
---------
Current code (plain DFS): exponential due to repeated subproblems.
With memoization / bottom-up DP: Time ≈ O(n√n), Space ≈ O(n).

Edge Cases / Pitfalls
---------------------
- n = 0 → 0.
- Without memoization, large n will TLE.
- Precomputing squares or bounding i*i ≤ num is crucial.

Optimization if needed
----------------------
- Add memoization: cache f(num).
- Bottom-up DP: dp[x] = 1 + min(dp[x - s]) over squares s ≤ x.
- BFS over remainders (levels = number of squares) also works in O(n) average.
========================================================
*/

class Solution {
public:
    // Exponential DFS without memoization (will TLE for large n).
    int dfs(int num){
        if (num == 0)
            return 0;                    // Base: zero needs zero squares

        int res = INT_MAX;
        // Try every square s = i*i <= num
        for (int i = 1; i * i <= num; i++ ){
            // Choose square i*i once, then solve the rest (num - i*i)
            res = min(res, 1 + dfs(num - (i * i)));
        }
        return res;                       // Minimum count among all choices
    }

    int numSquares(int n) {
        return dfs(n);
    }
};


/*
-----------------------------------------
Optional: Memoized Top-Down (O(n√n))
-----------------------------------------
class Solution {
public:
    int dfs(int x, vector<int>& memo){
        if (x == 0) return 0;
        int& ans = memo[x];
        if (ans != -1) return ans;
        ans = INT_MAX;
        for (int i = 1; i*i <= x; ++i)
            ans = min(ans, 1 + dfs(x - i*i, memo));
        return ans;
    }
    int numSquares(int n){
        vector<int> memo(n+1, -1);
        return dfs(n, memo);
    }
};

*/


class Solution {
public:
    int numSquares(int n) {
        if( n == 1) return 1;
        vector<int>dp(n+1, INT_MAX);
        dp[0] = 0;
        for(int num=1; num<=n; num++){
            for(int x=1; x*x <= num; x++){
                dp[num] = min(dp[num], 1 + dp[num - x*x]); 
            }
        }

        return dp[n];
    }
};

/*
==================== REVISION BLOCK — Perfect Squares (LeetCode 279) ====================

Problem
-------
Given an integer n, return the minimum number of perfect square numbers whose sum is n.

Pattern/ Idea
-------------
Bottom-up DP (unbounded coin change over square numbers).
Let dp[x] = minimum squares needed to sum to x.
Transition:
  dp[x] = 1 + min_{i >= 1, i*i <= x} dp[x - i*i]

Algorithm (step-by-step)
------------------------
1) Initialize dp[0] = 0, and dp[1..n] = +∞ (INT_MAX).
2) For x from 1..n:
   - For every square s = i*i ≤ x:
       dp[x] = min(dp[x], 1 + dp[x - s]).
3) Answer is dp[n].

Correctness (sketch)
--------------------
Any optimal decomposition of x ends with taking some square s and optimally decomposing (x - s).
Minimizing over all s ensures optimality. Bottom-up fills smaller targets before larger ones.

Complexity
---------
Time: O(n * √n) — for each x, try all squares up to √x.
Space: O(n)

Edge Cases / Pitfalls
---------------------
- n = 0 → 0; n = 1 → 1.
- Use INT_MAX as sentinel; always add to a valid dp[x - s] (initialized base guarantees this).
- Optional micro-opts: precompute squares ≤ n; early break if dp[x] becomes 1.

Optimization if needed
----------------------
- Precompute vector<int> squares.
- BFS on remainders (levels = answer).
- Theoretical: result ≤ 4 (Lagrange); check 1/2/3-square cases for pruning.
========================================================
*/

class Solution {
public:
    int numSquares(int n) {
        if (n == 1) return 1;

        // dp[x] = minimum number of perfect squares to sum to x
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        // Fill dp bottom-up
        for (int num = 1; num <= n; num++) {
            // Try all squares i*i not exceeding 'num'
            for (int i = 1; i * i <= num; i++) {
                int s = i * i;
                // Take one square 's' and add best for the remainder
                dp[num] = min(dp[num], 1 + dp[num - s]);
            }
        }

        return dp[n];
    }
};

