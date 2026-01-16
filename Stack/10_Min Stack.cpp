class MinStack {
public:
    stack<int>s, mn;
    MinStack() {
        
    }
    
    void push(int val) {
        if(s.empty() && mn.empty()){
            s.push(val);
            mn.push(val);
        } else {
            s.push(val);
            mn.push(min(val, mn.top()));
        }
    
    }
    
    void pop() {
        s.pop();
        mn.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return mn.top();
    }
};

/*
==================== REVISION BLOCK — LeetCode 155: Min Stack ====================

Problem
-------
Design a stack that supports push, pop, top, and retrieving the minimum element
in constant time (O(1)).

Pattern/ Idea
-------------
Auxiliary Stack (Parallel Min Tracking).
Idea:
- Use two stacks:
  1) s  → stores all pushed values (normal stack behavior)
  2) mn → stores the minimum value up to the current depth
- For every push, also push the current minimum so far into mn.
This way, the top of mn always represents the minimum element of the stack.

Algorithm (step-by-step)
------------------------
push(val):
1) If stack is empty:
   - Push val into s.
   - Push val into mn.
2) Else:
   - Push val into s.
   - Push min(val, mn.top()) into mn.

pop():
1) Pop the top element from s.
2) Pop the top element from mn.

top():
1) Return s.top().

getMin():
1) Return mn.top().

Correctness (sketch)
--------------------
- mn[i] stores the minimum of elements in s[0..i].
- When a new element is pushed, mn records the minimum including that element.
- When an element is popped, both stacks pop together, restoring the previous minimum.
Thus, getMin() always returns the correct minimum in O(1) time.

Complexity
---------
push: O(1)
pop: O(1)
top: O(1)
getMin: O(1)
Space: O(n) (extra stack for minimums)

Edge Cases / Pitfalls
---------------------
- pop(), top(), or getMin() on an empty stack (problem guarantees valid calls).
- Extra space usage due to auxiliary stack.
- Must pop from both stacks together to maintain consistency.

Optimization if needed
----------------------
Space-optimized approach:
- Store only new minimums in mn with counts, or
- Encode values using mathematical trick (2*x - min), but that approach is harder to reason about.
This solution is preferred for clarity and interview safety.

========================================================
*/

class MinStack {
public:
    stack<int> s, mn;

    MinStack() {}

    // Push element onto stack
    void push(int val) {
        if (s.empty()) {
            s.push(val);
            mn.push(val);                 // first element is min
        } else {
            s.push(val);
            mn.push(min(val, mn.top()));  // track min till this level
        }
    }

    // Remove top element
    void pop() {
        s.pop();      // remove from main stack
        mn.pop();     // remove corresponding min
    }

    // Get top element
    int top() {
        return s.top();
    }

    // Retrieve minimum element
    int getMin() {
        return mn.top();
    }
};
