class Solution {
  public:
    int helper(int W, vector<int> &val, vector<int> &wt, int n){
        if(n==0 || W==0)
            return 0;
        if(wt[n-1] > W)
            return helper(W, val, wt, n-1);
        else{
            int taken = val[n-1] + helper(W-wt[n-1], val, wt, n-1);
            int notTaken = helper(W,val, wt, n-1);
            return max(taken, notTaken);
        }
    }
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        // code here
        return helper(W, val, wt, val.size());
        
    }
};

int knapsack(int W, vector<int> &val, vector<int> &wt) {
        
        int n = wt.size();
        vector<vector<int>>dp(n+1, vector<int>(W+1));
        for(int i=0;i<=n;i++) dp[i][0] = 0;
        for(int j=0;j<=W;j++) dp[0][j] = 0;
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=W;j++){
                if(wt[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else{
                    int taken = val[i-1] + dp[i-1][j-wt[i-1]];
                    int notTaken = dp[i-1][j];
                    dp[i][j] = max(taken, notTaken);
                }
            }
        }
        return dp[n][W];
        
    }

/*
==================== REVISION BLOCK ====================

Problem (0/1 Knapsack — maximize value under weight limit):
- You have n items; item i has value val[i] and weight wt[i].
- Capacity W. Choose a subset (each item at most once) to maximize total value without exceeding W.

Pattern:
- 0/1 choice recursion (try both: take or skip), solving f(n, W) = best using first n items and capacity W.

State & Meaning:
- helper(W, val, wt, n) = maximum value achievable using items [0..n-1] within capacity W.

Intuition:
- At item (n-1): if it’s heavier than W → you can’t take it → skip.
- Otherwise, best = max(
    take it  : val[n-1] + f(W - wt[n-1], n-1),
    skip it  : f(W, n-1)
  ).

Algorithm (this code):
1) Base: if n == 0 or W == 0 → 0 (no items or no capacity).
2) If wt[n-1] > W → return f(W, n-1) (cannot take).
3) Else:
   - taken    = val[n-1] + f(W - wt[n-1], n-1)
   - notTaken = f(W, n-1)
   - return max(taken, notTaken).
4) Answer = helper(W, val, wt, val.size()).

Correctness (sketch):
- Exhaustive over the 0/1 decision at each item; by induction, each sub-call returns an optimal value for its subproblem; the max picks the better branch.

Complexity (of THIS pure recursion):
- Time: O(2^n) in worst case (each item branches take/skip; heavy overlap).
- Space: O(n) recursion depth (call stack).

Edge Cases / Pitfalls:
- W == 0 or n == 0 → 0.
- Items heavier than W get skipped automatically.
- Ensure val.size() == wt.size() in calling code (assumed by problem).

Note:
- Memoization/Tabulation reduces to O(n*W) time, O(n*W) space (or O(W) space with 1D DP).

Small Dry Run:
- W=5, val=[60,100,120], wt=[1,2,3]
  Optimal: items (1,2) with weight 5 → value 220.

========================================================
*/

class Solution {
  public:
    // f(n, W): best value using items [0..n-1] within capacity W
    int helper(int W, vector<int> &val, vector<int> &wt, int n){
        // Base cases: no items or no capacity -> 0 value
        if(n==0 || W==0)
            return 0;

        // If the nth item is too heavy, we cannot take it -> skip to n-1
        if(wt[n-1] > W)
            return helper(W, val, wt, n-1);

        // Otherwise, try both choices:
        // 1) take item (n-1): add its value and reduce capacity
        int taken = val[n-1] + helper(W - wt[n-1], val, wt, n-1);
        // 2) do not take item (n-1)
        int notTaken = helper(W, val, wt, n-1);

        // Return the better of the two choices
        return max(taken, notTaken);
    }

    // Wrapper: returns maximum value achievable within capacity W
    int knapsack(int W, vector<int> &val, vector<int> &wt) {
        // Time: O(2^n), Space: O(n) (recursion depth)
        return helper(W, val, wt, val.size());
    }
};


/*
==================== REVISION BLOCK ====================

Problem (0/1 Knapsack — maximize value under capacity):
- n items; item i has value val[i] and weight wt[i].
- Capacity W. Pick each item at most once to maximize total value without exceeding W.

Pattern:
- Dynamic Programming (tabulation, 2D).
- Think: "best value using first i items within capacity j".

State:
- dp[i][j] = maximum value achievable using items [0..i-1] with capacity j.

Transitions:
- If wt[i-1] > j → cannot take item i-1:
    dp[i][j] = dp[i-1][j]
- Else (can take or skip):
    dp[i][j] = max(
        val[i-1] + dp[i-1][j - wt[i-1]],   // take item i-1 (use previous row)
        dp[i-1][j]                          // skip item i-1
    )

Initialization:
- dp[0][*] = 0 (0 items → 0 value)
- dp[*][0] = 0 (capacity 0 → 0 value)
  (Created vector initializes to 0; we start loops from 1 so base row/col stay 0.)

Answer:
- dp[n][W].

Complexity:
- Time: O(n * W) — each cell computed once.
- Space: O(n * W) — 2D table.
  (Can optimize to O(W) with a 1D array iterating j from W down to wt[i-1].)

Edge notes:
- Assumes val.size() == wt.size() == n.
- We use 1-based DP indexing in the table; items are 0-based in arrays.

========================================================
*/

int knapsack(int W, vector<int> &val, vector<int> &wt) {
    int n = wt.size();

    // dp[i][j] = best value using first i items within capacity j
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for(int i=0;i<=n;i++) dp[i][0] = 0;
    for(int j=0;j<=W;j++) dp[0][j] = 0;

    // Build table bottom-up
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (wt[i - 1] > j) {
                // Current item too heavy -> must skip
                dp[i][j] = dp[i - 1][j];
            } else {
                // Take or skip the current item, choose better value
                int taken    = val[i - 1] + dp[i - 1][j - wt[i - 1]];
                int notTaken = dp[i - 1][j];
                dp[i][j] = max(taken, notTaken);
            }
        }
    }
    return dp[n][W];
}
