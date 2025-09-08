/* struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};*/

class Solution {
  public:
    int getKthFromLast(Node* head, int k) {
        // code here
        Node *fast = head;
        int i;
        for(i=0;i<k && fast!=NULL;i++){
            fast = fast->next;
        }
        if(i!=k) return -1;
        Node* slow = head;
        while(fast!=NULL){
            fast = fast->next;
            slow = slow->next;
        }
        return slow->data;
    }
};


/*
==================== REVISION BLOCK — Kth Node from End (Two Pointers) ====================

Problem
-------
Given the head of a singly linked list and an integer k (1-indexed), return the data of
the **k-th node from the end**. If the list has fewer than k nodes, return -1.

Pattern
-------
Two-pointer (fast/slow) technique:
- Move `fast` k steps ahead.
- Then move `slow` and `fast` together until `fast` hits null.
- `slow` now points to the k-th node from the end.

Algorithm
---------
1) Set `fast = head`. Advance `fast` exactly k steps.
   - If you hit null before making k steps, list is shorter than k → return -1.
2) Set `slow = head`. Move both pointers one step at a time until `fast` becomes null.
3) Return `slow->data`.

Why it works
------------
After advancing k steps, the gap between `fast` and `slow` is k nodes. When `fast` reaches
the end, `slow` is exactly k nodes behind it, i.e., at the k-th node from the end.

Complexity
----------
- Time: O(n) — each pointer traverses at most n nodes.
- Space: O(1) — constant extra space.

Edge notes / pitfalls
---------------------
- Ensure k is positive (if k<=0, return -1 per typical specs).
- Off-by-one: advance `fast` **k** times (not k-1).
- If the list is exactly length k, after advancing k steps `fast` is null and `slow`
  should be the head (the k-th from end).

========================================================
*/

/* struct Node {
  int data;
  struct Node *next;
  Node(int x) : data(x), next(nullptr) {}
};*/

class Solution {
  public:
    int getKthFromLast(Node* head, int k) {
        if (!head || k <= 0) return -1;      // guard invalid inputs

        Node* fast = head;
        int i = 0;
        // Move fast k steps ahead
        for (; i < k && fast != nullptr; ++i) {
            fast = fast->next;
        }
        if (i != k) return -1;               // list shorter than k

        Node* slow = head;
        // Move both until fast reaches the end
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow->data;                    // slow is k-th from end
    }
};
