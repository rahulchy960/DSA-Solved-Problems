

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



class MedianFinder {
public:
    // Max-heap for the smaller half of numbers
    priority_queue<int> smaller;

    // Min-heap for the greater half of numbers
    priority_queue<int, vector<int>, greater<int>> greater;

    MedianFinder() {
        // Constructor initializes two heaps
    }

    /*
    Algorithm:
    - Maintain two heaps:
        1. Max-heap (`smaller`) to store the smaller half of the numbers
        2. Min-heap (`greater`) to store the larger half
    - When a number is added:
        - If it's smaller than or equal to the top of `smaller`, push to `smaller`
        - Otherwise, push to `greater`
    - After insertion, balance the heaps such that:
        - `smaller` may have at most 1 more element than `greater`
        - If not, move the top from one heap to the other

    - To find the median:
        - If both heaps have the same size, the median is the average of the two tops
        - If `smaller` has more elements, the median is `smaller.top()`

    Time Complexity:
    - addNum(): O(log n), due to heap insertion and balancing
    - findMedian(): O(1), just comparing top elements

    Space Complexity:
    - O(n) to store all elements across the two heaps
    */

    void addNum(int num) {
        // Decide which heap the number belongs to
        if (smaller.empty() || num <= smaller.top())
            smaller.push(num);
        else
            greater.push(num);

        // Balance the heaps
        if (smaller.size() > greater.size() + 1) {
            greater.push(smaller.top());
            smaller.pop();
        } else if (greater.size() > smaller.size()) {
            smaller.push(greater.top());
            greater.pop();
        }
    }

    double findMedian() {
        // Odd number of elements → return top of max heap
        if (smaller.size() > greater.size())
            return (double)smaller.top();

        // Even number of elements → return average of tops
        return (smaller.top() + greater.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
