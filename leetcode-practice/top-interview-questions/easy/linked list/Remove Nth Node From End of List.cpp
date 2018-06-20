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
    	ListNode* dummy=new ListNode(0);
    	dummy.next=head;
    	
        ListNode* p=dummy;
        ListNode* end=head;
        for(int i=0; i<n; i++)
        	end=end->next;
        while(end!=NULL)
        {
        	p=p->next;
        	end=end->next;
		}
		p->next=p->next->next;
		ListNode* result=dummy->next;
		delete dummy;
		return result;
    }
};
