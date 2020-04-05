/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode *prev = NULL, *curr = head;
        
        while(curr){
            if(prev && prev->val == curr->val){
                prev->next = curr->next;
                curr = curr->next;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }
        
        return head;
    }
};