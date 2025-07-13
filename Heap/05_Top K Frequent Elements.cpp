class Solution {
public:
    struct myCmp{
        bool operator()(pair<int,int>p1, pair<int,int>p2){
            return p1.second<p2.second;
        }
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int>map;
        for(int i=0;i<nums.size();i++){
            map[nums[i]]++;
        }
        // priority_queue<pair<int,int>, vector<pair<int,int>>, myCmp>pq(map.begin(), map.end());
        // vector<int>res;
        // while(k--){                           /* heap based solution */
        //     res.push_back(pq.top().first);
        //     pq.pop();
        // }
        // return res;

        vector<vector<int>>freq(nums.size()+1);
        for(auto x: map){
            freq[x.second].push_back(x.first);
        }

        vector<int>res;
        int count=0;
        for(int i=nums.size();i>=0;i--){
            for(auto x: freq[i]){
                res.push_back(x);
                count++;
                if(count == k) return res;
            }
                
        }

        return res;
    }
};



class Solution {
public:
    // Custom comparator for the max heap
    struct myCmp {
        bool operator()(pair<int, int> p1, pair<int, int> p2) {
            return p1.second < p2.second; // higher frequency has higher priority
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Step 1: Count frequency of each element
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]]++;
        }

        // ----------------------------------------------------------------
        // Option 1: Max-Heap approach
        // ----------------------------------------------------------------
        // Algorithm:
        // - Push all (element, frequency) pairs into a max heap.
        // - Extract top k elements with highest frequencies.

        // Time Complexity: 
        //   - Building frequency map: O(n)
        //   - Inserting into heap: O(n log n)
        //   - Extracting k elements: O(k log n)
        //   - Total: O(n log n)
        //
        // Space Complexity: O(n) for frequency map + heap

        /*
        priority_queue<pair<int,int>, vector<pair<int,int>>, myCmp> pq(map.begin(), map.end());
        vector<int> res;
        while (k--) {
            res.push_back(pq.top().first);
            pq.pop();
        }
        return res;
        */

        // ----------------------------------------------------------------
        // Option 2: Bucket Sort approach (Optimized)
        // ----------------------------------------------------------------
        // Algorithm:
        // - Create a frequency map.
        // - Use a "bucket" array where index = frequency, and store elements in that bucket.
        // - Traverse from highest frequency to lowest and collect elements.

        // Time Complexity:
        //   - Frequency map: O(n)
        //   - Bucket creation: O(n)
        //   - Bucket traversal: O(n + k) => worst case O(n)
        //   - Total: O(n)
        //
        // Space Complexity: O(n) for map + buckets + result

        vector<vector<int>> freq(nums.size() + 1);
        for (auto x : map) {
            freq[x.second].push_back(x.first); // push element into frequency bucket
        }

        vector<int> res;
        int count = 0;

        // Traverse from highest frequency to lowest
        for (int i = nums.size(); i >= 0; i--) {
            for (auto x : freq[i]) {
                res.push_back(x);
                count++;
                if (count == k) return res;
            }
        }

        return res;
    }
};
