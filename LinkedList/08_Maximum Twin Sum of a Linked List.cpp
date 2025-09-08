class Solution {
public:
    int pairSum(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = NULL;
        while(fast && fast->next){
            fast = fast->next->next;
            ListNode* temp = slow->next;
            slow->next = prev;
            prev = slow;
            slow = temp;
        }
        int res = 0;
        while(slow){
            res = max(res, slow->val + prev->val);
            slow = slow->next;
            prev = prev->next;
        }
        return res;
    }
};

/*
==================== REVISION BLOCK — Maximum Twin Sum of a Linked List (LC 2130) ====================

Problem
-------
A list of even length n has nodes indexed 0..n-1. The “twin” of node i is node (n-1-i).
The twin sum of i is val[i] + val[n-1-i]. Return the maximum twin sum.

Idea (in-place, O(1) extra)
---------------------------
Use fast/slow pointers to reach the middle **while reversing the first half**:
- Move `fast` by 2 and `slow` by 1. While doing that, reverse the link of `slow`.
- When the loop ends (even n), `slow` points to the start of the second half,
  and `prev` points to the head of the **reversed first half**.
- Walk both halves in lockstep, compute sums `slow->val + prev->val`, keep the max.

Why this works
--------------
Reversing the first half makes the natural pairing line up:
`prev` visits nodes n/2-1, n/2-2, …, 0 while `slow` visits n/2, n/2+1, …, n-1.

Complexity
----------
- Time: O(n) — one pass to reverse half, one pass to compute sums.
- Space: O(1) — in-place reversal (we don't restore; not required by the problem).

Edge notes
----------
- The problem guarantees **even** length; thus `prev` and `slow` both exist for the pairing loop.
- If you ever needed to keep the original list, you’d reverse the first half back afterwards.
*/

class Solution {
public:
    int pairSum(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;

        // Reverse the first half while finding the midpoint
        while (fast && fast->next) {
            fast = fast->next->next;

            ListNode* nxt = slow->next; // store next
            slow->next = prev;          // reverse link
            prev = slow;                // advance prev
            slow = nxt;                 // advance slow (now at start of 2nd half when loop ends)
        }

        // Now: prev = head of reversed first half, slow = head of second half
        int ans = 0;
        while (slow) {
            ans = std::max(ans, slow->val + prev->val);
            slow = slow->next;
            prev = prev->next;
        }
        return ans;
    }
};
