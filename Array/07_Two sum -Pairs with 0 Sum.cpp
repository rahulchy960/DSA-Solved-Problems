// User function template for C++

class Solution {
  public:
    vector<vector<int>> getPairs(vector<int>& arr) {
        // code here
        sort(arr.begin(), arr.end());
        
        vector<vector<int>>res;
        
        int i=0, j=arr.size()-1;
        int n = arr.size();
        while(i<j){
            if(arr[i]+arr[j] < 0)
                i++;
            else if(arr[i]+arr[j] >0)
                j--;
            else{
                vector<int>temp;
                temp.push_back(arr[i]);
                temp.push_back(arr[j]);
                res.push_back(temp);
                i++;
                j--;
            }
            while(i>0 && i<n && arr[i]==arr[i-1])
                i++;
            while(j<n-1 && j>=i && arr[j]==arr[j+1])
                j--;
            
        }
        
        return res;
    }
};