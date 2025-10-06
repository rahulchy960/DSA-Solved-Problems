class Solution {
public:
    bool dfs(vector<int>& nums, int n, int target){
        if(n == 0)
            return false;
        if(target == 0) 
            return true;
        
        int taken = false;
        if(nums[n-1] <= target){
            taken = dfs(nums, n-1, target-nums[n-1]);
        }
        int notTaken = dfs(nums, n-1, target);

        if(taken || notTaken)
            return true;
        return false;
    }
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return false;
        int sum = 0;
        for(int i=0;i<n;i++)
            sum += nums[i];
        if(sum % 2 == 1)
            return false;
        
        return dfs(nums, n, sum/2);
    }
};

/*
==================== REVISION BLOCK — Partition Equal Subset Sum (LeetCode 416) ====================

Problem
-------
Given an array nums, decide if it can be partitioned into two subsets with equal sum.

Pattern/ Idea
-------------
Reduce to **subset-sum**: target = total_sum / 2 (must be integer).  
We need to know if there exists a subset of nums that sums to target.  
Your code uses **DFS** (choose/not-choose each element) to search for target.

Algorithm (step-by-step)
------------------------
1) Compute S = sum(nums). If S is odd → return false. Set target = S/2.
2) DFS(n, target):
   - If target == 0 → return true (we formed the subset).
   - If n == 0 → return false (no items left and target > 0).
   - Option A (take): if nums[n-1] ≤ target, recurse on DFS(n-1, target - nums[n-1]).
   - Option B (skip): recurse on DFS(n-1, target).
   - Return take || skip.
3) Start with DFS(n, target).

Correctness (sketch)
--------------------
The subset-sum formulation is equivalent to equal-partition.  
DFS explores all 2^n include/exclude decisions. If any path reaches target == 0,
a subset with sum target exists, which implies the other subset also sums to target.

Complexity
---------
Current DFS: Exponential in worst case (overlapping subproblems).  
Optimized (memoized or bottom-up DP): O(n * target) time, O(target) or O(n*target) space.

Edge Cases / Pitfalls
---------------------
- Single element → false unless value is 0 (not in constraints typically).
- Early parity check (sum odd) saves work.
- DFS needs memoization to avoid TLE on larger inputs.

Optimization if needed
----------------------
- Top-down memo: dp[n][target] with tri-state (-1/0/1) or unordered_map key.
- Bottom-up 1D DP over sum: `possible[t] |= possible[t - x]` iterating t downwards.
========================================================
*/

class Solution {
public:
    // DFS without memoization (may TLE on large inputs)
    bool dfs(vector<int>& nums, int n, int target){
        if (target == 0) return true;     // formed required subset
        if (n == 0)       return false;   // no items left

        bool take = false;
        if (nums[n-1] <= target) {
            take = dfs(nums, n-1, target - nums[n-1]); // include current
        }
        bool skip = dfs(nums, n-1, target);            // exclude current
        return take || skip;
    }

    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return false;

        int sum = 0;
        for (int x : nums) sum += x;
        if (sum & 1) return false;        // odd total cannot be split equally

        return dfs(nums, n, sum / 2);
    }
};


/*
-----------------------------------------
Optional: Fast 1D Bottom-Up DP (O(n*target))
-----------------------------------------

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int target = sum / 2;

        vector<char> can(target + 1, 0);
        can[0] = 1;
        for (int x : nums) {
            for (int t = target; t >= x; --t) {
                if (can[t - x]) can[t] = 1;
            }
        }
        return can[target];
    }
};

-----------------------------------------
Optional: Top-Down Memoized DFS (O(n*target))
-----------------------------------------

class Solution {
public:
    bool dfs(int i, int target, const vector<int>& a, vector<vector<char>>& memo){
        if (target == 0) return true;
        if (i == 0)      return false;
        char& m = memo[i][target];
        if (m != -1) return m;

        bool res = dfs(i-1, target, a, memo);
        if (!res && a[i-1] <= target) {
            res = dfs(i-1, target - a[i-1], a, memo);
        }
        return m = (res ? 1 : 0);
    }

    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) return false;
        int target = sum / 2;
        vector<vector<char>> memo(nums.size() + 1, vector<char>(target + 1, -1));
        return dfs(nums.size(), target, nums, memo);
    }
};
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return false;
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += nums[i];
        if (sum % 2 == 1)
            return false;

        int target = sum/2;
        vector<vector<bool>>dp(target+1, vector<bool>(n+1, false));
        for(int j=0;j<=n;j++)
            dp[0][j] = true;

        for(int sum=1; sum<=target; sum++){
            for(int j=1;j<=n;j++){
                bool taken = false;
                bool notTaken = dp[sum][j-1];

                if(nums[j-1] <= sum)
                    taken = dp[sum - nums[j-1]][j-1];
                else 
                    notTaken = dp[sum][j-1];
                
                dp[sum][j] = taken || notTaken;
                
            }
        }

        return dp[target][n];
    }
};


/*
==================== REVISION BLOCK — Partition Equal Subset Sum (LeetCode 416) ====================

Problem
-------
Given an array `nums`, determine whether it can be split into two subsets with equal sum.

Pattern/ Idea
-------------
Reduce to **subset-sum**: target = (total sum) / 2 (must be even).
Use DP where dp[s][j] = true iff using the **first j elements** we can make sum **s**.
Transition:
dp[s][j] = dp[s][j-1]  ||  (s >= nums[j-1] && dp[s - nums[j-1]][j-1])

Algorithm (step-by-step)
------------------------
1) Compute total sum S. If S is odd → return false. Set target = S/2.
2) Create a (target+1) x (n+1) boolean table `dp`, initialize:
   - dp[0][j] = true for all j (sum 0 is always possible by taking nothing).
3) For s = 1..target:
     For j = 1..n:
        - notTaken = dp[s][j-1]
        - taken    = (nums[j-1] <= s) ? dp[s - nums[j-1]][j-1] : false
        - dp[s][j] = taken || notTaken
4) Return dp[target][n].

Correctness (sketch)
--------------------
By induction over (s, j): a sum `s` with first `j` items is achievable either
without item j (dp[s][j-1]) or by taking item j if we could make `s - nums[j-1]`
with the first `j-1` items. The base row (s=0) is true, establishing the induction.

Complexity
---------
Time: O(n * target)  
Space: O(n * target)  (can be optimized to O(target) with a 1D array scanning `s` downward)

Edge Cases / Pitfalls
---------------------
- Single element → false unless it’s 0.
- Watch variable shadowing if you reuse the name `sum` for loop indices.
- Early parity check (sum odd) avoids unnecessary DP.

Optimization if needed
----------------------
Use 1D DP: `can[s] |= can[s - x]` iterating `s` from target down to `x` for each `x` in nums.
========================================================
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 1)
            return false;

        // Compute total sum
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += nums[i];

        // If sum is odd, cannot split into two equal halves
        if (sum % 2 == 1)
            return false;

        int target = sum / 2;

        // dp[s][j] = can we form sum 's' using first 'j' numbers?
        vector<vector<bool>> dp(target + 1, vector<bool>(n + 1, false));

        // Sum 0 is always achievable (take nothing)
        for (int j = 0; j <= n; j++)
            dp[0][j] = true;

        // Fill DP table
        // NOTE: the inner variable named 'sum' below shadows the outer total 'sum' (harmless but be mindful)
        for (int sum = 1; sum <= target; sum++) {          // 'sum' here is the running target s
            for (int j = 1; j <= n; j++) {
                bool taken = false;

                // Option 1: don't take nums[j-1]
                bool notTaken = dp[sum][j - 1];

                // Option 2: take nums[j-1] if it fits
                if (nums[j - 1] <= sum)
                    taken = dp[sum - nums[j - 1]][j - 1];

                // Achievable if either path works
                dp[sum][j] = taken || notTaken;
            }
        }

        return dp[target][n];
    }
};
