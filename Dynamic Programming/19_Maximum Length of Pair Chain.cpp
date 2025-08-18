class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end());
        int n = pairs.size();
        vector<int>dp(n,1);
        dp[0]=1;
        for(int i=1;i<pairs.size();i++){
            for(int j=0;j<i;j++){
                if(pairs[j][1]<pairs[i][0])
                    dp[i] = max(dp[i], dp[j]+1);
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Maximum Length of Pair Chain / LC 646):
- You have pairs [a, b]. One pair (a, b) can follow another (c, d) only if b < c.
- Find the longest possible chain length.

Pattern:
- Sort + DP (O(n^2)) over “last pair chosen”.

Intuition:
- After sorting pairs, let dp[i] be the longest chain that ends at pair i.
- To end at i, we may append pair i after any j < i with pairs[j].second < pairs[i].first.
- Take the best among all such j and add 1 for pair i itself.

Algorithm:
1) Sort pairs (lexicographic by default: first, then second).
2) dp[i] = 1 for all i (chain with only pair i).
3) For i = 1..n-1:
     For j = 0..i-1:
       If pairs[j][1] < pairs[i][0]:
         dp[i] = max(dp[i], dp[j] + 1)
4) Answer = max over dp[i].

Correctness (sketch):
- dp[i] examines all valid predecessors j of i and picks the best chain ending at i.
- Taking maximum over endpoints yields the optimal chain length.

Complexity:
- Sorting: O(n log n). DP: O(n^2). Overall: O(n^2) time, O(n) extra space.

Notes:
- Strict inequality (<) matches the problem’s requirement (b < c).
- There is an optimal **greedy** solution: sort by second element and pick earliest finishing pairs,
  which runs in O(n log n) time and O(1) space. This DP is clear but slower.

========================================================
*/

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        std::sort(pairs.begin(), pairs.end());    // sort to impose an order for DP

        int n = pairs.size();
        std::vector<int> dp(n, 0);
        dp[0] = 1;                                // base: chain ending at 0 has length 1

        for (int i = 1; i < n; i++) {
            dp[i] = 1;                            // at least the pair itself
            for (int j = 0; j < i; j++) {
                // Can pair j be followed by pair i? (strictly non-overlapping)
                if (pairs[j][1] < pairs[i][0]) {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }
        return *std::max_element(dp.begin(), dp.end()); // best chain among all endpoints
    }
};
