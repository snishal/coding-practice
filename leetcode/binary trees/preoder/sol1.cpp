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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> traversal;
        stack<TreeNode*> s;
        if(root)s.push(root);
        
        while(!s.empty()){
            root = s.top();
            s.pop();
            
            traversal.emplace_back(root->val);
            
            if(root->right)s.push(root->right);
            if(root->left)s.push(root->left);
        }
        
        return traversal;
    }
};