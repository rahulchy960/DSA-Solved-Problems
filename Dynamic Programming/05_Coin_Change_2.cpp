

// Algorithm: Coin Change II (Recursive - Count Total Combinations)
// -----------------------------------------------------------------
// Problem:
//   - Given coins of different denominations and a total amount,
//     return the number of combinations that make up that amount.
//   - Unlimited supply of each coin is allowed (each coin can be reused).
//
// Approach (Recursion):
//   - At each recursive step, you can either:
//       1. Exclude the current coin → move to n-1
//       2. Include the current coin → subtract coin value from amount, keep same index
//   - Base Cases:
//       - If amount == 0 → 1 valid way to make change
//       - If no coins left (n == 0) → 0 ways to form a positive amount
//
// Time Complexity: O(2^n) (Exponential)
//   - Each coin can either be taken or not taken at every level.
//
// Space Complexity: O(amount) for recursion stack (in worst case)
//
// ⚠️ Note: This solution will TLE for large inputs. Use DP or memoization to optimize.


class Solution {
public:
    int helper(int amount, vector<int>& coins, int n){
        if(amount == 0) return 1;
        if(n == 0) return 0;
        int notTaken = helper(amount, coins, n-1);
        int taken = 0;
        if(coins[n-1]<=amount){
            taken = helper(amount-coins[n-1], coins, n);
        }
        return taken + notTaken;
    }
    int change(int amount, vector<int>& coins) {
        return helper(amount, coins, coins.size());
    }
};


class Solution {
public:
   
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>>dp(amount+1, vector<int>(n+1));
        for(int i=0;i<=n;i++)dp[0][i] = 1;
        for(int i=1;i<=amount;i++) dp[i][0] = 0;

        for(int i=1;i<=amount;i++){
            for(int j=1;j<=n;j++){
                long long notTaken = dp[i][j-1];
                long long taken = 0; 
                if(coins[j-1]<=i)
                    taken = dp[i][j] + dp[i-coins[j-1]][j];  
                
                dp[i][j] = taken + notTaken;
            }
        }
        return dp[amount][n];
    }
};


// Algorithm: Coin Change II (Bottom-Up DP - Count Total Combinations)
// --------------------------------------------------------------------
// Problem:
//   - Given an amount and an array of coin denominations,
//     return the number of combinations that sum up to the given amount.
//   - Unlimited supply of each coin is allowed.
//   - Order of coins in combinations does NOT matter.
//
// Approach (Tabulation):
//   - Let dp[i][j] = number of ways to make amount i using the first j coins.
//   - Dimensions: (amount + 1) × (n + 1), where n = number of coins.
//
// Base Cases:
//   - dp[0][j] = 1 → 1 way to make amount 0 (by taking no coins)
//   - dp[i][0] = 0 for i > 0 → can't make positive amount with 0 coins
//
// Transition:
//   - For each dp[i][j]:
//       - notTaken = dp[i][j-1] (exclude current coin)
//       - taken = dp[i - coins[j-1]][j] if coins[j-1] ≤ i (include coin again)
//       - dp[i][j] = taken + notTaken
//
// Time Complexity: O(n × amount)
//   - Nested loops over amount and coins
//
// Space Complexity: O(n × amount)
//   - 2D DP table

