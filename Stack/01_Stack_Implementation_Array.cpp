#include<iostream>
using namespace std;

class Stack{
  public:
    int *arr;
    int capacity;
    int top;
    Stack(int cap){
        arr = new int[cap];
        capacity = cap;
        top = -1;
    }
    bool isEmpty();
    int Size();
    bool Push(int num);
    bool Pop();
    int Top();

};

bool Stack :: isEmpty(){
    return top == -1;
}

int Stack :: Size(){
    return top+1;
}

bool Stack :: Push(int num){
    if(top == capacity - 1){
        cout<<"Stack OverFlow"<<endl;
        return false;
    }
    top++;
    arr[top] = num;
    return true;
}

bool Stack :: Pop(){
    if(top == -1){
        cout<<"Stack UnderFlow"<<endl;
        return false;;
    }
    int num = arr[top];
    top--;
    return true;
}

int Stack :: Top(){
    if(top == -1){
        cout<<"Stack Underflow"<<endl;
        return INT_MIN;
    }
    return arr[top];
}


int main(){
    Stack s(3);
    s.Pop();
    cout<<s.isEmpty()<<endl;
    cout<<s.Size()<<endl;
    cout<<s.Top()<<endl;
    cout<<s.Push(5)<<endl;;
    cout<<s.Push(10)<<endl;;
    cout<<s.Push(15)<<endl;;
    cout<<s.Push(20)<<endl;;
    cout<<s.isEmpty()<<endl;
    cout<<s.Top()<<endl;
    cout<<s.Pop()<<endl;;
    cout<<s.Pop()<<endl;;
    cout<<s.Pop()<<endl;;
    cout<<s.Pop()<<endl;;
    cout<<s.isEmpty()<<endl;

}

/*
==================== REVISION BLOCK — Stack Implementation Using Array (GFG / Basic DSA) ====================

Problem
-------
Implement a Stack data structure using an array.
Support the following operations:
- push(x): insert an element
- pop(): remove the top element
- top(): return the top element
- isEmpty(): check if stack is empty
- size(): return current size of stack
Handle stack overflow and underflow conditions.

Pattern/ Idea
-------------
Array-based Stack (LIFO – Last In First Out).
Idea: Maintain an index `top` that always points to the topmost element.
- Push → increment top, then insert.
- Pop → remove element at top, then decrement top.
- Stack boundaries are controlled using `capacity`.

Algorithm (step-by-step)
------------------------
Initialization:
1) Allocate an array of given capacity.
2) Initialize top = -1 (stack is empty).

Push(num):
1) If top == capacity - 1 → Stack Overflow, return false.
2) Increment top.
3) Insert num at arr[top].
4) Return true.

Pop():
1) If top == -1 → Stack Underflow, return false.
2) Decrement top.
3) Return true.

Top():
1) If top == -1 → Stack Underflow, return INT_MIN.
2) Return arr[top].

isEmpty():
1) Return (top == -1).

Size():
1) Return top + 1.

Correctness (sketch)
--------------------
The variable `top` always represents the index of the most recently inserted element:
- Push places a new element above the current top.
- Pop removes exactly the most recent element.
- Boundary checks prevent illegal memory access.
Thus, all operations preserve LIFO order and stack invariants.

Complexity
---------
Push: O(1)
Pop: O(1)
Top: O(1)
isEmpty: O(1)
Size: O(1)
Space: O(n) where n = stack capacity

Edge Cases / Pitfalls
---------------------
- Stack overflow when pushing into a full stack.
- Stack underflow when popping or accessing top from an empty stack.
- Memory leak risk if destructor is not defined (delete[] arr).
- INT_MIN used as error value may clash with valid data.

Optimization if needed
----------------------
- Use std::vector to manage memory automatically.
- Add destructor to free allocated memory.
- Throw exceptions instead of printing errors (advanced design).

========================================================
*/
