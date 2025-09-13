/* Structure for tree and linked list

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};
 */

// This function should return head to the DLL
class Solution {
  public:
    Node* head = NULL;
    Node *prev = NULL;
    void toDLL(Node* root){
        
        if(root == NULL) return;
        
        toDLL(root->left);
        
        if(prev == NULL)
            head = root;
        else{
            root->left = prev;
            prev->right = root;
        }
        
        prev = root;
        
        toDLL(root->right);
        
    }
    Node* bToDLL(Node* root) {
        // code here
        toDLL(root);
        
        return head;
    }
};

/*
==================== REVISION BLOCK — Binary Tree to Doubly Linked List (in-order) ====================

Problem
-------
Convert a binary tree to a **doubly linked list (DLL)** in-place such that the DLL nodes
appear in **in-order** of the tree. The left pointer becomes `prev`, and the right pointer
becomes `next`. Return the head of the DLL.

Pattern
-------
**In-order traversal** (L → Root → R). While visiting nodes in-order, keep a pointer to
the previously visited node and link:
    prev->right = curr,  curr->left = prev
The first visited node becomes the head.

Algorithm (step-by-step, precise)
---------------------------------
We maintain two pointers: `head` (first DLL node) and `prev` (last linked node so far).

1) If root is null → return null.
2) Recurse (or iterate) to the **left** subtree.
3) Visit `root`:
   a) If `prev` is null, set `head = root` (first node in in-order).
   b) Else: connect bidirectionally:
        prev->right = root
        root->left  = prev
   c) Set `prev = root`.
4) Recurse (or iterate) to the **right** subtree.
5) After finishing, `head` is the DLL head (its `left` is null; tail’s `right` is null).

Correctness (sketch)
--------------------
In-order traversal visits nodes in ascending in-order. By linking each visited node with the
immediately prior visited node, we produce a linear doubly linked sequence in the exact in-order.
The first visit sets the head; all subsequent visits link consecutively, so the final list is correct.

Complexity
---------
Time: O(n) — each node visited once.
Space: 
- Recursive: O(h) recursion stack (h = tree height; worst O(n) for skewed trees).
- Iterative/Morris variants below: O(h) for explicit stack, or **O(1)** extra with Morris.

Edge Cases / Pitfalls
---------------------
- **Reset** `head` and `prev` for each call (avoid stale members across test cases).
- For very deep (skewed) trees, recursion may overflow → use iterative or Morris.
- If the original tree is a **BST**, the resulting DLL is sorted by `data`.
- Ensure final boundaries: `head->left == nullptr`, `tail->right == nullptr` (naturally true here).

========================================================
*/

// ===== Your recursive idea, made re-entrant (no stale members) =====
class Solution {
    Node* head = nullptr;
    Node* prev = nullptr;

    void inorderLink(Node* root) {
        if (!root) return;
        inorderLink(root->left);

        if (!prev) head = root;
        else {
            prev->right = root;
            root->left = prev;
        }
        prev = root;

        inorderLink(root->right);
    }

  public:
    Node* bToDLL(Node* root) {
        head = prev = nullptr;     // reset for each call
        inorderLink(root);
        return head;
    }
};

// ==================== Optional: Iterative in-order with explicit stack (O(h) space) ====================
Node* bToDLL_iterative(Node* root) {
    if (!root) return nullptr;
    std::stack<Node*> st;
    Node* cur = root;
    Node* head = nullptr;
    Node* prev = nullptr;

    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();

        if (!prev) head = cur;
        else {
            prev->right = cur;
            cur->left   = prev;
        }
        prev = cur;

        cur = cur->right;
    }
    return head;
}

