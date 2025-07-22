int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n);
        dp[0] = 1;
        for(int i=1;i<n;i++){
            dp[i] = 1;   // At minimum, LIS ending at i is 1 (itself)
            for(int j=0;j<i;j++){
                if(nums[j]<nums[i])
                    dp[i] = max(dp[i], dp[j]+1);
            }
        }
        return *max_element(dp.begin(), dp.end());  // Length of longest subsequence
    }

// Algorithm: Longest Increasing Subsequence (O(n²) Dynamic Programming)
// ----------------------------------------------------------------------
// Problem:
//   - Given an array of integers, return the length of the longest increasing subsequence.
//
// Approach:
//   - Use dynamic programming to build the LIS ending at each index.
//   - Create a dp[] array where:
//       - dp[i] = length of longest increasing subsequence ending at index i
//   - For each index i from 1 to n-1:
//       - For each j from 0 to i-1:
//           - If nums[j] < nums[i], then we can extend the LIS ending at j
//           - dp[i] = max(dp[i], dp[j] + 1)
//
// Base Case:
//   - dp[0] = 1 → the LIS ending at the first element is itself.
//
// Final Result:
//   - The maximum value in dp[] is the length of the longest increasing subsequence.
//
// Time Complexity: O(n²)
//   - Two nested loops over the array.
//
// Space Complexity: O(n)
//   - One array to store LIS lengths.



////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Solution {
public:

    int ceil(vector<int>&nums, int key){
        int l = 0;
        int r = nums.size()-1;
        while(l<r){
            int mid = l + (r-l)/2;
            if(nums[mid]>=key)
                r = mid;
            else
                l = mid+1;
        }
        return r;
    }

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int>lis;
        lis.push_back(nums[0]);
        for(int i=1;i<n;i++){
            if(nums[i]>lis.back())
                lis.push_back(nums[i]);
            else{
                int ceilIdx = ceil(lis, nums[i]);
                lis[ceilIdx] = nums[i];
            }
        }
        return lis.size();
    }
};


// Algorithm: Find the Ceiling Index of a Key in a Sorted Array (Binary Search)
// -----------------------------------------------------------------------------
// Problem:
//   - Given a sorted array `nums` and a target `key`, return the index of the
//     **ceiling** of the key:
//       → the smallest element in the array that is ≥ key.
//
// Approach:
//   - Use binary search:
//       - If nums[mid] ≥ key → potential ceiling → move left (r = mid)
//       - Else → move right (l = mid + 1)
//   - Loop ends when l == r → this is the smallest index where nums[index] ≥ key
//
// Edge Case:
//   - If no element ≥ key exists (i.e., key > nums.back()), this returns index out of bounds.
//     You should handle that separately if required.
//
// Time Complexity: O(log n)
//   - Binary search over sorted array of size n.
//
// Space Complexity: O(1)
//   - Constant extra space used.

int ceil(vector<int>& nums, int key) {
    int l = 0;
    int r = nums.size() - 1;

    while (l < r) {
        int mid = l + (r - l) / 2;

        if (nums[mid] >= key)
            r = mid;        // move left to find smaller ≥ key
        else
            l = mid + 1;    // move right
    }

    // After the loop, l == r → possible ceiling index
    // Caller should ensure that nums[l] ≥ key before using it
    return r;
}




// Algorithm: Longest Increasing Subsequence (O(n log n) using Binary Search)
// ---------------------------------------------------------------------------
// Problem:
//   - Given an array `nums`, return the length of the longest increasing subsequence.
//
// Optimized Approach (Patience Sorting + Binary Search):
//   - Maintain a vector `lis` where:
//       - Each element represents the smallest possible tail value of an increasing subsequence of that length.
//   - For each element in `nums`:
//       1. If it is greater than the last element in `lis`, append it → extends LIS.
//       2. Else, replace the **first element in `lis` that is ≥ nums[i]** → maintains minimal tail.
//
//   - Use binary search to find the ceiling index in `lis`.
//
// Time Complexity: O(n log n)
//   - For each element, perform a binary search on `lis`: O(log n)
//   - Total for n elements: O(n log n)
//
// Space Complexity: O(n)
//   - For storing the `lis` array

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> lis;

        lis.push_back(nums[0]);  // Start with first element

        for (int i = 1; i < n; i++) {
            if (nums[i] > lis.back()) {
                // Extend the LIS
                lis.push_back(nums[i]);
            } else {
                // Replace the first element ≥ nums[i]
                int ceilIdx = ceil(lis, nums[i]);
                lis[ceilIdx] = nums[i];
            }
        }

        return lis.size();  // Length of longest increasing subsequence
    }


