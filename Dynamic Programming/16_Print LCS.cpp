#include<bits/stdc++.h>
using namespace std;

int LCS(string s1, string s2, int m, int n){
    if(n==0 || m==0) return 0;
    if(s1[m-1] == s2[n-1]) 
        return 1 + LCS(s1,s2,m-1,n-1);
    return max(LCS(s1,s2,m-1,n), LCS(s1,s2,m,n-1));
}

int LCST(string s1, string s2){
    int m = s1.length();
    int n = s2.length();
    int dp[m+1][n+1];
    for(int i=0;i<=m;i++)dp[i][0] = 0;
    for(int j=0;j<=n;j++)dp[0][j] = 0;

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[m][n];
}