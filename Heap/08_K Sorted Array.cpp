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

// User function template for C++

class Solution {
  public:

    /*
    Algorithm (Min-Heap / Priority Queue):
    - A k-sorted array is an array where each element is at most k positions away from its target position.
    - Use a min-heap of size k+1 to efficiently sort the array:
        1. Insert the first k+1 elements into the heap.
        2. For the rest of the array, do:
            - Extract the minimum element from the heap and place it at the correct position.
            - Insert the next element from the array into the heap.
        3. Once done, extract and place the remaining elements from the heap.

    Time Complexity:
    - O(n log k)
      - Initial heap creation: O(k)
      - For each of the remaining n-k elements: insertion and removal take O(log k)

    Space Complexity:
    - O(k) for the heap
    */

    void SortK(int arr[], int n, int k) {
        // Min-heap to keep track of the k+1 smallest elements
        priority_queue<int, vector<int>, greater<int>> pq;

        // Step 1: Push first k+1 elements to the min-heap
        for (int i = 0; i <= k; i++) {
            pq.push(arr[i]);
        }

        int index = 0;

        // Step 2: For remaining elements, extract min and insert current element
        for (int i = k + 1; i < n; i++) {
            arr[index++] = pq.top(); // Place the smallest so far
            pq.pop();
            pq.push(arr[i]);         // Insert the next unsorted element
        }

        // Step 3: Empty the remaining elements from the heap
        while (!pq.empty()) {
            arr[index++] = pq.top();
            pq.pop();
        }
    }
};
