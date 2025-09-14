class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int i=0, j=n-1;
        while(j>=0 && i<m){
            if(matrix[i][j] == target)
                return true;
            else if(matrix[i][j] > target)
                j--;
            else 
                i++;
        }
        return false;
    }
};


/*
==================== REVISION BLOCK — Search a 2D Matrix II (rows & cols sorted) ====================

Problem
-------
Given an m×n matrix where each row is sorted left→right and each column is sorted top→bottom,
determine whether a target value exists in the matrix.

Pattern
-------
**Elimination from a corner** (two-pointer on 2D):
Start at **top-right** (or bottom-left). Each comparison discards a full row or column.

Algorithm (precise, top-right start)
------------------------------------
1) If matrix is empty → return false.
2) Set (i, j) = (0, n-1).
3) While i < m and j >= 0:
   a) If matrix[i][j] == target → return true.
   b) If matrix[i][j]  > target → --j   // eliminate current column (all below are ≥ this)
   c) Else (matrix[i][j] < target) → ++i // eliminate current row (all left are ≤ this)
4) Return false.

Why it works (correctness)
--------------------------
At (i, j) = top-right:
- All elements left of j are ≤ matrix[i][j].
- All elements below i are ≥ matrix[i][j].
So if current > target, target cannot be below (too large) → move left.
If current < target, target cannot be left (too small) → move down.
We strictly move closer to the answer, guaranteeing termination in ≤ m+n steps.

Complexity
----------
Time: O(m + n) comparisons.  
Space: O(1).

Edge Cases
----------
- Empty matrix or empty row.
- Target smaller than matrix[0][0] or larger than matrix[m-1][n-1] (fast exits by loop).
- Single row or single column.

Pitfalls
--------
- Don’t access matrix[0] if m == 0; guard before reading n.
- Ensure loop condition is `i < m && j >= 0`.
- This is **not** the LC-74 variant (each row’s first > previous row’s last). For LC-74, use a single binary search on a flattened index.

========================================================
*/

class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        int m = (int)matrix.size();
        if (m == 0) return false;
        int n = (int)matrix[0].size();
        if (n == 0) return false;

        int i = 0, j = n - 1;  // start at top-right
        while (i < m && j >= 0) {
            int x = matrix[i][j];
            if (x == target) return true;
            else if (x > target) --j;  // eliminate column j
            else ++i;                  // eliminate row i
        }
        return false;
    }
};

/* ==================== Optional: Bottom-left start (equivalent) ====================
int i = m - 1, j = 0;
while (i >= 0 && j < n) {
    if (matrix[i][j] == target) return true;
    else if (matrix[i][j] > target) --i; // move up
    else ++j;                            // move right
}
return false;
*/
