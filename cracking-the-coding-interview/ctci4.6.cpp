
typedef struct node{
	int data;
	node *left, *right;
	node *parent;
	
	node(int d):data(d),parent(NULL),left(NULL),right(NULL){}
	node(int d, node* p, node* l, node* r):data(d),parent(p),left(l),right(r){}
	
	bool isLeaf()
	{
		return (left==NULL &&  right==NULL ) ? true : false;
	}
}BTNode;

// 使用辅助存储
void sameAncestor1(BTNode* btn1, BTNode* btn2)
{
	std::set<BTNode*> s;
	BTNode* p=NULL;
	for(p=btn1->parent; p!=NULL; p=p->parent)
		s.push(p);
	for(p=btn2->parent; p!=NULL; p=p->parent)
	{
		if(s.count(p))
			break;
		s.push(p);
	}
	return p;
}

// 不使用辅助存储
void sameAncestor2(BTNode* btn1, BTNode* btn2)
{
	BTNode* p=NULL;
	for(p=btn1->parent; p!=NULL; p=p->parent)
	{
		if(father(p, btn2))
			break;
	}
	return p;
}


bool father(BTNode* f, BTNode* c)
{
	if(f=NULL ||  c==NULL)
		return false;
	BTNode* p=NULL;
	for(p=c->parent; p!=NULL; p=p->parent)
	{
		if(p==f)
			break;
	}
	return p!=NULL;
}

BTNode* getBinaryTree(int a[], int start, int end)
{
	if(start>end)
		return NULL;
	if(start==end)
	{
		BTNode* n=new BTNode(a[start], NULL, NULL);
		return n;
	}
	int middle=start+(end-start)/2;
	BTNode* n=new BTNode(a[middle]);
	n->left=getBinaryTree(a, start, middle-1);
	n->right=getBinaryTree(a, middle+1, end);
	return n;
}

BTNode* initBST()
{
	int a[]={3,1,4,1,5,9,2,6};
	int sz=sizeof(a)/sizeof(*a);
	BTNode* root=getBinaryTree2(a, 0, sz-1, NULL);
	
	printf("create BST :\nin Traverse:");
	inTraverse(root);
	printf("\n preTraverse:");
	preTraverse(root);
	printf("\n");
	return root;
}

// ===============================================================
typedef struct node2{
	int data;
	node2 *left, *right;
	
	node2(int d):data(d),left(NULL),right(NULL){}
	node2(int d, node2* l, node2* r):data(d),left(l),right(r){}
	
	bool isLeaf()
	{
		return (left==NULL &&  right==NULL ) ? true : false;
	}
}BTNode2;

bool father2(BTNode* f, BTNode* c)
{
	if(f=NULL ||  c==NULL)
		return false;
	if(f->left==c  ||  f->right==c)
		return true;
	if(father2(f->left, c)  ||  father2(f->right, c))
		return true;
	return false;
}

// 
void sameAncestor3(BTNode2 *root, BTNode2* btn1, BTNode2* btn2)
{
	BTNode* cur=root;
	while(true)
	{
		if(cur->left  &&  father2(cur->left, btn1)  &&  father2(cur->left, btn2))
			cur=cur->left;
		else if(cur->right  &&  father2(cur->right, btn1)  &&  father2(cur->right, btn2))
			cur=cur->right;
		else
			break;
	}
	return cur;
}

BTNode2* getBinaryTree2(int a[], int start, int end, BTNode2* parent)
{
	if(start>end)
		return NULL;
	if(start==end)
	{
		BTNode2* n=new BTNode2(a[start], parent, NULL, NULL);
		return n;
	}
	int middle=start+(end-start)/2;
	BTNode2* n=new BTNode2(a[middle]);
	n->left=getBinaryTree2(a, start, middle-1, n);
	n->right=getBinaryTree2(a, middle+1, end, n);
	return n;
}


int main()
{
	{
		BTNode* root=initBST();
		
		freeBST(root);
	}
	
	return 0;
}