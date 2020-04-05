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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        
        ListNode *node = nullptr;
        if(headA && headB){
            ListNode *itA = headA, *itB = headB;
            int l1 = 1, l2 = 1;

            while(itA->next){
                itA = itA->next;
                l1++;
            }

            while(itB->next){
                itB = itB->next;
                l2++;
            }

            if(itA->val == itB->val){
                itA = headA;
                itB = headB;
                if(l1 < l2){
                    l2 = l2 - l1;

                    while(l2 != 0){
                        itB = itB->next;
                        l2--;
                    }
                }else{
                    l1 = l1 - l2;

                    while(l1 != 0){
                        itA = itA->next;
                        l1--;
                    }
                }

                while(itA != itB){
                    itA = itA->next;
                    itB = itB->next;
                }
                node = itA;
            }
        }
        return node;
    }
};