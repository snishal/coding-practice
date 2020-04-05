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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() > 0){
            unordered_map<int, int> nodeIdxMap;
            for(int i = 0; i < inorder.size(); i++){
                nodeIdxMap.emplace(inorder[i], i);
            }
            return helper(preorder, 0, preorder.size()-1, 0, inorder.size()-1, nodeIdxMap);
        }
        return nullptr;
    }
    
    TreeNode* helper(vector<int>& preorder, size_t preStart, size_t preEnd, size_t inStart, size_t inEnd, unordered_map<int, int>& nodeIdxMap){
        if(preStart <= preEnd){
            TreeNode *root = new TreeNode(preorder[preStart]);
            auto rootInorderIdx = nodeIdxMap.find(preorder[preStart])->second;
            auto leftTreeSize = rootInorderIdx - inStart;
            root->left = helper(preorder, preStart + 1, preStart + 1 + leftTreeSize - 1, inStart, inStart + leftTreeSize - 1, nodeIdxMap);
            root->right = helper(preorder, preStart + leftTreeSize + 1, preEnd, inStart + leftTreeSize + 1, inEnd, nodeIdxMap);
            
            return root;
        }
        return nullptr;
    }
};