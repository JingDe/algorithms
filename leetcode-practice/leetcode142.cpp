
ListNode *detectCycle(ListNode *head) {
	if(head==NULL)
		return NULL;
	set<ListNode*> nodes;
	while(head!=NULL)
	{
		if(nodes.find(head)!=nodes.end())
			return head;
		nodes.insert(head);
		head=head->next;
	}
	return NULL;
}

ListNode *detectCycle(ListNode *head) 
{
	if(head==NULL)
		return NULL;
	ListNode* fast=head;
	ListNode* slow=head;
	ListNode* meet=NULL;
	while(fast->next  &&  fast->next->next)
	{
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow)
		{
			meet=fast;
			break;
		}
	}
	if(meet==NULL)
		return -1;
	fast=head;
	slow=meet;
	while(fast!=slow)
	{
		fast=fast->next;
		slow=slow->next;
	}
	return fast;
}