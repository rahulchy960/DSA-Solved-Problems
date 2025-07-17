#include<bits/stdc++.h>
using namespace std;

// Function to check if placing 'x' at position (i, j) is safe
bool isSafe(int i, int j, int x, vector<vector<int>>&grid){
    
    for(int k=0;k<grid.size();k++){   // Check the row and column for the same number
        if(grid[i][k] == x || grid[k][j] == x)
            return false;
    }
    
    // Check the 3x3 subgrid for the same number
    int s = sqrt(grid.size()); // Size of each subgrid (3x3 for standard Sudoku)
    int subR = i - (i % s);    // Starting row index of the subgrid
    int subC = j - (j % s);    // Starting column index of the subgrid
    for(int i=0;i<s;i++){
        for(int j=0;j<s;j++){
            if(grid[i+subR][j+subC]==x)
                return false;
        }
    }
    return true;
}

bool helper(vector<vector<int>>&grid){
    
    int i, j;
    bool foundEmpty = false;        // Flag to track empty cells preseant or not
    for(i=0;i<grid.size();i++){      // Find the first empty cell in the grid
        for(j=0;j<grid.size();j++){
            if(grid[i][j]==0){
                foundEmpty = true;
                break;        // Empty cell found
            }
        }
        if(foundEmpty)break;  // Exit loop once an empty cell is found
    }


    if(!foundEmpty)        // If no empty cell is found, the Sudoku is solved
        return true;
    
    for(int x=1;x<=grid.size();x++){    // Try placing digits 1-9 in the empty cell
        if(isSafe(i,j,x,grid)){       // Check if 'x' can be safely placed
            grid[i][j] = x;     // Place the number
            if(helper(grid))    // Recursive call to continue solving
                return true;    // Solution found
            grid[i][j] = 0;     // Backtrack if placing 'x' is wrong
        }
    }

    return false;        // No valid number can be placed in this cell
}

void solveSudoku(vector<vector<int>>&grid){
    if(helper(grid)==true)
        cout<<"Solution Exists"<<endl;
    else   
        cout<<"No Solution Exists"<<endl;
}

int main(){
    vector<vector<int>>grid = { { 0, 0, 0, 2, 6, 0, 7, 0, 1 },
                                { 6, 8, 0, 0, 7, 0, 0, 9, 0 },
                                { 1, 9, 0, 0, 0, 4, 5, 0, 0 },
                                { 8, 2, 0, 1, 0, 0, 0, 4, 0 },
                                { 0, 0, 4, 6, 0, 2, 0, 0, 0 },
                                { 0, 5, 0, 0, 0, 3, 0, 2, 8 },
                                { 0, 0, 9, 3, 0, 0, 0, 7, 4 },
                                { 0, 4, 0, 0, 5, 0, 0, 3, 6 },
                                { 7, 0, 3, 0, 1, 8, 0, 0, 0 } };

    solveSudoku(grid);

    for(auto x : grid){
        for(int i=0;i<grid.size();i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
}




class Solution {
public:
    bool isSafe(vector<vector<char>>& board, int i, int j, int x){
        for(int k=0;k<9;k++){
            if(board[i][k]==x+'0' || board[k][j]== x+'0')
                return false;
        }

        int s = sqrt(board.size());
        int subR = i-(i%s);
        int subC = j-(j%s);
        for(int ii=0;ii<s;ii++){
            for(int jj=0;jj<s;jj++){
                if(board[ii+subR][jj+subC]== x+'0')
                    return false;
            }
        }
        return true;
        

    }
    bool helper(vector<vector<char>>& board){
        int i, j;
        bool toSolve=false;
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                if(board[i][j]=='.'){
                    toSolve=true;
                    break;
                }
            }
            if(toSolve) break;
        }

        if(toSolve==false) return true;

        for(int x=1;x<=9;x++){
            if(isSafe(board, i, j, x)){
                board[i][j] = x+'0';
                if(helper(board)) return true;
                board[i][j] = '.';
            }
        }
        return false; // never going to reach if had a valid solution
    }
    void solveSudoku(vector<vector<char>>& board) {
        helper(board);
    }
};


    /*
    Algorithm:
    - This is a standard backtracking approach to solve the Sudoku puzzle.
    - The algorithm scans the board for an empty cell ('.').
    - For each empty cell, it tries all digits from 1 to 9.
    - For each digit, it checks if placing it is valid using the isSafe() function:
        - No repetition in the current row.
        - No repetition in the current column.
        - No repetition in the 3x3 sub-grid.
    - If valid, it places the digit and recursively calls the helper function.
    - If at any point a placement leads to a dead end, it backtracks (removes the digit and tries next).
    - The recursion ends when all cells are filled.

    Time Complexity:
    - In the worst case, there are 81 cells and each can try up to 9 numbers → O(9^81)
    - But due to constraint pruning (isSafe check), the effective complexity is much lower.

    Space Complexity:
    - O(1) extra space (only modifies board in-place and uses recursion)
    - Recursion stack depth up to 81 → O(81) = O(1) for constant-sized 9x9 board
    */

    





