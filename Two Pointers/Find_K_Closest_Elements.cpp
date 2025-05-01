#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<int> findClosestElements(vector<int>& arr, int k, int x) {
            /* priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int, int>>>pq;
            for(int i=0;i<arr.size();i++)
                pq.push({abs(arr[i]-x),i});
            vector<int>res;
            while(k--){
                res.push_back(arr[pq.top().second]);   // my solution (min heap and sorting based)
                pq.pop(); 
            }
            sort(res.begin(),res.end());
            return res;
            */
    
            // as the array is sorted we can use binary search like two pointer approach to solve this in O(n) time 
            int low = 0, high = arr.size()-1;
            while(high-low >= k){
                if(abs(arr[low]-x) > abs(arr[high]-x))   // if the diff in left side greater we move the left pointer
                    low++;
                else       // else we move the right pointer
                    high--;    
            }
            vector<int>res;  
            for(int i=low;i<=high;i++)   // min diff of element lies on low to high both included
                res.push_back(arr[i]);
            
            return res;
    
        }
    };