class Solution {
public:
    int numTrees(int n) {
        vector<int>dp(n+1, 0);
        dp[0] = 1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<i;j++){
                dp[i] += dp[j]*dp[i-1-j];
            }
        }
        return dp[n];
    }
};

/*
==================== REVISION BLOCK — Unique Binary Search Trees (LeetCode 96) ====================

Problem
-------
Given an integer `n`, return the number of structurally unique BSTs (binary search trees) 
that store values 1 ... n.

Pattern/ Idea
-------------
Dynamic Programming with **Catalan Numbers**.
The number of unique BSTs for `n` nodes follows the nth Catalan number.

Algorithm (step-by-step)
------------------------
1. Create a DP array `dp` of size `n+1`, initialized with 0.
2. Base case: `dp[0] = 1` (empty tree is one valid structure).
3. For each `i` from 1 to n:
   - Iterate `j` from 0 to i-1.
   - For each `j`, consider `j` nodes as the left subtree and `i-1-j` as the right subtree.
   - Add the product `dp[j] * dp[i-1-j]` to `dp[i]`.
4. Final result is `dp[n]`.

Correctness (sketch)
--------------------
Each node `k` chosen as root partitions the tree into left and right subtrees of sizes 
`j` and `i-1-j`. The total number of unique trees for `i` nodes is the sum over 
all possible partitions, which is exactly how Catalan numbers are defined.

Complexity
----------
Time: O(n^2) — double loop (for each i up to n, inner loop up to i).  
Space: O(n) — dp array of size n+1.

Edge Cases / Pitfalls
---------------------
- n = 0 → returns 1 (empty tree is valid).
- Large n may cause integer overflow if not handled with larger integer type.

Optimization if needed
----------------------
- Use the direct Catalan number formula with binomial coefficients for O(n) 
  or even O(1) with precomputation. formula: (1/n+1) * 2nCn
========================================================
*/

class Solution {
public:
    int numTrees(int n) {
        // dp[i] will store the number of unique BSTs with i nodes
        vector<int> dp(n+1, 0);

        dp[0] = 1; // Base case: empty tree
        
        // Compute dp[i] for all i from 1 to n
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < i; j++) {
                // Choose j nodes for left subtree and (i-1-j) for right subtree
                dp[i] += dp[j] * dp[i-1-j];
            }
        }

        return dp[n]; // Final answer: number of unique BSTs with n nodes
    }
};
