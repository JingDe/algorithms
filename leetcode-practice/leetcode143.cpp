
// 依序存储所有节点，最后链接起来
void reorderList(ListNode* head) {
	if(head==NULL)
		return;
	vector<ListNode*> nodes;
	while(head)
	{
		nodes.push_back(head);
		head=head->next;
	}
	int cnt=nodes.size();
	head=nodes[0];
	ListNode* before=NULL;
	
	int left=0; 
	int right=cnt-1;
	while(left<=right)
	{
		ListNode* p=nodes[left];
		ListNode* q=nodes[right];
		p->next=q;
		q->next=NULL;
		if(before)
			before->next=p;
		before=q;
	}
	return;
}

void reorderList(ListNode* head) {
	if(head==NULL)
		return ;
	
	// 找到链表中点
	ListNode* p1=head;
	ListNode* P2=head;
	while(p2->next  &&  p2->next->next)
	{
		p1=p1->next;
		p2=p2->next->next;
	}
	
	// p1->next指向后一半的第一个节点
	
	// 逆转后一半
	// 1->2->3->4->5->6 to 1->2->3->6->5->4
	ListNode* preMiddle=p1;
	ListNode* preCurrent=p1->next;
	while(preCurrent->next!=NULL)
	{
		ListNode* current=preCurrent->next;
		preCurrent->next=current->next;
		// 将current插入到preMiddle之后
		current->next=preMiddle->next;
		preMiddle->next=current;
	}
	
	// 1->2->3->6->5->4 to 1->6->2->5->3->4
	p1=head;
	p2=preMiddle->next;
	while(p1!=preMiddle)
	{
		preMiddle->next=p2->next;
		p2->next=p1->next;
		p1->next=p2;
		p1=p2->next;
		
		p2=preMiddle->next;
	}
	
}