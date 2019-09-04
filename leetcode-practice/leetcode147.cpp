

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
    ListNode* insertionSortList(ListNode* head) {
        if(head==NULL  ||  head->next==NULL)
			return head;
		ListNode* cur=head->next;
		ListNode* h=new ListNode(0);
		h->next=head;
		while(cur)
		{
			ListNode* before=h;
			while(before->next!=cur  &&  before->next->value<cur->value)
				before=before->next;
			if(before->next==cur)
			{
				cur=cur->next;
			}
			else // before->next->value >= cur->value
			{
				// 将cur插入到before之后
				ListNode* next=cur->next;
				cur->next=before->next;
				before->next=cur;
				cur=next;
			}
		}
		delete h;
		return before->next;
    }
};