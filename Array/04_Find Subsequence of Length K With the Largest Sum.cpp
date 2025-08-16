class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<pair<int,int>>arr;
        vector<pair<int,int>>res;
        for(int i=0;i<nums.size();i++){
            arr.push_back({nums[i],i});
        }
        sort(arr.begin(),arr.end());
        int idx=arr.size()-1;
        while(k--){
            res.push_back({arr[idx].second, nums[arr[idx].second]});
            idx--;
        }
        sort(res.begin(), res.end());
        
        vector<int>ans;
        for(int i=0;i<res.size();i++){
            ans.push_back(res[i].second);
        }
        return ans;
        
    }
};









/*
==================== REVISION BLOCK ====================

Problem (Max-Sum Subsequence of Length K, keep order):
- Pick a subsequence of exactly k elements (preserving original order) whose sum is maximum.
- Return the subsequence (not indices).

Pattern:
- Select top-k by value, then restore original order.

Algorithm:
1) Pair each element with its index: (value, index).
2) Sort pairs by value ascending.
3) Take the last k pairs (largest values).
4) Sort these k pairs by original index ascending to preserve order.
5) Output their values in this order.

Why correct:
- Steps 1–3 pick the k elements with the largest values (maximizes sum).
- Step 4 reorders them by original index, making a valid subsequence.

Complexity:
- Time: O(n log n) for the main sort + O(k log k) to resort k picks ⇒ O(n log n).
- Space: O(n) for the auxiliary pair arrays.

Edge cases:
- k == 0 → empty result.
- k == n → whole array.
- Duplicates/negatives: handled naturally by sorting by value; secondary sort by index keeps order.

========================================================
*/

class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        // (value, index) for selecting by largest values
        vector<pair<int,int>> arr;
        arr.reserve(nums.size());
        for (int i = 0; i < (int)nums.size(); i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by value (ascending)
        sort(arr.begin(), arr.end());

        // Take top-k by value, but store as (index, value) to ease ordering by index next
        vector<pair<int,int>> picked;
        picked.reserve(k);
        int idx = (int)arr.size() - 1;
        while (k--) {
            picked.push_back({arr[idx].second, nums[arr[idx].second]});
            idx--;
        }

        // Restore original order: sort by index
        sort(picked.begin(), picked.end()); // default: sort by first (index)

        // Emit values in original order
        vector<int> ans;
        ans.reserve(picked.size());
        for (int i = 0; i < (int)picked.size(); i++) {
            ans.push_back(picked[i].second);
        }
        return ans;
    }
};
