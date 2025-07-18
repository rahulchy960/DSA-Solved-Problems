#include<bits/stdc++.h>
using namespace std;

void print(vector<int>&arr){
    for(int i=0;i<arr.size();i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

void maxHepify(vector<int>&arr,int n,  int i){
    int largest = i;
    int left = 2*i+1, right = 2*i+2;
    if(left<n && arr[left]>arr[largest])
        largest = left;
    if(right<n && arr[right]>arr[largest])
        largest = right;
    if(largest != i){
        swap(arr[largest], arr[i]);
        maxHepify(arr, n, largest);
    }
    
}

void buildHeap(vector<int>&arr, int n){
    for(int i=n/2-1;i>=0;i--){
        maxHepify(arr,n, i);
    }
}

void heapSort(vector<int>&arr){
    buildHeap(arr, arr.size());
    for(int i=arr.size()-1;i>=0;i--){
        swap(arr[i], arr[0]);
        maxHepify(arr,i,0);
    }

}

int main(){
    vector<int>arr = {1, 5, 6, 33, 13, 9, 4, 5, 12, 10, 5};
    print(arr);
    heapSort(arr);
    print(arr);
}




#include <bits/stdc++.h>
using namespace std;

// Utility function to print the array
void print(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

/*
Algorithm:
- Heap Sort is a comparison-based sorting technique based on Binary Heap data structure.
- It builds a max-heap from the input array and then repeatedly extracts the maximum
  element (root of the heap) and moves it to the end of the array.
- After each extraction, it reduces the heap size by 1 and heapifies the root.

Steps:
1. Build a max-heap from the input array using buildHeap().
2. Repeatedly:
   - Swap the root (max) with the last element.
   - Heapify the root element to maintain the max-heap property.
   - Decrease heap size by 1.

Time Complexity:
- Building the heap: O(n)
- Extracting n elements and heapifying: O(n log n)
- Total: O(n log n)

Space Complexity:
- O(1) auxiliary space (sorting is done in-place)
*/

// Maintains the max-heap property for subtree rooted at index i
void maxHepify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1, right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[largest], arr[i]);           // Swap with the largest child
        maxHepify(arr, n, largest);           // Recursively heapify affected subtree
    }
}

// Builds a max heap from the input array
void buildHeap(vector<int>& arr, int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHepify(arr, n, i);
    }
}

// Heap sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Step 1: Build a max heap
    buildHeap(arr, n);

    // Step 2: Extract elements from heap one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);         // Move current root to end
        maxHepify(arr, i, 0);         // Heapify reduced heap
    }
}
