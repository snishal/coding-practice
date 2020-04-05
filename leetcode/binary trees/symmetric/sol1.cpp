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
    
    bool isMirror(TreeNode *t1, TreeNode *t2){
        if(t1 && t2){
            return (t1->val == t2->val) ? isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left) : false;
        }else if(t1 == nullptr && t2 == nullptr){
            return true;
        }else{
            return false;
        }
    }
    
    bool isSymmetric(TreeNode* root) {
        return isMirror(root, root);
    }
};