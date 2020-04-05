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
        if(root){
            if(root == p || root == q)return root;
            auto leftNode = lowestCommonAncestor(root->left, p, q);
            auto rightNode = lowestCommonAncestor(root->right, p, q);
            
            if(leftNode){
                if(rightNode){
                    return root;
                }else{
                    return leftNode;
                }
            }
            return rightNode;
        }
        return nullptr;
    }
    
};