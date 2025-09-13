class Solution {
  public:
    const int null = -1;
    
    void serializeHelper(Node *root, vector<int>&arr){
        if(root == NULL){
            arr.push_back(null);
            return;
        }
        arr.push_back(root->data);
        serializeHelper(root->left, arr);
        serializeHelper(root->right, arr);
    }
    
    vector<int> serialize(Node *root) {
        // Your code here
        vector<int>arr;
        serializeHelper(root, arr);
        return arr;
    }

    int index = 0;
    Node *deSerialize(vector<int> &arr) {
        
        if(index == arr.size()) return NULL;
        
        int val = arr[index];
        index++;
        if(val == null) return NULL;
        
        Node* root = new Node(val);
        root->left = deSerialize(arr);
        root->right = deSerialize(arr);
        
        return root;
        
    }
};




/*
==================== REVISION BLOCK — Serialize & Deserialize Binary Tree (preorder with nulls) ====================

Problem
-------
Design `serialize(root) -> vector<int>` and `deSerialize(arr) -> Node*` so that
deserializing the serialized output reconstructs the original binary tree.

Pattern
-------
**Preorder DFS** with a **null sentinel**:
- Visit: push node->data; recurse left; recurse right.
- For null children, push a sentinel value to preserve structure.

Algorithm (step-by-step)
------------------------
Serialize(root, arr):
1) If root is null: push SENTINEL and return.
2) Push root->data.
3) Serialize(root->left, arr).
4) Serialize(root->right, arr).

Deserialize(arr, idx):
1) If idx == arr.size(): return null (safety).
2) Let val = arr[idx++].
3) If val == SENTINEL: return null.
4) Make node = new Node(val).
5) node->left  = Deserialize(arr, idx).
6) node->right = Deserialize(arr, idx).
7) Return node.

Correctness (sketch)
--------------------
Preorder with explicit null markers uniquely encodes both **values** and **shape**.
During deserialization, the sequence is consumed in the same preorder; each sentinel
restores null links, so structure and values are reconstructed exactly.

Complexity
----------
Let n be the number of nodes.
- Time:  O(n) to serialize + O(n) to deserialize (visit each node/marker once).
- Space: O(n) output size; recursion stack O(h) where h is tree height (O(n) worst-case skewed).

Edge Cases
----------
- Empty tree → serialization is a single sentinel; deserialization returns null.
- Pathologically skewed tree → recursion depth = n (consider iterative or tail recursion limits).
- **Sentinel collisions**: Ensure the sentinel (e.g., -1) is not a valid node value in your domain.

Pitfalls
--------
- Global/member `index` must be **reset to 0** before each new `deSerialize` run.
  Prefer passing `idx` by reference to avoid shared state bugs.
- `pow(…)` not used here; avoid floating ops in count/height logic elsewhere.
- If values can be negative (including -1), pick a sentinel outside domain or use an
  auxiliary presence flag instead of overloading values.

========================================================
*/

// ===== Clean, re-entrant version (no shared index; same format as your code) =====
class Solution {
    static constexpr int SENTINEL = -1;  // ensure node->data never equals this (or change format)

    void serializeDFS(Node* root, std::vector<int>& out) {
        if (!root) { out.push_back(SENTINEL); return; }
        out.push_back(root->data);
        serializeDFS(root->left,  out);
        serializeDFS(root->right, out);
    }

    Node* deserializeDFS(const std::vector<int>& in, size_t& idx) {
        if (idx >= in.size()) return nullptr;          // safety
        int val = in[idx++];
        if (val == SENTINEL) return nullptr;
        Node* node = new Node(val);
        node->left  = deserializeDFS(in, idx);
        node->right = deserializeDFS(in, idx);
        return node;
    }

  public:
    std::vector<int> serialize(Node *root) {
        std::vector<int> out;
        out.reserve(2'000); // optional: pre-reserve if you have a size estimate
        serializeDFS(root, out);
        return out;
    }

    Node *deSerialize(std::vector<int> &arr) {
        size_t idx = 0;                 // re-entrant, no member state
        return deserializeDFS(arr, idx);
    }
};


/* ==================== Optional: Level-Order (BFS) format ====================

Idea
----
Serialize with BFS including nulls so that children of index i are at 2*i+1 / 2*i+2
(if you keep full-null padding). Or, more compactly, store values and explicit null markers in order:
[ root, L, R, L.L, L.R, R.L, R.R, ... ].

Pros: Iterative, shallow call stack.
Cons: Usually produces more markers than preorder for sparse trees.

Sketch:

std::vector<int> serialize_bfs(Node* root) {
    std::vector<int> out;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        if (!cur) { out.push_back(SENTINEL); continue; }
        out.push_back(cur->data);
        q.push(cur->left);
        q.push(cur->right);
    }
    // (Optional) trim trailing SENTINELs
    while (!out.empty() && out.back() == SENTINEL) out.pop_back();
    return out;
}

Node* deSerialize_bfs(const std::vector<int>& in) {
    if (in.empty()) return nullptr;
    size_t idx = 0;
    if (in[idx] == SENTINEL) return nullptr;
    Node* root = new Node(in[idx++]);
    std::queue<Node*> q; q.push(root);
    while (!q.empty() && idx < in.size()) {
        Node* cur = q.front(); q.pop();
        // left
        if (idx < in.size()) {
            if (in[idx] != SENTINEL) { cur->left = new Node(in[idx]); q.push(cur->left); }
            ++idx;
        }
        // right
        if (idx < in.size()) {
            if (in[idx] != SENTINEL) { cur->right = new Node(in[idx]); q.push(cur->right); }
            ++idx;
        }
    }
    return root;
}
*/
