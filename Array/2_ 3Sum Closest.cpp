class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int res = INT_MAX;
        int sum = 0;
        for(int i=0;i<nums.size();i++){
            int j = i+1;
            int k = nums.size()-1;
            while(j<k){
                int temp = nums[i] + nums[j] + nums[k];
                if(abs(temp  - target) < res){
                    res = abs(temp - target);
                    sum = temp;
                }
                else if(temp<target) j++;
                else k--;
            }
        }
        return sum;
    }
};





/*
==================== REVISION BLOCK ====================

Problem (3Sum Closest):
- Given an array nums and an integer target, find a triple (i<j<k) whose sum is
  closest to target. Return that sum.

Pattern:
- Sorting + Two Pointers (fixed-first element, sweep remaining with j,k).

Intuition:
- After sorting, for each fixed i, use a classic two-pointer walk (j=i+1, k=n-1):
  * If sum < target, increasing j may increase sum and get closer.
  * If sum > target, decreasing k may decrease sum and get closer.
  * Track the best (minimum absolute difference) and remember its sum.

Algorithm:
1) Sort nums.
2) Initialize:
   - res = +∞ (best absolute difference found so far),
   - bestSum = 0 (sum corresponding to res).
3) For i from 0..n-1:
   - Set j=i+1, k=n-1.
   - While j<k:
       temp = nums[i] + nums[j] + nums[k].
       If |temp - target| < res:
           res = |temp - target|; bestSum = temp.
       Else if temp < target: j++ (need larger sum).
       Else: k-- (need smaller sum).
4) Return bestSum.

Correctness (sketch):
- For fixed i, the sorted order makes the function sum(i,j,k) monotonic in j and k,
  so two pointers explore the optimal j,k for that i without missing the best.
- Taking the best over all i yields the global closest sum.

Complexity:
- Time: O(n log n) for sort + O(n^2) for the two-pointer sweep ⇒ O(n^2).
- Space: O(1) extra (in-place sort if allowed by the platform; otherwise O(log n) stack for sort impl).

Edge cases / notes:
- Duplicates are fine; no need to skip them for “closest”.
- If an exact match occurs (difference 0), we could early-return (not required here).
- Watch for integer overflow in temp if nums can be very large; typical constraints keep it safe.

========================================================
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end()); // sort to enable two-pointer monotonic moves

        int res = INT_MAX;  // best absolute difference seen so far
        int sum = 0;        // sum corresponding to 'res'

        for (int i = 0; i < nums.size(); i++) {     // fix the first element
            int j = i + 1;                          // left pointer
            int k = nums.size() - 1;                // right pointer

            while (j < k) {
                int temp = nums[i] + nums[j] + nums[k];

                // If this triple is closer to target, record it
                if (abs(temp - target) < res) {
                    res = abs(temp - target);
                    sum = temp;
                    // (Optional optimization: if res == 0) return sum;
                }
                // Move pointers to try to get closer to target:
                else if (temp < target) {
                    j++;   // need a larger sum -> move left pointer right
                } else {
                    k--;   // need a smaller sum -> move right pointer left
                }
            }
        }
        return sum; // best sum found
    }
};
