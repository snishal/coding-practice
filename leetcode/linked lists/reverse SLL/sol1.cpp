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
        if(m == n){
            return head;
        }
        
        ListNode *dummy_head = new ListNode(0);
        dummy_head->next = head;
        
        int k = 1;
        auto sublist_head = dummy_head;
        while(k++ < m){
            sublist_head = sublist_head->next;
        }
        
        auto sublist_iter = sublist_head->next;
        while(m++ < n){
            auto temp = sublist_iter->next;
            sublist_iter->next = temp->next;
            temp->next = sublist_head->next;
            sublist_head->next = temp;
        }
        
        return dummy_head->next;
    }
};