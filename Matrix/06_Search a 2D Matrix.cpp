class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int i = 0, j = n-1;
        while(i<m && j>=0){
            if(matrix[i][j] == target)
                return true;
            else if (matrix[i][j] < target)
                i++;
            else
                j--;
        }
        return false;
    }
};

/*
==================== REVISION BLOCK — Search a 2D Matrix (staircase from top-right) ====================

When it works
-------------
This “staircase” method is correct when:
- Each row is sorted in non-decreasing order, and
- Each column is sorted in non-decreasing order
  (LeetCode 240), OR rows are sorted and row[i+1][0] > row[i][n-1] (LeetCode 74).

Idea
----
Start at the **top-right** cell (i = 0, j = n-1):
- If matrix[i][j] == target → found.
- If matrix[i][j] < target → everything left in this row is smaller; move **down** (i++).
- If matrix[i][j] > target → everything below in this column is larger; move **left** (j--).

This shrinks the search space by one row or one column each step.

Correctness (invariant)
-----------------------
At position (i,j), all cells to the left are ≤ current, all cells below are ≥ current.
So moving down discards a row of too-small values; moving left discards a column of too-large values.

Complexity
----------
Time: O(m + n)  — at most m downward steps and n leftward steps.
Space: O(1).

Edge cases
----------
- Empty matrix or empty first row → return false (guard to avoid out-of-bounds).
- Duplicates are fine.
*/

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;

        int i = 0, j = n - 1;          // start at top-right
        while (i < m && j >= 0) {
            if (matrix[i][j] == target) return true;
            else if (matrix[i][j] < target) ++i;  // move down
            else --j;                             // move left
        }
        return false;
    }
};
