#include<bits/stdc++.h>
using namespace std;

/*

The goal is to find one valid solution for the N-Queens problem.
In this version, if a valid solution is found, the recursion returns immediately (return true;).
This approach finding a solution quickly without exploring all possible configurations.

*/

void print(vector<vector<char>>&sol){
    for(auto x : sol){
        for(int i=0;i<sol.size();i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
}

bool isSafe(int row, int col, vector<vector<char>>&sol){

    for(int i=row;i>=0;i--){       // Check vertically upwards
        if(sol[i][col] == 'Q')
            return false;
    }
    for(int i=row, j=col;i>=0 && j>=0; i--, j--){    // Check upper-left diagonal
        if(sol[i][j] == 'Q'){
            return false;
        }
    }
    for(int i=row, j=col;i>=0 && j<sol.size(); i--, j++){   // Check upper-right diagonal
        if(sol[i][j] == 'Q'){
            return false;
        }
    }
    return true;  // Position is safe
}

bool helper(int row, vector<vector<char>>&sol){

    if(row==sol.size())return true;  // Base condition: if all rows are filled, solution is complete

    for(int i=0;i<sol.size();i++){   // Try placing a queen in each column of the current row
        if(isSafe(row, i, sol)){     // Check if the position is safe
            sol[row][i] = 'Q';       // Place a queen at current position
            if(helper(row+1, sol))   // Recursively place queens in the next row
                return true;         // If a valid solution is found, return true
            sol[row][i] = '_';       // Backtrack if placing the queen didn't lead to a solution
        }
    }
    return false;                   // Return false if no valid placement is found for this row
}

void NQueens(int n){
    vector<vector<char>>sol(n, vector<char>(n, '_'));
    if(helper(0, sol)==false)  // Start placing queens from row 0
        cout<<"No solution"<<endl;
    else 
        cout<<"Can be placed"<<endl;
    print(sol);
}

int main(){
    int n = 5;
    NQueens(n);
    return 0;
}


/*    // Leetcode 52 : N-Queens II

// The goal here is to count all possible valid configurations for the N-Queens problem.

class Solution {
public:
    bool isSafe(int row, int col, vector<vector<bool>>&sol){
        for(int i=row;i>=0;i--){
            if(sol[i][col])return false;
        }
        for(int i=row, j=col; i>=0 && j>=0;i--,j--){
            if(sol[i][j])return false;
        }
        for(int i=row, j=col; i>=0 && j<sol.size();i--,j++){
            if(sol[i][j])return false;
        }
        return true;
    }

    void NQueens(int row, vector<vector<bool>>&sol, int &count){
        if(row == sol.size()){
            count++;
            return;
        }
        for(int i=0;i<sol.size();i++){
            if(isSafe(row, i, sol)){
                sol[row][i] = 1;
                NQueens(row+1, sol, count);
                sol[row][i] = 0;
            }
        }
    }
    int totalNQueens(int n) {
        int count = 0;
        vector<vector<bool>>sol(n,vector<bool>(n,0));
        NQueens(0,sol,count);          
        return count;
    }
};


Here, we continues the loop even after finding a valid configuration,
so that al solutions are explored.

There is no return statement inside the loop because the recursion 
needs to keep exploring all paths.

Each valid configuration must be counted. If we add return inside the loop, 
the function would exit immediately after finding the first valid solution — 
failing to count the other ones.

*/
