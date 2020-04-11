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
private:
    int longestPath(TreeNode* root, int& diameter){
        if(root == nullptr){
            return 0;
        }
        auto leftPath = longestPath(root->left, diameter);
        auto rightPath = longestPath(root->right, diameter);
        
        diameter = max(diameter, leftPath + rightPath);
        return max(leftPath, rightPath) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        longestPath(root, diameter);
        return diameter;
    }
};