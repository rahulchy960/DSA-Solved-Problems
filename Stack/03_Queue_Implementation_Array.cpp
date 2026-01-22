#include<bits/stdc++.h>
using namespace std;

class Queue{
  public: 
    int *arr;
    int front;
    int size;
    int capacity;
    Queue(int cap){
        arr = new int[cap];
        front = 0;
        size = 0;
        capacity = cap;
    }
    bool isEmpty();
    bool isFull();
    int getFront();
    int getRear();
    int getSize();
    int Front();
    int Back();
    bool enQueue(int val);
    void deQueue(); 
};

bool Queue :: isEmpty(){
    return size == 0;
}

bool Queue :: isFull(){
    return size == capacity;
}

int Queue :: getFront(){
    if(isEmpty())
        return -1;
    return front;
}

int Queue :: getRear(){
    if(isEmpty())
        return -1;
    int rear = (front + size - 1) % capacity;
    return rear;
}

int Queue :: getSize(){
    return size;
}

int Queue :: Front(){
    if(isEmpty())
        return INT_MIN;
    return arr[getFront()];
}

int Queue :: Back(){
    if(isEmpty())
        return INT_MIN;
    return arr[getRear()];
}

bool Queue :: enQueue(int val){
    if(isFull()){
        cout<<"Queue is Full"<<endl;
        return false;
    }
        
    // int rear = getRear();
    // rear = (rear + 1) % capacity;
    int rear = (front + size) % capacity;
    arr[rear] = val;
    size++;
    return true;
}

void Queue :: deQueue(){
    if(isEmpty()){
        cout<<"Queue is Empty"<<endl;
        return;
    }
    front = (front + 1) % capacity;
    size--;
}

int main(){
    Queue q(4);
    q.deQueue();
    cout<<q.enQueue(10)<<endl;
    cout<<q.Front()<<endl;
    cout<<q.Back()<<endl;
    cout<<q.enQueue(20)<<endl;
    cout<<q.enQueue(30)<<endl;
    cout<<q.enQueue(40)<<endl;
    cout<<q.enQueue(10)<<endl;
    cout<<q.Front()<<endl;
    cout<<q.Back()<<endl;
    q.deQueue();
    q.deQueue();
    q.deQueue();
    cout<<q.Front()<<endl;
    cout<<q.Back()<<endl;
    q.deQueue();
    cout<<q.Front()<<endl;
    cout<<q.Back()<<endl;
}

/*
==================== REVISION BLOCK — Circular Queue Implementation Using Array (GFG / Basic DSA) ====================

Problem
-------
Implement a Queue using a fixed-size array with circular behavior (circular queue).
Support operations:
- enQueue(x): insert at rear
- deQueue(): remove from front
- Front(): get front element
- Back(): get rear element
- isEmpty(), isFull(), size, and helper index getters
Handle overflow/underflow.

Pattern/ Idea
-------------
Circular Queue (Array + Modulo Arithmetic).
Idea:
- Maintain `front` index (points to current front element).
- Maintain `size` (current number of elements).
- Compute `rear` index using:
    rear = (front + size - 1) % capacity
- Insert at next rear:
    newRear = (rear + 1) % capacity
- Delete by moving front forward:
    front = (front + 1) % capacity
This reuses array space efficiently (wrap-around).

Algorithm (step-by-step)
------------------------
Initialization:
1) Allocate array of capacity.
2) Set front = 0, size = 0.

isEmpty():
1) Return (size == 0).

isFull():
1) Return (size == capacity).

getFrontIndex():
1) If empty return -1 else return front.

getRearIndex():
1) If empty return -1 else return (front + size - 1) % capacity.

Front():
1) If empty return INT_MIN.
2) Return arr[getFrontIndex()].

Back():
1) If empty return INT_MIN.
2) Return arr[getRearIndex()].

enQueue(val):
1) If full -> overflow, return false.
2) Compute rear index:
   - if empty, getRear() returns -1, but formula still works:
     rear = -1; newRear = (rear + 1) % cap => 0 (in C++ this is safe here because rear is set to -1 then +1)
   - (more robust: newRear = (front + size) % capacity)
3) Store val at newRear, size++.
4) Return true.

deQueue():
1) If empty -> underflow, return.
2) front = (front + 1) % capacity
3) size--

Correctness (sketch)
--------------------
- The queue elements occupy `size` slots starting at `front` and wrapping via modulo.
- enQueue always writes to the next free slot after the current rear, preserving FIFO order.
- deQueue always advances `front` by one, removing the oldest element.
- Modulo arithmetic ensures indices stay within [0..capacity-1] and reuse freed space.
Thus, operations maintain FIFO behavior and correct indexing.

Complexity
---------
enQueue: O(1)
deQueue: O(1)
Front/Back: O(1)
isEmpty/isFull/Size: O(1)
Space: O(capacity)

Edge Cases / Pitfalls
---------------------
- Important: `rear = -1; (rear + 1) % capacity` works to get 0 here, but relying on -1 with % can be risky in general.
  A cleaner formula is: newRear = (front + size) % capacity.
- Memory leak: no destructor to delete[] arr.
- Returning INT_MIN or -1 as error codes can clash with valid values.
- deQueue() doesn’t return removed value (fine if not required).

Optimization if needed
----------------------
- Replace the rear computation with: int rear = (front + size) % capacity; (direct and safer).
- Add destructor and possibly template support for generic queue.
- Provide deQueue() that returns the removed element (optional design improvement).

========================================================
*/
