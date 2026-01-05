class Solution {
public:
    int search(vector<int>& nums, int target) {  
        int low = 0;
        int high = nums.size()-1;
        while(low<=high){
            int mid = low + (high - low)/2;
            if(nums[mid] == target)
                return mid;

            if(nums[low] <= nums[mid]){ 
                if(target < nums[mid] && target >= nums[low])
                    high = mid - 1;
                else
                    low = mid + 1;
            } else {
                if(target > nums[mid] && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1; 
            }


        }

        return -1;
    }
};

/*
==================== REVISION BLOCK — LeetCode 33: Search in Rotated Sorted Array ====================

Problem
-------
Given a rotated sorted array (distinct integers) and a target, return the index of target if found,
else return -1. Must run in O(log n).

Pattern/ Idea
-------------
Modified Binary Search on a rotated sorted array.
Key insight: At any mid, at least one half (low..mid or mid..high) is sorted.
Decide which half is sorted, then check if target lies in that sorted range to discard the other half.

Algorithm (step-by-step)
------------------------
1) Initialize low = 0, high = n-1.
2) While low <= high:
   a) mid = low + (high-low)/2
   b) If nums[mid] == target -> return mid
   c) If nums[low] <= nums[mid], left half [low..mid] is sorted:
        - If target in [nums[low], nums[mid]) -> high = mid-1
        - Else -> low = mid+1
      Else, right half [mid..high] is sorted:
        - If target in (nums[mid], nums[high]] -> low = mid+1
        - Else -> high = mid-1
3) If loop ends, return -1.

Correctness (sketch)
--------------------
At each iteration, we identify a sorted half:
- If left half is sorted, we can safely decide whether target lies within its bounds.
  If yes, target (if exists) must be in left half, so we discard right half; otherwise discard left half.
- Similarly for the right sorted half.
This preserves the invariant that if target exists, it remains in the current [low..high] range.
Each step shrinks the search space, so we eventually find target or exhaust the range.

Complexity
---------
Time: O(log n) (search space halves each iteration)
Space: O(1)

Edge Cases / Pitfalls
---------------------
- Array not rotated (already sorted) -> left-sorted check still works.
- Target at boundaries (low/high) -> handled by range checks.
- Single element array.
- Important: This logic assumes DISTINCT elements. With duplicates, nums[low] <= nums[mid] can be ambiguous.

Optimization if needed
----------------------
None needed for distinct elements.
For duplicates (variant problem), additional handling is required (e.g., shrinking bounds when equal).

========================================================
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = (int)nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // safe mid

            if (nums[mid] == target)
                return mid;

            // If left half [low..mid] is sorted
            if (nums[low] <= nums[mid]) {
                // Check if target lies in the sorted left half
                if (target < nums[mid] && target >= nums[low])
                    high = mid - 1;  // discard right half
                else
                    low = mid + 1;   // discard left half
            } 
            // Otherwise right half [mid..high] is sorted
            else {
                // Check if target lies in the sorted right half
                if (target > nums[mid] && target <= nums[high])
                    low = mid + 1;   // discard left half
                else
                    high = mid - 1;  // discard right half
            }
        }

        return -1; // not found
    }
};
