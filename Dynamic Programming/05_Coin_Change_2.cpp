#include<bits/stdc++.h>
using namespace std;
/*
int coinChange(vector<int>&coins, int n, int amount){
    if(amount == 0)return 1;
    if(n==0) return 0;

    int res = coinChange(coins, n-1, amount);

    if(coins[n-1]<= amount)
        res = res + coinChange(coins, n, amount - coins[n-1]); 
    
    return res;
}
*/

/*
int coinChange(vector<int>&coins, int n, int amount, vector<vector<int>>&memo){
    if(amount == 0) return 1;
    if(n==0) return 0;
    if(memo[amount][n] == -1){
        int case1 = coinChange(coins,n-1,amount,memo);

        int case2=0;
        if(coins[n-1]<=amount)
            case2 = coinChange(coins,n,amount-coins[n-1],memo);
        
        memo[amount][n] = case1 + case2;
    }
    return memo[amount][n];
}
*/

int coinChange(vector<int>&coins, int n, int amount){
    int dp[amount+1][n+1];
    for(int i=0;i<=n;i++)dp[0][i] = 1;
    for(int i=1;i<=amount;i++) dp[i][0] = 0;

    for(int i=1;i<=amount;i++){
        for(int j=1;j<=n;j++){
            int notTaken = dp[i][j-1];
            int taken  = 0;
            if(coins[j-1]<=i) 
                taken = dp[i-coins[j-1]][j];
            dp[i][j] = taken + notTaken;
            
        }
    }
    return dp[amount][n];
}

int main(){
    
    vector<int>coins = {1,2,5};
    int amount = 5;
    // cout<<coinChange(coins,coins.size(),amount)<<endl;

    int n = coins.size();
    // vector<vector<int>>memo(amount+1,vector<int>(n+1, -1));
    // cout<<coinChange(coins,n,amount,memo)<<endl;

    cout<<coinChange(coins,n, amount)<<endl;
}