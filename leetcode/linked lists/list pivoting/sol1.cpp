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
    ListNode* partition(ListNode* head, int x) {
        
        if(head){
            
            ListNode *p1 = nullptr, *p2 = nullptr, *curr = nullptr, *t = nullptr;
            
            if(head->val < x){
                
                p1 = head;
                while(p1->next && p1->next->val < x){
                    p1 = p1->next;
                }
                
                if(p1){
                    p2 = p1->next;
                }
                
            }else{
                
                p2 = head;
                while(p2->next && p2->next->val >= x){
                    p2 = p2->next;
                }
                
                p1 = p2->next;
                
                if(p1){
                    p2->next = p1->next;
                    p1->next = head;
                    head = p1;
                }
                
            }
            
            if(p2){
                curr = p2->next;
                
                while(curr){
                    if(curr->val < x){
                        p2->next = curr->next;
                        curr->next = p1->next;
                        p1->next = curr;
                        p1 = p1->next;
                        curr = p2->next;
                    }else{
                        p2 = p2->next;
                        curr = curr->next;
                    }    
                }
                
            }
            
        }
        
        return head;
    }
};