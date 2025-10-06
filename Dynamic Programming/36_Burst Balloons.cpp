class Solution {
public:
    int dfs(vector<int>& nums, int i, int j){
        if(i+1==j)
            return 0;
        int res = INT_MIN;
        for(int k=i+1;k<j;k++){
            int cost = dfs(nums, i, k) + dfs(nums, k, j) + nums[i]*nums[k]*nums[j];
            res = max(res, cost);
        }
        return res;
    }
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int>newNum(n+2, 1);
        int i=1;
        for(int j=0;j<n;j++){
            newNum[i++] = nums[j];
        }
        return dfs(newNum, 0, n+2-1);
    }
};

// ----------------------------------------------------------------------------------------------------------

class Solution {  // Top-Down Memorized O(n^3)
public:
    int dfs(vector<int>& nums, int i, int j, vector<vector<int>>& memo) {
        if (i + 1 == j) return 0; 
        if (memo[i][j] != -1) return memo[i][j];
        
        int res = 0;
        for (int k = i + 1; k < j; k++) {
            int cost = dfs(nums, i, k, memo) + dfs(nums, k, j, memo) + nums[i] * nums[k] * nums[j];
            res = max(res, cost);
        }
        memo[i][j] = res;

        return memo[i][j];
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> newNum(n + 2, 1);
        for (int i = 0; i < n; i++) newNum[i + 1] = nums[i];

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
        return dfs(newNum, 0, n + 1, dp);
    }
};

// ----------------------------------------------------------------------------------------------------------

class Solution {
public:
   
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int>newNums(n+2, 1);
        int i=1;
        for(int j=0;j<n;j++){
            newNums[i++] = nums[j];
        }

        n = n+2;
        vector<vector<int>>dp(n, vector<int>(n, 0));

        for(int chainLen=2; chainLen < n; chainLen++){
            for(int i=0; i+chainLen < n; i++){
                int j = i + chainLen;
                dp[i][j] = INT_MIN;

                for(int k=i+1;k<j;k++){
                    int cost = dp[i][k] + dp[k][j] + newNums[i]*newNums[k]*newNums[j];
                    dp[i][j] = max(dp[i][j], cost);
                }
            }
        }

        return dp[0][n-1]; 
    }
};




/*
==================== REVISION BLOCK — Burst Balloons (LeetCode 312) ====================

Problem
-------
Given an array nums where bursting the i-th balloon yields coins
nums[left] * nums[i] * nums[right] with neighbors shrinking after each burst,
return the maximum coins obtainable.

Pattern/ Idea
-------------
Interval DP (choose the **last** balloon to burst in an interval).
Pad the array with 1 at both ends: val = [1, nums..., 1].
Let f(i,j) be the max coins from bursting balloons strictly between i and j.
If k is the last balloon burst in (i, j), gain = f(i,k) + f(k,j) + val[i]*val[k]*val[j].
Take the maximum over k in (i, j).

Algorithm (step-by-step)
------------------------
1) Build val = [1] + nums + [1].
2) Define dfs(i, j): if i+1 == j → 0 (empty interval).
3) For each k in (i, j):
     best = max(best, dfs(i,k) + dfs(k,j) + val[i]*val[k]*val[j]).
4) Answer = dfs(0, n+1) where n = |nums|.

Correctness (sketch)
--------------------
Choosing the **last** balloon k isolates the interval: its neighbors are fixed
as i and j at that moment, so the immediate gain is val[i]*val[k]*val[j], and
subproblems (i,k) and (k,j) are independent and optimally solved.

Complexity
---------
As written (pure recursion): exponential.
With memoization/tabulation: O(n^3) time, O(n^2) space.

Edge Cases / Pitfalls
---------------------
- Always pad with 1 at both ends.
- Use memoization to avoid TLE; costs are non-negative so init with 0 is fine.

Optimization if needed
----------------------
Add dp[i][j] memo so each interval (i,j) is computed once, or do bottom-up over increasing gap.
========================================================
*/

class Solution {
public:
    // Recurrence over padded array `newNum` (with 1 at both ends).
    // dfs(i, j): max coins from bursting balloons strictly between i and j.
    int dfs(vector<int>& nums, int i, int j){
        if (i + 1 == j) return 0;           // empty interval -> no coins

        int res = INT_MIN;
        for (int k = i + 1; k < j; k++) {   // choose last balloon to burst in (i, j)
            int cost = dfs(nums, i, k)                  // left interval
                    + dfs(nums, k, j)                  // right interval
                    + nums[i] * nums[k] * nums[j];     // burst k last
            res = max(res, cost);
        }
        return res;
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        // Build padded array: [1, nums..., 1]
        vector<int> newNum(n + 2, 1);
        int i = 1;
        for (int j = 0; j < n; j++) newNum[i++] = nums[j];

        // Solve full interval (0, n+1)
        return dfs(newNum, 0, n + 2 - 1);
    }
};



/*
==================== REVISION BLOCK — Burst Balloons (LeetCode 312) ====================

Problem
-------
Given an array nums, when you burst balloon k you gain nums[left] * nums[k] * nums[right],
where left/right are the adjacent *unburst* balloons. Return the maximum coins possible.

Pattern/ Idea
-------------
Interval DP by choosing the **last** balloon to burst in each interval.
Pad with sentinels 1 at both ends: val = [1, nums..., 1].
Let dp[i][j] = max coins from bursting balloons strictly between indices i and j (i < j).
If we choose k as the last to burst in (i, j), then:
  dp[i][j] = max over k∈(i,j) of  dp[i][k] + dp[k][j] + val[i] * val[k] * val[j]

Algorithm (step-by-step)
------------------------
1) Build val = [1] + nums + [1]. Let N = val.size().
2) Initialize dp[N][N] = 0.
3) For interval length L from 2 to N-1:
     For i from 0 to N-L-1:
       j = i + L
       dp[i][j] = max over k in (i, j):
                    dp[i][k] + dp[k][j] + val[i]*val[k]*val[j]
4) Answer = dp[0][N-1].

Correctness (sketch)
--------------------
Consider the **last** burst in (i, j): its neighbors must be exactly i and j,
so the immediate gain is val[i]*val[k]*val[j], and subproblems (i,k) and (k,j)
are independent and optimally solved. Enumerating k yields the optimal value.

Complexity
---------
Time: O(N^3) where N = n + 2 (due to all (i,j,k) triples)
Space: O(N^2) for the DP table

Edge Cases / Pitfalls
---------------------
- Always pad with 1 at both ends.
- Values can be large; if needed, use 64-bit for safety.
========================================================
*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();

        // Build padded array: [1, nums..., 1]
        vector<int> newNums(n + 2, 1);
        int pos = 1;
        for (int x : nums) newNums[pos++] = x;

        // Work with N = n + 2 (including sentinels at 0 and N-1)
        int N = n + 2;
        // dp[i][j] = max coins from bursting balloons strictly between i and j
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // Iterate over increasing interval length (gap = j - i)
        for (int len = 2; len < N; ++len) {          // len >= 2 ensures room between i and j
            for (int i = 0; i + len < N; ++i) {
                int j = i + len;
                int best = INT_MIN;

                // Choose k as the last balloon to burst in (i, j)
                for (int k = i + 1; k < j; ++k) {
                    int cost = dp[i][k] + dp[k][j] + newNums[i] * newNums[k] * newNums[j];
                    best = max(best, cost);
                }
                dp[i][j] = best;
            }
        }

        return dp[0][N - 1]; // Full interval (0, N-1)
    }
};
