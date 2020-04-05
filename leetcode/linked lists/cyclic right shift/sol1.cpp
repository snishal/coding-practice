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
    ListNode* rotateRight(ListNode* head, int k) {
        
        if(head){
            
            ListNode *it = head, *tail;
            int len = 1;
            
            while(it->next){
                it = it->next;
                len++;
            }
            
            k = k % len;
            
            if(k > 0){            
                
                tail = it;
                it = head;
                
                for(int i = 1; i < len - k; i++){
                    it = it->next;    
                }
                
                tail->next = head;
                head = it->next;
                it->next = NULL;
                
            }
            
            
        }
        
        return head;
        
    }
};