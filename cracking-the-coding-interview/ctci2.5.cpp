
#include<stdio.h>
#include<assert.h>
#include<set>

typedef struct _Node ListNode;

struct _Node{
	// int data;
	char ch;
	struct _Node* next;
	
	_Node(char c, _Node * n):ch(c),next(n){}
	_Node(char c):ch(c),next(NULL){}
};

// struct ListNode{
	int data;
	// char ch;
	// struct ListNode* next;
	
	// ListNode(char c, ListNode * n):ch(c),next(n){}
	// ListNode(char c):ch(c),next(NULL){}
// };

ListNode* getLoopNode(ListNode* head)
{
	ListNode *fast=head, *slow=head;
	while(fast  &&  slow  /* &&  fast!=slow */)
	{
		fast=fast->next;
		if(fast==NULL)
			break;
		fast=fast->next;
		
		slow=slow->next;
		
		if(fast==slow)
			break;
	}
	
	if(fast==NULL  ||  slow==NULL)
		return NULL;
	
	assert(fast==slow);
	slow=head;
	while(fast!=slow)
	{
		fast=fast->next;
		slow=slow->next;
	}
	return fast;
}

ListNode* hashSolution(ListNode* lt)
{
	std::set<ListNode*> nodes;
	ListNode* p=lt;
	while(p)
	{
		if(nodes.count(p))
			return p;
		nodes.insert(p);
		p=p->next;
	}
	return NULL;
}

int  main()
{
		ListNode* a=new ListNode('a');
		ListNode* b=new ListNode('b');
		ListNode* c=new ListNode('c');
		ListNode* d=new ListNode('d');
		ListNode* e=new ListNode('e');
		
		ListNode* start=NULL;
	{
		// A B C D E C
		a->next=b;
		b->next=c;
		c->next=d;
		d->next=e;
		e->next=c;
		
		if((start=getLoopNode(a))!=NULL)
			printf("start node is %c\n", start->ch);
		if((start=hashSolution(a))!=NULL)
			printf("start node is %c\n", start->ch);
	}
	
	{
		a->next=b;
		b->next=c;
		c->next=d;
		d->next=e;
		e->next=NULL;
		
		if((start=getLoopNode(a))!=NULL)
			printf("start node is %c\n", start->ch);
		if((start=hashSolution(a))!=NULL)
			printf("start node is %c\n", start->ch);
	}
		delete a;
		delete b;
		delete c,d,e;
	return 0;
}