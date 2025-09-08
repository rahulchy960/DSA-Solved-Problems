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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode* curr = head;
        while(curr!=NULL && curr->next!=NULL){
            if(curr->val == curr->next->val){
               ListNode* temp = curr->next;
               curr->next = curr->next->next;
               delete(temp);
            } else{
                curr=curr->next;
            }
        }
        return head;
    }
};


/*
==================== REVISION BLOCK — Remove Duplicates from Sorted List (LC 83) ====================

Problem
-------
Given the head of a **sorted** singly linked list, delete all duplicates so each element
appears exactly once. Return the head of the modified list.

Key Idea
--------
Because the list is **sorted**, duplicates are grouped contiguously. Walk once with a
pointer `curr`:
- If `curr->val == curr->next->val`, bypass the duplicate node: `curr->next = curr->next->next`.
- Otherwise, advance `curr`.

Algorithm
---------
1) Handle trivial cases: empty list or single node → return head.
2) Set `curr = head`.
3) While `curr` and `curr->next` exist:
     - If equal values → unlink the next node (optionally free it).
     - Else → move `curr` forward.
4) Return `head`.

Correctness (sketch)
--------------------
Sorted order ensures all duplicates for any value are adjacent. Each bypass removes exactly
one duplicate without affecting relative order or skipping distinct values. Repeating until
the next value differs leaves a single representative per value.

Complexity
----------
- Time: O(n) — single pass.
- Space: O(1) — in-place.

Edge Notes
----------
- Manual `delete` of removed nodes is optional on coding platforms (often managed), but
  safe to include as you did.
- If the task were **“remove all nodes that have duplicates”** (LC 82), the solution differs
  (use a dummy head and skip whole duplicate blocks).

========================================================
*/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* curr = head;
        while (curr && curr->next) {
            if (curr->val == curr->next->val) {
                ListNode* dup = curr->next;          // duplicate node
                curr->next = curr->next->next;       // unlink
                delete dup;                           // optional in judges; good hygiene
            } else {
                curr = curr->next;                   // advance only when distinct
            }
        }
        return head;
    }
};
