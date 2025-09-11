class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int>res;
        int top = 0, left = 0, right = n-1, bottom = m-1;
        while(left<=right && top<=bottom){
            for(int i=left;i<=right;i++)
                res.push_back(matrix[top][i]);
            top++;

            for(int i=top;i<=bottom;i++)
                res.push_back(matrix[i][right]);
            right--;

            if(top<=bottom){
                for(int i=right;i>=left;i--)
                    res.push_back(matrix[bottom][i]);
                bottom--;
            }

            if(left<=right){
                for(int i=bottom; i>=top; i--)
                    res.push_back(matrix[i][left]);
                left++;
            }
        }

        return res;
    }
};

/*
==================== REVISION BLOCK — Spiral Matrix (clockwise) ====================

Idea
----
Maintain 4 boundaries: top, bottom, left, right. In each “layer”, traverse:
1) top row  (left → right), then top++
2) right col (top → bottom), then right--
3) bottom row (right → left) if top ≤ bottom, then bottom--
4) left col (bottom → top) if left ≤ right, then left++

Stop when the boundaries cross.

Correctness
-----------
Each element is visited exactly once as the rectangle shrinks inward layer by layer.

Complexity
----------
Time: O(m·n) — every cell appended once.
Space: O(1) extra (excluding output).

Edge cases
----------
- Empty matrix: return {} (guard added).
- Non-square / rectangular matrices work naturally.

========================================================
*/

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        int m = matrix.size();
        if (m == 0) return {};
        int n = matrix[0].size();
        if (n == 0) return {};

        std::vector<int> res;
        res.reserve(m * n);

        int top = 0, bottom = m - 1;
        int left = 0, right = n - 1;

        while (left <= right && top <= bottom) {
            // 1) top row
            for (int j = left; j <= right; ++j) res.push_back(matrix[top][j]);
            ++top;

            // 2) right column
            for (int i = top; i <= bottom; ++i) res.push_back(matrix[i][right]);
            --right;

            // 3) bottom row (if still within bounds)
            if (top <= bottom) {
                for (int j = right; j >= left; --j) res.push_back(matrix[bottom][j]);
                --bottom;
            }

            // 4) left column (if still within bounds)
            if (left <= right) {
                for (int i = bottom; i >= top; --i) res.push_back(matrix[i][left]);
                ++left;
            }
        }
        return res;
    }
};
