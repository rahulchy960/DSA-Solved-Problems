/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* fast = head;
        for(int i=1; i<=n && fast!=NULL; i++)
            fast = fast->next;
        ListNode *slow = dummy;
        while(fast!=NULL){
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = slow->next->next;

        return dummy->next;
    }
};

/*
==================== REVISION BLOCK — Remove Nth Node From End of List (Two Pointers) ====================

Problem
-------
Given the head of a singly linked list and an integer n (1-indexed), remove the n-th node
from the end and return the head.

Core idea (Floyd two-pointer gap)
---------------------------------
Maintain a gap of exactly (n+1) nodes between `fast` and `slow` by using a **dummy head**:
- Advance `fast` (n+1) steps from the dummy.
- Move both `fast` and `slow` together until `fast` hits null.
- `slow->next` is the node to delete. Relink around it.

Why dummy + (n+1)?
------------------
Dummy simplifies removing the head when n equals the list length. Using (n+1) steps puts
`slow` **just before** the node to delete.

Complexity
----------
Time: O(L) where L is the list length.  
Space: O(1).

Pitfalls handled
----------------
- Empty list or n larger than length → return original head safely.
- No need to allocate dummy on heap; use stack-allocated dummy to avoid leaks.
- Optionally `delete` the removed node (judges don’t require it, but it’s tidy).

========================================================
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // Advance fast by (n+1) steps so slow ends up just before the target
        for (int i = 0; i < n + 1; ++i) {
            if (!fast) return head;   // n > length: no removal, return original
            fast = fast->next;
        }

        // Move both until fast reaches end
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        // slow->next is the node to remove
        ListNode* toDelete = slow->next;
        if (toDelete) {
            slow->next = toDelete->next;
            // optional: delete toDelete; // uncomment if ownership requires freeing
        }

        return dummy.next;
    }
};
