#include<bits/stdc++.h>
using namespace std;

int maxCutsTabulation(int n, int a, int b, int c){
    vector<int>dp(n+1,-1);
    dp[0] = 0;  //  If the rope length is 0, no cuts are needed.
    // dp[i] represent the maximum number of pieces that can be obtained from a rope of length i.
    for(int i=1;i<=n;i++){
        dp[i] = -1;      // Start with an invalid state
        if(i-a >= 0) dp[i] = max(dp[i], dp[i-a]);  // check If we can make a valid cut using length a
        if(i-b >= 0) dp[i] = max(dp[i], dp[i-b]);  // check If we can make a valid cut using length b
        if(i-c >= 0) dp[i] = max(dp[i], dp[i-c]);  // check If we can make a valid cut using length c

        if(dp[i] != -1)   // If dp[i] is not -1 (meaning a valid solution exists), we increment the cut count by 1
            dp[i]++;
    }
    return dp[n];
}

int maxCuts(int n, int a, int b, int c, vector<int>&memo){
    if(n==0) return 0;        // Base case: If rope length is zero, no cuts are needed
    if(n<0) return -1;        // If rope length becomes negative, it's not a valid state
    if(memo[n]==INT_MIN){     // If result is not already computed (indicated by INT_MIN)
        int res = max(max(maxCuts(n-a, a, b, c, memo), maxCuts(n-b, a, b, c, memo)), maxCuts(n-c, a, b, c, memo));
                              // Recursively try cutting the rope by lengths a, b, and c
        if(res==-1)           // If no valid cuts are possible, mark it as -1
            memo[n] = -1;
        else                  // If a valid cut is possible, store the maximum number of cuts
            memo[n] = res+1;
    } 
    return memo[n];   
}

int main(){
    int n = 3;
    int a = 2, b=4, c=2;
    vector<int>memo(n+1, INT_MIN);
    cout<<maxCuts(n, a, b, c, memo)<<endl;;    
    cout<<maxCutsTabulation(n, a, b, c)<<endl;
}