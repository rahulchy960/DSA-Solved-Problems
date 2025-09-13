

class MedianFinder {
public:
    priority_queue<int>smaller;
    priority_queue<int, vector<int>, greater<int>>greater;
    MedianFinder() {
        
    }
    
    void addNum(int num) {

        if(smaller.empty() || smaller.top()>=num)
            smaller.push(num);
        else 
            greater.push(num);
        
        if(smaller.size()>greater.size()+1){
            greater.push(smaller.top());
            smaller.pop();
        }
        else if(greater.size()>smaller.size()){
            smaller.push(greater.top());
            greater.pop();
        }
        

    }
    
    double findMedian() {
        if(smaller.size()>greater.size())
            return (double)smaller.top();
        else
            return (greater.top()+smaller.top())/2.0;
    }
};

/*
==================== REVISION BLOCK — Median from Data Stream (Two Heaps) ====================

Problem
-------
Continuously receive numbers and support:
- addNum(x): insert x
- findMedian(): return current median
Numbers can arrive in any order; queries interleave.

Idea
----
Maintain two heaps:
- max-heap `low`  (all values ≤ current median)
- min-heap `high` (all values ≥ current median)
Balance them so that |size(low) - size(high)| ≤ 1 and every element in `low` ≤ every element in `high`.

Pattern
-------
Greedy balancing with heaps:
- Insert into one heap based on value vs `low.top()`.
- Rebalance sizes so `low` has the extra element when total count is odd.

Algorithm
---------
addNum(x):
1) If low empty or x ≤ low.top(): push x into low; else push into high.
2) Rebalance:
   - If low.size() > high.size() + 1: move low.top() → high.
   - If high.size() > low.size():     move high.top() → low.

findMedian():
- If sizes equal: (low.top() + high.top()) / 2.0
- Else: low.top()   (low always holds the extra element)

Correctness
-----------
Ordering invariant (max(low) ≤ min(high)) ensures all values are split around the median.
Size invariant ensures median is either low.top() (odd) or average of the two tops (even).
Rebalancing after each insert preserves both invariants.

Complexity
----------
addNum:  O(log n) (one heap push, maybe one pop+push)
findMedian: O(1)
Space:    O(n)

Edge Cases
----------
- First insertion (heaps empty).
- Duplicates (allowed; tie goes to `low`).
- Even count average can overflow 32-bit if using `int + int`; sum using 64-bit.
- If `findMedian()` called when empty, behavior is undefined (guard if needed).

Pitfalls
--------
- Don’t forget to rebalance after insertion.
- Average with `2.0` must avoid intermediate 32-bit overflow: cast to 64-bit (or double) before addition.
- Naming a variable `greater` shadows std::greater; prefer `minHeap` for clarity.
*/

class MedianFinder {
public:
    std::priority_queue<int> low; // max-heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> high; // min-heap

    MedianFinder() = default;

    void addNum(int num) {
        if (low.empty() || num <= low.top()) low.push(num);
        else                                 high.push(num);

        // Rebalance sizes: low may exceed high by at most 1
        if (low.size() > high.size() + 1) {
            high.push(low.top()); low.pop();
        } else if (high.size() > low.size()) {
            low.push(high.top()); high.pop();
        }
    }

    double findMedian() const {
        if (low.size() > high.size()) {
            return static_cast<double>(low.top());
        } else {
            // use 64-bit sum to avoid overflow, then divide
            long long a = low.top();
            long long b = high.top();
            return (a + b) / 2.0;
        }
    }
};

/* ===== Optional Variant: Always insert to low, then move to high if needed =====
Slightly different insertion style that keeps code symmetric.

void addNum(int x) {
    low.push(x);
    high.push(low.top()); low.pop();
    if (high.size() > low.size()) { low.push(high.top()); high.pop(); }
}
*/


