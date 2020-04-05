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
    int sumRootToLeaf(TreeNode* root) {
        int _partialSum = 0;
        
        return helper(root, _partialSum);
    }
    
    int helper(TreeNode* root, int _partialSum){
        if(root){
            _partialSum = 2 * _partialSum + root->val;
            if(root->left == nullptr && root->right == nullptr){
                return _partialSum;
            }else{
                return helper(root->left, _partialSum) + helper(root->right, _partialSum); 
            }
        }
        return 0;
    }
};