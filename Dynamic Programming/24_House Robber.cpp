class Solution {
public:
    int dp(vector<int>& nums, int n){
        if(n==1) return nums[n-1];
        if(n==2) return max(nums[n-1], nums[n-2]);
        return max(dp(nums, n-1), dp(nums, n-2) + nums[n-1]);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        return dp(nums, n);
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return nums[0];
        if(n==2) return max(nums[0], nums[1]);
        vector<int>dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i=2;i<n;i++){
            int looted = dp[i-2] + nums[i];
            int notLooted = dp[i-1];
            dp[i] = max(looted, notLooted);
        }
        return dp[n-1];
    }
};

/*
==================== REVISION BLOCK — House Robber (LC 198) ====================

Problem
-------
Given non-negative integers nums[i] (money in each house along a street), compute the
maximum amount you can rob without robbing two adjacent houses.

DP Recurrence (1-based for clarity)
-----------------------------------
Let f(n) = best we can do using the first n houses (indices 0..n-1).
Choice at the last house (n-1):
- Skip it  → f(n-1)
- Take it  → nums[n-1] + f(n-2)
So:
    f(n) = max( f(n-1), f(n-2) + nums[n-1] )
Base:
    f(0) = 0
    f(1) = nums[0]

Why your original TLEs
----------------------
Plain recursion recomputes the same subproblems exponentially many times (O(2^n)).
Add memoization or use bottom-up to make it O(n).

Complexity (with memo)
----------------------
Time: O(n)  — each n is solved once.
Space: O(n) — memo array + recursion stack.

========================================================
*/

class Solution {
public:
    int rob(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> memo(n + 1, -1);

        // f(k): best using first k houses (indices 0..k-1)
        std::function<int(int)> dp = [&](int k) -> int {
            if (k <= 0) return 0;
            if (k == 1) return nums[0];
            int &ans = memo[k];
            if (ans != -1) return ans;
            return ans = std::max(dp(k - 1), dp(k - 2) + nums[k - 1]);
        };

        return dp(n);
    }
};



/*
==================== REVISION BLOCK — House Robber (iterative DP) ====================

Problem
-------
Maximize the sum of non-adjacent values in `nums` (can't rob two neighboring houses).

State & Recurrence (1-based over prefixes)
------------------------------------------
Let f[i] = best we can do using first i houses (indices 0..i-1):
- Skip i-th house:   f[i-1]
- Take i-th house:   nums[i] + f[i-2]
So:
    f[i] = max(f[i-1], f[i-2] + nums[i])
Base:
    f[0] = 0, f[1] = nums[0]

Your bottom-up table is correct. Two notes:
- The recursive `dp(...)` at the top is unused and exponential; you can drop it.
- Inside `rob`, naming the vector `dp` shadows the member function `dp(...)`. Prefer a different name.

Complexity
----------
Time: O(n)
Space: O(n) with the table; can be optimized to O(1).

Below: (A) your table version (renamed), (B) O(1) space version.
*/

class Solution {
public:
    // (A) Tabulation with O(n) space (same logic as your code, with clearer names)
    int rob(std::vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        if (n == 2) return std::max(nums[0], nums[1]);

        std::vector<int> f(n, 0);
        f[0] = nums[0];
        f[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i <= n; ++i) {
            int take = f[i - 2] + nums[i];
            int skip = f[i - 1];
            f[i] = std::max(take, skip);
        }
        return f[n-1];
    }
};

/* (B) O(1) space rolling variables:

int rob(std::vector<int>& nums) {
    int prev2 = 0;          // f[i-2]
    int prev1 = 0;          // f[i-1]
    for (int x : nums) {
        int cur = std::max(prev1, prev2 + x); // f[i]
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

*/
