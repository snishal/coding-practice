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
    vector<int> inorderTraversal(TreeNode* root) {
        
        TreeNode *currNode = nullptr;
        stack<TreeNode*> s;
        vector<int> inorder;
        
        while(true){
            
            while(root){
                s.push(root);
                root = root->left;
            }
            
            if(s.empty())break;
            
            root = s.top();
            s.pop();
            
            inorder.push_back(root->val);
            
            root = root->right;
            
        }
        
        return inorder;
    }
};