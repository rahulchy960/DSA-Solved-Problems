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
    // Function to merge k sorted arrays.
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
    Algorithm:
    - We use a min-heap (priority_queue with custom comparator) to efficiently merge K sorted arrays.
    - Initially push the first element of each of the K arrays into the min-heap.
    - Then repeatedly:
        - Extract the smallest element from the heap.
        - Add it to the result array.
        - If the extracted element's array has more elements, push the next element into the heap.

    Time Complexity:
    - O(N log K), where N is the total number of elements across all arrays
        - Inserting and popping from heap takes O(log K)
        - We do this N times
    - N = K * M (if each array has M elements)

    Space Complexity:
    - O(K) for the heap
    - O(N) for the result array
    */