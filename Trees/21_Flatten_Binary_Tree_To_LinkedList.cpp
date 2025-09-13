
class Solution {
public:
    void flatten(TreeNode* root) {
        if(root == NULL) return;
        stack<TreeNode*>s;
        s.push(root);
        while(!s.empty()){
            TreeNode *curr = s.top();
            s.pop();
            if(curr->right != NULL) s.push(curr->right);
            if(curr->left != NULL) s.push(curr->left);

            if(!s.empty()){
                curr->right = s.top();
            }  
            curr->left = NULL;
        }
        
    }
};

/*
==================== REVISION BLOCK — Flatten Binary Tree to Linked List (preorder) ====================

Problem
-------
Flatten the binary tree into a **right-skewed linked list** in-place, following **preorder**
(R, L, R) order: for every node, `left` becomes null and `right` points to the next node
in preorder.

Pattern
-------
Preorder traversal with **explicit stack** (or Morris-style O(1) rewiring).

Algorithm (Iterative stack; your approach, made precise)
-------------------------------------------------------
Goal invariant during traversal: all processed nodes have `left == nullptr` and their `right`
points to the next node in preorder.

1) If root == nullptr → return.
2) Push `root` on a stack `st`.
3) While `st` not empty:
   a) `cur = st.top(); st.pop();`
   b) If `cur->right` exists, `st.push(cur->right)`  // push right first
   c) If `cur->left`  exists, `st.push(cur->left)`   // then left so it’s processed next
   d) If `!st.empty()`, set `cur->right = st.top();` // next preorder node
   e) Set `cur->left = nullptr`.
4) Done. The tree is flattened in preorder as a right-only chain.

Correctness (sketch)
--------------------
The stack maintains remaining preorder nodes. Pushing `right` then `left` ensures `left`
is processed first (preorder). At each step we rewire `cur->right` to the next preorder
node sitting on the top of the stack and null the `left`, thus preserving a correct prefix
of the flattened list. By induction over the preorder sequence, all nodes become linked
in the right order.

Complexity
----------
Time: O(n) — each node is pushed/popped at most once.  
Space: O(n) — stack worst-case (skewed tree).

Edge Cases / Pitfalls
---------------------
- Push **right before left** to preserve preorder.
- Always null `cur->left` to avoid cycles.
- Works for empty tree and single-node trees (no-ops).
- In-place requirement: avoid building external lists.

==================== Optional: O(1) Space (Morris-like) ====================
Idea:
For each node with a left child, find the **rightmost** node in its left subtree (predecessor),
link that predecessor’s `right` to current’s original `right`, then rotate the left subtree
to the right and null out `left`. Move to `cur->right` and repeat.

Pseudo:
while (cur) {
  if (cur->left) {
    pred = cur->left;
    while (pred->right) pred = pred->right;
    pred->right = cur->right;
    cur->right = cur->left;
    cur->left = nullptr;
  }
  cur = cur->right;
}

Time: O(n) (each edge visited ≤ 2 times) ; Space: O(1).
*/

class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root) return;
        std::stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* cur = st.top(); st.pop();
            if (cur->right) st.push(cur->right);
            if (cur->left)  st.push(cur->left);
            if (!st.empty()) cur->right = st.top();
            cur->left = nullptr;
        }
    }
};

// ==================== Optional: O(1) Space variant ====================
void flatten_Morris(TreeNode* root) {
    TreeNode* cur = root;
    while (cur) {
        if (cur->left) {
            TreeNode* pred = cur->left;
            while (pred->right) pred = pred->right;
            pred->right = cur->right;
            cur->right = cur->left;
            cur->left = nullptr;
        }
        cur = cur->right;
    }
}
