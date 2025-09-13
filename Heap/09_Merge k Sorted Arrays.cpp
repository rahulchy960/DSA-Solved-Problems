struct triplet{
    int val;
    int arrPos;
    int nestedArrPos;
    triplet(int vall, int ap, int vp){
        val = vall;
        arrPos = ap;
        nestedArrPos = vp;
    }
};

struct myCmp{
    bool operator()(triplet t1, triplet t2){
        return t1.val > t2.val;
    }
};

class Solution {
  public:
    vector<int> mergeKArrays(vector<vector<int>> arr, int K) {
        // code here
        priority_queue<triplet, vector<triplet>, myCmp>pq;
        for(int i=0;i<arr.size();i++){
            pq.push(triplet(arr[i][0], i, 0));
        }
        
        vector<int>res;
        while(!pq.empty()){
            
            triplet t = pq.top();
            pq.pop();
            res.push_back(t.val);
            
            int ap = t.arrPos;
            int vp = t.nestedArrPos;
            if(vp+1 < arr[ap].size())
                pq.push(triplet(arr[ap][vp+1], ap, vp+1));
        }
        return res;
        
    }
};


/*
==================== REVISION BLOCK — Merge K Sorted Arrays ====================

Idea
----
Use a **min-heap of size ≤ K** that always exposes the smallest current head among the K arrays.
Pop the smallest, append to output, and push the next element from the same array.

Pattern
-------
Greedy + Heap (k-way merge). Equivalent to the merge phase of a K-way merge sort.

Algorithm
---------
1) For every non-empty array i, push (arr[i][0], i, 0) into a min-heap.
2) While heap not empty:
   a) Pop (val, i, j) — the smallest available element.
   b) Append val to the result.
   c) If j+1 < arr[i].size(), push (arr[i][j+1], i, j+1).
3) Return the result.

Correctness
-----------
At each step, the heap’s top is the globally smallest not-yet-output element across all arrays.
Appending it maintains global sort order; pushing its successor preserves future candidates.

Complexity
----------
Let N = total number of elements across all arrays, and K = number of arrays.
- Time: O(N log K) (each push/pop is O(log K), done O(N) times).
- Space: O(K) extra for the heap (plus O(N) for the output).

Edge Cases
----------
- Some arrays may be empty → skip pushing their heads.
- K may not equal arr.size(); use arr.size() to iterate safely.
- Large N: reserve output capacity to avoid reallocations.

Pitfalls
--------
- Don’t index arr[i][0] if arr[i] is empty.
- Comparator must be strict and accept **const** refs in priority_queue.
*/

struct Item {
    int val;
    int row;  // which array
    int col;  // index within that array
    Item(int v, int r, int c) : val(v), row(r), col(c) {}
};

struct MinCmp {
    bool operator()(const Item& a, const Item& b) const {
        return a.val > b.val;  // min-heap
    }
};

class Solution {
  public:
    // Function to merge k sorted arrays.
    std::vector<int> mergeKArrays(std::vector<std::vector<int>> arr, int /*K*/) {
        using std::vector;

        // Reserve total size to minimize reallocations
        size_t total = 0;
        for (const auto& v : arr) total += v.size();
        vector<int> res;
        res.reserve(total);

        std::priority_queue<Item, std::vector<Item>, MinCmp> pq;

        // Push first element of each non-empty array
        for (int i = 0; i < (int)arr.size(); ++i) {
            if (!arr[i].empty()) {
                pq.emplace(arr[i][0], i, 0);
            }
        }

        // K-way merge
        while (!pq.empty()) {
            Item cur = pq.top(); pq.pop();
            res.push_back(cur.val);

            int ni = cur.row, nj = cur.col + 1;
            if (nj < (int)arr[ni].size()) {
                pq.emplace(arr[ni][nj], ni, nj);
            }
        }
        return res;
    }
};

/* ==================== Optional: Divide & Conquer (also O(N log K)) ====================
Merge arrays pairwise like merge sort to reduce heap overhead for small K.

std::vector<int> mergeTwo(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> out; out.reserve(a.size() + b.size());
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size())
        out.push_back(a[i] <= b[j] ? a[i++] : b[j++]);
    while (i < a.size()) out.push_back(a[i++]);
    while (j < b.size()) out.push_back(b[j++]);
    return out;
}

std::vector<int> mergeAll(std::vector<std::vector<int>>& arr) {
    if (arr.empty()) return {};
    int n = arr.size();
    while (n > 1) {
        int w = 0;
        for (int i = 0; i + 1 < n; i += 2)
            arr[w++] = mergeTwo(arr[i], arr[i+1]);
        if (n % 2 == 1) arr[w++] = std::move(arr[n-1]);
        n = w;
    }
    return arr[0];
}
*/
