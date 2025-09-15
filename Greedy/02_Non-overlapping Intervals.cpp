bool myCmp(vector<int>&u, vector<int>&v){
        return u[1] < v[1];
}
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), myCmp);
        int count = 0;
        int end=0;
        for(int i=1;i<intervals.size();i++){
            if(intervals[end][1] > intervals[i][0]){
                count++;
            }
            else
                end=i;
                
        }
        return count;
    }
};

/*
==================== REVISION BLOCK — Non-overlapping Intervals (minimum removals) ====================

Problem
-------
Given a set of intervals [l, r), remove the **fewest** intervals so that the rest
are pairwise non-overlapping. Return the number of intervals removed.

Pattern
-------
Classic **interval scheduling / activity selection** greedy:
- Sort intervals by **end time ascending**.
- Greedily keep an interval if it doesn't overlap the last kept end.
- The number removed = total - number kept.

Algorithm (step-by-step)
------------------------
1) If n ≤ 1 → return 0.
2) Sort intervals by end (r) ascending.
3) Let `lastEnd = intervals[0][1]` and `kept = 1`.
4) For each interval i = 1..n-1:
   - If `intervals[i][0] >= lastEnd` (no overlap):
       • keep it → `kept++`, `lastEnd = intervals[i][1]`
   - Else (overlap):
       • remove it (do nothing; since sorted by end, the current one ends later or equal,
         so keeping the previous one is optimal).
5) Answer = `n - kept`.

Correctness (sketch)
--------------------
Sorting by end time makes the greedy choice optimal:
keeping the interval that finishes earliest leaves maximum room for the rest.
On an overlap, discarding the one with the **later** end (the current one, due to sorting)
cannot reduce the number of future compatible intervals.

Complexity
----------
- Time: O(n log n) for sorting + O(n) scan.
- Space: O(1) extra (in-place sort).

Edge Cases / Pitfalls
---------------------
- Empty input / single interval.
- Touching intervals: treat as **non-overlapping** if `end <= next.start`.
- Comparator should take **const references**; avoid non-const refs in `std::sort`.
- Your original loop using `end` as an **index** is fine, but it’s clearer to track
  the **last kept end value** instead.

========================================================
*/

static bool endCmp(const std::vector<int>& a, const std::vector<int>& b) {
    return a[1] < b[1];
}

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        int n = (int)intervals.size();
        if (n <= 1) return 0;

        std::sort(intervals.begin(), intervals.end(), endCmp);

        int kept = 1;
        int lastEnd = intervals[0][1];

        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] >= lastEnd) {
                // no overlap: keep it
                ++kept;
                lastEnd = intervals[i][1];
            } 
            // else overlap: discard current (do nothing)
        }
        return n - kept;
    }
};

/* ===== If you prefer your original index-based style (fixed comparator + small tweaks) =====
- Keep an index `endIdx` of the last kept interval. When overlap, increment `count`
  and keep `endIdx` unchanged (since the kept one ends earlier due to sorting).
*/
class Solution_indexStyle {
    static bool cmp(const std::vector<int>& u, const std::vector<int>& v) {
        return u[1] < v[1];
    }
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        int n = (int)intervals.size();
        if (n <= 1) return 0;
        std::sort(intervals.begin(), intervals.end(), cmp);

        int removals = 0;
        int endIdx = 0; // index of last kept interval
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] < intervals[endIdx][1]) {
                // overlap: remove current (since it ends later or equal)
                ++removals;
            } else {
                // non-overlap: keep current, advance endIdx
                endIdx = i;
            }
        }
        return removals;
    }
};
