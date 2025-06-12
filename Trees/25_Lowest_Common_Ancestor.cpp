/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        if(root == NULL) return NULL; // case 1
        if(root->val == p->val || root->val == q->val) return root; // case 2

        TreeNode* LCA1 = lowestCommonAncestor(root->left,p ,q);
        TreeNode* LCA2 = lowestCommonAncestor(root->right,p ,q);

        if(LCA1 != NULL && LCA2!= NULL) return root; // case 3;

        if(LCA1 != NULL) return LCA1;
        else return LCA2;
    }
};



TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    
    // ✅ Base Case 1: If the current node is NULL, return NULL (end of a path)
    if(root == NULL) return NULL;

    // ✅ Base Case 2: If the current node is either p or q, return the node
    // This means we've found one of the nodes; LCA could be this or higher up.
    if(root->val == p->val || root->val == q->val) return root;

    // 🔁 Recur for left and right subtrees
    TreeNode* LCA1 = lowestCommonAncestor(root->left, p, q);
    TreeNode* LCA2 = lowestCommonAncestor(root->right, p, q);

    // ✅ Case 3: If p and q are found in left and right subtrees respectively,
    // then current node is their Lowest Common Ancestor
    if(LCA1 != NULL && LCA2 != NULL) return root;

    // 🔄 If only one side returns a non-null, return that side
    // It means both p and q lie in that subtree
    if(LCA1 != NULL) return LCA1;
    else return LCA2;
}
