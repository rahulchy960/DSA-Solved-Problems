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

