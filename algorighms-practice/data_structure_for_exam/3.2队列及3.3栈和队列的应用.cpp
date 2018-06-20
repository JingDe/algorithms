//队列的顺序存储类型
#define MaxSize 50
typedef struct{
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;

//循环队列的操作
//初始化
void InitQueue(SqQueue &Q)
{
	Q.rear=Q.front=0;
}
//判队空
bool isEmpty(SqQueue Q)
{
	if(Q.rear==Q.front) return true;
	else return false;
}
//入队
bool EnQueue(SqQueue &Q, ElemType x)
{
	if((Q.rear+1)%MaxSize==Q.front) return false;
	Q.data[Q.rear]=x;
	Q.rear=(Q.rear+1)%MaxSize;
	return true;
}
//出队
bool DeQueue(SqQueue &Q, ElemType &x)
{
	if(Q.rear==Q.front) return true;
	x=Q.data[Q.front];
	Q.front=(Q.front+1)%MaxSize;
	return true;
}

//队列的链式存储类型
typedef struct{
	ElemType data;
	struct LinkNode *next;
}LinkNode;
typedef struct{
	LinkNode *front, *rear;
}LinkQueue;

//链式队列的基本操作
//初始化
void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(LinkNode*)malloc(sizeof(LinkNode));
	Q.front->next=NULL;
}
//判队空
bool isEmpty(LinkNode Q)
{
	if(Q.front==Q.rear) return true;
	else return false;
}
//入队
void EnQueue(LinkQueue &Q, ElemType x)
{
	s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data==x;
	s->next=NULL;
	Q.rear->next=s;
	Q.rear=s;
}
//出队
bool DeQueue(LinkQueue &Q, ElemType &x)
{
	if(Q.front==Q.rear)  return false;
	p=Q.front->next;
	x=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return true;
}

//如果希望循环队列中的元素都能得到利用，则需设置一个标志域tag，
//并以tag的值为0或1来区分队头指针front和队尾指针rear相同时的队列状态是空还是满。
//试编写与此结构相应的出队入队算法
//类型中增设tag数据成员。
// 队空：Q.tag==0   &&   Q.front==Q.rear
// 队满：Q.tag==1     &&    Q.front==Q.rear
//进队操作：Q.data[Q.rear]=x;   Q.rear=(Q.rear+1)%MaxSize;  Q.tag=1;
//出队操作：x=Q.data[Q.rear];   Q.front=(Q.front+1)%MaxSize;  Q.tag=0;
typedef struct{
	ElemType data[MaxSize];
	int front, rear;
};
bool EnQueue(SqQueue &Q, ElemType x)
{
	if(Q.front==Q.rear  &&  Q.tag==1)  return false;
	Q.data[Q.rear]=x;
	Q.rear=(Q.rear+1)%MaxSize;
	Q.tag=1;
	return true;
}
bool DeQueue(SqQueue &Q, ElemType &x)
{
	if(Q.front==Q.rear  &&  Q.tag==0)  return false;
	x=Q.data[Q.front];
	Q.front=(Q.front+1)%MaxSize;
	Q.tag=0;
	return true;
}

//Q是一个队列，S是一个空栈，实现将队列中的元素逆置的算法
//将队列中的元素逐个地出队列，入栈；全部入栈后，入队列
void reverse(Stack S, Queue &Q)
{
	ElemType x;
	while(!QueueEmpty(Q))
	{
		x=DeQueue(Q);
		Push(S, x);
	}
	while(!StackEmpty(S))
	{
		Pop(S, x);
		EnQueue(Q, x);
	}
}

//利用两个栈S1，S2来模拟一个队列，已知栈的4个运算定义如下：
//Push(S, x);
//Pop(S, x);
//StackEmpty(S);
//StackOverflow(S);
//那么如何利用栈的运算来实现该队列的3个运算
//EnQueue;
//DeQueue;
//QueueEmpty;
//算法思想：当需要向队列中插入一个元素时，用S1来存放已输入的元素，即S1执行入栈操作。
//当需要出队时，则对S2执行出站操作。必须将S1中的所有元素全部出栈并入栈到S2中，
//再在S2中执行出站操作，即可实现出对操作。而在执行此操作前必须判断S2是否为空，否则会导致顺序混乱
//当S1和S2都为空时队列为空
//总结
//1)对S2的出站操作用作出队，若S2为空，则先将S1中的所有元素送入S2
//2)对S1的入栈操作用作入队，若S1满，必须先保证S1为空，才能将S1中的元素全部插入S2中
bool EnQueue(Stack &S1, Stack &S2, ElemType e)
{
	if(!StackOverflow(S1))
	{
		Push(S1, e);
		return 1;
	}
	if(StackOverflow(S1)  &&  !StackEmpty(S2))
	{
		printf("队列满");
		return true;
	}
	if(StackOverflow(S1)  &&  StackEmpty(S2))
	{
		ElemType x;
		while(!StackEmpty(S1))
		{
			Pop(S1, x);
			Push(S2, x);
		}
	}
	Push(S1, e);
	return true;
}
bool DeQueue(Stack &S1, Stack &S2, ElemType &x)
{
	if(!StackEmpty(S2))
		Pop(S2, x);
	else if(StackEmpty(S1))
	{
		printf("队列空");
		return false;
	}
	else
	{
		while(!StackEmpty(S1))
		{
			Pop(S1, x);
			Push(S2, x);
		}
		Pop(S2, x);
	}
	return true;
}
bool QueueEmpty(Stack S1, Stack S2)
{
	if(StackEmpty(S1)  &&  StackEmpty(S2))
		return true;
	else
		return false;
}


//假设一个算术表达式中包含圆括号、方括号和花括号3中类型的括号，
//编写一个算法来判别表达式中的括号是否匹对，以字符\0作为算术表达式的结束符
bool BracketsCheck(char *str)
{
	InitStack(S);
	i=0;
	while(str[i]!='\0')
	{
		switch(str[i])
		{
		case '(':Push(S, '(');break;
		case '[':Push(S, '[');break;
		case '{':Push(S, '{');break;
		case ')':Pop(S, e);
			if(e!='(') return false;
			break;
		case ']':Pop(S, e);
			if(e!='[')  return false;
			break;
		case '}':Pop(S, e);
			if(e!='{') return false;
			break;
		default:break;
		}
		i++;
	}
	if(!IsEmpty(S))
	{
		printf("括号不匹配");
		return false;
	}
	else
	{
		printf("括号匹配");
		return true;
	}
}

//铁道进行车厢调度(两侧铁道均为单向行驶道,火车调度站有一个用于调度的栈道),
//火车调度站的入口处有n节硬座和软座车厢（分别以H和S表示）等待调度。
//试编写算法，输出对这n节车厢进行调度的操作（即入栈和出栈操作）序列，以使所有的软座车厢都被调整到硬座车厢之前。
//算法思想：所有车厢依次前进并逐一检查，若为硬座则入栈，等待最后调度。
void Train_Arrange(char *train)//用字符train表示火车，H表示硬座，S表示软座
{
	char *p=train, *q=train, c;
	stack s;
	while(*p)
	{
		if(*p=='H')
			Push(s, *p);
		else
			*(q++)=*p;
		p++;
	}
	while(!StackEmpty(s))
	{
		Pop(s, c);
		*(q++)=c;
	}
}

//利用一个栈实现以下递归函数的非递归计算
//算法思想：设置一个栈用于保存n和对应的Pn(x)值，栈中相邻元素的Pn(x)有题中关系。
//
double p(int n, double x)
{
	struct stack{
		int no;
		double val;
	}st[MaxSize];

	int top=-1, i;
	double fv1=1, fv2=2*x;
	for(i=n; i>=2; i--)
	{
		top++;
		st[top].no=i;
	}
	while(top>=0)
	{
		st[top].val=2*x*fv2-2*(st[top].no-1)*fv1;
		fv1=fv2;
		fv2=st[top].val;
		top--;
	}
	return fv2;
}

//某汽车轮渡口,过江渡船每次能载10辆车过江.过江车辆分为客车类和火车类,上渡船有如下规定:同类车先到先上船;
//客车先于货车上渡船,且每上4辆客车,才允许放上一辆货车;若等待客车不足4辆,则以货车代替;
//若无货车等待,允许客车都上船.试设计一个算法模拟渡口管理.
//算法思想：假设数组Q的最大下标为10，恰好是每次载渡的最大量。假设客车的队列为Q1，货车的队列为Q2.
//若Q1充足，则没取4个元素后再取一个Q2元素，直到Q的长度为10.若Q1不充足，则用Q2补齐。
Queue q;
Queue q1;
Queue q2;
void manager()
{
	int i=0, j=0;
	while(j<10)
	{
		if(!QueueEmpty(q1)  &&  i<4)
		{
			DeQueue(q1, x);
			EnQueue(q, x);
			i++;
			j++;
		}
		else if(i==4  &&  !Empty(q2))
		{
			DeQueue(q2, x);
			EnQueue(q1, x);
			j++;
			i=0;
		}
		else
		{
			while(j<10  &&  i<4  &&  !QueueEmpty(q2))
			{
				DeQueue(q2, x);
				EnQueue(q, x);
				i++;
				j++;
			}
			i=0;
		}

		if(QueueEmpty(q1)  &&  QueueEmpty(q2))
			j=11;
	}
}