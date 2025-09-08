/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast != NULL && fast->next!=NULL){
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)
                return true;
        }
        return false;
    }
};


/*
==================== REVISION BLOCK — Detect Cycle in Linked List (Floyd’s Tortoise & Hare) ====================

Problem
-------
Given the head of a singly linked list, determine if the list contains a cycle.

Pattern
-------
Two pointers moving at different speeds (Floyd’s algorithm):
- `slow` moves 1 step at a time.
- `fast` moves 2 steps at a time.
If there is a cycle, they will eventually meet inside the cycle. If there is no cycle,
`fast` hits null first.

Algorithm (step-by-step)
------------------------
1) Initialize slow = head, fast = head.
2) While fast != null and fast->next != null:
   - slow  = slow->next
   - fast  = fast->next->next
   - If slow == fast → cycle exists → return true.
3) Loop ends → no cycle → return false.

Why it works (intuition)
------------------------
Inside a cycle, the relative speed is 1 node per step (fast gains 1 on slow each loop);
on a circular track, gaining 1 per step guarantees a meeting.

Complexity
----------
- Time: O(n) — each pointer traverses at most O(n) nodes.
- Space: O(1) — constant extra memory.

Edge cases / notes
------------------
- Empty list or single node: immediately returns false.
- This method **does not** find the entry point. To find the start, after a meet, set one
  pointer to head and move both 1 step at a time; their meeting point is the cycle start.
- Alternative approach: store visited nodes in a hash set (O(n) space).

========================================================
*/

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;             // 1 step
            fast = fast->next->next;       // 2 steps
            if (slow == fast)              // met inside a cycle
                return true;
        }
        return false;                      // fast reached null → no cycle
    }
};
