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
    bool isPalindrome(ListNode* head) {
     
        ListNode *slow = head, *fast = head;
        vector<int> s;
        
        while(fast && fast->next){
            s.push_back(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if(!s.empty()){
            
            if(fast){
                slow = slow->next;
            }
            
            while(slow){
                if(slow->val == s.back()){
                    slow = slow->next;
                    s.pop_back();
                }else{
                    return false;
                }
            }
        }
        return s.empty();
    }
};