class Solution {
public:
    void helper(vector<int>& candidates, int target, vector<vector<int>>&res, vector<int>&curr, int n){
        if(target<0)return;
        if(n==0)return;
        if(target==0){
            res.push_back(curr);
            return;
        }
        
        helper(candidates,target,res,curr,n-1);
        curr.push_back(candidates[n-1]);
        helper(candidates,target-candidates[n-1],res,curr,n);
        curr.pop_back();
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>>res;
        vector<int>curr;
        helper(candidates, target, res, curr, candidates.size());
        return res;
    }
};





// Algorithm: Combination Sum (Backtracking)
// -----------------------------------------
// Problem:
//   - Given a list of unique candidate numbers and a target,
//     find all unique combinations where the candidate numbers sum to the target.
//   - You may use each number unlimited times.
//
// Approach:
//   - Use backtracking to explore all combinations.
//   - At each step:
//       - You can either include the current element (and stay at the same index)
//       - Or exclude it and move to the next index
//
// Base Cases:
//   - If target < 0 → invalid path → return
//   - If target == 0 → valid combination → add to result
//   - If n == 0 → no more elements to consider → return
//
// Time Complexity: O(2^t), where t = target
//   - In worst case, the number of combinations can be exponential,
//     since each candidate can be chosen multiple times.
//
// Auxiliary Space: O(t) for recursion stack (in worst case),
//   - Plus O(number of valid combinations × average length) to store results

class Solution {
public:
    // Recursive helper to explore combinations
    void helper(vector<int>& candidates, int target, vector<vector<int>>& res, vector<int>& curr, int n) {
        if (target < 0) return;         // Overshot the target
        if (n == 0) return;             // No more elements to consider
        if (target == 0) {              // Found valid combination
            res.push_back(curr);
            return;
        }

        // Option 1: Skip the current element
        helper(candidates, target, res, curr, n - 1);

        // Option 2: Include current element and stay on the same index (can reuse)
        curr.push_back(candidates[n - 1]);
        helper(candidates, target - candidates[n - 1], res, curr, n);
        curr.pop_back(); // Backtrack
    }

    // Main function
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> curr;
        helper(candidates, target, res, curr, candidates.size());
        return res;
    }
};


