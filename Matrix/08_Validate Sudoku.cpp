class Solution {
public:
    bool isSafe(vector<vector<char>>& board, int i, int j, char val){
        for(int k=0;k<9;k++){
            if(board[i][k] == val || board[k][j] == val)
                return false;
        }
        int subR = i - i % 3;
        int subC = j - j % 3;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i + subR][j + subC] == val)
                    return false;
            }
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        int n = 9;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(board[i][j] != '.'){
                    char temp = board[i][j];
                    board[i][j] = '#';
                    if(isSafe(board, i, j, temp)==false)
                        return false;
                    board[i][j] = temp;
                }
            }
        }
        return true;
    }
};


/*
==================== REVISION BLOCK — Validate Sudoku ====================

Idea
----
A board is valid iff each filled digit is unique within its ROW, COLUMN, and 3×3 BOX.

Pattern
-------
Per-cell validation (scan) or one-pass **bitmask** tracking for rows/cols/boxes.

Algorithm (Direct Scan)
-----------------------
For each filled cell (r,c) with digit d:
1) Check row r: no other cell has d.
2) Check col c: no other cell has d.
3) Check its 3×3 box: no other cell has d.
If any check fails → false; if all pass → true.

Correctness
-----------
Row/col/box uniqueness are the exact Sudoku constraints. We verify them for each filled cell.

Complexity
----------
- Direct Scan: O(9^3) = O(1) on fixed 9×9 board; Space O(1).
- Bitmask: O(81) time, O(1) space.

Edge Cases
----------
- All '.' → valid.
- Any duplicate in a row/col/box → invalid.
- Guard dimensions/characters if inputs aren’t guaranteed.

Pitfalls
--------
- Don’t mutate the board (no sentinel needed).
- Skip comparing the cell to itself.
- Avoid variable shadowing in the 3×3 box loops.
*/

class Solution {
    bool safe(const std::vector<std::vector<char>>& b, int r, int c, char val) {
        // Row & Col checks (skip (r,c))
        for (int k = 0; k < 9; ++k) {
            if (k != c && b[r][k] == val) return false;
            if (k != r && b[k][c] == val) return false;
        }
        // 3×3 box
        int br = (r / 3) * 3, bc = (c / 3) * 3;
        for (int dr = 0; dr < 3; ++dr)
            for (int dc = 0; dc < 3; ++dc) {
                int nr = br + dr, nc = bc + dc;
                if ((nr != r || nc != c) && b[nr][nc] == val) return false;
            }
        return true;
    }

public:
    // Direct-scan version (cleaned; no mutation)
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        if (board.size() != 9) return false;
        for (auto& row : board) if (row.size() != 9) return false;

        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                char ch = board[r][c];
                if (ch == '.') continue;
                if (ch < '1' || ch > '9') return false;  // optional guard
                if (!safe(board, r, c, ch)) return false;
            }
        }
        return true;
    }
};

/* ==================== Optional: Faster Bitmask One-Pass ====================

Idea/Pattern:
- row[9], col[9], box[9] are 9-bit masks for digits 1..9.
- For digit ch: bit = 1 << (ch-'1'); boxId = (r/3)*3 + (c/3)
- If bit already set in row/col/box → duplicate → invalid.

Time: O(81), Space: O(1)

class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& b) {
        if (b.size() != 9) return false;
        for (auto& row : b) if (row.size() != 9) return false;

        int row[9] = {0}, col[9] = {0}, box[9] = {0};
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                char ch = b[r][c];
                if (ch == '.') continue;
                if (ch < '1' || ch > '9') return false;
                int bit = 1 << (ch - '1');
                int id  = (r / 3) * 3 + (c / 3);
                if ((row[r] & bit) || (col[c] & bit) || (box[id] & bit)) return false;
                row[r] |= bit; col[c] |= bit; box[id] |= bit;
            }
        }
        return true;
    }
};
*/
