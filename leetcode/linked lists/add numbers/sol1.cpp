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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode *head, *curr;
        
        int sum;
        bool carry = false;
        
        if(l1 && l2){
            sum = l1->val + l2->val;
            if(sum >= 10){
                sum = sum - 10;
                carry = true;
            }
            
            l1 = l1->next;
            l2 = l2->next;
            
            head = new ListNode(sum);
            curr = head;
        }
        
        while(l1 && l2){
            sum = 0;
            if(carry){
                sum += sum + 1;
            }
            
            sum += l1->val + l2->val;
            if(sum >= 10){
                sum = sum - 10;
                carry = true;
            }else{
                carry = false;
            }
            
            l1 = l1->next;
            l2 = l2->next;
            
            curr->next = new ListNode(sum);
            curr = curr->next;
        }
        
        while(l1){
            sum = 0;
            if(carry){
                sum = sum + 1;
            }
            
            sum += l1->val;
            if(sum >= 10){
                sum = sum - 10;
                carry = true;
            }else{
                carry = false;
            }
            
            l1 = l1->next;
            
            curr->next = new ListNode(sum);
            curr = curr->next;
        }
        
        while(l2){
            sum = 0;
            if(carry){
                sum = sum + 1;
            }
            
            sum += l2->val;
            if(sum >= 10){
                sum = sum - 10;
                carry = true;
            }else{
                carry = false;
            }
            
            l2 = l2->next;
            
            curr->next = new ListNode(sum);
            curr = curr->next;
        }
        
        if(carry){
            curr->next = new ListNode(1);        
        }
        
        return head;
        
    }
};