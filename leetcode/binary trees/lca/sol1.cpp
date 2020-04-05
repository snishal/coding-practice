/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct Status{
    int nodeCount;
    TreeNode *ancestor;
    
    Status(int _nodeCount = 0, TreeNode* _ancestor = nullptr){
        nodeCount = _nodeCount;
        ancestor = _ancestor;
    }
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return lcaHelper(root, p, q).ancestor;
    }
    
    Status lcaHelper(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root){
            auto leftStatus = lcaHelper(root->left, p, q);
            if(leftStatus.nodeCount == 2)return leftStatus;
            
            auto rightStatus = lcaHelper(root->right, p, q);
            if(rightStatus.nodeCount == 2)return rightStatus;
            
            int nodeCount = leftStatus.nodeCount + rightStatus.nodeCount + (root->val == p->val) + (root->val == q->val);
            return {nodeCount, nodeCount == 2 ? root : nullptr};
        }
        return {};
    }
    
};