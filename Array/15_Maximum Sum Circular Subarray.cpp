class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int currMax = nums[0];
        int currMin = nums[0];
        int globalMax = nums[0];
        int globalMin = nums[0];
        int sum = nums[0];
        for(int i=1; i<nums.size(); i++){
            sum += nums[i];

            currMax = max(currMax + nums[i], nums[i]);
            currMin = min(currMin + nums[i], nums[i]);

            globalMax = max(globalMax, currMax);
            globalMin = min(globalMin, currMin);
        }

        if(globalMax < 0)  // edge case: all negetive element in array 
            return globalMax;
        
        return max(globalMax, sum - globalMin);
    }
};

/*
==================== REVISION BLOCK — Maximum Sum Circular Subarray (LeetCode 918) ====================

Problem
-------
Given a circular integer array nums, return the maximum possible sum of a non-empty subarray.

Pattern/ Idea
-------------
Two cases:
1) **Non-wrapping subarray** → standard Kadane’s max-subarray.
2) **Wrapping subarray** → take total sum minus the minimum (non-empty) subarray inside.
Answer = max( max_subarray_sum, total_sum - min_subarray_sum ).
But if all numbers are negative, the wrap formula becomes invalid (would pick empty),
so return the (negative) max element.

Algorithm (step-by-step)
------------------------
1) Initialize currMax = currMin = globalMax = globalMin = nums[0], and sum = nums[0].
2) For each element x from nums[1..]:
   - sum += x
   - currMax = max(x, currMax + x)         // Kadane for maximum
   - currMin = min(x, currMin + x)         // Kadane for minimum
   - globalMax = max(globalMax, currMax)
   - globalMin = min(globalMin, currMin)
3) If globalMax < 0 → all numbers are negative ⇒ return globalMax.
4) Else return max(globalMax, sum - globalMin).

Correctness (sketch)
--------------------
Any maximum circular subarray either doesn’t wrap (classic Kadane) or wraps once:
wrapping means we exclude a contiguous **minimum** subarray from the middle, hence total_sum - min_subarray.
The all-negative guard ensures we don’t choose an empty wrap (which would otherwise be larger).

Complexity
---------
Time: O(n)  — single pass
Space: O(1) — constant variables

Edge Cases / Pitfalls
---------------------
- All elements negative → must return the largest (least negative) element (handled by globalMax < 0).
- Single element array works naturally.
- Avoid using sum - globalMin when all-negative (would imply empty subarray).

Optimization if needed
----------------------
This is already optimal O(n)/O(1). Variants: run Kadane twice or compute in one pass (as below).
========================================================
*/

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int currMax = nums[0], currMin = nums[0];     // running best/worst ending here
        int globalMax = nums[0], globalMin = nums[0]; // best/worst over all prefixes
        int sum = nums[0];                            // total sum

        for (int i = 1; i < (int)nums.size(); i++) {
            sum += nums[i];

            // Kadane for maximum subarray
            currMax = max(nums[i], currMax + nums[i]);
            globalMax = max(globalMax, currMax);

            // Kadane for minimum subarray
            currMin = min(nums[i], currMin + nums[i]);
            globalMin = min(globalMin, currMin);
        }

        // If all numbers are negative, the wrap (sum - globalMin) would be zero/invalid.
        if (globalMax < 0) return globalMax;

        // Max of non-wrap and wrap cases
        return max(globalMax, sum - globalMin);
    }
};
