struct Node{
    char ch;
    int val;
    Node *left;
    Node *right;
    Node(char c, int v, Node *l = NULL, Node *r = NULL){
        ch = c;
        val = v;
        left = l;
        right = r;
    }
    
};

struct myCmp{
    bool operator()(Node *a, Node*b){
        return a->val > b->val;
    }
};

void buildNodes(Node* root, vector<string>&res, string str){
    if(root == NULL)
        return;
    if(root->ch != '#'){
        res.push_back(str);
    }
    buildNodes(root->left, res, str + '0');
    buildNodes(root->right, res, str + '1');
}

class Solution {
  public:
    vector<string> huffmanCodes(string S, vector<int> f, int N) {
        if(f.size() == 1){
            return {"0"};
        }
        // Code here
        priority_queue<Node*, vector<Node*>, myCmp> pq;
        for(int i=0;i<f.size();i++){
            pq.push(new Node({S[i], f[i], NULL, NULL}));
        }
        while(pq.size() > 1){
            Node *left = pq.top();
            pq.pop();
            Node *right = pq.top();
            pq.pop();
            Node *root = new Node({'#', (left->val + right->val), NULL, NULL});
            root->left = left;
            root->right = right;
            pq.push(root);
        }
        
        vector<string>res;
        string str = "";
        buildNodes(pq.top(), res, str);
        return res;
    }
};


/*
==================== REVISION BLOCK — Huffman Encoding (build codes) ====================

Problem
-------
Given N distinct characters `S[i]` with frequencies `f[i]`, build the **Huffman codes**
and return a vector of strings where the i-th string is the code for `S[i]`.

Pattern
-------
Greedy + **min-heap** (priority queue):
- Repeatedly merge the two least-frequent nodes to build the Huffman tree.
- Code assignment = DFS from root: left edge '0', right edge '1'.
- A single symbol edge-case gets code "0".

Algorithm (step-by-step)
------------------------
1) Build a min-heap of leaf nodes: (char, freq).
2) While heap.size() > 1:
   a) Pop two nodes L, R with smallest freq.
   b) Create parent P with freq = L.freq + R.freq, P.left=L, P.right=R.
   c) Push P back into the heap.
3) The remaining node is the root. Do a DFS:
   - If leaf: code[leaf.char] = (path == "" ? "0" : path)   // single-symbol fix
   - Else: recurse left with path+'0', right with path+'1'.
4) Build result vector: for i in [0..N-1], push code[S[i]].

Correctness (sketch)
--------------------
Huffman’s algorithm is optimal: merging least-frequent nodes minimizes the weighted
external path length (classic proof via exchange/greedy-choice & optimal substructure).
DFS labeling produces a prefix-free code consistent with the tree.

Complexity
---------
- Building tree: O(N log N) for heap operations.
- DFS labeling: O(N) codes, total length equals sum of code lengths.
- Space: O(N) nodes + recursion stack O(height).

Edge Cases / Pitfalls
---------------------
- **Single symbol** → return {"0"}.
- Use a **leaf test** (left==nullptr && right==nullptr) instead of sentinel chars.
- Your original code collected codes in traversal order; the judge expects order **aligned to S**.
- Avoid brace-initializing `new Node({ ... })` when you have a user-defined constructor.
- Prefer 1-based-safe `priority_queue` comparator returning smallest freq on top.

========================================================
*/

struct Node {
    char ch;
    int  val;
    Node *left, *right;
    Node(char c, int v, Node* l=nullptr, Node* r=nullptr) : ch(c), val(v), left(l), right(r) {}
};

struct Cmp {
    bool operator()(const Node* a, const Node* b) const {
        return a->val > b->val; // min-heap by frequency
    }
};

void buildCodes(Node* root, const std::string& path, std::unordered_map<char,std::string>& code) {
    if (!root) return;
    if (!root->left && !root->right) { // leaf
        code[root->ch] = path.empty() ? "0" : path; // single-symbol fix
        return;
    }
    buildCodes(root->left,  path + '0', code);
    buildCodes(root->right, path + '1', code);
}

class Solution {
public:
    std::vector<std::string> huffmanCodes(std::string S, std::vector<int> f, int N) {
        if (N == 0) return {};
        if (N == 1) return {"0"};

        std::priority_queue<Node*, std::vector<Node*>, Cmp> pq;
        for (int i = 0; i < N; ++i) {
            pq.push(new Node(S[i], f[i]));
        }

        while ((int)pq.size() > 1) {
            Node* L = pq.top(); pq.pop();
            Node* R = pq.top(); pq.pop();
            Node* P = new Node('\0', L->val + R->val, L, R);
            pq.push(P);
        }

        Node* root = pq.top();
        std::unordered_map<char, std::string> code;
        code.reserve(N * 2);

        buildCodes(root, "", code);

        std::vector<std::string> res;
        res.reserve(N);
        for (int i = 0; i < N; ++i) {
            res.push_back(code[S[i]]);
        }
        return res;
    }
};
