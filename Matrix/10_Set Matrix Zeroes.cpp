class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<bool>row(m,true), col(n, true);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j] == 0){
                    row[i] = 0;
                    col[j] = 0;
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(row[i] == 0 || col[j] == 0)
                    matrix[i][j] = 0;
            }
        }
    }
};


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int c0 = 1;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j] == 0){
                    matrix[i][0] = 0;
                    if(j==0)
                        c0 = 0;
                    else
                        matrix[0][j] = 0;
                }
            }
        }
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                if(matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
        }
        if(matrix[0][0] == 0)  // mark the first row
            for(int j=0;j<n;j++)
                matrix[0][j] = 0;
        if(c0 == 0) // mark the first col
            for(int i=0;i<m;i++)
                matrix[i][0] = 0;
            
    }

};


/*
==================== REVISION BLOCK — Set Matrix Zeroes (in-place O(1) space) ====================

Problem
-------
Given an m×n matrix, if an element is 0, set its entire **row** and **column** to 0.
Do it **in place** with O(1) extra space.

Pattern
-------
Use the matrix’s **first row** and **first column** as marker arrays:
- For any cell (i,j) that is 0, mark row i by setting matrix[i][0]=0 and
  mark column j by setting matrix[0][j]=0.
- You also need two flags to remember whether the original first row/col themselves
  must be zeroed: `firstRowZero`, `firstColZero`.

Algorithm (precise)
-------------------
1) Edge guard: if m==0 or n==0 → return.
2) Scan the **first row** and **first column** to set `firstRowZero`, `firstColZero`.
3) For i=0..m-1, j=0..n-1:
   - If matrix[i][j] == 0 → set `matrix[i][0]=0` and `matrix[0][j]=0`.
4) Second pass (fill zeros except first row/col):
   - For i=1..m-1, j=1..n-1:
       If `matrix[i][0]==0 || matrix[0][j]==0` → `matrix[i][j]=0`.
5) Finally zero the first row/col if needed:
   - If `firstRowZero` → zero all `matrix[0][j]`.
   - If `firstColZero` → zero all `matrix[i][0]`.

Why it works (correctness)
--------------------------
The first row/col act as O(1)-space bitmasks for which rows/columns must be zeroed.
Steps 3–4 ensure every cell in a marked row/column becomes 0. Step 5 handles the
special-case dependency of the marker carriers themselves.

Complexity
----------
Time: O(m·n) — two linear scans over the matrix.  
Space: O(1) — only two boolean flags; marks stored in the matrix.

Edge Cases / Pitfalls
---------------------
- **Empty matrix** or **empty row** — guard before reading `matrix[0]`.
- Single row / single column — flags handle them correctly.
- Don’t rely on `matrix[0][0]` alone to encode both first row & first column;
  you need two separate flags (or a `c0` + separate first-row check).
- Avoid extra passes by computing `firstRowZero`/`firstColZero` in the initial scan.

========================================================
*/

class Solution {
public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        int m = (int)matrix.size();
        if (m == 0) return;
        int n = (int)matrix[0].size();
        if (n == 0) return;

        bool firstRowZero = false, firstColZero = false;

        // Check first row
        for (int j = 0; j < n; ++j)
            if (matrix[0][j] == 0) { firstRowZero = true; break; }

        // Check first column
        for (int i = 0; i < m; ++i)
            if (matrix[i][0] == 0) { firstColZero = true; break; }

        // Use first row/col as markers
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Zero cells based on markers
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
        }

        // Zero first row/column if needed
        if (firstRowZero) {
            for (int j = 0; j < n; ++j) matrix[0][j] = 0;
        }
        if (firstColZero) {
            for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
    }
};

/* ==================== Notes on your version ====================
- Your approach is the same O(1)-space idea and is correct.
- Minor improvements:
  • Add guards for empty matrix/row before using matrix[0].
  • Prefer `bool` over `int` for flags (`c0`).
  • You can compute `firstRowZero` separately instead of relying on `matrix[0][0]`.
*/
