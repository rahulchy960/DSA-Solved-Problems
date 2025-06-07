#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0 || k == 0) return 0;

        // If k >= n/2, we can perform unlimited transactions
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                maxProfit += abs(prices[i] - prices[i - 1]);
            }
            return maxProfit;
        }

        // dp[t][d] = max profit at day d with at most t transactions
        vector<vector<int>> dp(k + 1, vector<int>(n, 0));

        for (int t = 1; t <= k; ++t) {
            // These track the max values for normal and short transactions
            int maxNormal = -prices[0];
            int maxShort = prices[0];
            for (int d = 1; d < n; ++d) {
                // Max of:
                // - No transaction at day d
                // - Sell today after buying earlier (normal)
                // - Buy back today after short-selling earlier
                dp[t][d] = max({
                    dp[t][d - 1],                         // No trade
                    prices[d] + maxNormal,               // Normal buy-sell
                    maxShort - prices[d]                 // Short-sell then buy back
                });

                // Update maxNormal and maxShort
                maxNormal = max(maxNormal, dp[t - 1][d - 1] - prices[d]);
                maxShort = max(maxShort, dp[t - 1][d - 1] + prices[d]);
            }
        }

        return dp[k][n - 1];
    }
};
