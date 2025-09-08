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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *dummy = new ListNode(0);
        ListNode* node = dummy;
        while(list1 && list2){
            if(list1->val < list2->val){
                node->next = list1;
                list1 = list1->next;
            } else {
                node->next = list2;
                list2 = list2->next;
            }
            node = node->next;
        }
        if(list1)
            node->next = list1;
        if(list2)
            node->next = list2;
        
        return dummy->next;
    }
};

/*
==================== REVISION BLOCK — Merge Two Sorted Lists (Iterative, dummy head) ====================

Problem
-------
Given two sorted singly linked lists list1 and list2, merge them into one sorted list
by splicing nodes together. Return the head of the merged list.

Pattern
-------
- **Two-pointer merge** using a **dummy head** to simplify edge cases.
- Always attach the smaller current node and advance that list’s pointer.

Algorithm (step-by-step)
------------------------
1) Create a dummy node and a `node` cursor pointing to it.
2) While both list1 and list2 are non-null:
     - If list1->val < list2->val: attach list1, advance list1.
       Else: attach list2, advance list2.
     - Move `node` forward to the newly attached node.
3) One list may have leftover nodes; attach the remainder to `node->next`.
4) Return `dummy->next` as the head of the merged list.

Correctness (sketch)
--------------------
- At each step, the smallest remaining head among the two lists is appended, so the merged
  prefix remains sorted. When one list empties, the rest of the other is already sorted and
  larger/equal, so appending it preserves order.

Complexity
---------
- Time: O(m + n), where m,n are the lengths of list1 and list2 (each node processed once).
- Space: O(1) extra — in-place relinking; no new list nodes are created.

Edge cases / notes
------------------
- If either list is null, the answer is the other list.
- This code uses `new` for the dummy node; typical judge environments ignore the leak.
  In production, prefer a stack-allocated dummy: `ListNode dummy(0); ListNode* node = &dummy;`
  or `unique_ptr` for ownership.
- The merge is **stable**: equal values keep relative order because we take from list2 only
  when `list1->val >= list2->val`.

========================================================
*/

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *dummy = new ListNode(0);   // dummy head to simplify attachments
        ListNode* node = dummy;

        // Merge while both lists have nodes
        while (list1 && list2) {
            if (list1->val < list2->val) {
                node->next = list1;
                list1 = list1->next;
            } else {
                node->next = list2;
                list2 = list2->next;
            }
            node = node->next;
        }

        // Attach any remaining nodes
        if (list1) node->next = list1;
        if (list2) node->next = list2;

        return dummy->next;  // head of merged list
    }
};

/* Optional: memory-safe dummy (no heap allocation)
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* cur = &dummy;
    while (a && b) {
        if (a->val < b->val) { cur->next = a; a = a->next; }
        else { cur->next = b; b = b->next; }
        cur = cur->next;
    }
    cur->next = a ? a : b;
    return dummy.next;
}
*/
