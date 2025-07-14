
class Solution {
public:
    void permuteRec(vector<vector<int>>&res, vector<int>&nums, int i){
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


// Algorithm: Generate All Permutations of an Array (Backtracking)
// ---------------------------------------------------------------
// Problem:
//   - Given an array of distinct integers, return all possible permutations.
//
// Approach:
//   - Use recursion and backtracking.
//   - At each recursion level `i`, fix one element at index `i`
//     and recursively generate permutations of the remaining subarray.
//   - For each `j` from i to end:
//       1. Swap nums[i] and nums[j] to fix nums[i].
//       2. Recurse to generate all permutations of nums[i+1..end].
//       3. Backtrack by swapping back to restore the array.
//
// Base Case:
//   - When i == nums.size() - 1, we’ve formed a complete permutation → add to result.
//
// Time Complexity: O(n × n!)
//   - There are n! permutations.
//   - Each permutation takes O(n) time to copy into result.
//
// Auxiliary Space:
//   - O(n) recursion stack (due to depth of recursion)
//   - O(n × n!) for storing all permutations in result

void permuteRec(vector<vector<int>>& res, vector<int>& nums, int i) {
    if (i == nums.size() - 1) {
        res.push_back(nums); // Base case: store the current permutation
        return;
    }

    for (int j = i; j < nums.size(); j++) {
        swap(nums[i], nums[j]);           // Fix element at index i
        permuteRec(res, nums, i + 1);     // Recurse for remaining elements
        swap(nums[j], nums[i]);           // Backtrack to restore original array
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    int i = 0;
    permuteRec(res, nums, i);
    return res;
}
