
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* deleteDuplicates(ListNode* head) {
	if(head==NULL  ||  head->next==NULL)
		return head;
	ListNode* before=NULL;
	ListNode* start=head;
	ListNode* end=head->next;
	while(end!=NULL)
	{
		if(start->val!=end->val)
		{
			before=start;
			start=end;
			end=end->next;
		}
		else
		{
			while(end!=NULL  &&  end->val==start->val)
				end=end->next;
			if(before==NULL)
				head=end;
			else
				before->next=end;
			if(end==NULL)
				break;
			start=end;
			end=end->next;
		}
	}
	return head;
}