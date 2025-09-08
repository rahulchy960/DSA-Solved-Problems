class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int maxOnes = 0;
        int ocount = 0;
        int zcount = 0;
        int left = 0;
        int n = nums.size();
        for(int i=0;i<n;i++){
            if(nums[i] == 1)
                ocount++;
            if(nums[i]==0)
                zcount++;
            if(zcount<=k){
                maxOnes = max(maxOnes, ocount+zcount);
            } else {
                if(nums[left] == 1) ocount--;
                else zcount--;
                left++;
            }

        }
        return maxOnes;
        
    }
};




/*
==================== REVISION BLOCK — Max Consecutive Ones III (sliding window) ====================

Problem
-------
Given a binary array nums and an integer k, return the length of the longest subarray
that contains at most k zeros (we may "flip" up to k zeros).

Core idea (two-pointer window)
------------------------------
Maintain a window [left..right] that contains **≤ k zeros**.
- Expand `right` each step and count zeros.
- If zeros exceed k, **shrink `left` in a while-loop** until the window is valid again.
- Track the best window length as we go.

Why your code missed cases
--------------------------
You shrank the window by **only one** step when zeros > k (an `if`), then moved `right`
to the next index. If the window still had > k zeros, you’d skip updating the answer
for that `right` and never revisit the same `right` after enough shrinks.  
Fix: use a **while (zcount > k)** loop to fully restore the invariant before updating `ans`.

Complexity
----------
Time: O(n) — each index enters/leaves the window at most once.  
Space: O(1).

========================================================
*/

class Solution {
public:
    int longestOnes(std::vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, zcount = 0, ans = 0;

        for (int right = 0; right < n; ++right) {
            if (nums[right] == 0) ++zcount;

            // shrink until window has at most k zeros
            while (zcount > k) {
                if (nums[left] == 0) --zcount;
                ++left;
            }

            // window [left..right] is valid here
            ans = std::max(ans, right - left + 1);
        }
        return ans;
    }
};
