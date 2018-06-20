BSTNode *BST_Search(BiTree T, ElemType key, BSTNode *&p)
{
	 p=NULL;
	 while(T!=NULL  &&  key!=T->data)
	 {
		 p=T;
		 if(key<T->data)
			 T=T->lchild;
		 else
			 T=T->rchild;
	 }
	 return T;
}


int BST_Insert(BiTree &T, KeyType k)
{
	if(T==NULL)
	{
		T=(BiTree)malloc(sizeof(BSTNode));
		T->key=k;
		T->lchild=T->rchild=NULL;
		return 1;
	}
	else if(k==T->key)
		return 0;
	else if(k<T->key)
		return BST_Insert(T->lchild, k);
	else
		return BST_Insert(T->rchild, k);
}


void Create_BST(BiTree &T, KeyType str[], int n)
{
	T=NULL;
	int i=0;
	while(i<n)
	{
		BST_Insert(T, str[i]);
		i++;
	}
}





//判定二叉排序树
KeyType predt=-32767;

int JudgeBST(BiTree bt)
{
	int b1, b2;
	if(bt==NULL)
		return 1;
	else
	{
		b1=JudgeBST(bt->lchild);
		if(b1==0  ||  predt>=bt->data)
			return 0;
		predt=bt->data;
		b2=JudgeBST(bt->rchild);
		return b2;
	}
}


//二叉排序树中结点层次
int level(BiTree bt, BSTNode *p)
{
	int n=0;
	BiTree t=bt;
	if(bt!=NULL)
	{
		n++;
		while(t->data!=p->data)
		{
			if(t->data<p->data)
				t=t->rchild;
			else
				t=t->lchild;
			n++;
		}
	}
	return n;
}

//判断平衡二叉树
void Judge_AVL(BiTree bt, int &balance, int &h)
{
	int bl, br, hl, hr;
	if(bt==NULL)
	{
		h=0;
		balance=1;
	}
	else if(bt->lchild==NULL  &&  bt->rchild==NULL)
	{
		h=1;
		balance=1;
	}
	else
	{
		Judge_AVL(bt->lchild, bl, h1);
		Judge_AVL(bt->rchild, br, hr);
		h=(h1>hr?hl:hr)+1;
		if(abs(hl, hr)<2)
			balance=bl&br;
		else
			balance=0;
	}
}




//二叉排序树最小最大关键字
KeyType MinKey(BSTNode *bt)
{
	while(bt->lchild!=NULL)
		bt=bt->lchild;
	return bt->data;
}

KeyType MaxKey(BSTNode *bt)
{
	while(bt->rchild!=NULL)
		bt=bt->rchild;
	return bt->data;
}



//从大到小输出二叉排序树中值不小于k的关键字
void OutPut(BSTNode *bt, KeyType k)
{
	if(bt==NULL)
		return ;
	if(bt->rchild!=NULL)
		OutPut(bt->rchild, k);
	if(bt->ldata>=k)
		printf(" %d", bt->data);
	if(bt->lchild!=NULL)
		OutPut(bt->lchild, k);
}



//查找二叉排序树中第k小的元素
BSTNode *Search_Small(BSTNode* t, int k)
{
	//在以t为根的子树上寻找第k小的元素，返回其所在结点的指针。k从1开始计算
	//在树结点中增加一个count数据成员，存储以该结点为根的子树的结点个数
	if(k<1  ||  k>t->count)
		return NULL;
	if(t->lchild==NULL)
	{
		if(k==1)
			return t;
		else
			return Search_Small(t->rchild, k-1);
	}
	else
	{
		if(t->lchild->count==k-1)
			return t;
		if(t->lchild->count>k-1)
			return Search_Small(t->lchild, k);
		if(t->lchild->count<k-1)
			return Search_Small(t->rchild, k-(t->lchild->count+1));
	}
}



//后序遍历的非递归算法
typedef struct{
	BTNode *p;
	int rvisited;
}SNode;//栈中的结点定义

typedef struct{
	SNode Elem[maxsize];
	int top;
}SqStack;//栈结构体

void PostOrder2(BiTree T)
{
	SNode sn;
	BTNode *pt=T;
	InitStack(S);

	while(pt)
	{
		Push(pt, 0);
		pt=pt->lchild;
	}

	while(!S.IsEmpty())
	{
		sn=S.getTop();
		if(sn.p->rchild==NULL  ||  sn.rvisited)
		{
			Pop(S, pt);
			visit(pt);
		}
		else
		{
			sn.rvisited=1;
			pt=sn.p->rchild;
			while(pt!=NULL)
			{
				Push(S, pt, 0);
				pt=pt->lchild;
			}
		}
	}
}



//输入一个整数data和一棵二元树。从根的根结点开始往下访问一直到叶节点，所经过的所有结点形成一条路径。打印出路径和与data相等的所有路径。
bool Track(BiTree *p, int sum, int data, Queue<BiTree> q)
{
	if(p==NULL)
		return;

	if(p->lchild==NULL  &&  p->rchild==NULL  &&  p->data+sum==data)
	{
		q.EnQueue(p);
		while(!q.QueueEmpty())
		{
			DataType x=q.DeQueue()->data;
			cout<<x<<" ";
		}
		cout<<endl;
		return;
	}

	if((p->lchild!=NULL  ||  p->rchild!=NULL)  &&  p->data+sum<data)
	{			
		q.EnQueue(p);
		if(p->lchild!=NULL)
		{
			Track(p->lchild, sum+p->data, data, q);
		}
		if(p->lchild!=NULL  &&  p->rchild!=NULL)
		{
			Track(p->rchild, sum+p->data, data, q);
		}
		q.DeQueue();
	}
}


Track(T, 0, 12, q);




//先序遍历的非递归算法
void PreOrder2(BiTree T)
{
	InitStack(S);
	BiTree p=T;
	Push(S, p);
	while(!IsEmpty(S))
	{
		Pop(S, p);
		Visit(p);
		if(p->rchild)
			Push(S, p->rchild);
		if(p->lchild)
			Push(S, p->lchild);
	}
}


void PreOrder3(BiTree T)
{
	InitStack(S);
	BiTree p=T;
	while(p!=NULL  ||  !IsEmpty(S))
	{
		while(p!=NULL)
		{
			Visit(p);
			Push(S, p);
			p=p->lchild;
		}
		if(!IsEmpty(S))
		{
			Pop(S, p);
			p=p->rchild;
		}
	}
}



//二叉树的层次遍历
void level(BiTree T)
{
	InitQueue(Q);
	BiTree t=T;
	EnQueue(Q, t);
	while(!IsEmpty(Q))
	{
		DeQueue(Q, t);
		Visit(t);
		if(t->lchild)
			EnQueue(Q, t->lchild);
		if(t->rchild)
			EnQueue(Q, t->rchild);
	}
}