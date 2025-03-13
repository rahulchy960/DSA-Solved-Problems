#include<bits/stdc++.h>
using namespace std;

int LCS(string &s1, string &s2, int m, int n, vector<vector<int>>&memo){
    if(memo[m][n]!=-1)
        return memo[m][n];
    
    if(m==0 || n==0)
        memo[m][n] = 0;
    else{
        if(s1[m-1] == s2[n-1])
            memo[m][n] = 1 + LCS(s1,s2,m-1,n-1,memo);
        else    
            memo[m][n] = max(LCS(s1,s2,m-1,n,memo), LCS(s1,s2,m,n-1,memo)); 
    }
    return memo[m][n];
    
}

int main(){
    string s1 = "XYZ";
    string s2 = "AXBZ";
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    cout<<LCS(s1,s2,m,n, memo);   
}