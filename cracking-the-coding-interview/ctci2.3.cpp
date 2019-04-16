#include<stdio.h>


typedef struct _Node ListNode;
struct _Node{
	int data;
	struct _Node* next;
};

void deleteNode(ListNode *node)
{
	if(node->next==NULL)
		return;
	ListNode* next=node->next;
	node->data=next->data;
	node->next=next->next;
	delete next;
}

void printlist(ListNode* start)
{
	while(start)
	{
		printf("%d, ", start->data);
		start=start->next;
	}
	printf("\n");
}

ListNode* init(int a[], int n)
{
	ListNode *head, *p;
	for(int i=0; i < n; ++i)
	{
		ListNode *nd = new ListNode();
		nd->data = a[i];
		nd->next=NULL;
		if(i==0){
			head = p = nd;
			continue;
		}
		p->next = nd;
		p = nd;
	}
	return head;
}

void freeList(ListNode* head)
{
	ListNode *p=head, *q=NULL;
	while(p)
	{
		q=p->next;
		delete p;
		p=q;
	}
}

int main()
{
	{
		ListNode* l1;
		int a[]={3,1,4,1,5,9,2,6,0};
		l1=init(a, sizeof(a)/sizeof(a[0]));
		printlist(l1);
		
		ListNode* c=l1;
		for(int i=0; i<4; ++i) c = c->next;
		deleteNode(c);
		printlist(l1);
		
		freeList(l1);
	}
	return 0;
}