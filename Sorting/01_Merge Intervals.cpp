class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        int n = intervals.size();
        int window = 0;
        for(int i=1;i<n;i++){
            if(intervals[window][1] >= intervals[i][0]){
                intervals[window][0] = min(intervals[window][0],intervals[i][0]);
                intervals[window][1] = max(intervals[window][1],intervals[i][1]);
            }
            else{
                window++;
                swap(intervals[window] , intervals[i]);
            }
        }
        for(int i = 1; i< (n - window);i++)
            intervals.pop_back();
        
        return intervals;
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Merge Intervals):
- Given a list of intervals [l, r], merge all overlapping intervals and return the merged list.

Pattern:
- Sort by start, then sweep once, merging into a growing output.

Intuition:
- After sorting, any overlap for the current interval can only happen with the **last** merged interval.
- Keep a write pointer `window` to the tail of the merged list-in-place:
  * If current interval overlaps the last merged one → merge by expanding [L..R].
  * Else → start a new merged block by advancing `window` and placing current there.

Algorithm:
1) Sort intervals by start (and end as tiebreaker).
2) Set `window = 0` — the index of the last merged interval.
3) For i from 1..n-1:
   - If intervals[window].end ≥ intervals[i].start → merge:
       intervals[window].start = min(...)
       intervals[window].end   = max(...)
   - Else:
       window++ and swap intervals[window] with intervals[i] (place new block next).
4) Remove the trailing, now-unused elements (keep first `window+1` intervals).
5) Return intervals.

Correctness (sketch):
- Sorting ensures any interval that can overlap a block appears immediately after it in the sweep.
- We always merge with the latest merged block, so no overlaps are missed.

Complexity:
- Time: O(n log n) for sorting + O(n) sweep → O(n log n).
- Space: O(1) extra (in-place; ignoring sort’s internal stack).

Edge cases:
- Empty input → return empty.
- Single interval → unchanged.
- Touching endpoints: consider overlapping if intervals[window][1] ≥ intervals[i][0] (as in code).

========================================================
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());   // sort by start, then end
        int n = intervals.size();
        int window = 0;                              // last merged interval's index

        for (int i = 1; i < n; i++) {
            // Overlap: current starts before/at the last merged end → merge into window
            if (intervals[window][1] >= intervals[i][0]) {
                intervals[window][0] = min(intervals[window][0], intervals[i][0]);
                intervals[window][1] = max(intervals[window][1], intervals[i][1]);
            } else {
                // Disjoint: advance window and place current interval there
                window++;
                swap(intervals[window], intervals[i]);
            }
        }

        // Keep only the merged prefix [0..window]; pop the rest
        for (int i = 1; i < (n - window); i++)
            intervals.pop_back();
        // (Equivalently: intervals.resize(window + 1);)

        return intervals;
    }
};
