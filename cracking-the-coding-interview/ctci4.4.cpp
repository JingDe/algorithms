#include<stdio.h>
#include<vector>
#include<list>
#include<queue>

typedef struct node{
	int data;
	node *left, *right;
	node *parent;
	int level;
	
	node(int d):data(d),parent(NULL),left(NULL),right(NULL){}
	node(int d, node* p, node* l, node* r):data(d),parent(p),left(l),right(r){}
	
	bool isLeaf()
	{
		return (left==NULL &&  right==NULL ) ? true : false;
	}
}BTNode;

void inTraverse(BTNode* root);
void preTraverse(BTNode* root);

// 从有序数组创建二叉查找树
BTNode* getBinaryTree2(int a[], int start, int end, BTNode* parent)
{
	if(start>end)
		return NULL;
	if(start==end)
	{
		BTNode* n=new BTNode(a[start], parent, NULL, NULL);
		return n;
	}
	int middle=start+(end-start)/2;
	BTNode* n=new BTNode(a[middle]);
	n->left=getBinaryTree2(a, start, middle-1, n);
	n->right=getBinaryTree2(a, middle+1, end, n);
	return n;
}

BTNode* initBST()
{
	int a[]={1,2,3,4,5,6,7,8};
	int sz=sizeof(a)/sizeof(*a);
	BTNode* root=getBinaryTree2(a, 0, sz-1, NULL);
	
	printf("create BST :\nin Traverse:");
	inTraverse(root);
	printf("\n preTraverse:");
	preTraverse(root);
	printf("\n");
	return root;
}

void freeBST(BTNode* root)
{
	
}

void inTraverse(BTNode* root)
{
	if(root==NULL)
		return;
	inTraverse(root->left);
	printf("%d ", root->data);
	inTraverse(root->right);
}

void preTraverse(BTNode* root)
{
	if(root==NULL)
		return;
	printf("%d ", root->data);
	preTraverse(root->left);
	preTraverse(root->right);
}

void printLists(std::vector<std::list<BTNode*> > ls);

std::vector<std::list<BTNode*> > getNodeLists(BTNode *head)
{
	std::vector<std::list<BTNode*> > lists;
	if(head==NULL)
		return lists;
	std::list<BTNode*> l;
	
	std::queue<BTNode*> Q;
	BTNode* rightest=head;
	Q.push(head);	
	BTNode* latest=head;
	printf("level traverse: ");
	while(!Q.empty())
	{
		BTNode* cur=Q.front();
		Q.pop();
		
		printf("%d ", cur->data);
		
		l.push_back(cur);
		if(cur==rightest)
		{
			lists.push_back(l);
			l.clear();
		}
		if(cur->left)
		{
			Q.push(cur->left);
			latest=cur->left;
		}
		if(cur->right)
		{
			Q.push(cur->right);
			latest=cur->right;
		}
		if(cur==rightest)
				rightest=latest;
		printf("rightest %d\n", rightest->data);
	}
	printf("\n");
	return lists;
}

void printLists(std::vector<std::list<BTNode*> > ls)
{
	printf("all %d lists : \n", ls.size());
	for(int i=0; i<ls.size(); ++i)
	{
		std::list<BTNode*> l=ls[i];
		printf("list %d:\n", i);
		for(std::list<BTNode*>::iterator it=l.begin(); it!=l.end(); ++it)
		{
			printf("%d, ", (*it)->data);
		}
		printf("\n");
	}
}

int main()
{
	{
		BTNode* root=initBST();
		std::vector<std::list<BTNode*> > ls=getNodeLists(root);
		freeBST(root);
		printLists(ls);
	}
	return 0;
}
