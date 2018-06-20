void PreOrder(BiTree T)
{
	if(T!=NULL)
	{
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void InOrder(BiTree T)
{
	if(T!=NULL)
	{
		InOrder(T->lchild);
		visit(T);
		InOrder(T->rchild);
	}
}

void PostOrder(BiTree T)
{
	if(T!=NULL)
	{
		PostOrder(T>lchild);
		PostOrder(T->rchild);
		visit(T);
	}
}

void InOrder2(BiTree T)
{
	InitStack(S);
	BiTree p=T;
	while(p  ||  !IsEmpty(S))
	{
		if(p)
		{
			Push(S, p);
			p=p->lchild;
		}
		else
		{
			Pop(S, p);
			visit(p);
			p=p->rchild;
		}
	}
}

void LevelOrder(BiTree T)
{
	InitQueue(Q);
	BiTree p;
	EnQueue(Q, T);
	while(!IsEmpty(Q))
	{
		DeQueue(Q, p);
		visit(p);
		if(p->lchild!=NULL)
			EnQueue(Q, p->lchild);
		if(p->rchild!=NULL)
			EnQueue(Q, p->rchild);
	}
}

void InThread(ThreadTree &p, ThreadTree &pre)
{
	if(p!=NULL)
	{
		InThread(p->lchild, pre);
		if(p->lchild==NULL)
		{
			p->lchild=pre;
			p->ltag=1;
		}
		if(pre!=NULL &&  pre->rchild==NULL)
		{
			pre->rchild=p;
			pre->rtag=1;
		}
		pre=p;
		InThread(p->rchild, pre);
	}
}

void CreateInThread(ThreadTree T)
{
	ThreadTree pre=NULL;
	if(T!=NULL)
	{
		InThread(T, pre);
		pre->rchild=NULL;
		pre->rtag=1;
	}
}

void PostOrder(BiTree T)
{
	InitStack(S);
	p=T;
	r=NULL;//辅助指针r，其指向最近访问过的结点
	while(p  ||  !IsEmpty(S))
	{
		if(p)//走到最左边
		{
			push(S, p);
			p=p->lchild;
		}
		else
		{
			GetTop(S, p);
			if(p->rchild  &&  p->rchild!=r)//如果右子树存在，且未被访问过
			{
				p=p->rchild;//转向右
				push(S, p);//压入栈
				p=p->lchild;//再走到最左
			}
			else//否则，弹出结点并访问
			{
				pop(S, p);//将结点弹出
				visit(p->data);//访问该结点
				r=p;//记录最近访问过的结点
				p=NULL;//结点访问完后，重置p指针
			}
		}
	}
}


void InvertLevel(BiTree bt)
{
	Stack s;
	Queue Q;
	if(bt!=NULL)
	{
		InitStack(s);
		InitQueue(Q);
		EnQueue(Q, bt);
		while(IsEmpty(Q)==false)
		{
			DeQueue(Q, p);
			Push(s, p);
			if(p->lchild)
				EnQueue(Q, p->lchild);
			if(p->rchild)
				EnQueue(Q, p->rchild);
		}
		while(IsEmpty(s)==false)
		{
			Pop(s, p);
			visit(p->data);
		}
	}
}

int BtDepth(BiTree T)
{
	if(!T)//树空，高度为0
		return 0;
	int front=-1, rear=-1;
	int last=0, level=0;//last指向下一层第一个结点的位置
	BiTree Q[MaxSize];//设置队列Q，元素是二叉树结点指针且容量足够
	Q[++rear]=T;//将根结点入队
	BiTree p;
	while(front<rear)
	{
		p=Q[++front];
		if(p->lchild)
			Q[++rear]=p->lchild;
		if(p->rchild)
			Q[++rear]=p->rchild;
		if(front==last)
		{
			level++;
			last=rear;
		}
	}
	return level;
}

int BtDepth2(BiTree T)
{
	if(T==NULL)
		return 0;
	ldep=BtDepth(T->lchild);
	rdep=BtDepth(T->rchild);
	if(ldep->rdep)
		return ldep+1;
	else
		return rdep+1;
}

BiTree PreInCreate(ElemType A[], ElemType B[], int ll, int h1, int l2, int h2)
{
	root=(BiTNode*)malloc(sizeof(BiTNode));
	root->data=A[l1];
	for(i=l2; B[i]!=root->data; i++);
	llen=i-i2;
	rlen=h2-i;
	if(llen)
		root->lchild=PreInCreate(A, B, l1+1, l1+llen, l2, l2+llen-1);
	else
		root->lchild=NULL;
	if(rlen)
		root->rchild=PreInCreate(A, B, h1-rlen+1, h1, h2-rlen+1, h2);
	else
		root->rchild=NULL;
	return root;
}

bool IsComplete(BiTree T)
{
	InitQueue(Q);
	if(!T)
		return 1;
	EnQueue(Q, T);
	while(!IsEmpty(Q))
	{
		DeQueue(Q, p);
		if(p)
		{
			EnQueue(Q, p->lchild);
			EnQueue(Q, p->rchild);
		}
		else
		{
			while(!IsEmpty(Q))
			{
				DeQueue(Q, p);
				if(p)
					return 0;
			}
		}
	}
	return 1;
}

int DsonNodes(BiTree b)
{
	if(b==NULL)
		return 0;
	else if(b->lchild!=NULL  &&  b->rchild!=NULL)
		return DsonNodes(b->lchild)+DsonNodes(b->rchild)+1;
	else
		return DsonNodes(b->lchild)+DsonNodes(b->rchild);
}

void swap(BiTree b)
{
	if(b)
	{
		swap(b->lchild);
		swap(b->rchild);
		temp=b->lchild;
		b->lchild=b->rchild;
		b->rchild=temp;
	}
}

int i=1;
ElemType PreNode(BiTree b, int k)
{
	if(b==NULL)
		return '#';
	if(i==k)
		return b->data;
	i++;
	ch=PreNode(b->lchild, k);
	if(ch!='#')
		return ch;
	ch=PreNode(b->rchild, k);
	return ch;
}

void DeleteXTree(BiTree bt)
{
	if(bt)
	{
		DeleteXTree(bt->lchild);
		DeleteXTree(bt->rchild);
		free(bt);
	}
}
void Search(BiTree bt, ElemType x)
{
	BiTree Q[];
	if(bt)
	{
		if(bt->data==x)
		{
			DeleteXTree(bt);
			exit(0);
		}
		InitQueue(Q);
		EnQueue(Q, bt);
		while(!IsEmpty(Q))
		{
			DeQueue(Q, p);
			if(p->lchild)
				if(p->lchild->data==x)
				{
					DeleteXTree(p->lchild);
					p->lchild=NULL;
				}
				else
					EnQueue(Q, p->lchild);
			if(p->rchild)
				if(p->rchild->data==x)
				{
					DeleteXTree(p->rchild);
					p->rchild=NULL;
				}
				else
					EnQueue(Q, p->rchild);
		}
	}
}


typedef struct{
	BiTree t;
	int tag;
}stack;

void Search(BiTree bt, ElemType x)
{
	stack s[];
	top=0;
	while(bt!=NULL  ||  top>0)
	{
		while(bt!=NULL  &&  bt->data!=x)
		{
			s[++top].t=bt;
			s[top].tag=0;
			bt=bt->lchild;
		}
		if(bt->data==x)
		{
			printf("所查结点的所有祖先结点的值为：\n");
			for(i=1; i<=top; i++)
				printf("%d", s[i].t->data);
			exit(1);
		}
		while(top!=0  &&  s[top].tag==1)
			top--;
		if(top!=0)
		{
			s[top].tag=1;
			bt=s[top].t->rchild;//沿右分支向下遍历
		}
	}
}



typedef struct{
	BiTree t;
	int tag;
}stack;

stack s[], s1[];
BiTree Ancestor(BiTree ROOT, BiTNode *p, BiTNode *q)
{
	top=0;
	bt=ROOT;
	while(bt!=NULL  ||  top>0)
	{
		while(bt!=NULL  &&  bt!=p  &&  bt!=q)
		{
			s[++top].t=bt;
			s[top].tag=0;
			bt=bt->lchild;
		}
		while(top!=0  &&  s[top].tag==1)
		{
			if(s[top].t==p)
			{
				for(i=1; i<=top; i++)
					s1[i]=s[i];
				top1=top;
			}
			if(s[top].t==q)
			{
				for(i=top; i>0; i--)
					for(j=top1; j>0; j--)
						if(s1[j].t==s[i].t)
							return s[i].t;
			}
			top--;
		}
		if(top!=0)
		{
			s[top].tag=1;
			bt=s[top].t->rchild;
		}
	}
	return NULL;
}

typedef struct{
	BiTree data[MaxSize];
	int level[MaxSize];
	int front, rear;
}Qu;
int BTWidth(BiTree b)
{
	BiTree p;
	int k, max, i, n;
	Qu.front=Qu.rear=-1;
	Qu.rear++;
	Qu.data[Qu.rear]=b;
	Qu.level[Qu.rear]=1;
	while(Qu.front<Qu.rear)
	{
		Qu.front++;
		p=Qu.data[Qu.front];
		k=Qu.level[Qu.front];
		if(p->lchild!=NULL)
		{
			Qu.rear++;
			Qu.data[Qu.rear]=p->lchild;
			Qu.level[Qu.rear]=k+1;
		}
		if(p->rchild!=NULL)
		{
			Qu.rear++;
			Qu.data[Qu.rear]=p->rchild;
			Qu.level[Qu.rear]=k+1;
		}
	}
	printf("各结点的层次编号：\n");
	for(i=0; i<=Qu.rear; i++)
		printf("%c, %d\n", Qu.data[i]->data, Qu.level[i]);
	max=0;
	i=0;
	k=1;
	while(i<=Qu.rear)
	{
		n=0;
		while(i<=Qu.rear  &&  Qu.level[i]==k)
		{
			n++;
			i++;
		}
		k=Qu.level[i];
		if(n>max)
			max=n;
	}
	return max;
}

void PreToPost(ElemType pre[], int l1, int h1, ElemType post[], int l2, int h2)
{
	int half;
	if(l1<=h1)
	{
		post[h2]=pre[l1];
		half=(h1-l1)/2;
		PreToPost(pre, l1+1, l1+half, post, l2, l2+half-1);
		PreToPost(pre, l1+half+1, h1, post, h2+half, h2-1);
	}
}




LinkedList head, pre=NULL;
LinkedList InOrder(BiTree bt)
{
	if(bt)
	{
		InOrder(bt->lchild);
		if(bt->lchild==NULL  &&  bt->rchild==NULL)
			if(pre==NULL)
			{
				head=bt;
				pre=bt;
			}
			else
			{
				pre->rchild=bt;
				pre=bt;
			}
		InOrder(bt->rchild);
		pre->rchild=NULL;
	}
	return head;
}



int similar(BiTree T1, BiTree T2)
{
	int leftS, rightS;
	if(T1==NULL  &&  T2==NULL)
		return 1;
	else if(T1==NULL  ||  T2==NULL)
		return 0;
	else
	{
		leftS=similar(T1->lchild, T2->lchild);
		rightS=similar(T1->rchild, T2->rchild);
		return leftS&&rightS;
	}
}

BiTree InPostPre(BiTree t, BiThrTree p)
{
	BiThrTree q;
	if(p->rtag==0)
		q=p->rchild;
	else if(p->ltag==0)
		q=p->lchild;
	else if(p->lchild==NULL)
		q=NULL;
	else
	{
		while(p->ltag==1  &&  p->lchild!=NULL)
			p=p->lchild;
		if(p->ltag==0)
			q=p->lchild;
		else
			q=NULL;
	}
	return q;
}