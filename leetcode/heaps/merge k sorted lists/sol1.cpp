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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        ListNode *dummyHead = new ListNode(0), *curr = dummyHead, *minNode = nullptr;
        
        auto listNodeCmp = [](const ListNode* l1, const ListNode* l2){
            return l1->val > l2->val;
        };
        
        priority_queue<ListNode*, vector<ListNode*>, decltype(listNodeCmp)> minHeap(listNodeCmp);
        
        for(auto list : lists){
            if(list)minHeap.emplace(list);
        }
        
        while(!minHeap.empty()){
            minNode = minHeap.top();
            minHeap.pop();
            
            curr->next = new ListNode(minNode->val);
            curr = curr->next;
            
            if(minNode->next){
                minHeap.emplace(minNode->next);
            }
        }
        
        return dummyHead->next;
    }
};