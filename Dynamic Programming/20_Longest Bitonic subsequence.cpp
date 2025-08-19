
class Solution {
  public:
    int LongestBitonicSequence(int n, vector<int> &nums) {
        if(n<3) return 0;  // If there are less than 3 elements, no bitonic subsequence exists
        // code here
        vector<int>lis(n,1);
        vector<int>lds(n,1);
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i])
                    lis[i] = max(lis[i], lis[j]+1);
            }
        }
        for(int i=n-2;i>=0;i--){
            for(int j=n-1;j>i;j--){
                if(nums[j]<nums[i])
                    lds[i] = max(lds[i], lds[j]+1);
            }
        }
        int res = 0;
        for(int i=0;i<n;i++)
            if (lis[i] > 1 && lds[i] > 1) // valid lis and lds
                res = max(res, lis[i] + lds[i] -1);
        return res;
    }
};





/*
==================== REVISION BLOCK (Longest Bitonic Subsequence) ====================

Problem
-------
Given an array nums of length n, find the length of the **longest bitonic subsequence** (LBS).
A bitonic subsequence first **strictly increases** and then **strictly decreases**.
(Here we require both parts to exist — i.e., peak is not at an end.)

Core Idea
---------
Compute, for every index i:
- lis[i] = length of the **Longest Increasing Subsequence** ending at i (strictly increasing).
- lds[i] = length of the **Longest Decreasing Subsequence** starting at i (strictly decreasing).

Then any bitonic subsequence that peaks at i has length: lis[i] + lds[i] - 1.
We take the maximum over i, but only if both sides exist (lis[i] > 1 and lds[i] > 1).

Why it works (Invariant/Correctness)
------------------------------------
- lis[i] summarizes the best increasing “left part” that ends exactly at i.
- lds[i] summarizes the best decreasing “right part” that starts exactly at i.
- Combining them at i counts the peak twice; subtract 1.
- Requiring lis[i] > 1 and lds[i] > 1 enforces a real “up then down” shape.

Algorithm (O(n^2))
------------------
1) Initialize lis[i] = 1 and lds[i] = 1 for all i (a single element subsequence).
2) For i from left to right:
     For j in [0..i-1]:
       if nums[j] < nums[i] → lis[i] = max(lis[i], lis[j] + 1)
3) For i from right to left:
     For j in [n-1..i+1]:
       if nums[j] < nums[i] → lds[i] = max(lds[i], lds[j] + 1)
4) For each i, if lis[i] > 1 and lds[i] > 1, update ans = max(ans, lis[i] + lds[i] - 1).

Complexity
----------
Time : O(n^2) (two nested loops for LIS and two for LDS, but each pair (i,j) checked once per phase)
Space: O(n)   (two arrays lis and lds)

Edge Notes / Variants
---------------------
- If n < 3, a strict “up then down” sequence cannot exist → return 0 (as implemented).
- Some judges allow a purely increasing or purely decreasing subsequence to be “bitonic”.
  If so, remove the (lis[i] > 1 && lds[i] > 1) check and the early `n<3` return,
  and just take max over lis[i] + lds[i] - 1.
- Duplicates: comparisons are strict (<) to ensure **strict** increase/decrease.

Optimization Hint (for later)
-----------------------------
You can compute lis/lds in O(n log n) **overall LIS length**, but to get **per-index**
lis[i]/lds[i] efficiently you typically need coordinate compression + Fenwick/Segment Tree
to query best dp over values < nums[i] (left-to-right and right-to-left), yielding O(n log U).

Tiny Dry Run
------------
nums = [1, 4, 3, 2] 
lis = [1, 2, 2, 2]
lds = [1, 3, 2, 1]  // from right: at 4 → 4>3>2
At i=1 (value 4): lis=2, lds=3 → bitonic length = 2+3-1=4 (1,4,3,2)

======================================================================================
*/

class Solution {
  public:
    int LongestBitonicSequence(int n, std::vector<int> &nums) {
        if (n < 3) return 0;  // strict bitonic requires at least 3 elements

        std::vector<int> lis(n, 1), lds(n, 1);

        // LIS ending at i (strictly increasing)
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    lis[i] = std::max(lis[i], lis[j] + 1);
                }
            }
        }

        // LDS starting at i (strictly decreasing)
        for (int i = n - 2; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (nums[j] < nums[i]) {
                    lds[i] = std::max(lds[i], lds[j] + 1);
                }
            }
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (lis[i] > 1 && lds[i] > 1) {                 // enforce up-then-down shape
                res = std::max(res, lis[i] + lds[i] - 1);
            }
        }
        return res;
    }
};
