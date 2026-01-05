class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int low = 0;
        int high = arr.size() - 1;
        while(low < high){
            int mid = low + (high - low) / 2;
            if(arr[mid] < arr[mid+1])
                low = mid + 1;
            else
                high = mid;
        }
        return high;
    }
};


/*
==================== REVISION BLOCK — LeetCode 852: Peak Index in a Mountain Array ====================

Problem
-------
Given a mountain array arr (strictly increasing then strictly decreasing),
return the index of the peak element.
The peak element is greater than its neighbors.

Pattern/ Idea
-------------
Binary Search on a mountain (unimodal array).
Key insight: Compare arr[mid] with arr[mid+1] to determine whether we are on
the increasing slope or the decreasing slope of the mountain.

Algorithm (step-by-step)
------------------------
1) Initialize low = 0, high = n-1.
2) While low < high:
   a) mid = low + (high-low)/2
   b) If arr[mid] < arr[mid+1]:
        - We are on the increasing slope
        - Peak lies to the right
        - Set low = mid + 1
      Else:
        - We are on the decreasing slope or at the peak
        - Peak lies to the left or at mid
        - Set high = mid
3) When loop ends, low == high and points to the peak index.
4) Return low (or high, same value).

Correctness (sketch)
--------------------
Because the array is strictly increasing up to the peak and strictly
decreasing after:
- If arr[mid] < arr[mid+1], mid lies on the increasing side, so the peak
  must exist in [mid+1..high].
- Otherwise, mid lies on the decreasing side or is the peak, so the peak
  must exist in [low..mid].
The algorithm maintains the invariant that the peak index is always within
[low..high], shrinking the interval until one index remains, which must be
the peak.

Complexity
---------
Time: O(log n)
Space: O(1)

Edge Cases / Pitfalls
---------------------
- Valid mountain array guarantees a peak (length ≥ 3).
- Peak is never at index 0 or n-1 (problem guarantee).
- Accessing arr[mid+1] is safe because low < high ensures mid < high.

Optimization if needed
----------------------
Already optimal.
This is the best possible solution under the constraints.

========================================================
*/
