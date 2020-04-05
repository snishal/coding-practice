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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        
        if(m < n){
            int idx = 1;
            ListNode *l = nullptr, *tail = nullptr, *prev = nullptr, *curr = head, *t = nullptr;

            while(idx < m){
                prev = curr;
                curr = curr->next;
                idx++;
            }
            
            l = prev;
            tail = curr;
            
            prev = curr;
            curr = curr->next;

            while(idx < n){
                t = curr->next;
                curr->next = prev;
                prev = curr;
                curr = t;
                idx++;
            }
            
            if(l){
                tail->next = curr;
                l->next = prev;
            }else{
                head = prev;
                tail->next = curr;
            }
            
        }
        
        return head;
    }
};