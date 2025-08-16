class Solution {

  public:
    int minDeletions(int arr[], int n) {
        // Your code goes here
        vector<int>dp(n,0);
        dp[0] = 1;
        for(int i=1;i<n;i++){
            dp[i] = 1;
            for(int j=0;j<i;j++){
                if(arr[j] < arr[i]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }
        int len = *max_element(dp.begin(),dp.end());
        return n - len;
    }
};



/*
==================== REVISION BLOCK ====================

Problem (Min deletions to make array strictly increasing):
- Given an array arr[0..n-1], remove the fewest elements so that the remaining
  elements are in strictly increasing order.
- Return that minimum number of deletions.

Key Fact:
- Minimum deletions = n − LIS_length,
  where LIS_length = length of the Longest Increasing Subsequence (strictly increasing).

Pattern:
- Dynamic Programming for LIS (O(n^2)).

State:
- dp[i] = length of the LIS that ends at index i (i.e., must include arr[i]).

Transition:
- dp[i] = 1 + max{ dp[j] | 0 ≤ j < i and arr[j] < arr[i] }, or 1 if no such j.

Algorithm:
1) Initialize dp[i] = 1 for all i (each element alone is an LIS of length 1).
2) For i = 1..n-1:
     For j = 0..i-1:
       If arr[j] < arr[i], dp[i] = max(dp[i], dp[j] + 1).
3) Let L = max_i dp[i]. Answer = n − L.

Correctness (sketch):
- By definition of LIS, dp[i] captures the best increasing subsequence ending at i.
- Taking the max over i gives the global LIS length.
- Removing everything not in an LIS yields the minimum deletions.

Complexity:
- Time: O(n^2) due to the nested loops.
- Space: O(n) for the dp array.

Notes / Pitfalls:
- Strictly increasing → use '<' (not '≤').
- If non-decreasing was required, use '≤' in the transition instead.
- There is an O(n log n) LIS method (patience sorting + binary search) to optimize time.

========================================================
*/

class Solution {
  public:
    int minDeletions(int arr[], int n) {
        // Compute LIS length via O(n^2) DP, then return n - LIS.
        std::vector<int> dp(n, 0);
        dp[0] = 1;

        for (int i = 1; i < n; i++) {
            dp[i] = 1; // each element alone
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }

        int lisLen = *std::max_element(dp.begin(), dp.end());
        return n - lisLen;
    }
};
