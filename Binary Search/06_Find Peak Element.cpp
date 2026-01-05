class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0;
        int high = nums.size()-1;
        while(low < high){
            int mid = low + (high - low)/2;
            if(nums[mid] < nums[mid+1])
                low = mid + 1;
            else
                high = mid;

        }
        return low; 
    }
};



/*
==================== REVISION BLOCK — LeetCode 162: Find Peak Element ====================

Problem
-------
Given an array nums, find a peak element and return its index.
A peak element is an element that is strictly greater than its neighbors.
You may assume nums[-1] = nums[n] = -∞.
You must solve it in O(log n).

Pattern/ Idea
-------------
Binary Search on the slope (gradient-based binary search).
Key insight: If nums[mid] < nums[mid+1], we are on an increasing slope,
so a peak must exist on the right side. Otherwise, a peak exists on the left
side (including mid).

Algorithm (step-by-step)
------------------------
1) Initialize low = 0, high = n-1.
2) While low < high:
   a) mid = low + (high-low)/2
   b) If nums[mid] < nums[mid+1]:
        - We are moving uphill
        - A peak must exist in [mid+1..high]
        - Set low = mid + 1
      Else:
        - We are on a downhill or peak
        - A peak exists in [low..mid]
        - Set high = mid
3) When loop ends, low == high and points to a peak element.
4) Return low.

Correctness (sketch)
--------------------
At each step, we compare adjacent elements:
- If nums[mid] < nums[mid+1], the sequence is rising, so a peak must appear
  to the right (either at mid+1 or later).
- Otherwise, the sequence is falling or mid itself is a peak, so a peak
  exists on the left side (including mid).
This guarantees that we never discard all peaks and always shrink the
search interval until one index remains, which must be a peak.

Complexity
---------
Time: O(log n)
Space: O(1)

Edge Cases / Pitfalls
---------------------
- Single element array (always a peak).
- Peak at index 0 or n-1 (handled by -∞ assumption).
- Do NOT use nums[mid-1]; comparing mid and mid+1 avoids boundary issues.

Optimization if needed
----------------------
Already optimal.
This approach is preferred over linear scan due to O(log n) complexity.

========================================================
*/



class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0;
        int high = (int)nums.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2; // safe mid

            // If next element is greater, peak lies on the right
            if (nums[mid] < nums[mid + 1])
                low = mid + 1;
            else
                // Peak lies on the left or at mid
                high = mid;
        }

        // low == high, pointing to a peak element
        return low;
    }
};
