
// 归并排序，递归
ListNode* sortList(ListNode* head) {
	if(head==NULL  ||  head->next==NULL)
		return head;
	ListNode* slow=head;
	ListNode* fast=head->next;
	while(fast  &&  fast->next)
	{
		fast=fast->next->next;
		slow=slow->next;
	}
	ListNode* second=slow->next;
	second=sortList(second);
	slow->next=NULL;
	head=sortList(head);
	head=merge(head, second);
	return head;
}

ListNode* merge(ListNode* first, ListNode* second)
{
	ListNode* head=new ListNode(0);
	ListNode* tmp=head;
	while(first  &&  second)
	{
		if(first->val<second->val)
		{
			tmp->next=first;
			tmp=tmp->next;
			first=first->next;
		}
		else
		{
			tmp->next=second;
			tmp=tmp->next;
			second=second->next;
		}
	}
	while(first)
	{
		tmp->next=first;
		first=first->next;
		tmp=tmp->next;
	}
	while(second)
	{
		tmp->next=second;
		second=second->next;
		tmp=tmp->next;
	}
	tmp->next=NULL;
	
	tmp=head->next;
	delete head;
	return tmp;
}

// 归并排序，迭代
ListNode* sortList(ListNode* head) {
	
}