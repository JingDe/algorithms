#include<stdio.h>
#include<list>

struct Node{
	int data;
	Node* next;
	Node(int d):data(d),next(NULL){}
	Node(int d, Node* n):data(d),next(n){}
	
};

Node* listAdd(std::list<int>& l1, std::list<int>& l2)
{
	std::list<int>::iterator it1=l1.begin();
	std::list<int>::iterator it2=l2.begin();
	//std::list<int> l3;
	Node* l3=NULL;
	Node* tail=NULL;
	int c=0;
	for(; it1!=l1.end()  &&  it2!=l2.end(); ++it1, ++it2)
	{
		int tmp=*it1+*it2+c;
		if(tmp>=10)
		{
			tmp=tmp-10;
			c=1;
		}
		else
		{
			c=0;
		}
		Node* node=new Node(tmp);
		if(l3==NULL)
		{
			l3=node;
			tail=l3;
		}
		else
		{
			tail->next=node;
			tail=node;
		}
	}
	while(it1!=l1.end())
	{
		int tmp=*it1+c;
		if(tmp>=10)
		{
			tmp=tmp-10;
			c=1;
		}
		else
			c=0;
		Node* node=new Node(tmp);
		if(l3==NULL)
		{
			l3=node;
			tail=l3;
		}
		else
		{
			tail->next=node;
			tail=node;
		}
		++it1;
	}
	
	while(it2!=l2.end())
	{
		int tmp=*it2+c;
		if(tmp>=10)
		{
			tmp=tmp-10;
			c=1;
		}
		else
			c=0;
		Node* node=new Node(tmp);
		if(l3==NULL)
		{
			l3=node;
			tail=l3;
		}
		else
		{
			tail->next=node;
			tail=node;
		}
		++it2;
	}
	if(c==1)
	{
		Node* node=new Node(1);
		tail->next=node;
		tail=node;
	}
	return l3;
}

void printList(Node* head)
{
	if(head==NULL)
	{
		printf("null\n");
		return ;
	}
	for(Node* p=head; p!=NULL; p=p->next)
		printf("%d ", p->data);
	printf("\n");
}

void free(Node* head)
{
	Node* p=head;
	while(p!=NULL)
	{
		Node* cur=p->next;
		delete p;
		p=cur;
	}
}

int main()
{
	{
		std::list<int> l1({1, 1, 1});
		std::list<int> l2({9, 9, 9, 9, 9});
		Node* l3=listAdd(l1, l2);
		printf("get result list:\n");
		printList(l3);
		free(l3);
	}
	{
		std::list<int> l1;
		std::list<int> l2;
		Node* l3=listAdd(l1, l2);
		printf("get result list:\n");
		printList(l3);
		free(l3);
	}
	return 0;
}