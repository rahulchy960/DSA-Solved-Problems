class Solution {
public:
    void helper(vector<int>& candidates, int target, int level, vector<vector<int>>&res, vector<int>&curr){
        
        if(target < 0) return;
        if(target == 0){
            res.push_back(curr);
            return;
        }
        for(int i=level;i<candidates.size();i++){
            if(i>level && candidates[i] == candidates[i-1]) continue;
            if(candidates[i] > target) break;
            curr.push_back(candidates[i]);
            helper(candidates, target-candidates[i], i+1, res, curr);
            curr.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>>res;
        vector<int>curr;
        int level=0;
        helper(candidates, target, level, res, curr);
        return res;
    }
};

// Algorithm: Combination Sum II (Backtracking with Duplicate Handling)
// --------------------------------------------------------------------
// Problem:
//   - Given a list of candidate numbers (with possible duplicates) and a target,
//     return all unique combinations where the candidate numbers sum to the target.
//   - Each number may only be used once in each combination.
//   - Combinations must be unique (no duplicates in result).
//
// Approach:
//   - Sort the candidates to make duplicate elements adjacent.
//   - Use backtracking to build combinations.
//   - At each level:
//       - Skip duplicates: If candidates[i] == candidates[i-1] and i > level, continue.
//       - If current candidate > target, break early (since array is sorted).
//       - Recur with the next index (i+1) because each element is used only once.
//
// Base Cases:
//   - If target == 0 → valid combination → add to result
//   - If target < 0 → invalid path → return
//
// Time Complexity: O(2^n)
//   - In the worst case, we explore all subsets of the array.
//   - Pruning due to early break and duplicate checks improves practical performance.
//
// Space Complexity: O(k) recursion stack (where k is the depth of recursion)
//   - Plus O(#combinations × average length) for storing results

class Solution {
public:
    // Helper function for backtracking
    void helper(vector<int>& candidates, int target, int level,
                vector<vector<int>>& res, vector<int>& curr) {

        if (target < 0) return;         // Overshot target
        if (target == 0) {              // Valid combination
            res.push_back(curr);
            return;
        }

        for (int i = level; i < candidates.size(); i++) {
            // Skip duplicates at the same recursion level
            if (i > level && candidates[i] == candidates[i - 1]) continue;

            // Early termination: no need to consider elements larger than target
            if (candidates[i] > target) break;

            curr.push_back(candidates[i]); // Choose current element
            helper(candidates, target - candidates[i], i + 1, res, curr); // Move to next index
            curr.pop_back(); // Backtrack
        }
    }

    // Main function
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // Sort to handle duplicates & enable pruning
        vector<vector<int>> res;
        vector<int> curr;
        helper(candidates, target, 0, res, curr);
        return res;
    }
};
