

ListNode* rotateRight(ListNode* head, int k) {
	if(head==NULL)
		return NULL;
	int len=0;
	ListNode* tail=NULL;
	ListNode* cur=head;
	while(cur!=NULL)
	{
		tail=cur;
		cur=cur->next;
		++len;
	}
	// get tail
	
	int move = k % len;
	ListNode* fast=head;
	ListNode* slow=head;
	for(int i=0; i<move; ++i)
		fast=fast->next;
	
	while(fast->next!=NULL)
	{
		fast=fast->next;
		slow=slow->next;
	}
	
	ListNode* newHead=slow->next;
	tail->next=head;
	slow->next=NULL;
	
	return newHead;
}