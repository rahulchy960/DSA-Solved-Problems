class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while(left<right){
            int mid = left + (right-left)/2;
            if(nums[mid]<nums[right])
                right = mid;
            else
                left=mid+1;

        }
        return nums[right];
    }
};

/*
==================== REVISION BLOCK — LeetCode 153: Find Minimum in Rotated Sorted Array ====================

Problem
-------
Given a rotated sorted array of DISTINCT integers, find the minimum element.
The array was originally sorted in ascending order and then rotated.
You must solve it in O(log n).

Pattern/ Idea
-------------
Binary Search on a rotated sorted array.
Key insight: Compare nums[mid] with nums[right] to decide where the minimum lies.
The minimum always lies in the **unsorted half** (or at mid itself).

Algorithm (step-by-step)
------------------------
1) Initialize left = 0, right = n-1.
2) While left < right:
   a) mid = left + (right-left)/2
   b) If nums[mid] < nums[right]:
        - The range [mid..right] is sorted
        - Minimum lies in [left..mid], so set right = mid
      Else:
        - Minimum lies in (mid..right], so set left = mid + 1
3) When loop ends, left == right and points to the minimum element.
4) Return nums[left] (or nums[right], same index).

Correctness (sketch)
--------------------
At every iteration:
- If nums[mid] < nums[right], the right half is sorted, so the pivot (minimum)
  cannot be after mid; it must be at mid or to the left.
- Otherwise, the pivot must lie strictly to the right of mid.
Thus, the algorithm always keeps the minimum within [left..right] and shrinks
the interval until a single index remains, which must be the minimum.

Complexity
---------
Time: O(log n)
Space: O(1)

Edge Cases / Pitfalls
---------------------
- Array not rotated (already sorted): nums[mid] < nums[right] always true,
  right keeps moving left, and answer becomes nums[0].
- Single element array.
- Works only for DISTINCT elements (this is LeetCode 153).
  With duplicates, logic needs modification (LeetCode 154).

Optimization if needed
----------------------
Already optimal for the given constraints.
For duplicate elements, add handling when nums[mid] == nums[right].

========================================================
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = (int)nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2; // avoid overflow

            // If mid element is smaller than right,
            // minimum lies in [left..mid]
            if (nums[mid] < nums[right])
                right = mid;
            else
                // minimum lies in (mid..right]
                left = mid + 1;
        }

        // left == right, pointing to minimum element
        return nums[right];
    }
};
