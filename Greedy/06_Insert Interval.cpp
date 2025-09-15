class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        vector<vector<int>>res;
        int i=0;
        while(i<n && intervals[i][1] < newInterval[0]){
            res.push_back(intervals[i]);
            i++;
        }

        while(i<n && newInterval[1] >= intervals[i][0]){
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        
        res.push_back(newInterval);
        while(i<n){
            res.push_back(intervals[i]);
            i++;
        }
        
        return res;
    }
};

/*
==================== REVISION BLOCK — Insert Interval (merge-on-the-fly) ====================

Problem
-------
Given a list of non-overlapping intervals sorted by start time, insert a new interval
and merge any overlaps. Return the resulting list.

Pattern
-------
Single pass in **three phases**:
1) Push all intervals that end **before** the new interval starts.
2) Merge all intervals that **overlap** the new interval into one expanded interval.
3) Append the remaining intervals (which start **after** the merged interval ends).

Algorithm (step-by-step)
------------------------
Let intervals be sorted and pairwise disjoint (as per standard statement).
1) i = 0, res = [].
2) While i < n and intervals[i].end < new.start: push intervals[i], ++i.
3) While i < n and intervals[i].start <= new.end:
      new.start = min(new.start, intervals[i].start);
      new.end   = max(new.end,   intervals[i].end);
      ++i;
   Push the merged `new` into res.
4) While i < n: push intervals[i], ++i.
5) Return res.

Correctness (sketch)
--------------------
The intervals naturally partition into 3 groups w.r.t. new: strictly left (no overlap),
overlapping, and strictly right. Steps (2) and (4) copy left/right groups unchanged, and
step (3) merges the entire overlapping group into a single interval by expanding bounds.
Sortedness/disjointness ensures no missed or double-counted intervals.

Complexity
---------
- Time: O(n), single pass.
- Space: O(k) for output (O(n) in the worst case). No extra auxiliary structures.

Edge Cases / Pitfalls
---------------------
- Empty `intervals` → result is just `[newInterval]`.
- `newInterval` before all or after all → phases (2) or (4) handle it.
- **Closed intervals** [l, r]: overlap check is `interval.start <= new.end`.
  (Your code uses `intervals[i][1] < newInterval[0]` for left side and
   `newInterval[1] >= intervals[i][0]` for merging — consistent.)
- If the input might be **unsorted** or already overlapping, sort by start and then do a
  standard merge; that becomes O(n log n).

========================================================
*/

class Solution {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals,
                                         std::vector<int>& newInterval) {
        std::vector<std::vector<int>> res;
        const int n = (int)intervals.size();
        int i = 0;

        // 1) add all intervals ending before newInterval starts
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            ++i;
        }

        // 2) merge all overlapping intervals into newInterval
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = std::min(newInterval[0], intervals[i][0]);
            newInterval[1] = std::max(newInterval[1], intervals[i][1]);
            ++i;
        }
        res.push_back(newInterval);

        // 3) append the rest
        while (i < n) {
            res.push_back(intervals[i]);
            ++i;
        }
        return res;
    }
};

/* ==================== Optional: if input may be unsorted / overlapping ====================
- Sort by start, then merge `newInterval` as a normal interval:
    intervals.push_back(newInterval);
    sort(intervals.begin(), intervals.end());
    // standard merge O(n)
*/
