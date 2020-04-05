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
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        longestPath(root, diameter);
        
        return diameter;
    }
    
    int longestPath(TreeNode* root, int& diameter){
        if(root){
            int leftPath = (root->left) ? longestPath(root->left, diameter) + 1 : 0;
            int rightPath = (root->right) ? longestPath(root->right, diameter) + 1 : 0;
            
            diameter = max(diameter, leftPath + rightPath);
            return max(leftPath, rightPath);
        }
        return 0;
    }
};