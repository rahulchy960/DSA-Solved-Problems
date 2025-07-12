#include<bits/stdc++.h>
using namespace std;

class minHeap{ 
    int *arr;
    int size;
    int capacity;
    public:
    minHeap(int capacity){
        this->capacity = capacity;
        size = 0;
        arr = new int[capacity];
    }
    int getLeftChild(int i){
        if((2*i+1) < size)
            return (2*i+1);
        return INT_MAX;
    }
    int getRightChild(int i){
        if((2*i+2) < size)
            return (2*i+2);
        return INT_MAX;
    }
    int getParent(int i){
        if((i-1)/2 >= 0)
            return (i-1)/2;
        return INT_MAX;
    }
    void Insert(int x);
    void display();
    void Heapify(int idx);
    int getMin();
    int extractMin();
    void decreaseKey(int idx, int x);
    int Delete(int idx);
    void buildHeap();
    
};

void minHeap::Insert(int x){
    if(size == capacity){
        cout<<"Heap OverLoaded"<<endl;
        return;
    }
    size++;
    arr[size-1] = x;
    for(int i=size-1; i!=0 && arr[i]<arr[getParent(i)];){
        swap(arr[i], arr[getParent(i)]);
        i = getParent(i);
    }       
}

void minHeap::display(){
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void minHeap::Heapify(int idx){  
    int smallest = idx;
    int left = getLeftChild(idx);
    int right = getRightChild(idx);
    if(left < size && arr[left]<arr[smallest])
        smallest = left;
    if(right<size && arr[right]<arr[smallest])
        smallest = right;
    if(smallest != idx){ // violation in heap
        swap(arr[idx], arr[smallest]);
        Heapify(smallest);
    }
}

int minHeap::getMin(){
    if(size == 0)
        return INT_MAX;
    return arr[0];
}

int minHeap::extractMin(){
    if(size == 0)
        return INT_MAX;
    swap(arr[0], arr[size-1]);
    size--;
    Heapify(0);
    return arr[size];
}

void minHeap::decreaseKey(int idx, int x){  // the new key should be smaller than the previous key 
    arr[idx] = x;
    while(idx!=0 && arr[idx] < arr[getParent(idx)]){
        swap(arr[idx], arr[getParent(idx)]);
        idx = getParent(idx);
    }
}

// void minHeap::decreaseKey(int idx, int x){  
//     if(idx < size){
//         arr[idx] = x;
//         swap(arr[0], arr[idx]);
//         Heapify(0);
//     }
// }


int minHeap::Delete(int idx){
    int del = arr[idx];
    decreaseKey(idx, INT_MIN);
    extractMin();
    return del;
}


void minHeap::buildHeap(){
        for(int i= (size-2)/2; i>=0 ; i++){   // i = (size-2)/2  is the buttom most right most internal node
            Heapify(i);  // heapify can only fix one possible violation but for a random array we must call heapify
                        // for all nodes bacause the assumtion for heapify is when we call min or max heapify its
        }               // left and right child must be heapified
}

int main(){
    minHeap heap(5);
    heap.Insert(20);
    heap.Insert(10);
    heap.Insert(25);
    heap.Insert(5);
    heap.Insert(15);
    heap.Insert(50);
    heap.display();
    // cout<<heap.getMin()<<endl;
    cout<<heap.extractMin()<<endl;
    // cout<<heap.extractMin()<<endl;
    // cout<<heap.extractMin()<<endl;
    // cout<<heap.extractMin()<<endl;
    // cout<<heap.extractMin()<<endl;
    // cout<<heap.extractMin()<<endl;
    heap.display();
    heap.decreaseKey(2, 5);
    heap.display();
    cout<<heap.Delete(3)<<endl;
    heap.display();
    cout<<heap.extractMin()<<endl;
    heap.display();

}



// Implementation of a Min Heap data structure:
// --------------------------------------------
// A Min Heap is a binary tree where:
//   - Every parent node is less than or equal to its children.
//   - It is a complete binary tree (all levels fully filled except possibly the last, filled from left to right).
//
// Key Operations:
// 1. Insert(x)     → Insert element and maintain heap property
// 2. getMin()      → Return the minimum element (root) in O(1)
// 3. extractMin()  → Remove and return the minimum element and re-heapify
// 4. decreaseKey() → Decrease the value of a key and restore heap
// 5. Delete(idx)   → Delete a node at index `idx`
// 6. buildHeap()   → Convert a random array into a valid min-heap in O(n)

class minHeap {
    int* arr;       // pointer to heap array
    int size;       // current number of elements in heap
    int capacity;   // maximum number of elements heap can hold

public:
    minHeap(int capacity) {
        this->capacity = capacity;
        size = 0;
        arr = new int[capacity]; // dynamic array allocation
    }

    // Return index of left child of node at index i
    int getLeftChild(int i) {
        if ((2 * i + 1) < size) return (2 * i + 1);
        return INT_MAX; // Invalid index
    }

    // Return index of right child of node at index i
    int getRightChild(int i) {
        if ((2 * i + 2) < size) return (2 * i + 2);
        return INT_MAX; // Invalid index
    }

    // Return index of parent of node at index i
    int getParent(int i) {
        if (i > 0) return (i - 1) / 2;
        return INT_MAX; // Root has no parent
    }

    void Insert(int x);               // Insert new key x
    void display();                   // Print heap array
    void Heapify(int idx);            // Maintain heap property from idx down
    int getMin();                     // Return minimum element (root)
    int extractMin();                 // Remove and return minimum element
    void decreaseKey(int idx, int x); // Decrease value at idx to x
    int Delete(int idx);             // Delete node at idx
};

/*
Algorithm: Insert(x)
--------------------
1. If heap is full, return error.
2. Insert x at the end of the array (arr[size]).
3. While x is smaller than its parent:
   - Swap it with parent
   - Move index to parent's index
Time: O(log N)
*/
void minHeap::Insert(int x) {
    if (size == capacity) {
        cout << "Heap OverLoaded" << endl;
        return;
    }
    size++;
    arr[size - 1] = x;

    // Fix the min heap property if violated
    for (int i = size - 1; i != 0 && arr[i] < arr[getParent(i)];) {
        swap(arr[i], arr[getParent(i)]);
        i = getParent(i);
    }
}

/*
Algorithm: display()
--------------------
Prints all elements in the heap array.
Time: O(N)
*/
void minHeap::display() {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*
Algorithm: Heapify(idx)
------------------------
1. Compare the node at idx with its left and right child.
2. If smallest is not idx:
   - Swap with smallest child
   - Recursively call Heapify on smallest
Time: O(log N)
*/
void minHeap::Heapify(int idx) {
    int smallest = idx;
    int left = getLeftChild(idx);
    int right = getRightChild(idx);

    if (left < size && arr[left] < arr[smallest])
        smallest = left;

    if (right < size && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(arr[idx], arr[smallest]);
        Heapify(smallest); // recurse
    }
}

/*
Algorithm: getMin()
--------------------
Return root (min element).
If heap is empty, return INT_MAX.
Time: O(1)
*/
int minHeap::getMin() {
    if (size == 0)
        return INT_MAX;
    return arr[0];
}

/*
Algorithm: extractMin()
------------------------
1. Replace root with last element.
2. Reduce heap size.
3. Call Heapify on root.
4. Return the removed minimum element.
Time: O(log N)
*/
int minHeap::extractMin() {
    if (size == 0)
        return INT_MAX;

    swap(arr[0], arr[size - 1]);
    size--;
    Heapify(0);

    return arr[size]; // return removed min
}

/*
Algorithm: decreaseKey(idx, x)
-------------------------------
1. Replace arr[idx] with x.
2. While arr[idx] < arr[parent(idx)], swap up.
Time: O(log N)
*/
void minHeap::decreaseKey(int idx, int x) {
    arr[idx] = x;
    while (idx != 0 && arr[idx] < arr[getParent(idx)]) {
        swap(arr[idx], arr[getParent(idx)]);
        idx = getParent(idx);
    }
}

/*
Algorithm: Delete(idx)
-----------------------
1. Replace arr[idx] with INT_MIN using decreaseKey().
2. Call extractMin() to remove it.
Time: O(log N)
*/
int minHeap::Delete(int idx) {
    int del = arr[idx];        // store value for return
    decreaseKey(idx, INT_MIN); // bubble to root
    extractMin();              // remove root
    return del;
}

/*
buildHeap():
------------
Builds heap from current array of size `size`.
Used when initial array is filled without heap property.

Algorithm:
-----------
1. Start from the buttom most right most internal node: (size - 2) / 2
2. Apply Heapify on each internal node from bottom to top.
Time: O(N)
*/
void minHeap::buildHeap() {
    for (int i = (size - 2) / 2; i >= 0; i--) {
        Heapify(i);
    }
}


