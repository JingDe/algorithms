
ListNode* reverseBetween(ListNode* head, int m, int n) {
	ListNode* pre=head;
	int cnt=0;
	while(++cnt<m-1)
	{
		pre=pre->next;
	}
	
	ListNode* cur=pre->next->next;
	ListNode* curPre=pre->next;
	cnt=n-m;
	// 将包括cur在内开始的cnt个节点插入到pre后面
	for(int i=0; i<cnt; ++i)
	{
		ListNode* tmp=cur;
		curPre->next=cur->next;
		cur=cur->next;
		
		tmp->next=pre->next;
		pre->next=tmp;
	}
	return head;
}

ListNode* reverseBetween(ListNode* head, int m, int n) {
	ListNode* newDumpHead=new ListNode(0);
	newDumpHead->next=head;
	
	ListNode* pre=newDumpHead;
	int cnt=0;
	while(++cnt<m)
	{
		pre=pre->next;
	}
	
	ListNode* cur=pre->next->next;
	ListNode* curPre=pre->next;
	cnt=n-m;
	// 将包括cur在内开始的cnt个节点插入到pre后面
	for(int i=0; i<cnt; ++i)
	{
		ListNode* tmp=cur;
		curPre->next=cur->next;
		cur=cur->next;
		
		tmp->next=pre->next;
		pre->next=tmp;
	}
	return newDumpHead->next;
}

