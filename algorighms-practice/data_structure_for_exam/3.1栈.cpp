//栈的顺序表示
#define  MaxSize 50
typedef struct{
	ElemType data[MaxSize];
	int top;					//栈顶指针
}SqStack;

//顺序栈的基本运算
//初始化
void InitStack(SqStack &S)
{
	S.top=-1;
}
//判栈空
bool StackEmpty(SqStack S)
{
	if(S.top==-1)
		return true;
	else
		return false;
}
//进栈
bool Push(SqStack &S, ElemType x)
{
	if(S.top==MaxSize-1)
		return false;
	S.data[++S.top]=x;
	return true;
}
//出栈
bool Pop(SqStack &S, ElemType &x)
{
	if(S.top==-1)
		return false;
	x=S.data[S.top--];
	return true;
}
//读栈顶元素
bool GetTop(SqStack S, ElemType &x)
{
	if(S.top==-1)
		return false;
	x=S.data[S.top];
	return true;
}

//栈的链式存储类型
typedef struct LinkNode{
	ElemType data;
	struct LinkNode *next;
}*LiStack;


//假设以I和O分别表示入栈和出栈操作。栈的初态和终态均为空，入栈和出栈的操作序列可表示为仅由I和O组成的序列，
//可以操作的序列称为合法序列，否则称为非法序列。
//写出一个算法，判定所给的操作序列是否合法。若合法，返回true，否则返回false
bool validata(char seq[], int n)
{
	LiStack<char> s;
	char c;
	for(int i=0; i<n; i++)
	{
		if(seq[i]=='I')
			push(s, 'I');
		if(seq[i]=='O')
		{
			bool res=pop(s, c);
			if(res==false)
				return false;
		}
	}
	if(StackEmpty(s))
		return true;
	else
		return false;
}
//算法思想：依次逐一扫描入栈出栈序列，每扫描至任一位置均需检查出栈次数是否小于入栈次数，若大于则为非法序列。
//扫描结束后，再判断入栈和出栈次数是否相等，若不相等则不合题意，为非法序列。
int Judge(char A[])
{
	i=0;
	j=k=0;
	while(A[i]!='\0')
	{
		switch(A[i])
		{
		case 'I':j++; break;
		case 'O':k++;
			if(k>j)
			{
				printf("序列非法\n"); exit(0);
			}
		}
	}

	if(j!=k)
	{
		printf("序列非法\n");
		return false;
	}
	else
	{
		printf("序列合法\n");
		return true;
	}
}
//另解：转化为一组+1，-1组成的序列，它的任意前缀子序列的累加和不小于0（每次出栈或入栈操作后判断），则合法，否则非法


//设单链表的表头指针为h,结点结构由data和next两个域构成，其中data域为字符型。
//试设计算法判断该链表的前n个字符是否中心对称。例如xyx，xyyx都是中心对称。
bool symmetry(LinkList h, int n)
{
	LiStack<char> s;
	LNode *p=h->next;
	char c;

	int count;
	if(n%2==0)
		count=n/2;
	else
		count=(n-1)/2;

	for(int i=0; i<count; i++)
	{
		push(s, p->data);
		p=p->next;
	}

	if(n%2==1)
		p=p->next;

	for(i=0; i<count; i++)
	{
		pop(s, c);
		if(c==p->data)
			p=p->next;
		else
			return false;
	}
	return true;
}
//算法思想：使用栈来判断链表中的数据是否中心对称。将链表的前一半元素一次进栈。在处理链表的后一半元素时，
//当访问到链表的一个元素后，就从栈中弹出一个元素，两个元素比较，若相等，则将链表中下一个元素与栈中再弹出的元素比较，
//直至链表到尾。这时若栈是空栈，则得出链表中心对称的结论；否则，当链表中的一个元素与栈中弹出元素不等时，结论为非对称。
int dc(LinkList L, int n)
{
	char s[n/2];
	int i=1;
	p=L->next;
	for(i=0; i<n/2; i++)
	{
		s[i]=p->data;
		p=p->next;
	}
	i--;

	if(n%2==1)
		p=p->next;
	while(p  &&  s[i]==p->data)
	{
		i--;
		p=p->next;
	}
	if(i==-1)//栈为空栈
		return 1;
	else
		return 0;
}

//设有两个栈s1, s2都采用顺序栈方式，并且共享一个存储区[ 0, ..., maxsize-1 ], 为了尽量利用空间，减少溢出的可能，
//可采用栈顶相向、迎面增长的存储方式。试设计s1, s2有关入栈和出栈的操作算法。
#define maxsize
#define elemtp int
typedef struct{
	elemtp stack[maxsize];
	int top[2];
}stk;
stk s;

//入栈操作
int push(int i, int x)//i为栈号，x是入栈元素
{
	if(i<0  ||  i>1)
		exit(0);
	if(s.top[1]-s.top[0]==1)
		return 0;
	switch(i)
	{
	case 0: s.stack[++s.top[0]]=x; return 1; break;
	case 1: s.stack[--s.top[1]]=x; return 1;
	}
}
//退栈操作
elemtp pop(int i)//i代表栈号
{
	if(i<0  ||  i>1)
		exit(0);
	switch(i)
	{
	case 0:
		if(s.top[0]==-1)
			return -1;
		else
			return s.stack[s.top[0]--];
	case 1:
		if(s.top[1]==maxsize)
			return -1;
		else
			return s.stack[s.top[1]++];
	}
}