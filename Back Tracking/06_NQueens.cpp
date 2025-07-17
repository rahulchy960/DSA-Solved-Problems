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
