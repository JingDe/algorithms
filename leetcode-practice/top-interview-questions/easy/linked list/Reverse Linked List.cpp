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
    ListNode* reverseList(ListNode* head) {
    	if(head==NULL)
    		return NULL;
        ListNode* p=head->next;   
		head->next=NULL;     
        while(p!=NULL)
        {
        	ListNode* temp=p->next;
        	
        	// 将p插入到head之前，更新head
			p->next=head;
			head=p; 
        	
        	p=temp;
		}
		return head;
    }
};
