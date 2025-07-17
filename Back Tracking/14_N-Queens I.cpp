class Solution {
public:
    vector<vector<string>>res;
    bool isSafe(vector<string>&board, int row, int col){
        int n = board.size();
        for(int i=0;i<row;i++){
            if(board[i][col]=='Q')
                return false;
        }
        for(int i=row,j=col;i>=0 && j<n;i--,j++){
            if(board[i][j]=='Q')
                return false;
        }
        for(int i=row,j=col; i>=0 && j>=0; i--,j--){
            if(board[i][j]=='Q')
                return false;
        }
        return true;
    }
    void solve(vector<string>&board, int row){
        if(row == board.size()){
            res.push_back(board);
            return;
        }
        for(int col=0;col<board.size();col++){
            if(isSafe(board, row, col)){
                board[row][col] = 'Q';
                solve(board, row+1);
                board[row][col] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string>board(n, string(n, '.'));
        solve(board, 0);
        return res;
    }
};

// Algorithm: N-Queens Problem (Backtracking)
// ------------------------------------------
// Problem:
//   - Place N queens on an N×N chessboard such that no two queens threaten each other.
//   - A queen can attack horizontally, vertically, and diagonally.
//   - Return all distinct valid board configurations.
//
// Approach:
//   - Use backtracking to try placing a queen row-by-row.
//   - At each row, try placing a queen in each column (0 to n-1).
//   - Use `isSafe()` function to check if placing a queen at (row, col) is valid.
//     - Check vertically up (same column).
//     - Check upper-left diagonal.
//     - Check upper-right diagonal.
//   - If safe, place the queen and recurse to next row.
//   - On backtrack, remove the queen and try the next column.
//
// Time Complexity: O(N!) 
//   - Each queen has N options initially, then N−1, then N−2, etc.
//   - With pruning, the upper bound becomes closer to O(N!) instead of O(N^N)
//
// Space Complexity:
//   - O(N^2) to store each board configuration.
//   - O(N) recursion stack depth + O(N^2 × #solutions) result space

class Solution {
public:
    vector<vector<string>> res; // Stores all valid board configurations

    // Check if it's safe to place a queen at (row, col)
    bool isSafe(vector<string>& board, int row, int col) {
        int n = board.size();

        // Check column for queen
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q')
                return false;
        }

        // Check upper-right diagonal
        for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }

        // Check upper-left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        return true;
    }

    // Backtracking function to solve row by row
    void solve(vector<string>& board, int row) {
        if (row == board.size()) {
            res.push_back(board); // Found a valid configuration
            return;
        }

        for (int col = 0; col < board.size(); col++) {
            if (isSafe(board, row, col)) {
                board[row][col] = 'Q';    // Place queen
                solve(board, row + 1);    // Recurse to next row
                board[row][col] = '.';    // Backtrack
            }
        }
    }

    // Main function to initialize board and start recursion
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.')); // Create empty board
        solve(board, 0);
        return res;
    }
};
