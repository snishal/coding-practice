/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct BalancedStatus{
    int height;
    bool balanced;
    
    BalancedStatus(int _height = 0, bool _balanced = false){
        height = _height;
        balanced = _balanced;
    }
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return helperBalanced(root).balanced;
    }
    
    BalancedStatus helperBalanced(TreeNode *root){
        if(root == nullptr){
            return {0, true};
        }
        auto leftStatus = helperBalanced(root->left);
        auto rightStatus = helperBalanced(root->right);
        
        bool balanced = leftStatus.balanced && rightStatus.balanced && (abs(leftStatus.height - rightStatus.height) <= 1);
        return {max(leftStatus.height, rightStatus.height) + 1, balanced};
    }
};