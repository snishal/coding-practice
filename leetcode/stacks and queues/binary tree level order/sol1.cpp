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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> traversal;
        queue<TreeNode*> level;
        
        if(root)level.push(root);
        
        while(!level.empty()){
            int levelSize = level.size();
            vector<int> levelTraversal;
            for(int i = 0; i < levelSize; i++){
                root = level.front();
                level.pop();
                
                levelTraversal.emplace_back(root->val);
                if(root->left)level.emplace(root->left);
                if(root->right)level.emplace(root->right);
            }
            traversal.emplace_back(levelTraversal);
        }
        return traversal;
    }
};