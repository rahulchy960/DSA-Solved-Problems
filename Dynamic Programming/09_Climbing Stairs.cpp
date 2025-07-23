class Solution {
public:
    int climbStairs(int n) {

    // Base cases: If there are 0 or 1 stairs,
    // there is only one way to reach the top.
    if (n == 0 || n == 1)
        return 1;

    return countWays(n - 1) + countWays(n - 2);

    }
    int climbStairs(int n) {
        int dp[n+1];
        dp[0] = 1;
        dp[1] = 1;
        for(int i=2;i<=n;i++)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};



// Algorithm: Climbing Stairs (Fibonacci DP Problem)
// --------------------------------------------------
// Problem:
//   - You are climbing a staircase with `n` steps.
//   - You can climb either 1 or 2 steps at a time.
//   - Find the number of distinct ways to reach the top.
//
// --------------------------------------------------
// ✅ Recursive Solution (Inefficient)
// --------------------------------------------------
//   - Idea: From step `n`, you can come from step `n-1` or `n-2`.
//   - So total ways to reach step `n`: countWays(n-1) + countWays(n-2)
//
// Time Complexity: O(2^n) → exponential (overlapping subproblems)
// Space Complexity: O(n) → recursion stack

/*
int countWays(int n) {
    if (n == 0 || n == 1) return 1;
    return countWays(n - 1) + countWays(n - 2);
}

int climbStairs(int n) {
    return countWays(n);
}
*/

// --------------------------------------------------
// ✅ Bottom-Up DP (Tabulation)
// --------------------------------------------------
// Approach:
//   - dp[i] = number of ways to reach i-th step
//   - dp[0] = 1 (1 way to stand at ground step)
//   - dp[1] = 1 (1 way to take 1 step)
//   - dp[i] = dp[i-1] + dp[i-2] for i ≥ 2
//
// Time Complexity: O(n)
// Space Complexity: O(n)

