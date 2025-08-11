#include<bits/stdc++.h>
using namespace std;

int maxCuts(int n, int a, int b, int c){
    if(n<0) return -1;
    if(n==0) return 0;
    int res = max(maxCuts(n-a,a,b,c), max(maxCuts(n-b,a,b,c), maxCuts(n-c,a,b,c)));
    if(res != -1)
        return res+1;
    return res;
}

int maximizeTheCuts(int n, int a, int b, int c) {
        // Your code here
        vector<int>dp(n+1);
        dp[0] = 0;
        for(int i=1;i<=n;i++){
            dp[i] = -1;
            if(i-a>=0) dp[i] = max(dp[i], dp[i-a]);
            if(i-b>=0) dp[i] = max(dp[i], dp[i-b]);
            if(i-c>=0) dp[i] = max(dp[i], dp[i-c]);
            if(dp[i] != -1)
                dp[i] = dp[i] + 1;
        }
        return (dp[n] == -1)? 0: dp[n];
        
    }

int main(){
    int n=2;
    int a = 1;
    int b = 13;
    int c = 5;
    int res = maxCuts(n,a,b,c);
    cout<<res;
}


// Algorithm: Maximum Number of Cuts (Recursive)
// ----------------------------------------------
// Problem:
//   - Given a rope of length `n` and possible cut lengths a, b, c.
//   - You need to cut the rope in maximum number of segments,
//     where each segment must be either of length a, b, or c.
//   - Return the maximum number of segments or 0 if not possible.
//
// Approach (Pure Recursion):
//   - Base Case:
//       - If n == 0 → valid configuration → return 0 (no more cuts needed)
//       - If n < 0  → invalid configuration → return -1
//   - Recursive Case:
//       - Try all three cut options: n-a, n-b, n-c
//       - Take the maximum result among them
//       - If result is not -1, add 1 (for the current cut)
//
// Time Complexity: O(3^n) → exponential
//   - Each recursive call branches into 3 more
//
// Space Complexity: O(n) recursion stack depth
//
// ⚠️ Note: This approach is inefficient for large `n` and should be optimized using DP or memoization.

class Solution {
public:
    // Function to find the maximum number of cuts.
    int maximizeTheCuts(int n, int a, int b, int c) {
        if (n < 0) return -1;       // Invalid length
        if (n == 0) return 0;       // No more cuts needed (valid end)

        // Try all three cuts
        int res = max({
            maximizeTheCuts(n - a, a, b, c),
            maximizeTheCuts(n - b, a, b, c),
            maximizeTheCuts(n - c, a, b, c)
        });

        // If any valid result was found, count this cut
        return (res == -1) ? -1 : res + 1;
    }
};


// Algorithm: Maximum Number of Cuts (Bottom-Up Dynamic Programming)
// ------------------------------------------------------------------
// Problem:
//   - Given a rope of length `n` and three possible cut lengths `a`, `b`, and `c`,
//     return the **maximum number of cuts** that can be made such that every cut
//     is either of length a, b, or c.
//   - If it's not possible to cut the rope exactly into those sizes, return 0.
//
// Approach (Tabulation - Bottom-Up DP):
//   1. Create a DP array `dp[0...n]` where:
//        - dp[i] = maximum number of cuts that can be made for length `i`
//   2. Initialize:
//        - dp[0] = 0 (zero cuts needed for length 0)
//        - dp[i] = -1 (initially assume unreachable)
//
//   3. Iterate `i` from 1 to n:
//        - For each `i`, check if a cut of size a, b, or c is possible.
//        - If yes and dp[i - cut] is valid (not -1), update dp[i] = max(dp[i], dp[i - cut] + 1)
//
//   4. Final answer: if dp[n] == -1 → return 0 (not possible); else return dp[n]
//
// Time Complexity: O(n)
//   - We compute each dp[i] once, checking 3 cut options (a, b, c)
//
// Space Complexity: O(n)
//   - For storing the dp array

class Solution {
  public:
    int maximizeTheCuts(int n, int a, int b, int c) {
        vector<int> dp(n + 1, -1); // dp[i] = max cuts to make length i
        dp[0] = 0; // Base case: no cuts needed to make length 0

        for (int i = 1; i <= n; i++) {
            // Try each possible cut if it fits
            if (i - a >= 0 && dp[i - a] != -1)
                dp[i] = max(dp[i], dp[i - a]);

            if (i - b >= 0 && dp[i - b] != -1)
                dp[i] = max(dp[i], dp[i - b]);

            if (i - c >= 0 && dp[i - c] != -1)
                dp[i] = max(dp[i], dp[i - c]);

            // If a valid way exists to make i, increment the cut count
            if (dp[i] != -1)
                dp[i] += 1;
        }

        // Return result, or 0 if no valid cuts possible
        return (dp[n] == -1) ? 0 : dp[n];
    }
};
