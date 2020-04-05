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
    int kthSmallest(TreeNode* root, int k) {
        if(root){
            int it = 0;
            stack<TreeNode*> inorder;

            while(root || !inorder.empty()){
                while(root){
                    inorder.push(root);
                    root = root->left;
                }
                root = inorder.top();
                inorder.pop();
                it++;

                if(it == k)break;

                root = root->right;
            }

            return root->val;
        }
        return -1;
    }
};