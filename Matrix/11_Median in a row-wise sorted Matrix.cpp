class Solution {
  public:
    int median(vector<vector<int>> &mat) {
        // code here
        int m = mat.size();
        int n = mat[0].size();
        int mn = mat[0][0], mx = mat[0][n-1];
        for(int i=1;i<m;i++){
            mx = max(mx, mat[i][n-1]);
            mn = min(mn, mat[i][0]);
        }
        int medPos = (m*n + 1) / 2;
        while(mn<mx){
            int mid = mn + (mx-mn)/2;
            int count = 0;   // count of elements less than or equal to mid
            for(int i=0;i<m;i++){
                count += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
            }
            if(count < medPos)
                mn = mid + 1;
            else
                mx = mid;
        }
        return mn;
    }
};

/*
==================== REVISION BLOCK — Median in a Row-wise Sorted Matrix ====================

Problem
-------
Given an m×n matrix where **each row is sorted** in nondecreasing order, return the median
value of all m·n elements. (If m·n is even, this routine returns the **lower median**;
common problems assume m·n is odd.)

Pattern
-------
**Binary search on value space** (not on indices):
- Search over the closed range [global_min, global_max].
- For a candidate value `mid`, count how many elements in the matrix are `<= mid`.
  If that count is < desired rank, the median is bigger; otherwise it is <= mid.

Algorithm (step-by-step)
------------------------
1) Let `mn = min_i row_i[0]`, `mx = max_i row_i[n-1]` (since rows are sorted).
2) Let `need = (m*n + 1)/2`  // 1-indexed rank of the lower median.
3) While `mn < mx`:
   a) `mid = mn + (mx - mn)/2`
   b) `cnt = sum over rows of upper_bound(row, mid) - row.begin()`  // #elements ≤ mid in that row
   c) If `cnt < need` → median is larger → set `mn = mid + 1`
      else             → median is ≤ mid → set `mx = mid`
4) Return `mn` (== `mx`), the smallest value such that at least `need` elements are ≤ it.

Why it works (correctness)
--------------------------
For any threshold `x`, `cnt(x)` is nondecreasing in `x`. The predicate
P(x): “cnt(x) ≥ need” is monotone. Binary searching the smallest x that satisfies P(x)
yields exactly the **need**-th smallest element, i.e., the (lower) median.

Complexity
----------
- Each mid check: O(m · log n) via `upper_bound` per row.
- Number of checks: O(log(range)), where `range = mx - mn + 1`.
⇒ **Time:** O(m · log n · log(range))  
**Space:** O(1)

Edge Cases / Pitfalls
---------------------
- Empty matrix / empty rows → guard before accessing `mat[0]`.
- If m·n is **even**, `(m*n + 1)/2` returns the **lower** median (k = n/2).
- Use 64-bit for counters/indices if m and n can be large (avoid overflow on `cnt`).
- Rows must be individually sorted; otherwise this approach is invalid.

========================================================
*/

class Solution {
public:
    int median(std::vector<std::vector<int>> &mat) {
        int m = (int)mat.size();
        if (m == 0) return 0;                   // or throw / define behavior
        int n = (int)mat[0].size();
        if (n == 0) return 0;

        int mn = mat[0][0], mx = mat[0][n - 1];
        for (int i = 1; i < m; ++i) {
            mn = std::min(mn, mat[i][0]);
            mx = std::max(mx, mat[i][n - 1]);
        }

        const int need = (m * n + 1) / 2;       // lower median rank
        while (mn < mx) {
            int mid = mn + (mx - mn) / 2;
            long long cnt = 0;                  // 64-bit for safety
            for (int i = 0; i < m; ++i) {
                cnt += std::upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
            }
            if (cnt < need) mn = mid + 1;
            else            mx = mid;
        }
        return mn;
    }
};

/* ==================== Optional Alternative (K-way merge) ====================
Push first element of each row into a min-heap and pop/push until you pop `need` times.
Time: O( (need + m) · log m ), Space: O(m). Usually slower than value-space binary search,
but good to know as a row-wise-sorted merge technique.
*/
