class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int ans = 0;
        for (int i = 1; i < points.size(); i++) {
            ans += max(
                abs(points[i][0] - points[i - 1][0]),
                abs(points[i][1] - points[i - 1][1])
            );
        }
        return ans;
    }
};

/*
==================== REVISION BLOCK — LeetCode 1266: Minimum Time Visiting All Points ====================

Problem
-------
You are given a list of points on a 2D plane in the order you must visit them.
In one second, you can move:
- 1 unit vertically, or
- 1 unit horizontally, or
- 1 unit diagonally (changes both x and y by 1).
Return the minimum time to visit all points in order.

Pattern/ Idea
-------------
Chebyshev distance between consecutive points.
Idea: In one move (second), diagonal movement reduces both |dx| and |dy| together.
So you take min(|dx|, |dy|) diagonal steps, then finish remaining steps in the larger direction.
Total time = max(|dx|, |dy|) for each consecutive pair.

Algorithm (step-by-step)
------------------------
1) Initialize ans = 0.
2) For each i from 1 to n-1:
   a) dx = abs(points[i][0] - points[i-1][0])
   b) dy = abs(points[i][1] - points[i-1][1])
   c) ans += max(dx, dy)
3) Return ans.

Correctness (sketch)
--------------------
For two points:
- Each diagonal step reduces both dx and dy by 1, so we can do at most min(dx, dy) diagonals.
- After that, one of dx or dy becomes 0, and we need the remaining |dx-dy| straight moves.
Thus total steps = min(dx,dy) + (max(dx,dy)-min(dx,dy)) = max(dx,dy).
Summing this optimal cost for every consecutive pair gives the minimal total time for the entire path.

Complexity
---------
Time: O(n) where n = number of points
Space: O(1)

Edge Cases / Pitfalls
---------------------
- Only one point -> time 0 (loop doesn't run).
- Consecutive identical points -> adds 0.
- Negative coordinates are fine due to abs().

Optimization if needed
----------------------
Already optimal.

========================================================
*/

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int ans = 0;

        // Sum minimal time between consecutive points
        for (int i = 1; i < (int)points.size(); i++) {
            int dx = abs(points[i][0] - points[i - 1][0]); // x distance
            int dy = abs(points[i][1] - points[i - 1][1]); // y distance

            // Minimum time equals Chebyshev distance
            ans += max(dx, dy);
        }

        return ans;
    }
};
