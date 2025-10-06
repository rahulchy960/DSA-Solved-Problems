class Solution {
  public:
    int mChain(vector<int> &arr, int i, int j){
        if(i+1 == j) return 0;
        int res = INT_MAX;
        for(int k=i+1; k<j; k++){
            int cost = mChain(arr, i, k) + mChain(arr, k, j) + (arr[i]* arr[k]* arr[j]);
            res = min(res, cost);
        }
        return res;
    }
  
    int matrixMultiplication(vector<int> &arr) {
        // code here
        int n = arr.size();
        if(n <= 2) return 0;
        return mChain(arr, 0, n-1);
    }
};

//---------------------------------------------------------------------------------------------------------------

int memoChain(vector<int>& a, int i, int j, vector<vector<int>>& dp){  //  Memoized Top-Down O(n^3)
    if (i + 1 == j) 
        return 0;
    if (dp[i][j] != -1) 
        return ans;

    dp[i][j] = INT_MAX;
    for (int k = i + 1; k < j; ++k) {
        dp[i][j] = min(dp[i][j], memoChain(a,i,k,dp) + memoChain(a,k,j,dp) + a[i]*a[k]*a[j]);
    }
    return ans;
}

int matrixMultiplication(vector<int>& arr){
    int n = arr.size();
    if (n <= 2) return 0;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return memoChain(arr, 0, n-1, dp);
}

//---------------------------------------------------------------------------------------------------------------

class Solution {   //  Tabulized Buttom-Up O(n^3)
  public:
    int matrixMultiplication(vector<int> &arr) {
        // code here
        int n = arr.size();
        if(n <= 2) return 0;
  
        vector<vector<int>>dp(n, vector<int>(n, 0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i+1 == j)
                    dp[i][j] = 0;
            }
        }
        
        for(int bracketLen = 2; bracketLen<n; bracketLen++){
            for(int i=0; i + bracketLen < n; i++){
                int j = i + bracketLen;
                dp[i][j] = INT_MAX;
                for(int k = i+1; k < j; k++){
                    int cost = dp[i][k] + dp[k][j] + arr[i]*arr[k]*arr[j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        return dp[0][n-1];
    }
};

/*
==================== REVISION BLOCK — Matrix Chain Multiplication (GFG) ====================

Problem
-------
Given an array arr of length n where the i-th matrix has dimensions arr[i-1] x arr[i],
compute the minimum number of scalar multiplications to multiply the chain of (n-1) matrices.

Pattern/ Idea
-------------
Optimal Substructure with interval DP.
If we place the last split at k between matrices (i..k) and (k+1..j),
the total cost is:
    cost(i,j,k) = cost(i,k) + cost(k+1,j) + arr[i-1] * arr[k] * arr[j]
Take the minimum over all k in [i..j-1].

Algorithm (step-by-step)
------------------------
1) Define f(i,j) = minimum cost to multiply matrices i..j (1-indexed over matrices).
2) Base: f(i,i) = 0 (single matrix needs no multiplication).
3) Recurrence: f(i,j) = min over k∈[i..j-1] of
       f(i,k) + f(k+1,j) + arr[i-1]*arr[k]*arr[j].
4) Answer: f(1, n-1). 
(Note: In this implementation, indices are adapted to a helper using arr indices [i..j] with the base i+1==j.)

Correctness (sketch)
--------------------
Any optimal parenthesization must make a final split at some k.
Both subchains must themselves be optimally parenthesized (otherwise we could improve the total),
and the multiplication cost of the resulting two matrices is fixed by their dimensions.
Thus minimizing over k yields the global optimum (induction on interval length).

Complexity
---------
Current code (pure recursion):
- Time: Exponential (recomputes overlapping subproblems).
- Space: O(n) recursion depth.

Edge Cases / Pitfalls
---------------------
- n ≤ 2 → no multiplication needed (0).
- Integer overflow is unlikely with typical constraints, but beware very large dimensions.
- Exponential recursion will TLE; memoization/tabulation is preferred in practice.

Optimization if needed
----------------------
- Memoization: O(n^2) states, each tries O(n) splits → O(n^3) time, O(n^2) space.
- Bottom-up DP over increasing chain length with the same O(n^3)/O(n^2) bounds.
========================================================
*/

class Solution {
  public:
    // Helper for recursion over the dimension array `arr`.
    // Interpretation: matrices correspond to intervals between indices.
    // Base: if there is no matrix between i and j (i+1==j), cost is 0.
    int mChain(vector<int> &arr, int i, int j){
        if (i + 1 == j) return 0;  // only one matrix -> no multiplication cost

        int res = INT_MAX;
        // Try placing the final split at every k between i and j
        for (int k = i + 1; k < j; k++) {
            // Cost = left chain + right chain + cost to multiply the two results
            int cost = mChain(arr, i, k)
                     + mChain(arr, k, j)
                     + (arr[i] * arr[k] * arr[j]);
            res = min(res, cost);
        }
        return res;
    }

    int matrixMultiplication(vector<int> &arr) {
        int n = arr.size();     // arr length is number of dims; matrices = n-1
        if (n <= 2) return 0;   // 0 or 1 matrix -> no cost
        // We call with endpoints around the entire dimension range.
        // This computes optimal cost for matrices 1..n-1 (inclusive).
        return mChain(arr, 0, n - 1);
    }
};


/*
==================== REVISION BLOCK — Matrix Chain Multiplication (GFG) ====================

Problem
-------
Given dimensions arr[0..n-1] where matrix i has size arr[i-1] × arr[i],
find the minimum number of scalar multiplications to multiply the entire chain (matrices 1..n-1).

Pattern/ Idea
-------------
Interval DP (optimal substructure over parenthesizations).
Let dp[i][j] = minimum cost to multiply the matrices whose overall dimension span is arr[i]..arr[j].
A final split at k (i < k < j) partitions the chain into (i..k) and (k..j) and adds
the cost to multiply the two results: arr[i] * arr[k] * arr[j].

Algorithm (step-by-step)
------------------------
1) Base: For any adjacent pair (i, i+1) there is only one matrix — cost 0 ⇒ dp[i][i+1] = 0.
2) Expand interval length L from 2 to n-1 (i.e., j = i + L):
     dp[i][j] = min over k∈(i..j-1): dp[i][k] + dp[k][j] + arr[i]*arr[k]*arr[j]
3) Answer is dp[0][n-1].

Correctness (sketch)
--------------------
Any optimal parenthesization makes a last split at some k. The two subchains must themselves
be optimally parenthesized (by optimal substructure), and the multiplication of the two
resulting matrices has fixed cost arr[i]*arr[k]*arr[j]. Taking the minimum over k yields the optimum.

Complexity
---------
Time: O(n^3) — O(n^2) states × O(n) splits
Space: O(n^2)

Edge Cases / Pitfalls
---------------------
- n ≤ 2 → 0 (no multiplication).
- Indexing: dp is over dimension indices (0..n-1), matrices are 1..n-1.
- Beware overflow with very large arr values (use long long if needed).
========================================================
*/

class Solution {
  public:
    int matrixMultiplication(vector<int> &arr) {
        int n = arr.size();
        if (n <= 2) return 0; // 0 or 1 matrix => no cost

        // dp[i][j] = minimum cost to multiply chain spanning dimensions arr[i]..arr[j]
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base: dp[i][i+1] = 0 already (single matrix). Explicit fill optional:
        for (int i = 0; i + 1 < n; ++i) dp[i][i+1] = 0;

        // bracketLen = j - i, start from length 2 (at least two matrices) up to n-1
        for (int bracketLen = 2; bracketLen < n; ++bracketLen) {
            for (int i = 0; i + bracketLen < n; ++i) {
                int j = i + bracketLen;
                dp[i][j] = INT_MAX;

                // Try all possible split points k between i and j
                for (int k = i + 1; k < j; ++k) {
                    // Cost = left + right + cost to multiply the two resulting matrices
                    int cost = dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

        // Minimum cost to multiply the entire chain (matrices 1..n-1)
        return dp[0][n - 1];
    }
};

