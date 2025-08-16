class Solution {
  public:
    int maxSumIS(vector<int>& arr) {
        // Your code goes here
        int n = arr.size();
        vector<int>dp(n,0);
        dp[0] = arr[0];
        
        for(int i=1;i<n;i++){
            dp[i] = arr[i];
            for(int j=0;j<i;j++){
                if(arr[j] < arr[i]){
                    dp[i] = max(dp[i], dp[j] + arr[i]);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Maximum Sum Increasing Subsequence, MSIS):
- Given an array arr, pick a subsequence with strictly increasing values that maximizes the SUM of chosen elements.
- Return that maximum sum.

Pattern:
- Dynamic Programming over last index (classic O(n^2)).

State & Meaning:
- dp[i] = maximum sum of an increasing subsequence that **ends at index i** (must include arr[i]).

Transition:
- Initialize dp[i] = arr[i] (subsequence of length 1 ending at i).
- For each j < i with arr[j] < arr[i], we can extend j’s subsequence:
    dp[i] = max(dp[i], dp[j] + arr[i])

Answer:
- max_i dp[i]

Correctness (sketch):
- Base: dp[i] starts as single element arr[i].
- Induction: considering all valid predecessors j ensures dp[i] is the best among sequences ending at i.
- Taking the maximum over all endpoints returns the global optimal MSIS sum.

Complexity:
- Time: O(n^2) (nested loops i over j).
- Space: O(n) for dp.

Edge notes:
- Assumes n ≥ 1 (as in many platforms like GFG). If n==0, define answer 0.
- Strictly increasing: uses arr[j] < arr[i].

Optional optimizations:
- With coordinate compression + Fenwick/Segment Tree over values storing best sums, can achieve O(n log n).

Tiny dry run:
- arr=[1, 101, 2, 3, 100, 4, 5]
  MSIS = 1 + 2 + 3 + 100 = 106 (best), dp captures this by chaining increasing ends.

========================================================
*/

class Solution {
  public:
    int maxSumIS(vector<int>& arr) {
        int n = arr.size();
        std::vector<int> dp(n, 0);
        dp[0] = arr[0];                         // base: subsequence ending at 0 is just arr[0]

        for (int i = 1; i < n; i++) {
            dp[i] = arr[i];                     // start with the single-element subsequence
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {          // can extend an increasing subsequence ending at j
                    dp[i] = std::max(dp[i], dp[j] + arr[i]);
                }
            }
        }

        return *std::max_element(dp.begin(), dp.end()); // best sum among all endpoints
    }
};
