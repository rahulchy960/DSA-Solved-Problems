#include<bits/stdc++.h>
using namespace std;

void print(vector<vector<int>>&sol){
    for(auto x : sol){
        for(int i=0;i<x.size();i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
}

bool isSafe(int i, int j, vector<vector<int>>&maze){  // Function to check if the current cell is safe to visit
    int n = maze.size();
    return (i<n && j<n && maze[i][j]==1);  // Check if the cell is within the maze boundaries and not blocked
}

bool helper(int i, int j, vector<vector<int>>&maze, vector<vector<int>>&sol){
    int n = maze.size();
    if(i==n-1 && j==n-1 && maze[i][j]==1){  // Base case: If we reached the destination cell
        sol[i][j]=1;
        return true;
    }
    if(isSafe(i, j, maze)){  // If the current cell is safe to visit
        sol[i][j] = true;    // Mark the cell as part of the solution path
        if(helper(i+1, j, maze, sol)) return true;  // Try moving down
        else if(helper(i,j+1, maze, sol)) return true;  // Try moving right
        sol[i][j] = 0;     // Backtrack: Unmark the cell if no path is found
    }
    return false;

}

void solveMaze(vector<vector<int>>&maze){

    int n = maze.size();
    vector<vector<int>>sol(n,vector<int>(n,0));
    if(helper(0, 0, maze, sol)==true)
        print(sol);
    else
        cout<<"No valid Path";

    return;
    
}

int main(){
    vector<vector<int>>maze = { { 1, 0, 0, 0 },
                                { 1, 1, 0, 1 },
                                { 0, 1, 0, 0 },
                                { 0, 1, 1, 1 } };
    solveMaze(maze);
    return 0;
}