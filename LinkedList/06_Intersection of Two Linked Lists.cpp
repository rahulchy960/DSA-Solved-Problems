
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*>s;
        while(headA){
            s.insert(headA);
            headA = headA->next;
        }
        while(headB){
            if(s.find(headB) != s.end())
                return headB;
            headB = headB->next;
        }
        return NULL;

    }
};
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*>s;
        ListNode* curr = headA;
        int c1=0, c2=0;
        while(curr){
            c1++;
            curr = curr->next;
        }
        curr = headB;
        while(curr){
            c2++;
            curr = curr->next;
        }

        int n = abs(c1-c2);
        ListNode *currA = headA;
        ListNode *currB = headB; 
        if(c1 > c2){
            for(int i=1;i<=n;i++){
                currA = currA->next;
            }
        } else {
            for(int i=1;i<=n;i++){
                currB = currB->next;
            }
        }
        
        while(currA && currB){
            if(currA == currB)
                return currA;
            currA = currA->next;
            currB = currB->next;
        }

        return NULL;

    }
};

/*
==================== REVISION BLOCK — Intersection of Two Linked Lists ====================

Problem
-------
Given heads headA and headB, return the node where the two singly linked lists intersect.
If they do not intersect, return nullptr.

Two classic O(1)-space approaches
---------------------------------
A) Length-align (what you wrote, cleaned up):
   1) Compute lengths c1, c2.
   2) Advance the longer list by |c1-c2|.
   3) Move both one step until pointers meet or reach null.

B) Pointer switching (no lengths, very slick):
   - Walk pa over A and pb over B. When a pointer hits null, redirect it to the other list’s head.
   - After at most c1+c2 steps, pa == pb at the intersection (or both null if no intersection).

Why B works:
- Each pointer traverses exactly c1 + c2 nodes total; they align on the second pass.

Complexity
----------
Time: O(c1 + c2) ; Space: O(1)

Pitfalls
--------
- Don’t use node values to compare; intersection is by node **address**.
- Unused variables (e.g., unordered_set) can be removed.

========================================================
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Approach B: Pointer switching (concise and avoids length math)
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode *pa = headA, *pb = headB;
        while (pa != pb) {
            pa = (pa ? pa->next : headB);
            pb = (pb ? pb->next : headA);
        }
        return pa; // either intersection node or nullptr
    }
};

/* --- If you prefer your length-align approach, here’s a cleaned version ---
ListNode *getIntersectionNode_len(ListNode *headA, ListNode *headB) {
    auto len = [](ListNode* p){ int c=0; while(p){ ++c; p=p->next; } return c; };
    int c1 = len(headA), c2 = len(headB);
    ListNode *a = headA, *b = headB;
    int delta = abs(c1 - c2);
    if (c1 > c2) while (delta--) a = a->next;
    else         while (delta--) b = b->next;
    while (a && b && a != b) { a = a->next; b = b->next; }
    return (a == b) ? a : nullptr;
}
*/```
