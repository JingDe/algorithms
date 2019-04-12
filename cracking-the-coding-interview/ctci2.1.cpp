#include<stdio.h>
#include<iostream>

typedef struct _Node{
	int data;
	struct _Node* next;
}ListNode;

class List{
private:
	ListNode *head;
	
public:
	List():head(NULL){}
	~List();
	
	void Init(int a[], int cnt);
	void PushFront(int data);
	void PushFront2(int data);
	void Print();
	
	void removeDuplicateList1();
	void removeDuplicateList2();
};

List::~List()
{
	ListNode *p=head, *q=NULL;
	while(p)
	{
		q=p->next;
		delete p;
		p=q;
	}
}

void List::Init(int a[], int cnt)
{
	for(int i=0; i<cnt; i++)
		PushFront2(a[i]);
}

void List::PushFront(int data)
{
	ListNode *node=new ListNode;
	node->data=data;
	node->next=NULL;
	if(head==NULL)
	{
		head=node;
	}
	else
	{
		node->next=head->next;
		head->next=node;
	}
}

void List::PushFront2(int data)
{
	ListNode *node=new ListNode;
	node->data=data;
	node->next=NULL;
	if(head==NULL)
	{
		head=node;
	}
	else
	{
		node->next=head;
		head=node;
	}
}

void List::Print()
{
	for(ListNode* p=head; p; p=p->next)
		printf("%d,", p->data);
	printf("\n");
}

// 不使用缓存
void List::removeDuplicateList2()
{
	ListNode *cur=head, *check=cur, *pre=cur;
	while(cur)
	{
		pre=cur;
		check=cur->next;
		while(check)
		{
			if(check->data==cur->data)
			{
				pre->next=check->next;
				delete check;
				//check=pre->next;
			}
			else
			{
				//check=check->next;
				pre=pre->next;
			}
			check=pre->next;
		}
		cur=cur->next;
	}
}

// ======================== 
ListNode* Init(int a[], int n)
{
	ListNode *head=NULL, *p=NULL;
	for(int i=0; i<n; ++i)
	{
		ListNode* nd=new ListNode();
		nd->data=a[i];
		if(i==0)
		{
			head=p=nd;
		}
		else
		{
			p->next=nd;
			p=nd;
		}
	}
	p->next=NULL;
	return head;
}

bool hash[100]={0};
// 允许使用缓存，存储元素是否出现过
void removeDuplicateList1(ListNode* head)
{
	if(head==NULL) return;
	ListNode *p=head, *q=head->next;
	hash[head->data]=true;
	while(q)
	{
		if(hash[q->data])
		{
			ListNode *t=q;
			p->next=q->next;
			delete t;
			q=p->next;
		}
		else
		{
			hash[q->data]=true;
			p=p->next;
			q=q->next;
		}
	}
}

void print(ListNode *head){
    while(head){
        std::cout << head->data << " ";
        head = head->next;
    }
	std::cout<<std::endl;
}

int main()
{
	{
		List l;
		int a[]={4,3,2,4,6,7,1,2,2,3,3,3};
		l.Init(a, sizeof(a)/sizeof(a[0]));
		l.Print();
		l.removeDuplicateList2();
		l.Print();
	}
	
	printf("\n===========================\n");
	{
		int a[]={4,3,2,4,6,7,1,2,2,3,3,3};
		ListNode* l=Init(a, sizeof(a)/sizeof(a[0]));
		print(l);
		removeDuplicateList1(l);
		print(l);
	}
	return 0;
}