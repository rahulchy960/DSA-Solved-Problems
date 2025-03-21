#include<bits/stdc++.h>
using namespace std;

int LCS(string &s1, string &s2){
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>>dp(m+1, vector<int>(n+1,-1));
    // Base cases: LCS of any string with an empty string is 0
    for(int i=0;i<=m;i++)   
        dp[i][0] = 0;
    for(int j=0;j<=n;j++)
        dp[0][j] = 0;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            // If last character of the two strings match, 
            // Include this character in LCS and add 1 to the result of previous substring
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                // If characters don't match, take the maximum:
                // 1. Exclude the current character of s1 → dp[i-1][j]
                // 2. Exclude the current character of s2 → dp[i][j-1]
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
    
}

int main(){
    string s1 = "XYZ";
    string s2 = "AXBZ";
    cout<<LCS(s1,s2);   
}