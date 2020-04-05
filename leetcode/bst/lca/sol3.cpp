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
    int num_nodes;
    TreeNode* ancestor;
    
    Status(int _num_nodes = 0, TreeNode* _node = nullptr){
        num_nodes = _num_nodes;
        ancestor = _node;
    }
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return LCAHelper(root, p, q).ancestor;
    }
    
    Status LCAHelper(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root){
            Status leftStatus = LCAHelper(root->left, p, q);
            if(leftStatus.num_nodes == 2)return leftStatus;
            
            Status rightStatus = LCAHelper(root->right, p, q);
            if(rightStatus.num_nodes == 2)return rightStatus;
            
            int nodes = leftStatus.num_nodes + rightStatus.num_nodes + (root->val == p->val) + (root->val == q->val);
            return Status(nodes, (nodes == 2) ? root : nullptr);
        }
        return Status();
    }
    
};