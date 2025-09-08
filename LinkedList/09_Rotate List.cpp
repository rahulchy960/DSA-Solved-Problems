class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == NULL || head->next == NULL) 
            return head;
        int len = 1;
        ListNode* tail = head;
        while(tail->next){
            len++;
            tail = tail->next;
        }
        k= k % len;
        if(k==0) return head;

        ListNode* curr = head;
        for(int i=1;i<=len-k-1 && curr!=NULL;i++)
            curr = curr->next;

        ListNode *newHead = curr->next;
        curr->next = NULL;
        tail->next = head;

        return newHead;
        


    }
};

/*
==================== REVISION BLOCK — Rotate List Right by k ====================

Problem
-------
Given head of a singly linked list, rotate it to the right by k places.

Idea
----
Let len be the length. Rotating right by k is the same as rotating by k % len.
The new head is the (len - k%len)-th node (1-indexed) after the current head.
Equivalently:
1) Connect tail->next = head to make a cycle.
2) Advance (len - k%len - 1) steps from head to land on the new tail.
3) newHead = newTail->next; break the cycle: newTail->next = nullptr.

Your code does this correctly (computes len, reduces k, finds newTail at index len-k-1,
cuts there, and stitches tail->next = head). Time O(n), Space O(1).

Clean, equivalent version (link first, then cut):
*/

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || k == 0) return head;

        // 1) Find length and tail
        int len = 1;
        ListNode* tail = head;
        while (tail->next) {
            tail = tail->next;
            ++len;
        }

        k %= len;
        if (k == 0) return head;

        // 2) Make it circular
        tail->next = head;

        // 3) Find new tail: (len - k - 1) steps from original head
        int steps = len - k - 1;
        ListNode* newTail = head;
        while (steps--) newTail = newTail->next;

        // 4) Break the cycle
        ListNode* newHead = newTail->next;
        newTail->next = nullptr;

        return newHead;
    }
};
