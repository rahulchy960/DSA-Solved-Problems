class MyQueue {
public:
    stack<int>s1, s2;
    MyQueue() {
        
    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        if(s1.empty() && s2.empty())
            return INT_MIN;

        int x = INT_MIN;
        if(!s2.empty()){
            x = s2.top();
            s2.pop();
        } else {
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            x = s2.top();
            s2.pop();
        }
        return x;
    }
    
    int peek() {
        if(s1.empty() && s2.empty())
            return INT_MIN;
        if(!s2.empty()){
            return s2.top();
        } else{
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            return s2.top();
        }
    }
    
    bool empty() {
        if(s1.empty() && s2.empty())
            return true;
        return false;
    }
};

/*
==================== REVISION BLOCK — LeetCode 232: Implement Queue using Stacks ====================

Problem
-------
Implement a queue using only stacks.
Support the following operations:
- push(x): push element x to the back of the queue
- pop(): removes the element from the front of the queue
- peek(): get the front element
- empty(): return whether the queue is empty

Pattern/ Idea
-------------
Two-Stack Technique (Amortized Analysis).
Idea:
- Use s1 as the input stack (for push operations).
- Use s2 as the output stack (for pop/peek operations).
- Transfer elements from s1 to s2 only when s2 is empty, reversing order
  and exposing the oldest element on top of s2.

Algorithm (step-by-step)
------------------------
push(x):
1) Push x onto s1.

pop():
1) If both s1 and s2 are empty → underflow.
2) If s2 is empty:
   - Move all elements from s1 to s2 (push s1.top() into s2, pop s1).
3) Pop and return top of s2.

peek():
1) If both s1 and s2 are empty → underflow.
2) If s2 is empty:
   - Move all elements from s1 to s2.
3) Return top of s2.

empty():
1) Return true if both s1 and s2 are empty.

Correctness (sketch)
--------------------
- Elements are always pushed into s1 in arrival order.
- When s2 is empty, transferring all elements from s1 to s2 reverses their order,
  making the oldest element appear on top of s2.
- pop() and peek() always operate on s2, ensuring FIFO behavior.
- Transfers happen only when necessary, preserving correctness and efficiency.

Complexity
---------
push: O(1)
pop: Amortized O(1)
peek: Amortized O(1)
empty: O(1)
Space: O(n)

Edge Cases / Pitfalls
---------------------
- Calling pop or peek on an empty queue (handled by returning INT_MIN here).
- Repeated transfers if not checking s2 emptiness.
- Returning INT_MIN may clash with valid values (better to throw exception in production code).

Optimization if needed
----------------------
Already optimal.
Alternative approach: always push into s1 and always pop from s2 with lazy transfer (used here).

========================================================
*/
