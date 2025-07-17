class Solution {
public:
    vector<pair<int,int>>d ={{1,0},{0,1},{-1,0},{0,-1}};

    bool isSafe(vector<vector<char>>& board, char letter, int i, int j){
        return (i>=0 && j>=0 && i<board.size() && j<board[i].size() && board[i][j] == letter);
    }

    bool solve(vector<vector<char>>& board, string word, int i, int j, int wordIdx){
        if(wordIdx == word.length()) return true;
        if(isSafe(board, word[wordIdx], i, j)){
            char temp = word[wordIdx];
            board[i][j] = '$';
            for(int k=0;k<d.size();k++){
                if(solve(board, word, i+d[k].first, j+d[k].second, wordIdx+1))
                    return true;
            }
            board[i][j] = temp;

        }
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j] == word[0]){
                    if(solve(board, word, i, j, 0) == true) 
                        return true;
                }
            }
        }
        return false;
    }
};



// Algorithm: Word Search in 2D Grid (Backtracking)
// -------------------------------------------------
// Problem:
//   - Given an m x n board of characters and a word,
//     return true if the word exists in the grid.
//   - The word must be constructed from letters of sequentially adjacent cells,
//     where "adjacent" cells are horizontally or vertically neighboring.
//   - A cell cannot be used more than once in a word.
//
// Approach: Backtracking
// ----------------------
// 1. Traverse the grid to find the first character of the word.
// 2. From every matching cell, launch a DFS (solve function).
// 3. At each recursive call:
//     - If current character matches, mark the cell as visited.
//     - Explore all 4 directions (up, down, left, right).
//     - If any path leads to completing the word, return true.
//     - Otherwise, backtrack: unmark the cell.
// 4. Return true if any DFS search is successful.
//
// Optimizations:
//   - Early return on success.
//   - In-place marking with a special character to save extra visited array.
//
// Time Complexity: O(m × n × 4^L)
//   - m × n: for each cell as a starting point.
//   - 4^L: each character in the word can branch in 4 directions, L = word length.
//
// Space Complexity: O(L)
//   - Recursion stack for the length of the word.

class Solution {
public:
    // Directions: down, right, up, left
    vector<pair<int, int>> d = {{1,0}, {0,1}, {-1,0}, {0,-1}};

    // Check if cell (i,j) is within bounds and matches the expected character
    bool isSafe(vector<vector<char>>& board, char letter, int i, int j) {
        return (i >= 0 && j >= 0 && i < board.size() && j < board[0].size() && board[i][j] == letter);
    }

    // Recursive function to search for the word starting from cell (i,j)
    bool solve(vector<vector<char>>& board, string& word, int i, int j, int wordIdx) {
        if (wordIdx == word.length()) return true; // Entire word matched

        if (isSafe(board, word[wordIdx], i, j)) {
            char temp = board[i][j]; // Save original character
            board[i][j] = '$';       // Mark visited

            // Explore all 4 directions
            for (auto& dir : d) {
                int ni = i + dir.first;
                int nj = j + dir.second;
                if (solve(board, word, ni, nj, wordIdx + 1))
                    return true;
            }

            board[i][j] = temp; // Backtrack
        }

        return false;
    }

    // Main function to search for the word in the board
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        // Try to start the DFS from each cell that matches word[0]
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (solve(board, word, i, j, 0))
                        return true;
                }
            }
        }

        return false; // No path found
    }
};
