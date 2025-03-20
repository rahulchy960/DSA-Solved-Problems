#include<bits/stdc++.h>
using namespace std;

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