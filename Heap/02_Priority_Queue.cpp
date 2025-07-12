#include <queue>
#include <vector>
#include <functional>
using namespace std;

int main() {
    // Default: Max-heap (largest element on top)
    priority_queue<int> pq;

    // Alternative: Min-heap (smallest element on top)
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // ---------- Member Functions with Time Complexities ----------

    // Insert an element into the priority queue
    pq.push(10);            // O(log n)

    // Access the top (largest or smallest) element
    int topElement = pq.top();  // O(1)

    // Remove the top element
    pq.pop();              // O(log n)

    // Check if the priority queue is empty
    bool isEmpty = pq.empty(); // O(1)

    // Return the number of elements
    int size = pq.size();      // O(1)

    // Swap contents with another priority queue
    priority_queue<int> other;
    pq.swap(other);         // O(1)

    // Clear all elements (C++23 and above only)
    // pq.clear();          // O(n) — C++23 only

    // Emplace (construct element in-place)
    pq.emplace(20);         // O(log n)

    // Comparison (operator==, !=, <, etc. — C++20 and above)
    // priority_queue<int> pq2;
    // bool equal = (pq == pq2); // O(n) — C++20 only

    return 0;
}
