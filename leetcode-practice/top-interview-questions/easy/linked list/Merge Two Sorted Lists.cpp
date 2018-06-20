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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
//    	if(l1==NULL)
//    		return l2;
//    	else if(l2==NULL)
//    		return l1;
        
        ListNode* head=new ListNode(0);
        ListNode* cur=head;
        
        ListNode* p=l1;
        ListNode* q=l2;
        while(p  &&  q)
        {
        	if(p->val<=q->val)
        	{
        		cur->next=p;
        		cur=p;
        		p=p->next;
        		cur->next=NULL;        		
			}
			else
			{
				cur->next=q;
				cur=q;
				q=q->next;
				cur->next=NULL;
			}
		}
		if(p)
		{
			cur->next=p;	
		}
		else
		{
			cur->next=q;
		}
		
		ListNode* result=head->next;
		delete head;
		return result;
    }
};
