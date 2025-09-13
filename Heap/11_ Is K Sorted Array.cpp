// User function template for C++

class Solution {
  public:
    string isKSortedArray(int arr[], int n, int k) {
       vector<pair<int, int>> v;
        for(int i = 0; i < n; i++) {
            v.push_back({arr[i], i});
        }

        sort(v.begin(), v.end());

        for(int i = 0; i < n; i++) {
            if(abs(v[i].second - i) > k) {
                return "No";
            }
        }

        return "Yes";
    
       // code here.
    }
};


class Solution {
  public:

    /*
    Algorithm:
    - An array is called k-sorted if each element is at most k positions away from its sorted position.
    - Steps:
        1. Store each element along with its original index as (value, index) pairs.
        2. Sort the array by value.
        3. After sorting, check if the difference between the original index and the new index
           of any element is more than k → if yes, array is not k-sorted.

    Time Complexity:
    - O(n log n) for sorting the array of pairs

    Space Complexity:
    - O(n) for the auxiliary vector of pairs
    */

    string isKSortedArray(int arr[], int n, int k) {
        vector<pair<int, int>> v;

        // Step 1: Store (value, original_index) pairs
        for (int i = 0; i < n; i++) {
            v.push_back({arr[i], i});
        }

        // Step 2: Sort based on value
        sort(v.begin(), v.end());

        // Step 3: Check how far each element has moved
        for (int i = 0; i < n; i++) {
            if (abs(v[i].second - i) > k) {
                return "No"; // Element moved more than k positions
            }
        }

        return "Yes"; // All elements are within k positions of their original place
    }
};
