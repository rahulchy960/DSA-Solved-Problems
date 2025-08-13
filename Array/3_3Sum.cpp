class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>res;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n-2;i++){
            while(i>0 && i<n && nums[i]==nums[i-1])i++;
            int j=i+1;
            int k=n-1;
            while(j<k){
                if(nums[i]+nums[j]+nums[k]==0){
                    vector<int>temp = {nums[i], nums[j], nums[k]};
                    res.push_back(temp);
                    j++;
                    k--;
                    while(j<k && nums[j]==nums[j-1])j++;
                    while(k>j && nums[k]==nums[k+1])k--;
                }
                else if(nums[i]+nums[j]+nums[k]<0)j++;
                else k--;
            }
        }
        return res;
    }
};


/*
==================== REVISION BLOCK ====================

Problem (3Sum — unique triplets that sum to zero):
- Given an integer array nums, return all UNIQUE triplets [a,b,c] such that a + b + c = 0.

Pattern:
- Sort + Two Pointers + Deduplication.

Intuition:
- After sorting, fix the first element at index i.
- Use two pointers j (i+1) and k (n-1) to find pairs so that nums[i] + nums[j] + nums[k] == 0.
  If the sum is too small, move j right (increase sum); if too large, move k left (decrease sum).
- When you record a valid triplet, advance both pointers and skip duplicates to keep results unique.

Algorithm (step-by-step):
1) Sort nums.
2) For i from 0 to n-3:
   - Skip duplicates for i (so the first element of the triplet is unique).
   - Set j = i+1, k = n-1.
   - While j < k:
       s = nums[i] + nums[j] + nums[k]
       - If s == 0: push triplet; j++, k--; then skip duplicates at j and k.
       - Else if s < 0: j++.
       - Else: k--.
3) Return the list of collected triplets.

Correctness (sketch):
- Sorting enables monotonic adjustments with two pointers for each fixed i.
- Deduplication on i, j, k ensures each unique triplet appears exactly once.

Complexity:
- Time: O(n^2) — O(n log n) to sort plus O(n^2) for the i + two-pointer sweep, dominated by O(n^2).
- Space: O(1) extra (ignoring output), since we sort in place and use constant pointers.

Edge cases / pitfalls:
- Fewer than 3 elements → return empty.
- Arrays with many duplicates → ensure proper skipping at i, j, k.
- Note: A common pattern for skipping i-duplicates is `if (i>0 && nums[i]==nums[i-1]) continue;`
  This implementation uses a `while` inside the loop (works but interacts with the for-loop’s `i++`).

========================================================
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;

        sort(nums.begin(), nums.end());  // sort to enable two-pointer technique

        for (int i = 0; i < n - 2; i++) {
            // Skip duplicate first elements for uniqueness.
            // (Typical alternative is: if (i>0 && nums[i]==nums[i-1]) continue;)
            while (i > 0 && i < n && nums[i] == nums[i - 1]) i++;

            int j = i + 1;        // left pointer
            int k = n - 1;        // right pointer

            while (j < k) {
                long long sum = 1LL * nums[i] + nums[j] + nums[k]; // (guard overflow if values are large)

                if (sum == 0) {
                    res.push_back({nums[i], nums[j], nums[k]});
                    j++; k--;
                    // Skip duplicates at j and k to avoid repeating the same triplet.
                    while (j < k && nums[j] == nums[j - 1]) j++;
                    while (k > j && nums[k] == nums[k + 1]) k--;
                }
                else if (sum < 0) {
                    j++;          // need a larger sum
                } else {
                    k--;          // need a smaller sum
                }
            }
        }
        return res;
    }
};
