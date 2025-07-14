// Approach is like generate subsets 


#include<bits/stdc++.h>
using namespace std;

int countSubsetSum(int arr[], int n, int sum){ // Time -> O(2^n)  Aux -> O(n)

    if(n==0) 
        return (sum==0)? 1 : 0; 
    
    return countSubsetSum(arr, n-1, sum-arr[n-1]) + countSubsetSum(arr, n-1, sum);
    
}

int main(){
    int arr[] = {10, 5, 2, 3, 6};
    int sum = 8;
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<countSubsetSum(arr, n, sum)<<endl;    
}




// Algorithm: Count the number of subsets with given sum
// ------------------------------------------------------
// Problem:
//   - Given an array of integers and a target sum,
//   - Count how many subsets exist such that the subset sum equals the target.
//
// Approach:
//   - Use recursion similar to subset generation.
//   - At each index `n`, we have two choices:
//       1. Include the current element in the sum → call with (sum - arr[n-1])
//       2. Exclude the current element → call with same sum
//   - Base case:
//       - If n == 0 and sum == 0 → 1 valid subset found
//       - If n == 0 and sum != 0 → no subset found
//
// Time Complexity: O(2^n)
//   - Each element can be either included or excluded → 2^n combinations
//
// Auxiliary Space: O(n)
//   - Maximum recursion depth is `n` (number of elements)

int countSubsetSum(int arr[], int n, int sum) {
    if (n == 0)
        return (sum == 0) ? 1 : 0;

    // Count subsets including and excluding the current element
    return countSubsetSum(arr, n - 1, sum - arr[n - 1]) +
           countSubsetSum(arr, n - 1, sum);
}



