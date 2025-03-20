#include<bits/stdc++.h>
using namespace std;

int countSubsets(vector<int>&arr, int sum, int n){
    
    if(n==0)      // Base case: If there are no elements left to consider
        return (sum==0)? 1 : 0;   // If the sum become zero, we found a valid subset
    
    if(sum<0)return 0;      // If the remaining sum becomes negative, no valid subset is possible

    // case 1 : Excluding current element
    // case 2 : Including current element and reducing the sum
    return countSubsets(arr,sum,n-1) + countSubsets(arr,sum-arr[n-1],n-1);  
}

int main(){
    vector<int>arr = {1,2,3,4,5};
    int sum = 7;
    cout<<countSubsets(arr, sum, arr.size());    
}