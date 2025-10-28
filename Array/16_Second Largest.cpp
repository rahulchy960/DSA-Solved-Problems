class Solution {
  public:
    int getSecondLargest(vector<int> &arr) {
        // code here
        int largest = arr[0];
        int res = -1;
        for(int i=1;i<arr.size();i++){
            if(arr[i] > largest){
                res = largest;
                largest = arr[i];
            }
            else if(arr[i] > res && arr[i] != largest){
                res = arr[i];
            }
        }
        return res;
    }
};