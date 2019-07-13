
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* l3=NULL;
		ListNode* p=l1;
		ListNode* q=l2;
		ListNode* r=l3;
		int c=0;
		while(p  &&  q)
		{
			int digit=p->val+q->val+c;
			c=0;
			if(digit>=10)
			{
				c=1;
				digit-=10;
			}
			ListNode* n=new ListNode(digit);
			if(l3==NULL)
			{
				l3=n;
				r=l3;
			}
			else
			{
				r->next=n;
				r=n;
			}
			p=p->next;
			q=q->next;
		}
		if(p==NULL)
			p=q;
		while(p)
		{
			int digit=p->val+c;
			c=0;
			if(digit>=10)
			{
				c=1;
				digit-=10;
			}
			ListNode* n=new ListNode(digit);
			if(l3==NULL)
			{
				l3=n;
				r=l3;
			}
			else
			{
				r->next=n;
				r=n;
			}
			p=p->next;
		}
		if(c>0)
		{
			ListNode* n=new ListNode(c);
			r->next=n;
		}
		
		return l3;
    }
};