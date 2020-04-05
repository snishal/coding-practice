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
    ListNode *detectCycle(ListNode *head) {
        
        bool flag = false;
        ListNode *slow = head, *fast = head, *node = nullptr;
        
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast){
                flag = true;
                slow = head;
                break;
            }
        }
        
        if(flag){
            while(slow != fast){
                slow = slow->next;
                fast = fast->next;
            }   
            
            node = slow;
        }
        
        return node;
    }
};