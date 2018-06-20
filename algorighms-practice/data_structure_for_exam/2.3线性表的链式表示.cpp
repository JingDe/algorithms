//单链表中结点类型的描述
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

//采用头插法创建单链表
//从表尾到表头逆向建立单链表L，每次均在头结点之后插入元素
LinkList CreateList(LinkList &L)
{
	LNode *s;
	int x;
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	scanf("%d", &x);
	while(x!=9999)
	{
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		s->next=L->next;
		L->next=s;
		scanf("%d", &x);
	}
	return L;
}

//采用尾插法建立单链表
//从表头到表尾正向建立单链表L，每次均在表尾插入元素
LinkList CreateList(LinkList &L)
{
	int x;
	L=(LinkList)malloc(sizeof(LNode));
	LNode *s,*r=L;
	scanf("%d", &x);
	while(x!=9999)
	{
		s=(LNode*)malloc(sizeof(LNode));
		s->data=x;
		r->next=s;
		r=s;
		scanf("%d",&x);
	}
	r->next=NULL;
	return L;
}

//按序号查找节点值
LNode *GetElem(LinkList L, int i)
{
	int j=1;
	LNode *p=L->next;
	if(i==0)
		return L;
	if(i<1)
		return NULL;
	while(p  &&  j<i)
	{
		p=p->next;
		j++;
	}
	return p;//返回第i个 结点的指针，如果i大于表长，p=NULL
}

//按值查找表结点
LNode *LocationElem(LinkList L, ElemType e)
{
	LNode *p=L->next;
	while(p!=NULL  &&  p->data!=e)
		p=p->next;
	return p;
}

//插入结点操作
//将*s插入到*p之后
p=GetElem(L, i-1);//查找插入位置的前驱结点
s->next=p->next;
p->next=s;

//将*s结点插入到*p之前的主要代码片段
s->next=p->next;//修改指针域，不能颠倒
p->next=s;
temp=p->data;//交换数据域部分
p->data=s->data;
s->data=temp;

//删除结点操作
p=GetElem(L, i-1);
q=p->next;
p->next=q->next;
free(q);

//删除结点*p的操作可以用删除*p的后继结点操作来实现
q=p->next;
p->data=p->next->data;
p->next=q->next;
free(q);

//双链表
typedef struct DNode{
	ElemType data;
	struct DNode *prior, *next;
}DNode, *DLinklist;

//双链表的插入操作

//双链表的删除操作

//循环链表
//循环单链表
//循环双链表

//静态链表
//静态链表结构类型的描述
typedef MaxSize 50;
typedef struct{
	ElemType data;
	int next;
}SLinkList[MaxSize];


//设计一个递归算法，删除不带头结点的单链表L中所有值为x的节点
void Del_x_3(LinkList &L, ElemType x)
{
	LNode *p;
	if(L==NULL)
		return ;
	if(data==x)
	{
		p=L;
		L=L->next;
		free(p);
		Del_x_3(L, x);
	}
	else
		Del_x_3(L->next, x);
}

//在头结点的单链表L中，删除所有值为x的结点，并释放其空间，假设值为x的结点不唯一，编写算法实现上述操作
void del_x(LinkList &L, ElemType x)
{
	LNode *p=L;
	while(p->next!=NULL)
	{
		if(p->next->data==x)
		{
			LNode *q=p->next;
			p->next=q->next;
			free(q);
		}
		p=p->next;
	}
}
//解法一：用p从头到尾扫描单链表，pre指向*p结点的前驱。若p所指结点的值为x，则删除，并让p移向下一个结点，
//否则让pre、p指针同步后移一个结点
void Del_x_1(LinkList &L, ElemType x)
{
	LNode *p=L->next, *pre=L, *q;
	while(p!=NULL)
	{
		if(p->data==x)
		{
			q=p;
			p=p->next;
			pre->next=p->next;
			free(q);
		}
		else
		{
			pre=p;
			p=p->next;
		}
	}
}
//解法二：采用尾插法建立单链表。用p指针扫描L的所有结点，当其值不为x时将其链接到L之后，否则将其释放
void Del_x_2(LinkList &L, ElemType x)
{
	LNode *p=L->next, *r=L, *q;
	while(p!=NULL)
	{
		if(p->data!=x)
		{
			r->next=p;
			r=p;
			p=p->next;
		}
		else
		{
			q=p;
			p=p->next;
			free(q);
		}
	}
	r->next=NULL;
}

//设L为带头结点的单链表，编写算法实现从尾到头反向输出每个节点的值
void print(LinkList L)
{
	if(L->next==NULL)
		return;
	LNode *p=L->next;
	L->next=p->next;//错
	print(L);
	cout<<p->data<<endl;
	free(p);//错
}
//
void R_Print(LinkList L)
{
	if(L->next!=NULL)
		R_Print(L->next);
	print(L->data);//错
}
void R_Print(LinkList L)
{
	if(L->next==NULL)
		return;
	else
		recurrence_print(L->next);
}
void recurrence_print(LinkList L)
{
	if(L->next!=NULL)
		recurrence_print();
	print(L->data);
}

//试编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设最小值结点是唯一的）
void del_min(LinkList &L)
{
	LNode *p=L;
	LNode *q=L->next;
	int min=-(1<<8);
	LNode m;
	while(q!=NULL)
	{
		if(q->data<min)
		{
			min=q->data;
			m=p;
		}
		else//错
		{
			p=q;
			q=p->next;
		}
	}
	LNode n=m->next;
	n->next=m->next;
	free(n);
}
//
LinkList Delete_Min()
{
	LNode *pre=L, *q=pre->next;
	LNode *minpre=pre, *q=p;
	while(p!=NULL)
	{
		if(p->data<minp->data)
		{
			minp=p;
			minpre=pre;
		}
		pre=p;
		p=p->next;
	}
	minpre->next=minp->next;
	free(minp);
	return L;
}

//试编写算法将带头结点的单链表就地逆置，辅助空间复杂度为O（1）
//解法一：将头结点摘下，然后从第一结点开始，依次前插入到头结点的后面（头插法建立单链表），
//直到最后一个结点为止
LinkList Reverse_1(LinkList &L)
{
	LinkList r;
	p=L->next;
	L->next=NULL;
	while(p!=NULL)
	{
		r=p->next;
		p->next=L->next;
		L->next=p;
		p=r;
	}
	return L;
}
//解法二：
LinkList Reverse_2(LinkList &L)
{
	LNode *pre, *p=L->next, *r=p->next;
	p->next=NULL;
	while(r!=NULL)
	{
		pre=p;
		p=r;
		r=r->next;
		p->next=pre;
	}
	L->next=p;
	return L;
}


//有一个带头结点的单链表L，设计一个算法使其元素递增有序
//算法思想：采用直接插入排序算法的思想，先构成只含一个数据节点的有序单链表，然后依次扫描单链表中剩下的节点
//*p（直至p==NULL为止），在有序表中通过比较查找插入*p的前驱结点*pre，然后将*p插入到*pre之后
void Sort(LinkList &L)
{
	LNode *p=L->next, *pre;
	LNode *r=p->next;
	p->next=NULL;
	p=r;
	while(p!=NULL)
	{
		r=p->next;
		pre=L;
		while(pre->next!=NULL  &&  pre->next->data<p->data)
			pre=pre->next;
		p->next=pre->next;
		pre->next=p;
		p=r;
	}
}

//设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，删除表中所有介于两个给定值之间的元素
void RangeDelete(LinkList &L, int min, int max)
{
	LNode *pr=L, *p=L->link;
	while(p!=NULL)
	{
		if(p->data>min  &&  p->data<max)
		{
			pr->link=p->link;
			free(p);
			p=pr->link;
		}
		else
		{
			pr=p;
			p=p->link;
		}
	}
}

//给定两个单链表，编写算法找出两个链表的公共结点
LinkList Search_1st_common(LinkList L1, LinkList L2)
{
	int len1=length(L1), len2=length(L2);
	LinkList longList, shortList;
	if(len1>len2)
	{
		longList=L1->next;
		shortList=L2->next;
		dist=len1-len2;
	}
	else
	{
		longList=L2->next;
		shortList=L1->next;
		dist=len2-len1;
	}
	while(dist--)
		longList=longList->next;
	while(longList!=NULL)
	{
		if(longList==shortList)
			return longList;
		else
		{
			longList=longList->next;
			shortList=shortList->next;
		}
	}
	return NULL;
}


//给定一个带头结点的单链表，设head为头指针，结点的结构为（data，next），data为整型元素，next为指针，
//试写出算法：按递增次序输出单链表中各结点的数据元素，并释放结点所占的存储空间（要求：不允许使用数组作为辅助空间）
//算法思想：对链表进行遍历，在每趟遍历中查找出整个链表的最小值元素，输出并释放结点所占空间；
//再查找次小值元素，输出并释放空间，如此下去，直至链表为空，最后释放头结点所占存储空间，时间复杂度为O(n*n)
void Min_Delete(LinkList &head)
{
	while(head->next!=NULL)
	{
		pre=head;
		p=pre->next;
		while(p->next!=NULL)
		{
			if(p->next->data<pre->next->data)
				pre=p;
			p=p->next;
		}   
		print(pre->next->data);
		u=pre->next;
		pre->next=u->next;
		free(u);
	}
	free(head);
}


//将一个带头结点的单链表A分解为两个带头结点的单链表A和B，使得A表中含有原表中序号为奇数的元素，
//而B表中含有原表中序号为偶数的元素，且保持其相对顺序不变。
//设置一个访问序号变量（初值为0），每访问一个结点序号自动加1，然后根据序号的奇偶性将结点插入到A表或B表中。
//重复以上操作直到表尾。
LinkList DisCreat_1(LinkList &A)
{
	i=0;
	B=(LinkList)malloc(sizeof(LNode));
	B->next=NULL;
	
	LNode *ra=A, *rb=B;
	p=A->next;
	A->next=NULL;
	
	while(p!=NULL)
	{
		i++;
		if(i%2==0)
		{
			rb->next=p;
			rb=p;
		}
		else
		{
			ra->next=p;
			ra=p;
		}
		p=p->next;
	}
	ra->next=NULL;
	rb->next=NULL;
	return B;
}
//采用尾插法保持原来结点中的顺序
//解法二：不用设置序号变量。while循环中的代码改成将结点插入到表A中和 将下一结点插入到表B中，
//这样while中第一处理的结点就是奇数号结点，第二处理的结点就是偶数号结点
LinkList Discret_2(LinkList &A)
{
	B=(LinkList)malloc(sizeof(LNode));
	B->next=NULL;
	LNode *ra=A, *rb=B;
	p=A->next;
	A->next=NULL;
	while(p!=NULL)
	{
		ra->next=p;
		ra->p;
		
		p=p->next
			if(p==NULL)
				break;
			rb->next=p;
			rb=p;
			p=p->next;
	}
	ra->next=NULL;
	rb->next=NULL;
	return B;
}

//设C={a1, b1, a2, b2, ..., an, bn}为线性表，采用带头结点的hc单链表存放，设计一个就地算法，将其拆分为两个线性表，使得A={a1, a2, ..., an}, B={bn,..., b2,b1}
//采用上题的思路，不设序号变量。二者的差别仅在于对B表的建立不采用尾插法，而是采用头插法
LinkList DisCreat_2(LinkList &A)
{
	LinkList B=(LinkList)malloc(sizeof(LNode));
	B->next=NULL;
	LNode *p=A->next, *q;
	LNode *ra=A;
	while(p!=NULL)
	{
		ra->next=p;
		ra=p;

		p=p->next;
		q=p->next;
		p->next=B->next;
		B->next=p;
		p=q;
	}
	ra->next=NULL;
	return B;
}


//在一个递增有序的线性表中，有数值重复的元素存在。若存储方式为单链表，
//设计算法去掉数值相同的元素，使表中不再有重复的元素
void delete_same(LinkList &L)
{
	if(L->next==NULL)
		return;
	LNode *q=L->next;
	LNode *p=q->next;
	while(p!=NULL)
	{
		if(p->data==q->data)
		{
			q->next=p->next;
			free(p);
			p=q->next;
		}
		else
		{
			q=p;
		}
	}
}
//算法思想：由于是有序表，所有相同值域的结点都是相邻的。用p扫描递增单链表L，
//若*p结点的值域等于其后继结点的值域，则删除后者，否则p移向下一个结点
void Del_same(LinkList &L)
{
	LNode *p=L->next, *q;
	while(p->next!=NULL)
	{
		q=p->next;
		if(p->data==q->data)
		{
			p->next=q->next;
			free(q);
		}
		else
			p=p->next;
	}
}


//假设有两个按元素值递增次序排列的线性表，均以单链表形式存储。请编写算法将这两个单链表归并为一个按元素值递减次序排列的单链表，
//并要求利用原来两个单链表的结点存放归并后的单链表。
//头插法
void merge(LinkList &A, LinkList &B, LinkList &L)
{
	LNode *hA=A;
	LNode *hB=B;
	A=A->next;
	B=B->next;
	free(hA);
	free(hB);

	LNode *p;
	while(A!=NULL  &&  B!=NULL)
	{
		if(A->data<B->data)
		{
			p=A->next;
			A->next=L->next;
			L->next=A;
			A=p;
		}
		else
		{
			p=B->next;
			B->next=L->next;
			L->next=B;
			B=p;
		}
	}
	while(A!=NULL)
	{
		p=A->next;
		A->next=L->next;
		L->next=A;
		A=p;
	}
	while(B!=NULL)
	{
		p=B->next;
		B->next=L->next;
		L->next=B;
		B=p;
	}
}
//算法思想：两个链表已经按元素值递增次序排序，将其合并时，均从第一个结点起进行比较，将小的结点链入链表中，同时后移工作指针。
void MergeList(LinkList &La, LinkList &Lb)
{
	LNode *r, *pa=La->next, *pb=Lb->next;
	La->next=NULL;
	while(pa  &&  pb)
	{
		if(pa->data<pb->data)
		{
			r=pa->next;
			pa->next=La->next;
			La->next=pa;
			pa=r;
		}
		else
		{
			r=pb->next;
			pb->next=La->next;
			La->next=pb;
			pb=r;
		}
	}
	if(pa)
		pb=pa;
	while(pb)
	{
		r=pb->next;
		pb->next=La->next;
		La->next=pb;
		pb=r;
	}
	free(Lb);
}

//设A和B是两个单链表（带头结点），其中元素递增有序。设计一个算法从A和B中公共元素产生单链表C，要求不破坏A、B的结点。
void create_same(LinkList &C, LinkList &A, LinkList &B)
{
	LNode *pc=C;
	LNode *small=A->next;
	LNode *big=B->next;
	while(small  &&  big)
	{
		if(small->data>big->data)
		{
			LNode *tmp=big;
			big=small;
			small=tmp;
		}
		while(small->data<big->data)
			small=small->next;
		if(small==NULL)
			break;
		if(small->data==big->data)
		{
			LNode *p=new LNode;
			p->data=small->data;

			p->next=pc->next;
			pc->next=p;
			pc=p;

			small=small->next;
			big=big->next;
		}
//		else if(small->data>big->data)
//		{
//			big=big->next;
//		}
	}
}
//算法思想：表A、B都有序，可从第一个元素起依次比较A和B两表的元素，若元素值不等，则值小的指针往后移，
//若元素值相等，则创建一个值等于两结点的元素值的新的结点，使用尾插法插入到新的链表中，
//并两个原表指针后移一位，直到其中一个链表遍历到表尾
void Get_Common(LinkList A, LinkList B)
{
	LNode *p=A->next, *q=B->next, *r, *s;
	LinkList C=(LinkList)malloc(sizeof(LNode));
	r=C;
	while(p!=NULL  &&  q!=NULL)
	{
		if(p->data<q->data)
			p=p->next;
		else if(p->data>q->data)
			q=q->next;
		else
		{
			s=(LNode*)malloc(sizeof(LNode));
			s->data=p->data;
			r->next=s;
			r=s;
			p=p->next;
			q=q->next;
		}
	}
	r->next=NULL;
}

//已知两个链表A和B分别表示两个集合，其元素递增排列。编制函数，求A和B的交集，并存放于A链表中
//算法思想：采用归并的思想，设置两个工作指针pa和pb，对两个链表进行归并扫描，只有同时出现在两集合中的元素才链接到结果表中
//且仅保留一个，其它的结点全部释放。当一个链表遍历完毕后，释放另一个表中剩下的全部结点。
void Union(LinkList &la, LinkList &lb)
{
	pa=la->next;
	pb=lb->next;
	pc=la;
	while(pa  &&  pb)
	{
		if(pa->data==pb->data)
		{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
			u=pb;
			pb=pb->next;
			free(u);
		}
		else if(pa->data<pb->data)
		{
			u=pa;
			pa=pa->next;
			free(u);
		}
		else
		{
			u=pb;
			pb=pb->next;
			free(u);
		}
	}
	while(pa)
	{
		u=pa;
		pa=pa->next;
		free(u);
	}
	while(pb)
	{
		u=pb;
		pb=pb->next;
		free(u);
	}
	pc->next=NULL;
	free(lb);
	return la;
}

//两个整数序列A=a1,a2,a3...am和B=b1,b2...bn已经存入两个单链表中，设计一个算法，判断序列B是否序列A的连续子序列
bool child(LinkList A, LinkList B)//错误：并非递增序列
{
	LNode *pa=A->next;
	LNode *pb=B->next;
	while(pa->data!=pb->data)
		pa=pa->next;
	while(pa  &&  pb)
	{
		if(pa->data!=pb->data)
			return false;
		pa=pa->next;
		pb=pb->next;
	}
	return true;
}
//算法思想：操作从两个链表的第一结点开始，若对应数据相等，则后移指针；若对应数据不等，则A链表从上次开始比较结点的后继
//结点开始，B链表仍从第一个结点开始比较，直到B链表到表尾表示匹配成功。A链表到尾而B链表未到尾表示失败。
//操作中应记住A链表每次的开始结点，以便下趟匹配时好从其后继结点开始
int pattern(LinkList A, LinkList B)
{
	LNode *p=A;
	LNode *pre=p;
	LNode *q=B;
	while(p  &&  q)
	{
		if(p->data==q->data)
		{
			p=p->next;
			q=q->next;
		}
		else
		{
			pre=pre->next;
			p=pre;
			q=B;
		}
	}
	if(q==NULL)
		return 1;
	else
		return 0;
}

typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode * prior;
	struct LNode * next;
}LNode, *LinkList;

//设计一个算法用于判断带头结点的循环双链表是否对称
//算法思想：让p从左向右扫描，q从右向左扫描，直到它们指向同一结点（p==q,当循环双链表中结点个数个数为奇数时）
//或相邻（p->next==q或q->prior==p,当循环双链表中结点个数为偶数时）为止。若它们所指结点值相同，则继续进行下去，
//否则返回0.若比较全部相等，则返回1.
int Symmetry(DLinkList L)
{
	DNode *p=L->next, *q=L->prior;
	while(p!=q  &&  q->next!=p)
	{
		if(p->data==q->data)
		{
			p=p->next;
			q=q->next;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

//有两个循环单链表，链表头指针分别为h1和h2，编写一个函数将 链表h2链接到链表h1之后，要求链接后的链表仍保持循环链表形式
//算法思想：先找到链表的尾指针，将第一个链表的尾指针与第二个链表的头指针结点连接起来，再使之成为循环的
LinkList link(LinkList &h1, LinkList &h2)
{
	LNode *p, *q;
	p=h1;
	while(p->next!=h1)
		p=p->next;
	q=h2;
	while(q->next!h2)
		q=q->next;
	p->next=h2;
	q->next=h1;
	return h1;
}


//设有一个带头结点的循环单链表，其结点值均为正整数。设计一个算法，反复找出单链表中结点值最小的结点并输出，
//然后将该结点从中删除，直到单链表空为止，再删除表头结点
void Del_All(LinkList &L)
{
	LNode *p;
	LNode *pre;
	while(L->next!=NULL)
	{
		p=L;
		pre=L;
		while(p)//错误
		{
			if(pre->next->data>p->next->data)
			{
				pre=p;
				p=p->next;
			}
			else
				p=p->next;
		}
		printf("%d ", pre->next->data);
		LNode *q=pre->next;
		pre->next=q->next;
		free(q);
	}
	free(L);
}
//
void Del_All(LinkList &L)
{
	LNode *p, *pre, *minp, *minpre;
	while(L->next!=L)
	{
		p=L->next;
		pre=L;
		minp=p;
		minpre=pre;
		while(p!=L)
		{
			if(p->data<minp->data)
			{
				minp=p;
				minpre=pre;
			}
			pre=p;
			p=p->next;
		}
		printf("%d ", minp->data);
		minpre->next=minp->next;
		free(minp)
	}
	free(L);
}


//设头指针为L的带表头结点的非循环双向链表，其每个结点中除有pred（前驱指针）、data（数据）和next（后继指针）域外，
//还有一个访问频度域freq。在链表被启用前，其值均初始化为零。每当在链表中进行一次Locate(L, x)运算时，
//令元素值为x的结点中freq域的值增1，并使此链表中的结点保持按访问频度非增（递减）的顺序排列，同时最近访问的结点排在频度相同的结点前面，
//以便使频繁访问的结点总是靠近表头。试编写符合上述要求的Locate(L, x)运算的算法，该算法为函数过程，返回找到结点的地址，类型为指针型。
LNode * Locate(LinkList &L, Elemtype x)
{
	LNode *p=L->next;
	while(p  &&  p->data!=x)
			p=p->next;
	
	if(p==NULL)
		return NULL;
	p->freq++;

	LNode *pre=p->prior;
	while(pre!=L  &&  pre->freq<=p->freq)
			pre=pre->prior;

	LNode *l=p->prior;
	LNode *r=p->next;
	l->next=r;
	r->prior=l;

	p->next=pre->next;
	pre->next->prior=p;
	pre->next=p;
	p->prior=pre; 
	return p;
}
//算法思想：首先在双向链表中查找数据值为x的结点，查到后，将结点从链表上摘下，然后再顺着结点的前驱链查找结点的插入位置。
//（频度递减，且排在同频度的第一个，即向前找到第一个比它频度大的结点，插入位置为该结点之后），并插入到该位置。
DLinkList Locate(DLinkList &L, ElemType x)
{
	DNode *p=L->next, *q;
	while(p  &&  p->data!=x)
		p=p->next;
	if(!p)
	{
		printf("不存在值为x的结点\n");
		exit(0);
	}
	else
	{
		p->freq++;
		p->next->pred=p->pred;
		p->pred->next=p->next;

		q=p->pred;
		while(q!=L  &&  q->freq<=p->freq)
			q=q->pred;
		p->next=q->next;
		q->next->pred=p;
		p->pred=q;
		q->next=p;
	}
	return p;
}


//已知一个带表头结点的单链表，结点结构为data、link。
//假设该链表只给出了头指针list。在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的接点，
//k为正整数。若查找成功，算法输出该节点的data域的值，并返回1；否则，只返回0.
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *link;
}LNode, *LinkList;

int search_k(LinkList list, int k)
{
	LNode *p=list->link, *q=list->link;
	int count=0;
	while(p!=NULL)
	{
		if(count<k)
			count++;
		else
			q=q->link;
		p=p->link;
	}
	if(count<k)
		return 0;
	else
		printf("%d", q->data);
	return 1;
}

//假设采用带头结点的单链表保存单词，当两个单词有相同的后缀时，则可共享相同的后缀存储空间，例如，loading和being；
//设str1和str2分别指向两个单词所在单链表的头结点，链表结点结构为data、next，
//请设计一个时间上尽可能高效的算法，找出由str1和str2所指向两个链表共同后缀的起始位置。
typedef struct Node{
	char data;
	struct Node *next;
}SNode;

int listlen(SNode *head)
{
	int len=0;
	while(head->next!=NULL)
	{
		len++;
		head=head->next;
	}
	return len;
}

SNode * find_addr(SNode *str1, SNode *str2)
{
	int m, n;
	SNode *p, *q;
	m=listlen(str1);
	n=listlen(str2);
	for(p=str1; m>n; m--)
		p=p->next;
	for(q=str2; m<n; n--)
		q=q->next;

	while(p->next!=NULL  &&  p->next!=q->next)
	{
		p=p->next;
		q=q->next;
	}
	return p->next;
}
