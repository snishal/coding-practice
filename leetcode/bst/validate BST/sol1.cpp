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
    bool isValidBST(TreeNode* root) {
        bool isValid = true;
        TreeNode *prevNode = nullptr, *pred = nullptr;
        while(root){
            if(root->left == nullptr){
                if(prevNode != nullptr && prevNode->val >= root->val){
                    isValid = false;
                }
                prevNode = root;
                root = root->right;
            }else{
                pred = root->left;
                while(pred->right != nullptr && pred->right != root){
                    pred = pred->right;
                }
                if(pred->right == nullptr){
                    pred->right = root;
                    root = root->left;
                }else{
                    pred->right = nullptr;
                    if(prevNode != nullptr && prevNode->val >= root->val){
                        isValid = false;
                    }
                    prevNode = root;
                    root = root->right;
                }
            }
        }
        
        return isValid;
    }
};