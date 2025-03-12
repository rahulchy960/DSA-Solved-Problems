#include<bits/stdc++.h>
using namespace std;
int n;

int nthFibonacci(int n, vector<int> &memo){
    if(memo[n]==-1){
        int res;
        if(n==0 || n==1)
            res = n;
        else    
            res = nthFibonacci(n-1, memo) + nthFibonacci(n-2, memo);
        memo[n] = res;
    }
    return memo[n];
}

int main(){
    n = 5;
    vector<int>memo(n+1, -1);
    cout<<nthFibonacci(n, memo)<<endl;
}