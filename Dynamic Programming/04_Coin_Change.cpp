// Algorithm: Coin Change (Recursive - Brute Force)
// ------------------------------------------------
// Problem:
//   - Given coins of different denominations and a total amount,
//     return the fewest number of coins needed to make up that amount.
//   - If it is not possible, return -1.
//
// Approach (Naive Recursion):
//   - For each coin, try to include it if it's ≤ amount.
//   - Recursively call on (amount - coin).
//   - Take the minimum number of coins needed among all choices.
//   - Base case: if amount == 0 → 0 coins needed
//   - If result from recursion is INT_MAX → skip it (invalid path)
//
// Time Complexity: O(2^amount)
//   - For each amount, we explore all combinations of coins recursively.
//   - Very slow due to overlapping subproblems.
//
// Space Complexity: O(amount) (recursion stack depth)
//

class Solution {
public:
    int helper(vector<int>& coins, int amount){
        if(amount == 0) return 0;
        int res = INT_MAX;
        for(int i=0;i<coins.size();i++){
            if(coins[i]<=amount){
                int taken = helper(coins, amount - coins[i]);
                
                if(taken != INT_MAX)
                    res = min(res, taken+1);
            }
           
        }
        return res;
    }
    int coinChange(vector<int>& coins, int amount) {
        int res = helper(coins, amount);
        return (res==INT_MAX) ? -1 : res;
    }
};



// Algorithm: Coin Change (Bottom-Up DP - Tabulation)
// ---------------------------------------------------
// Problem:
//   - Given coin denominations and a total amount,
//     find the minimum number of coins required to make up that amount.
//   - If it's not possible to form the amount, return -1.
//
// Approach (Tabulation):
//   1. Create a DP array `dp` of size (amount + 1) initialized to INT_MAX.
//       - dp[i] = minimum coins needed to make amount `i`
//   2. Set dp[0] = 0 → base case (0 coins needed for amount 0)
//   3. For each amount `i` from 1 to `amount`:
//       - For each coin:
//           - If coin ≤ i and dp[i - coin] is not INT_MAX:
//               → dp[i] = min(dp[i], dp[i - coin] + 1)
//
// Time Complexity: O(n × amount)
//   - n = number of coins
//   - amount = target amount
//
// Space Complexity: O(amount)
//   - 1D array of size (amount + 1)

class Solution {
public:
    int helper(vector<int>& coins, int amount){
        vector<int>dp(amount+1, INT_MAX);
        dp[0] = 0;
        for(int i=1;i<=amount;i++){
            for(int j=0;j<coins.size();j++){
                if(coins[j]<=i){
                    int taken = dp[i-coins[j]];
                    if(taken != INT_MAX)
                        dp[i] = min(dp[i], taken+1);
                }
            }
        }
        return dp[amount];
    }
    int coinChange(vector<int>& coins, int amount) {
        int res = helper(coins, amount);
        return (res==INT_MAX) ? -1 : res;
    }
};
