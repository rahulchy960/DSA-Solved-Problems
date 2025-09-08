class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        for(int i=1;i<height.size()-1;i++){
            int lmax = 0;
            int rmax = 0;
            for(int j=0;j<i;j++)
                lmax = max(lmax, height[j]);
            for(int k = i+1;k<height.size();k++)
                rmax = max(rmax, height[k]);
            
            res += max(0, min(rmax, lmax) - height[i]);
        }
        return res;
    }
};

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n <= 2) return 0;
        int res = 0;
        int lmax = height[0];
        int rmax = height[n-1];
        int left = 1;
        int right = n-2;
        while(left <= right){
            if(lmax <= rmax){
                res += max(0, lmax - height[left]);
                lmax = max(lmax, height[left]);
                left++;
            } else {
                res += max(0, rmax - height[right]);
                rmax = max(rmax, height[right]);
                right--;
            }
        } 

        return res;
    }
};


/*
==================== REVISION BLOCK — Trapping Rain Water (Two Pointers, O(n), O(1)) ====================

Problem
-------
Given non-negative bar heights, compute how much water is trapped after raining.

Core Insight
------------
The water above position i is:  min(maxLeft[i], maxRight[i]) - height[i], if positive.
We can compute this without extra arrays by keeping:
- lmax: maximum to the left of the current left pointer,
- rmax: maximum to the right of the current right pointer.

Greedy Invariant
----------------
At each step, whichever side has the smaller boundary (lmax vs rmax) limits the water level
on that side. So:
- If lmax <= rmax, the water at `left` is fixed by lmax → process `left`, then move left++.
- Else, the water at `right` is fixed by rmax → process `right`, then move right--.

Algorithm (step-by-step)
------------------------
1) Initialize lmax = height[0], rmax = height[n-1], left = 1, right = n-2, res = 0.
2) While left <= right:
   - If lmax <= rmax:
       res += max(0, lmax - height[left]);
       lmax = max(lmax, height[left]);
       ++left;
     Else:
       res += max(0, rmax - height[right]);
       rmax = max(rmax, height[right]);
       --right;
3) Return res.

Correctness (sketch)
--------------------
When lmax <= rmax, the right boundary can only be ≥ lmax, so the limiting level for `left`
is exactly lmax; thus we can safely finalize water at `left`. Symmetric reasoning for the right side.

Complexity
----------
- Time: O(n) single pass.
- Space: O(1) extra.

Edge cases
----------
- n <= 2 → 0 (cannot trap water).
- Plateaus/flat areas handled naturally.
- If values could be very large, consider `long long` for `res`.

========================================================
*/

class Solution {
public:
    int trap(std::vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;

        int res = 0;
        int lmax = height[0];
        int rmax = height[n - 1];
        int left = 1, right = n - 2;

        while (left <= right) {
            if (lmax <= rmax) {
                // lmax is the limiting boundary on the left side
                res += std::max(0, lmax - height[left]);
                lmax = std::max(lmax, height[left]);
                ++left;
            } else {
                // rmax is the limiting boundary on the right side
                res += std::max(0, rmax - height[right]);
                rmax = std::max(rmax, height[right]);
                --right;
            }
        }
        return res;
    }
};
