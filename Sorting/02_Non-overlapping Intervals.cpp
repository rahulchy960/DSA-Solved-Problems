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
==================== REVISION BLOCK ====================

Problem (Non Overlapping Intervals — Minimum Removals):
- Given intervals [li, ri], remove the minimum number so that the rest are non-overlapping.

Pattern:
- Greedy by **earliest finishing time**:
  Sort by end (ri). Keep the interval that ends earliest; drop any interval that overlaps it.

Greedy Intuition:
- Choosing the earliest finishing interval leaves the maximum room for future intervals.
- Scan in end-time order; if current.start < last_kept.end ⇒ it overlaps ⇒ count a removal.
  Else, accept it and update the "last kept" to this interval.

Algorithm:
1) Sort intervals by end ascending.
2) Initialize `end = 0` (index of last kept interval), `count = 0` (removals).
3) For i = 1..n-1:
     If intervals[i].start < intervals[end].end:
        // Overlap: remove one (greedy keeps the earlier finishing = intervals[end])
        count++
     Else:
        // No overlap: keep current as the new last kept
        end = i
4) Return `count`.

Correctness (sketch):
- Classic interval scheduling optimality: always keeping the earliest finishing compatible interval
  yields a maximum-size non-overlapping set ⇒ minimal removals = n − that maximum size.

Complexity:
- Time: O(n log n) for sorting + O(n) scan ⇒ O(n log n).
- Space: O(1) extra (in-place sort aside from stack).

Edge notes:
- Touching intervals (a.end == b.start) are **not** overlapping here because the code uses `>`:
  we only count a removal when current.start < last_end.
- Comparator ideally takes `const vector<int>&` parameters for generality.

========================================================
*/

bool myCmp(std::vector<int>& u, std::vector<int>& v) {
    return u[1] < v[1]; // sort by end time; (prefer: const std::vector<int>&)
}

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), myCmp); // 1) sort by end

        int count = 0; // removals
        int end = 0;   // index of the last kept (non-overlapping) interval

        // 2) sweep through intervals in end-time order
        for (int i = 1; i < (int)intervals.size(); i++) {
            // Overlap if current.start < last_end
            if (intervals[end][1] > intervals[i][0]) {
                // Overlap → remove one. Greedy keeps the earliest finishing (intervals[end]),
                // so we increment `count` and DO NOT move `end`.
                count++;
            } else {
                // No overlap → keep current and advance `end`
                end = i;
            }
        }
        return count;
    }
};
