class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int currMax = 1, currMin = 1;
        int res = nums[0];
        for(int i=0; i<n; i++){
            int temp = currMax*nums[i];
            currMax = max(nums[i], max(currMax*nums[i], currMin*nums[i]));
            currMin = min(nums[i], min(temp, currMin*nums[i]));
            res = max(currMax, res);

        }
        return res;
    }
};

/*
==================== REVISION BLOCK — Maximum Product Subarray (LeetCode 152) ====================

Problem
-------
Given an integer array `nums`, find the contiguous subarray (containing at least one number) 
which has the largest product and return the product.

Pattern/ Idea
-------------
Dynamic Programming (Kadane-like) with tracking both maximum and minimum product values 
because a negative number can flip the product sign.

Algorithm (step-by-step)
------------------------
1. Initialize `currMax` and `currMin` as 1 to track running maximum and minimum product.
2. Initialize result `res` with the first element (base case).
3. Iterate through each element in `nums`:
   - Store temporary product of `currMax * nums[i]` before updating.
   - Update `currMax` as the maximum of:
        - current number,
        - product with previous `currMax`,
        - product with previous `currMin`.
   - Update `currMin` as the minimum of:
        - current number,
        - product with previous `currMax` (saved as temp),
        - product with previous `currMin`.
   - Update result `res` as the maximum of itself and `currMax`.
4. Return `res`.

Correctness (sketch)
--------------------
By tracking both max and min products at each step, we correctly account for the effect 
of negative numbers: multiplying two negatives can yield a larger positive product. 
This guarantees the optimal subarray product is always captured.

Complexity
----------
Time: O(n) — single pass through the array.  
Space: O(1) — only constant extra variables are used.

Edge Cases / Pitfalls
---------------------
- Single-element arrays (must handle correctly since `res` starts at nums[0]).
- Arrays with all negatives.
- Zeros in the array — correctly handled since `currMax` and `currMin` reset with current number.

Optimization if needed
----------------------
This approach is already optimal (linear time and constant space).
========================================================
*/

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();            // Size of the array
        int currMax = 1, currMin = 1;   // Track current max and min products
        int res = nums[0];              // Initialize result with the first element

        for(int i = 0; i < n; i++) {
            int temp = currMax * nums[i];   // Save product before updating currMax

            // Update current maximum product
            currMax = max(nums[i], max(currMax * nums[i], currMin * nums[i]));

            // Update current minimum product (important for negative numbers)
            currMin = min(nums[i], min(temp, currMin * nums[i]));

            // Update result if needed
            res = max(currMax, res);
        }

        return res;   // Return maximum product subarray value
    }
};
