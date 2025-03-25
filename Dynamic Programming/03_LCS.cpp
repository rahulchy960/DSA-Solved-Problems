#include<bits/stdc++.h>
using namespace std;

/*  Recursive solution

int LCS(string s1, string s2, int m, int n){
    if(n==0 || m==0) return 0;
    if(s1[m-1] == s2[n-1]) 
        return 1 + LCS(s1,s2,m-1,n-1);
    return max(LCS(s1,s2,m-1,n), LCS(s1,s2,m,n-1));
}

*/

/*  Memorization based solution

int LCS(string &s1, string &s2,int m, int n, vector<vector<int>>&memo){
    if(memo[m][n]==-1){
        if(m==0 || n==0)
            return 0;
        else if(s1[m-1] == s2[n-1])
            memo[m][n] = 1 + LCS(s1,s2,m-1,n-1,memo);
        else
            memo[m][n] = max(LCS(s1,s2,m-1,n,memo), LCS(s1,s2,m,n-1,memo));
    }
    return memo[m][n]; 
}

*/


// LCS tabulation based solution
int LCS(string s1, string s2){
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




int main(){
    string s1 = "abc";
    string s2 = "def";
    int m = s1.length();
    int n = s2.length();

    // cout<<LCS(s1,s2,m,n)<<endl;  

    // vector<vector<int>>memo(m+1,vector<int>(n+1,-1));
    // cout<<LCS(s1,s2,m,n,memo)<<endl;  

    cout<<LCS(s1,s2)<<endl;


}