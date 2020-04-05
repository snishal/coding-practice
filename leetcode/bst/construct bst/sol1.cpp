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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return helper(preorder, 0, preorder.size());
    }
    
    TreeNode* helper(vector<int>& preorder, int l, int r){
        if(l >= r){
            return nullptr;    
        }
        
        TreeNode *root = new TreeNode(preorder[l]);
        
        int partition = l+1;
        while(partition < r && preorder[l] > preorder[partition])partition++;
        
        root->left = helper(preorder, l + 1, partition);
        root->right = helper(preorder, partition, r);
        
        return root;
    }
};