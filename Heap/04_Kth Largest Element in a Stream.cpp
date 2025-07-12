class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>>pq;
    int isK;
    KthLargest(int k, vector<int>& nums) {
        isK = k;
        if(nums.size()){
            for(int i=0;i<k && i<nums.size();i++){
                pq.push(nums[i]);
            }
            for(int i=k;i<nums.size();i++){
                if(pq.top()<nums[i]){
                    pq.pop();
                    pq.push(nums[i]);
                }
            }
        }
            
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size()>isK){
            pq.pop();
        }
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */




 // Problem: Design a class to continuously maintain the K-th largest element
// in a stream of numbers.
//
// Approach:
// ---------
// 1. Use a Min Heap (priority_queue with greater<int>) to store the **top k largest elements**.
// 2. The smallest element in this heap (pq.top()) will be the K-th largest overall.
// 3. Constructor logic:
//    - Insert the first k elements directly into the heap.
//    - For remaining elements:
//        - If the current element is larger than the smallest in the heap,
//          pop the smallest and insert the current one.
//    - This ensures that the heap always has the **k largest elements**.
// 4. add(val) method:
//    - Insert the new value into the heap.
//    - If heap size exceeds k, remove the smallest (since we want only k largest).
//    - Return pq.top(), which is the current K-th largest.

class KthLargest {
public:
    // Min heap to keep track of the top k largest elements
    priority_queue<int, vector<int>, greater<int>> pq;
    int isK; // the value of k

    // Constructor
    KthLargest(int k, vector<int>& nums) {
        isK = k;

        // Step 1: Insert first k elements
        for (int i = 0; i < k && i < nums.size(); i++) {
            pq.push(nums[i]);
        }

        // Step 2: For the rest of the elements, maintain top k largest
        for (int i = k; i < nums.size(); i++) {
            if (pq.top() < nums[i]) {
                pq.pop();        // Remove smallest of top k
                pq.push(nums[i]); // Insert current element
            }
        }
    }

    // Add a new value to the stream and return the K-th largest element
    int add(int val) {
        pq.push(val);

        // If size exceeds k, remove the smallest
        if (pq.size() > isK) {
            pq.pop();
        }

        // Return the K-th largest (top of min heap)
        return pq.top();
    }
};

/**
 * Usage:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
