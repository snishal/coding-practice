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
    
    bool isLeaf(TreeNode* node){
        return (node->left == nullptr && node->right == nullptr);
    }
    
    bool hasPathSum(TreeNode* root, int sum) {
        if(root == nullptr){
            return false;
        }else if(isLeaf(root) && (sum - root->val) == 0){
            return true;
        }
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};