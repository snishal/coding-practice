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
    
    void appendNode(ListNode** curr, ListNode** next){
        (*curr)->next = *next;
        *curr = *next;
        *next = (*next)->next;
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummy_head = new ListNode(0), *tail= dummy_head;
        
        while(l1 && l2){
            appendNode(&tail, l1->val < l2->val ? &l1 : &l2);
        }
        
        tail->next = l1 ? l1 : l2;
        
        return dummy_head->next;
    }
};