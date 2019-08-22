

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
 
 
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* next=NULL;
		ListNode* cur=head;
		ListNode* curPrior=NULL;
		
		ListNode* newHead;
		while(cur!=NULL)
		{
			if(cur->val<x)
			{
				if(next==NULL)
				{
					newHead=cur;
					newHead->next
				}
				else
				{
					
				}
			}
		}
    }
};


ListNode* partition(ListNode* head, int x) 
{
	ListNode* before_head=new ListNode(0);
	ListNode* before=before_head;
	ListNode* after_head=new ListNode(0);
	ListNode* after=after_head;
	
	while(head!=NULL)
	{
		if(head.val<x)
		{
			before.next=head;
			before=before.next;
		}
		else
		{
			after.next=head;
			after=after.next;
		}
		head=head.next;
	}
	
	after.next=NULL;
	before.next=after_head.next;
	returnn before_head.next;	
}