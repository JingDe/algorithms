#include<stdio.h>


typedef struct _Node ListNode;

struct _Node{
	int data;
	struct _Node* next;
};

// 使用一快一慢两个指针
void lastN1(ListNode* head, int n)
{
	ListNode *fast=head, *slow=head, *start=head;
	int i=0;
	for(i=0; i<n  &&  fast!=NULL; i++)
		fast=fast->next;
	
	if(i==n)
	{
		while(fast)
			fast=fast->next, slow=slow->next;
		start=slow;
	}
	while(start)
	{
		printf("%d, ", start->data);
		start=start->next;
	}
	printf("\n");
}

// 递归解法，逆序打印
int out=0;
void lastN2(ListNode* head, int n)
{
	if(head==NULL)
		return;
	lastN2(head->next, n);
	if(out<n)
	{
		if(out==0)
			printf("%d", head->data);
		else
			printf(", %d", head->data);
		out++;
		if(out==n)
			printf("\n");
	}
	
}

int out2=0;
ListNode* start=NULL;
// 递归解法，正序打印
void lastN3(ListNode* head, int n)
{
	if(head==NULL)
		return;
	lastN3(head->next, n);
	out2++;
	if(out2==n)
		start=head;
}

void solution3(ListNode* head, int n)
{
	lastN3(head, n);
	ListNode* res=head;
	if(start!=NULL)
		res=start;
	while(res)
	{
		printf("%d, ", res->data);
		res=res->next;
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
	printf("\n---------solution1--------\n");
	{
		ListNode* l1;
		int a[]={3,1,4,1,5,9,2,6,0};
		l1=init(a, sizeof(a)/sizeof(a[0]));
		printf("l1, 5:\n");
		lastN1(l1, 5);		
		
		printf("l1, 200:\n");
		lastN1(l1, 200);
		freeList(l1);
	}
	
	printf("\n----------solution2-------\n");
	{
		ListNode* l1;
		int a[]={3,1,4,1,5,9,2,6,0};
		l1=init(a, sizeof(a)/sizeof(a[0]));
		printf("l1, 5:\n");
		out=0;
		lastN2(l1, 5);
		
		
		printf("l1, 200:\n");
		out=0;
		lastN2(l1, 200);
		freeList(l1);
	}
	
	printf("\n-----------------\n");
	{
		ListNode* l1;
		int a[]={3,1,4,1,5,9,2,6,0};
		l1=init(a, sizeof(a)/sizeof(a[0]));
		printf("l1, 5:\n");
		out2=0;
		solution3(l1, 5);
		
		
		printf("l1, 200:\n");
		out2=0;
		start=NULL;
		solution3(l1, 200);
		freeList(l1);
	}
	
	return true;
}
