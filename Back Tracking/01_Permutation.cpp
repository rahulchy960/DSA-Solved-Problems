#include<bits/stdc++.h>
using namespace std;

void helper(vector<int>arr, vector<vector<int>>&res, int i=0){
    if(i==arr.size()-1){   // Base case: If we have reached the last element, store the permutation
        res.push_back(arr);
        return;
    }
    // fixed every character at the 1st position and generate all permutations
    // beginning with that character
    for(int j=i;j<arr.size();j++){  // Swap the current index with all possible indices and recur
        swap(arr[i], arr[j]);   
        helper(arr, res, i+1);  // Recursively generate permutations for the remaining elements
        swap(arr[j], arr[i]);   // Backtrack: Swap back to restore original order
    }
}

vector<vector<int>> permute(vector<int>arr){
    vector<vector<int>>res;
    helper(arr, res);
    return res;
}

int main(){
    vector<int>arr = {10, 20, 30};
    vector<vector<int>>res = permute(arr);
    for(auto x : res){
        for(int i=0;i<x.size();i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
}




/*

class Solution {
public:
    static void permuteRec(vector<vector<int>>&res, vector<int>&nums, int i){
        if(i==nums.size()-1){
            res.push_back(nums);
            return;
        }
        for(int j=i;j<nums.size();j++){
            swap(nums[i], nums[j]);
            permuteRec(res,nums,i+1);
            swap(nums[j],nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        int i = 0;
        permuteRec(res, nums, i);
        return res;
    }
};

*/