class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>>pq;
        for(int i=0;i<arr.size();i++)
            pq.push({abs(arr[i]-x),i});
        vector<int>res;
        while(k--){
            res.push_back(arr[pq.top().second]);   // my solution
            pq.pop(); 
        }
        sort(res.begin(),res.end());
        return res;
    }
};

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        
        int low = 0, high = arr.size()-1;
        while(high-low >= k){
            if(abs(arr[low]-x) > abs(arr[high]-x))
                low++;
            else       
                high--;    
        }
        vector<int>res;  
        for(int i=low;i<=high;i++)  
            res.push_back(arr[i]);
        
        return res;

    }
};


/*
==================== REVISION BLOCK — Find K Closest Elements (sorted array) ====================

Idea
----
Maintain a window [low..high] that will shrink to size k. At each step, drop the endpoint
that is **farther** from x. When the window size becomes k, it contains the k closest.

Pattern
-------
Two pointers on a **sorted** array (shrink-window), or a **binary search** on the window’s
left index for an O(log n) solution.

Algorithm (Two-Pointer Shrink, O(n))
------------------------------------
1) low = 0, high = n-1
2) While (high - low + 1) > k:
   - If |arr[low] - x| > |arr[high] - x| → ++low  (drop left, it’s farther)
   - Else → --high                         (drop right; ties favor smaller/left values)
3) Return arr[low..high]

Correctness (sketch)
--------------------
For any window of size k+1, at least one endpoint is not among the k closest to x.
If |arr[low]-x| > |arr[high]-x|, arr[low] is strictly worse than all elements inside
and can be discarded; symmetrically for the right. Repeating yields the optimal k-window.

Complexity
----------
- Two-pointer: Time O(n), Space O(1).
- Binary-search window (below): Time O(log(n-k) + k), Space O(1).

Edge Cases
----------
- k == 0 → []
- k >= n → whole array
- x < arr[0] or x > arr[n-1] → leftmost/rightmost k elements
- Duplicates near x, tie-breaking → this method keeps **smaller values** first (as required).
- Input must be **sorted non-decreasing**.

Pitfalls
--------
- Use `long long` when computing differences to avoid overflow in extreme ranges.
- Ensure loop condition shrinks until length == k (use `while (high - low + 1 > k)`).
*/

class Solution {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
        int n = (int)arr.size();
        if (k <= 0) return {};
        if (k >= n) return arr;

        int low = 0, high = n - 1;
        while (high - low + 1 > k) {
            long long leftDiff  = std::llabs( (long long)arr[low]  - x );
            long long rightDiff = std::llabs( (long long)arr[high] - x );
            if (leftDiff > rightDiff) ++low;   // drop farther left
            else --high;                       // drop right (ties favor left/smaller)
        }

        return std::vector<int>(arr.begin() + low, arr.begin() + high + 1);
    }
};

/* ==================== Optional: Faster Binary-Search Window ====================
Idea:
- The answer is a contiguous window of size k. Binary-search the **left bound** L in [0..n-k].
- Compare distances at the ends: if x - arr[mid] > arr[mid + k] - x → shift right.

Time: O(log(n-k) + k), Space: O(1)
*/
std::vector<int> findClosestElements_bs(std::vector<int>& arr, int k, int x) {
    int n = (int)arr.size();
    if (k <= 0) return {};
    if (k >= n) return arr;

    int lo = 0, hi = n - k;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        // if left endpoint is "worse" than right endpoint, move window right
        if ((long long)x - arr[mid] > (long long)arr[mid + k] - x) lo = mid + 1;
        else hi = mid;
    }
    return std::vector<int>(arr.begin() + lo, arr.begin() + lo + k);
}
