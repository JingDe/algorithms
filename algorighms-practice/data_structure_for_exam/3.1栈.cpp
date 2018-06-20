//ջ��˳���ʾ
#define  MaxSize 50
typedef struct{
	ElemType data[MaxSize];
	int top;					//ջ��ָ��
}SqStack;

//˳��ջ�Ļ�������
//��ʼ��
void InitStack(SqStack &S)
{
	S.top=-1;
}
//��ջ��
bool StackEmpty(SqStack S)
{
	if(S.top==-1)
		return true;
	else
		return false;
}
//��ջ
bool Push(SqStack &S, ElemType x)
{
	if(S.top==MaxSize-1)
		return false;
	S.data[++S.top]=x;
	return true;
}
//��ջ
bool Pop(SqStack &S, ElemType &x)
{
	if(S.top==-1)
		return false;
	x=S.data[S.top--];
	return true;
}
//��ջ��Ԫ��
bool GetTop(SqStack S, ElemType &x)
{
	if(S.top==-1)
		return false;
	x=S.data[S.top];
	return true;
}

//ջ����ʽ�洢����
typedef struct LinkNode{
	ElemType data;
	struct LinkNode *next;
}*LiStack;


//������I��O�ֱ��ʾ��ջ�ͳ�ջ������ջ�ĳ�̬����̬��Ϊ�գ���ջ�ͳ�ջ�Ĳ������пɱ�ʾΪ����I��O��ɵ����У�
//���Բ��������г�Ϊ�Ϸ����У������Ϊ�Ƿ����С�
//д��һ���㷨���ж������Ĳ��������Ƿ�Ϸ������Ϸ�������true�����򷵻�false
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
//�㷨˼�룺������һɨ����ջ��ջ���У�ÿɨ������һλ�þ������ջ�����Ƿ�С����ջ��������������Ϊ�Ƿ����С�
//ɨ����������ж���ջ�ͳ�ջ�����Ƿ���ȣ���������򲻺����⣬Ϊ�Ƿ����С�
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
				printf("���зǷ�\n"); exit(0);
			}
		}
	}

	if(j!=k)
	{
		printf("���зǷ�\n");
		return false;
	}
	else
	{
		printf("���кϷ�\n");
		return true;
	}
}
//��⣺ת��Ϊһ��+1��-1��ɵ����У���������ǰ׺�����е��ۼӺͲ�С��0��ÿ�γ�ջ����ջ�������жϣ�����Ϸ�������Ƿ�


//�赥����ı�ͷָ��Ϊh,���ṹ��data��next�����򹹳ɣ�����data��Ϊ�ַ��͡�
//������㷨�жϸ������ǰn���ַ��Ƿ����ĶԳơ�����xyx��xyyx�������ĶԳơ�
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
//�㷨˼�룺ʹ��ջ���ж������е������Ƿ����ĶԳơ��������ǰһ��Ԫ��һ�ν�ջ���ڴ�������ĺ�һ��Ԫ��ʱ��
//�����ʵ������һ��Ԫ�غ󣬾ʹ�ջ�е���һ��Ԫ�أ�����Ԫ�رȽϣ�����ȣ�����������һ��Ԫ����ջ���ٵ�����Ԫ�رȽϣ�
//ֱ������β����ʱ��ջ�ǿ�ջ����ó��������ĶԳƵĽ��ۣ����򣬵������е�һ��Ԫ����ջ�е���Ԫ�ز���ʱ������Ϊ�ǶԳơ�
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
	if(i==-1)//ջΪ��ջ
		return 1;
	else
		return 0;
}

//��������ջs1, s2������˳��ջ��ʽ�����ҹ���һ���洢��[ 0, ..., maxsize-1 ], Ϊ�˾������ÿռ䣬��������Ŀ��ܣ�
//�ɲ���ջ������ӭ�������Ĵ洢��ʽ�������s1, s2�й���ջ�ͳ�ջ�Ĳ����㷨��
#define maxsize
#define elemtp int
typedef struct{
	elemtp stack[maxsize];
	int top[2];
}stk;
stk s;

//��ջ����
int push(int i, int x)//iΪջ�ţ�x����ջԪ��
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
//��ջ����
elemtp pop(int i)//i����ջ��
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