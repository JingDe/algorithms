//���е�˳��洢����
#define MaxSize 50
typedef struct{
	ElemType data[MaxSize];
	int front, rear;
}SqQueue;

//ѭ�����еĲ���
//��ʼ��
void InitQueue(SqQueue &Q)
{
	Q.rear=Q.front=0;
}
//�жӿ�
bool isEmpty(SqQueue Q)
{
	if(Q.rear==Q.front) return true;
	else return false;
}
//���
bool EnQueue(SqQueue &Q, ElemType x)
{
	if((Q.rear+1)%MaxSize==Q.front) return false;
	Q.data[Q.rear]=x;
	Q.rear=(Q.rear+1)%MaxSize;
	return true;
}
//����
bool DeQueue(SqQueue &Q, ElemType &x)
{
	if(Q.rear==Q.front) return true;
	x=Q.data[Q.front];
	Q.front=(Q.front+1)%MaxSize;
	return true;
}

//���е���ʽ�洢����
typedef struct{
	ElemType data;
	struct LinkNode *next;
}LinkNode;
typedef struct{
	LinkNode *front, *rear;
}LinkQueue;

//��ʽ���еĻ�������
//��ʼ��
void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=(LinkNode*)malloc(sizeof(LinkNode));
	Q.front->next=NULL;
}
//�жӿ�
bool isEmpty(LinkNode Q)
{
	if(Q.front==Q.rear) return true;
	else return false;
}
//���
void EnQueue(LinkQueue &Q, ElemType x)
{
	s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data==x;
	s->next=NULL;
	Q.rear->next=s;
	Q.rear=s;
}
//����
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

//���ϣ��ѭ�������е�Ԫ�ض��ܵõ����ã���������һ����־��tag��
//����tag��ֵΪ0��1�����ֶ�ͷָ��front�Ͷ�βָ��rear��ͬʱ�Ķ���״̬�ǿջ�������
//�Ա�д��˽ṹ��Ӧ�ĳ�������㷨
//����������tag���ݳ�Ա��
// �ӿգ�Q.tag==0   &&   Q.front==Q.rear
// ������Q.tag==1     &&    Q.front==Q.rear
//���Ӳ�����Q.data[Q.rear]=x;   Q.rear=(Q.rear+1)%MaxSize;  Q.tag=1;
//���Ӳ�����x=Q.data[Q.rear];   Q.front=(Q.front+1)%MaxSize;  Q.tag=0;
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

//Q��һ�����У�S��һ����ջ��ʵ�ֽ������е�Ԫ�����õ��㷨
//�������е�Ԫ������س����У���ջ��ȫ����ջ�������
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

//��������ջS1��S2��ģ��һ�����У���֪ջ��4�����㶨�����£�
//Push(S, x);
//Pop(S, x);
//StackEmpty(S);
//StackOverflow(S);
//��ô�������ջ��������ʵ�ָö��е�3������
//EnQueue;
//DeQueue;
//QueueEmpty;
//�㷨˼�룺����Ҫ������в���һ��Ԫ��ʱ����S1������������Ԫ�أ���S1ִ����ջ������
//����Ҫ����ʱ�����S2ִ�г�վ���������뽫S1�е�����Ԫ��ȫ����ջ����ջ��S2�У�
//����S2��ִ�г�վ����������ʵ�ֳ��Բ���������ִ�д˲���ǰ�����ж�S2�Ƿ�Ϊ�գ�����ᵼ��˳�����
//��S1��S2��Ϊ��ʱ����Ϊ��
//�ܽ�
//1)��S2�ĳ�վ�����������ӣ���S2Ϊ�գ����Ƚ�S1�е�����Ԫ������S2
//2)��S1����ջ����������ӣ���S1���������ȱ�֤S1Ϊ�գ����ܽ�S1�е�Ԫ��ȫ������S2��
bool EnQueue(Stack &S1, Stack &S2, ElemType e)
{
	if(!StackOverflow(S1))
	{
		Push(S1, e);
		return 1;
	}
	if(StackOverflow(S1)  &&  !StackEmpty(S2))
	{
		printf("������");
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
		printf("���п�");
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


//����һ���������ʽ�а���Բ���š������źͻ�����3�����͵����ţ�
//��дһ���㷨���б���ʽ�е������Ƿ�ƥ�ԣ����ַ�\0��Ϊ�������ʽ�Ľ�����
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
		printf("���Ų�ƥ��");
		return false;
	}
	else
	{
		printf("����ƥ��");
		return true;
	}
}

//�������г������(����������Ϊ������ʻ��,�𳵵���վ��һ�����ڵ��ȵ�ջ��),
//�𳵵���վ����ڴ���n��Ӳ�����������ᣨ�ֱ���H��S��ʾ���ȴ����ȡ�
//�Ա�д�㷨���������n�ڳ�����е��ȵĲ���������ջ�ͳ�ջ���������У���ʹ���е��������ᶼ��������Ӳ������֮ǰ��
//�㷨˼�룺���г�������ǰ������һ��飬��ΪӲ������ջ���ȴ������ȡ�
void Train_Arrange(char *train)//���ַ�train��ʾ�𳵣�H��ʾӲ����S��ʾ����
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

//����һ��ջʵ�����µݹ麯���ķǵݹ����
//�㷨˼�룺����һ��ջ���ڱ���n�Ͷ�Ӧ��Pn(x)ֵ��ջ������Ԫ�ص�Pn(x)�����й�ϵ��
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

//ĳ�����ֶɿ�,�����ɴ�ÿ������10��������.����������Ϊ�ͳ���ͻ���,�϶ɴ������¹涨:ͬ�೵�ȵ����ϴ�;
//�ͳ����ڻ����϶ɴ�,��ÿ��4���ͳ�,���������һ������;���ȴ��ͳ�����4��,���Ի�������;
//���޻����ȴ�,����ͳ����ϴ�.�����һ���㷨ģ��ɿڹ���.
//�㷨˼�룺��������Q������±�Ϊ10��ǡ����ÿ���ضɵ������������ͳ��Ķ���ΪQ1�������Ķ���ΪQ2.
//��Q1���㣬��ûȡ4��Ԫ�غ���ȡһ��Q2Ԫ�أ�ֱ��Q�ĳ���Ϊ10.��Q1�����㣬����Q2���롣
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