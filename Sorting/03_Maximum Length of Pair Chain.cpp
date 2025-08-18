
bool myCmp(vector<int>&u, vector<int>&v){
        return u[1] < v[1];
}
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), myCmp);
        int n = pairs.size();
        int count=1;
        int end = 0;
        for(int i=0;i<n;i++){
            if(pairs[end][1]<pairs[i][0]){
                count++;
                end = i;
            }
            
                
        }
        return count;
    }
};



/*
==================== REVISION BLOCK ====================

Problem (Maximum Length of Pair Chain / LC 646):
- You’re given pairs [a, b]. One pair can follow another only if previous.b < current.a.
- Return the maximum number of pairs you can chain.

Pattern:
- Greedy by earliest finishing time (sort by second element, then sweep).

Intuition:
- To fit the most pairs, always keep the pair that finishes earliest, leaving room for more.
- After sorting by end, scan once: take current pair if its start > last chosen end.

Algorithm:
1) Sort pairs by their second value (end) ascending.
2) Keep the first pair → count = 1, end = index of that pair.
3) For each next pair i (in sorted order):
     if pairs[i].start > pairs[end].end  (strictly greater):
         take it → count++, end = i
4) Return count.

Correctness (sketch):
- Classic interval-scheduling optimality: choosing the earliest-finishing compatible interval
  maximizes the number of intervals kept, hence yields the longest chain.

Complexity:
- Time: O(n log n) to sort + O(n) sweep = O(n log n).
- Space: O(1) extra (ignoring the sort’s internals).

Pitfalls:
- Start loop from i=1 (we already chose index 0).
- Strict inequality (<) as per problem: b < c (not ≤).

========================================================
*/

bool myCmp(const std::vector<int>& u, const std::vector<int>& v) {
    return u[1] < v[1]; // sort by end time
}

class Solution {
public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        int n = pairs.size();
        if (n == 0) return 0;

        std::sort(pairs.begin(), pairs.end(), myCmp);

        int count = 1;  // take the first (earliest finishing) pair
        int end = 0;    // index of last chosen pair

        for (int i = 1; i < n; i++) { // start from the next pair
            if (pairs[end][1] < pairs[i][0]) { // strictly non-overlapping for chaining
                count++;
                end = i;                        // update last chosen
            }
        }
        return count;
    }
};
