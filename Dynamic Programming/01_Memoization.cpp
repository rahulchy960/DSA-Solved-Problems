#include<bits/stdc++.h>
using namespace std;
int n;

int nthFibonacci(int n, vector<int> &memo){
    if(memo[n]==-1){    // if the subproblem is not calculated
        int res; 
        if(n==0 || n==1)
            res = n;
        else    
            res = nthFibonacci(n-1, memo) + nthFibonacci(n-2, memo);
        memo[n] = res;  // store the result of subproblems
    }
    return memo[n];  // return the result of already calculated subproblem
}

int main(){
    n = 20;
    vector<int>memo(n+1, -1);
    cout<<nthFibonacci(n, memo)<<endl;
}