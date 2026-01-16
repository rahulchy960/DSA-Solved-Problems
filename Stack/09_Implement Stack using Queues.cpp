class MyStack {
public:
    queue<int>q;
    MyStack() {
        
    }
    
    void push(int x) {
        q.push(x);
        int n = q.size();
        for(int i=0;i<n-1;i++){
            int x = q.front();
            q.pop();
            q.push(x);
        }
    }
    
    int pop() {
        if(q.empty())
            return INT_MIN;
        int top = q.front();
        q.pop();
        return top;
    }
    
    int top() {
        if(q.empty())
            return INT_MIN;
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/*
==================== REVISION BLOCK — LeetCode 225: Implement Stack using Queues ====================

Problem
-------
Implement a stack using only a single queue.
Support the following operations:
- push(x): Push element x onto stack
- pop(): Removes the element on top of the stack
- top(): Get the top element
- empty(): Return whether the stack is empty

Pattern/ Idea
-------------
Single Queue Rotation (Costly Push).
Idea:
- Always maintain the stack’s TOP at the front of the queue.
- After pushing a new element, rotate the queue so that the newly added element
  comes to the front, mimicking LIFO behavior.

Algorithm (step-by-step)
------------------------
push(x):
1) Push x into the queue.
2) Let n = current size of queue.
3) Rotate the queue n-1 times:
   - Pop front element and push it back.
   (This brings the newly added element to the front.)

pop():
1) If queue is empty → underflow.
2) Pop and return the front element (stack top).

top():
1) If queue is empty → underflow.
2) Return the front element.

empty():
1) Return whether the queue is empty.

Correctness (sketch)
--------------------
- After each push, rotation ensures the newest element is placed at the front.
- Therefore, the front of the queue always represents the top of the stack.
- pop() and top() operate on the front, preserving LIFO order.
Thus, the queue faithfully simulates stack behavior.

Complexity
---------
push: O(n) due to rotation
pop: O(1)
top: O(1)
empty: O(1)
Space: O(n)

Edge Cases / Pitfalls
---------------------
- pop/top on empty stack (handled by returning INT_MIN here).
- Using INT_MIN as error value may conflict with valid data.
- Costly push but cheap pop/top (important to mention in interviews).

Optimization if needed
----------------------
Alternative approach:
- Use two queues with costly pop instead of costly push.
This version is usually preferred for simpler logic.

========================================================
*/
