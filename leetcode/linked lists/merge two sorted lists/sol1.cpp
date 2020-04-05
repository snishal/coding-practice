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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *l3 = NULL;
        ListNode *itr = NULL;
        
        while(l1 && l2){
            if(l1->val < l2->val){
                if(itr){
                    itr->next = new ListNode(l1->val);
                    itr = itr->next;
                }else{
                    l3 = new ListNode(l1->val);
                    itr = l3;
                }
                l1 = l1->next;
            }else{
                if(itr){
                    itr->next = new ListNode(l2->val);
                    itr = itr->next;
                }else{
                    l3 = new ListNode(l2->val);
                    itr = l3;
                }
                l2 = l2->next;
            }
        }
        
        while(l1){
            if(itr){
                itr->next = new ListNode(l1->val);
                itr = itr->next;
            }else{
                l3 = new ListNode(l1->val);
                itr = l3;
            }
            l1 = l1->next;
        }
        
        while(l2){
            if(itr){
                itr->next = new ListNode(l2->val);
                itr = itr->next;
            }else{
                l3 = new ListNode(l2->val);
                itr = l3;
            }
            l2 = l2->next;
        }
        
        return l3;
    }
};