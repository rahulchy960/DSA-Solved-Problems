class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        vector<bool>vis(n, 0);
        for(int i=0; i<n; i++){
            if(nums[i] > 0 && nums[i] <= n){
                vis[nums[i]-1] = true;
            }
        }

        for(int i=0;i<n;i++){
            if(vis[i] == 0)
                return i+1;
        }
        return n+1;
    }
};

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i=0; i<n; i++){
            while(nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i]){
                swap(nums[nums[i]-1], nums[i]);
            }
        }

        for(int i=0;i<n;i++){
            if(nums[i] != i+1)
                return i+1;
        }
        return n+1;
    }
};

/*
==================== REVISION BLOCK — LeetCode 41: First Missing Positive ====================

Problem
-------
Given an unsorted integer array nums, find the smallest missing positive integer.
Must run in O(n) time and use O(1) extra space.

Pattern/ Idea
-------------
In-place Hashing / Cyclic Placement.
Idea: For any value x in [1..n], its correct position is index (x-1).
Rearrange the array so that whenever possible, nums[i] == i+1.
Then the first index where this fails gives the answer.

Algorithm (step-by-step)
------------------------
1) Let n = nums.size().
2) For i from 0 to n-1:
   - While nums[i] is in range [1..n] AND nums[i] is not already at its correct position:
       swap nums[i] with nums[nums[i]-1]
   (This keeps moving the current number to its correct slot.)
3) After placement, scan i from 0 to n-1:
   - If nums[i] != i+1, return i+1 (smallest missing positive).
4) If all positions are correct, return n+1.

Correctness (sketch)
--------------------
- Any positive integer x in [1..n] can be placed at index x-1 via swapping.
- The while-condition ensures we keep swapping until either:
  a) nums[i] is out of range (irrelevant), or
  b) nums[i] is already correctly placed, or
  c) a duplicate blocks further progress (nums[nums[i]-1] == nums[i]).
- After the rearrangement, if a value k in [1..n] exists in the array, it will be at index k-1.
  Therefore, the first index i where nums[i] != i+1 implies (i+1) is missing.
- If all 1..n exist, the missing one must be n+1.

Complexity
---------
Time: O(n) amortized (each swap places at least one number into its final position)
Each swap permanently places at least one number into its correct position, 
so the total number of swaps across the entire algorithm is ≤ n.
Space: O(1) extra space (in-place)

Edge Cases / Pitfalls
---------------------
- Negatives, zeros, and values > n are ignored by range check.
- Duplicates: critical to check nums[nums[i]-1] != nums[i] to avoid infinite loops.
- Works even when array contains all 1..n -> answer n+1.

Optimization if needed
----------------------
Already optimal for the required constraints.

========================================================
*/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = (int)nums.size();

        // Place each number x (1..n) at index x-1 if possible
        for (int i = 0; i < n; i++) {
            // Keep swapping until nums[i] is either out of range,
            // or already in correct position, or a duplicate blocks it.
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]); // move nums[i] to its correct index
            }
        }

        // First index where nums[i] != i+1 gives the missing positive
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1)
                return i + 1;
        }

        // If 1..n are present, answer is n+1
        return n + 1;
    }
};
