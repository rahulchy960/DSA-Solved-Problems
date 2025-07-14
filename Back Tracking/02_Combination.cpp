class Solution {
public:
    vector<vector<int>>res;

    void combinations(int n, int k, vector<int>&arr, vector<int>&temp, int i=0){
        if(temp.size()==k){
            res.push_back(temp);
            return;
        }
        for(int j=i;j<n;j++){
            temp.push_back(arr[j]);
            combinations(n, k, arr, temp, j+1);
            temp.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<int>arr(n);
        for(int i=0;i<n;i++)
            arr[i] = i+1;
        vector<int>temp;
        combinations(n, k, arr, temp);
        return res;
    }
};


// Algorithm: Generate All Combinations of k numbers out of 1 to n
// ----------------------------------------------------------------
// Problem:
//   - Given two integers n and k, return all possible combinations of k numbers from 1 to n.
//
// Approach: Backtracking
//   1. Generate an array of numbers from 1 to n.
//   2. Use recursion to build combinations of size k.
//   3. At each step, choose whether to include a number at index j (starting from i to n-1).
//   4. If temp.size() == k, we have a valid combination → add it to the result.
//
// Time Complexity: O(C(n, k) × k)
//   - Total C(n, k) combinations.
//   - Each combination takes O(k) time to construct.
//
// Auxiliary Space: O(k) for recursion stack
//   - Plus O(C(n, k) × k) for storing results.


vector<vector<int>> res; // stores all valid combinations

// Recursive helper function to generate combinations
void combinations(int n, int k, vector<int>& arr, vector<int>& temp, int i = 0) {
    if (temp.size() == k) {
        res.push_back(temp); // valid combination found
        return;
    }

    // Try all elements from index i to n-1
    for (int j = i; j < n; j++) {
        temp.push_back(arr[j]);                // Choose current element
        combinations(n, k, arr, temp, j + 1);  // Recurse to build rest
        temp.pop_back();                       // Backtrack to explore other choices
    }
}

// Main function to prepare the input and start recursion
vector<vector<int>> combine(int n, int k) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = i + 1; // Fill array with 1 to n

    vector<int> temp;   // Temporary vector to hold current combination
    res.clear();        // Clear global result before use
    combinations(n, k, arr, temp); // Start backtracking
    return res;
}

