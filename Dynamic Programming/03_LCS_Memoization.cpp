#include<bits/stdc++.h>
using namespace std;

int LCS(string &s1, string &s2, int m, int n, vector<vector<int>>&memo){

    if(memo[m][n]!=-1)     // solution is already calculated
        return memo[m][n];
    
    if(m==0 || n==0)       // base case : if any of the strings become empty
        memo[m][n] = 0;
    else{
        if(s1[m-1] == s2[n-1])   // if last character matches : we recursively call for the remaining part of the strings
            memo[m][n] = 1 + LCS(s1,s2,m-1,n-1,memo);
        else                    // 
            memo[m][n] = max(LCS(s1,s2,m-1,n,memo), LCS(s1,s2,m,n-1,memo));  // we reccur for two cases, 
            // In one case we ignore the last char of the first string and other case we remove the last char of
            // 2nd string And take max of both the LCSs
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