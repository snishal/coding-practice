/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:
    Node* connect(Node* root) {
        queue<Node*> level;
        if(root)level.push(root);
        size_t levelSize = 0;
        Node *prev = nullptr, *curr = nullptr;
        
        while(!level.empty()){
            levelSize = level.size();
            prev = nullptr;
            for(int i = 0 ; i < levelSize; i++){
                curr = level.front();
                level.pop();
                
                if(prev)prev->next = curr;
                prev = curr;
                
                if(curr->left)level.push(curr->left);
                if(curr->right)level.push(curr->right);
            }
            prev->next = nullptr;
        }
        return root;
    }
};