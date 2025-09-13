// User function template for C++

class Solution {
  public:
    void SortK(int arr[], int n, int k) {
       priority_queue<int, vector<int>, greater<int>>pq;
       for(int i=0;i<=k;i++){
           pq.push(arr[i]);
       }
       int index=0;
       for(int i=k+1;i<n;i++){
           arr[index++] = pq.top();
           pq.pop();
           pq.push(arr[i]);
       }
       while(!pq.empty()){
           arr[index++] = pq.top();
           pq.pop();
       }
    
       // code here.
    }
};


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


