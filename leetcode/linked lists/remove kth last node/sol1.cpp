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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *itr1 = head, *itr2 = head, *del;
        
        while(n != 0){
            itr1 = itr1->next;
            n--;
        }
        
        if(itr1){
            while(itr1->next){
                itr1 = itr1->next;
                itr2 = itr2->next;
            }
            del = itr2->next;
            itr2->next = itr2->next->next;

        }else{
            del = head;
            head = head->next;
        }
        
        
        delete del;
        
        return head;
    }
};