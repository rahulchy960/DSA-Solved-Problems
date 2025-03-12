// Approach is like generate subsets 


#include<bits/stdc++.h>
using namespace std;

int countSubsetSum(int arr[], int n, int sum){ // Time -> O(2^n)  Aux -> O(n)

    if(n==0) // when all elements are included in the subsets
        return (sum==0)? 1 : 0; // if sum == 0 then there is a valid result otherwise no valid result
    
    return countSubsetSum(arr, n-1, sum-arr[n-1]) + countSubsetSum(arr, n-1, sum);
    // we recursively count subset sum equal to sum by including the current element or not including the current element
    
}

int main(){
    int arr[] = {10, 5, 2, 3, 6};
    int sum = 8;
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<countSubsetSum(arr, n, sum)<<endl;    
}
