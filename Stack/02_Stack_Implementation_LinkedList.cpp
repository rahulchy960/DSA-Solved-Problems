#include<iostream>
using namespace std;

class Node{
  public:
    int val;
    class Node *next;
    Node(int val){
        this->val = val;
        next = NULL;
    }
};

class Stack{
  public:
    Node *head;
    int size;
    Stack(){
        head = NULL;
        size = 0;
    }
    int Size();
    bool isEmpty();
    int Top();
    bool Push(int data);
    bool Pop();
};

int Stack :: Size(){
    return size;
}

bool Stack :: isEmpty(){
    return size==0;
}

int Stack :: Top(){
    if(head == NULL){
        cout<<"Stack UnderFlow"<<endl;
        return INT_MIN;
    }
    return head->val;
}

bool Stack :: Push(int data){
    Node *temp = new Node(data);
    temp->next = head;
    head = temp;
    size++;
    return true;
}

bool Stack :: Pop(){
    if(head == NULL){
        cout<<"Stack Underflow"<<endl;
        return false;
    }
    Node *temp = head;
    head = head->next;
    delete(temp);
    size--;
    return true;
}


int main(){
    Stack stk;
    cout<<stk.Top()<<endl;
    cout<<stk.Size()<<endl;
    cout<<stk.Pop()<<endl;
    cout<<stk.Push(10)<<endl;
    cout<<stk.Pop()<<endl;
    cout<<stk.Top()<<endl;

    cout<<stk.Push(10)<<endl;
    cout<<stk.Top()<<endl;
    cout<<stk.Push(15)<<endl;
    cout<<stk.Top()<<endl;
    cout<<stk.Push(20)<<endl;
    cout<<stk.Top()<<endl;

    cout<<stk.Pop()<<endl;
    cout<<stk.Pop()<<endl;
    cout<<stk.Top()<<endl;
    cout<<stk.Pop()<<endl;
    
}


/*
==================== REVISION BLOCK — Stack Implementation Using Linked List (GFG / Basic DSA) ====================

Problem
-------
Implement a Stack data structure using a singly linked list.
Support the following operations:
- push(x): insert an element at the top
- pop(): remove the top element
- top(): return the top element
- isEmpty(): check if stack is empty
- size(): return number of elements in stack

Pattern/ Idea
-------------
Linked List based Stack (LIFO – Last In First Out).
Idea:
- Use the head of the linked list as the TOP of the stack.
- Push and Pop operations are performed at the head for O(1) efficiency.
- Unlike array-based stack, there is no fixed capacity (dynamic size).

Algorithm (step-by-step)
------------------------
Initialization:
1) Set head = NULL and size = 0.

Push(data):
1) Create a new node with given data.
2) Point new node’s next to current head.
3) Update head to the new node.
4) Increment size.
5) Return true.

Pop():
1) If head == NULL → Stack Underflow, return false.
2) Store current head in temp.
3) Move head to head->next.
4) Delete temp.
5) Decrement size.
6) Return true.

Top():
1) If head == NULL → Stack Underflow, return INT_MIN.
2) Return head->val.

isEmpty():
1) Return (size == 0).

Size():
1) Return size.

Correctness (sketch)
--------------------
- The head of the linked list always represents the top of the stack.
- Push inserts a new node at the head, making it the most recent element.
- Pop removes exactly the head node, ensuring LIFO order.
- Size is updated consistently on every push/pop.
Thus, all stack operations behave correctly and maintain stack invariants.

Complexity
---------
Push: O(1)
Pop: O(1)
Top: O(1)
isEmpty: O(1)
Size: O(1)
Space: O(n), where n is the number of elements in the stack

Edge Cases / Pitfalls
---------------------
- Calling Pop or Top on an empty stack (handled with underflow check).
- Memory leaks if popped nodes are not deleted.
- INT_MIN used as error value may conflict with valid stack values.

Optimization if needed
----------------------
- Use exceptions instead of INT_MIN for error handling.
- Add destructor to free remaining nodes.
- Can be extended to a template stack (generic type).

========================================================
*/
