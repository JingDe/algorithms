
ListNode* swapPairs(ListNode* head) {
	if(head==NULL  ||  head->next==NULL)
		return head;
	
	ListNode* p=head;
	ListNode* q=p->next;
	ListNode* newHead=q;
	
	while(p  &&  q)
	{
		// insert p after q 
		ListNode* r=q->next;
		p->next=r;
		q->next=p;
		
		// if(p->next!=NULL)
			// p->next=p->next->next;				
		
		if(r==NULL)
			break;
		if(p->next->next)
			p->next=p->next->next;
		p=r;
		q=p->next;
	}
	return newHead;
}