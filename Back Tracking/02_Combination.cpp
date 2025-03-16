#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>res; // Stores all possible combinations

// Recursive helper function to generate combinations
void helper(int n, int k, vector<int>&arr, vector<int>&temp, int i=0){

    if(temp.size()==k){   // Base case: If the combination reaches the required size (k), add it to results
        res.push_back(temp);
        return;
    }
    for(int j=i;j<n;j++){   // Iterate through remaining elements starting from index i
        temp.push_back(arr[j]);  // Add the current element to the combination
        helper(n, k, arr, temp, j+1);  // Recursive call for the next index
        temp.pop_back();   // Backtrack by removing the last element
    }
}

void Combinations(int n, int k){
    vector<int>arr(n);
    for(int i=0;i<n;i++)
        arr[i] = i+1;
    vector<int>temp;
    helper(n, k, arr, temp);
}

int main(){
    int n = 5;
    int k = 2;
    Combinations(n, k);
    for(auto x : res){
        for(int i=0;i<x.size();i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
}