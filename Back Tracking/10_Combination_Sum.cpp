#include<bits/stdc++.h>
using namespace std;

//  Leetcode 39 : Combination Sum

class Solution {
    public:
    void helper(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int> curr, int n) {
        
        if (target<0) return;   // Base case 1: If the target becomes negative, no valid combination exists
        
        if (n<=0) return;     // Base case 2: If no more elements are left to consider, stop the recursion

        if (target == 0) {     // Base case 3: If the target is zero, a valid combination has been found
            res.push_back(curr); // Add the current combination to the result list
            return;
        }
        
        helper(candidates,target,res,curr,n-1);  // case 1: do not include the current element and move to the next
        
        curr.push_back(candidates[n-1]); // case 2: Include the current element in the combination
        helper(candidates,target-candidates[n-1],res,curr,n); 

        curr.pop_back();   // Backtrack by removing the last element to explore other combinations
    }
    
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            vector<vector<int>>res;
            vector<int>curr;
            helper(candidates, target, res, curr, candidates.size());
            return res;
        }
    };