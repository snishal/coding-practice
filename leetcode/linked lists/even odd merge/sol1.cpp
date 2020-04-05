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
    ListNode* oddEvenList(ListNode* head) {
        
        ListNode *l1 = head, *l2 = nullptr, *next;
        
        if(l1){
            l2 = l1->next;
            next = l2;
            
            while(l1->next && l2->next){
                l1->next = l2->next;
                l2->next = l1->next->next;
                
                l1 = l1->next;
                l2 = l2->next;
            }
            
            l1->next = next;
            
        }
        
        return head;
    }
};