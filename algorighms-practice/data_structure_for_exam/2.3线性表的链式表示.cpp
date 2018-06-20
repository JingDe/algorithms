//�������н�����͵�����
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

//����ͷ�巨����������
//�ӱ�β����ͷ������������L��ÿ�ξ���ͷ���֮�����Ԫ��
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

//����β�巨����������
//�ӱ�ͷ����β������������L��ÿ�ξ��ڱ�β����Ԫ��
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

//����Ų��ҽڵ�ֵ
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
	return p;//���ص�i�� ����ָ�룬���i���ڱ���p=NULL
}

//��ֵ���ұ���
LNode *LocationElem(LinkList L, ElemType e)
{
	LNode *p=L->next;
	while(p!=NULL  &&  p->data!=e)
		p=p->next;
	return p;
}

//���������
//��*s���뵽*p֮��
p=GetElem(L, i-1);//���Ҳ���λ�õ�ǰ�����
s->next=p->next;
p->next=s;

//��*s�����뵽*p֮ǰ����Ҫ����Ƭ��
s->next=p->next;//�޸�ָ���򣬲��ܵߵ�
p->next=s;
temp=p->data;//���������򲿷�
p->data=s->data;
s->data=temp;

//ɾ��������
p=GetElem(L, i-1);
q=p->next;
p->next=q->next;
free(q);

//ɾ�����*p�Ĳ���������ɾ��*p�ĺ�̽�������ʵ��
q=p->next;
p->data=p->next->data;
p->next=q->next;
free(q);

//˫����
typedef struct DNode{
	ElemType data;
	struct DNode *prior, *next;
}DNode, *DLinklist;

//˫����Ĳ������

//˫�����ɾ������

//ѭ������
//ѭ��������
//ѭ��˫����

//��̬����
//��̬����ṹ���͵�����
typedef MaxSize 50;
typedef struct{
	ElemType data;
	int next;
}SLinkList[MaxSize];


//���һ���ݹ��㷨��ɾ������ͷ���ĵ�����L������ֵΪx�Ľڵ�
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

//��ͷ���ĵ�����L�У�ɾ������ֵΪx�Ľ�㣬���ͷ���ռ䣬����ֵΪx�Ľ�㲻Ψһ����д�㷨ʵ����������
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
//�ⷨһ����p��ͷ��βɨ�赥����preָ��*p����ǰ������p��ָ����ֵΪx����ɾ��������p������һ����㣬
//������pre��pָ��ͬ������һ�����
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
//�ⷨ��������β�巨������������pָ��ɨ��L�����н�㣬����ֵ��Ϊxʱ�������ӵ�L֮�󣬷������ͷ�
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

//��LΪ��ͷ���ĵ�������д�㷨ʵ�ִ�β��ͷ�������ÿ���ڵ��ֵ
void print(LinkList L)
{
	if(L->next==NULL)
		return;
	LNode *p=L->next;
	L->next=p->next;//��
	print(L);
	cout<<p->data<<endl;
	free(p);//��
}
//
void R_Print(LinkList L)
{
	if(L->next!=NULL)
		R_Print(L->next);
	print(L->data);//��
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

//�Ա�д�ڴ�ͷ���ĵ�����L��ɾ��һ����Сֵ���ĸ�Ч�㷨��������Сֵ�����Ψһ�ģ�
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
		else//��
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

//�Ա�д�㷨����ͷ���ĵ�����͵����ã������ռ临�Ӷ�ΪO��1��
//�ⷨһ����ͷ���ժ�£�Ȼ��ӵ�һ��㿪ʼ������ǰ���뵽ͷ���ĺ��棨ͷ�巨������������
//ֱ�����һ�����Ϊֹ
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
//�ⷨ����
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


//��һ����ͷ���ĵ�����L�����һ���㷨ʹ��Ԫ�ص�������
//�㷨˼�룺����ֱ�Ӳ��������㷨��˼�룬�ȹ���ֻ��һ�����ݽڵ����������Ȼ������ɨ�赥������ʣ�µĽڵ�
//*p��ֱ��p==NULLΪֹ�������������ͨ���Ƚϲ��Ҳ���*p��ǰ�����*pre��Ȼ��*p���뵽*pre֮��
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

//����һ������ͷ���ĵ�����������Ԫ�ؽ�������ֵ�����Ա�дһ��������ɾ���������н�����������ֵ֮���Ԫ��
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

//����������������д�㷨�ҳ���������Ĺ������
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


//����һ����ͷ���ĵ�������headΪͷָ�룬���ĽṹΪ��data��next����dataΪ����Ԫ�أ�nextΪָ�룬
//��д���㷨����������������������и���������Ԫ�أ����ͷŽ����ռ�Ĵ洢�ռ䣨Ҫ�󣺲�����ʹ��������Ϊ�����ռ䣩
//�㷨˼�룺��������б�������ÿ�˱����в��ҳ������������СֵԪ�أ�������ͷŽ����ռ�ռ䣻
//�ٲ��Ҵ�СֵԪ�أ�������ͷſռ䣬�����ȥ��ֱ������Ϊ�գ�����ͷ�ͷ�����ռ�洢�ռ䣬ʱ�临�Ӷ�ΪO(n*n)
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


//��һ����ͷ���ĵ�����A�ֽ�Ϊ������ͷ���ĵ�����A��B��ʹ��A���к���ԭ�������Ϊ������Ԫ�أ�
//��B���к���ԭ�������Ϊż����Ԫ�أ��ұ��������˳�򲻱䡣
//����һ��������ű�������ֵΪ0����ÿ����һ���������Զ���1��Ȼ�������ŵ���ż�Խ������뵽A���B���С�
//�ظ����ϲ���ֱ����β��
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
//����β�巨����ԭ������е�˳��
//�ⷨ��������������ű�����whileѭ���еĴ���ĳɽ������뵽��A�к� ����һ�����뵽��B�У�
//����while�е�һ����Ľ����������Ž�㣬�ڶ�����Ľ�����ż���Ž��
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

//��C={a1, b1, a2, b2, ..., an, bn}Ϊ���Ա����ô�ͷ����hc�������ţ����һ���͵��㷨��������Ϊ�������Ա�ʹ��A={a1, a2, ..., an}, B={bn,..., b2,b1}
//���������˼·��������ű��������ߵĲ������ڶ�B��Ľ���������β�巨�����ǲ���ͷ�巨
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


//��һ��������������Ա��У�����ֵ�ظ���Ԫ�ش��ڡ����洢��ʽΪ������
//����㷨ȥ����ֵ��ͬ��Ԫ�أ�ʹ���в������ظ���Ԫ��
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
//�㷨˼�룺�����������������ֵͬ��Ľ�㶼�����ڵġ���pɨ�����������L��
//��*p����ֵ��������̽���ֵ����ɾ�����ߣ�����p������һ�����
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


//������������Ԫ��ֵ�����������е����Ա����Ե�������ʽ�洢�����д�㷨��������������鲢Ϊһ����Ԫ��ֵ�ݼ��������еĵ�����
//��Ҫ������ԭ������������Ľ���Ź鲢��ĵ�����
//ͷ�巨
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
//�㷨˼�룺���������Ѿ���Ԫ��ֵ�����������򣬽���ϲ�ʱ�����ӵ�һ���������бȽϣ���С�Ľ�����������У�ͬʱ���ƹ���ָ�롣
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

//��A��B��������������ͷ��㣩������Ԫ�ص����������һ���㷨��A��B�й���Ԫ�ز���������C��Ҫ���ƻ�A��B�Ľ�㡣
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
//�㷨˼�룺��A��B�����򣬿ɴӵ�һ��Ԫ�������αȽ�A��B�����Ԫ�أ���Ԫ��ֵ���ȣ���ֵС��ָ�������ƣ�
//��Ԫ��ֵ��ȣ��򴴽�һ��ֵ����������Ԫ��ֵ���µĽ�㣬ʹ��β�巨���뵽�µ������У�
//������ԭ��ָ�����һλ��ֱ������һ�������������β
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

//��֪��������A��B�ֱ��ʾ�������ϣ���Ԫ�ص������С����ƺ�������A��B�Ľ������������A������
//�㷨˼�룺���ù鲢��˼�룬������������ָ��pa��pb��������������й鲢ɨ�裬ֻ��ͬʱ�������������е�Ԫ�ز����ӵ��������
//�ҽ�����һ���������Ľ��ȫ���ͷš���һ�����������Ϻ��ͷ���һ������ʣ�µ�ȫ����㡣
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

//������������A=a1,a2,a3...am��B=b1,b2...bn�Ѿ����������������У����һ���㷨���ж�����B�Ƿ�����A������������
bool child(LinkList A, LinkList B)//���󣺲��ǵ�������
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
//�㷨˼�룺��������������ĵ�һ��㿪ʼ������Ӧ������ȣ������ָ�룻����Ӧ���ݲ��ȣ���A������ϴο�ʼ�ȽϽ��ĺ��
//��㿪ʼ��B�����Դӵ�һ����㿪ʼ�Ƚϣ�ֱ��B������β��ʾƥ��ɹ���A����β��B����δ��β��ʾʧ�ܡ�
//������Ӧ��סA����ÿ�εĿ�ʼ��㣬�Ա�����ƥ��ʱ�ô����̽�㿪ʼ
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

//���һ���㷨�����жϴ�ͷ����ѭ��˫�����Ƿ�Գ�
//�㷨˼�룺��p��������ɨ�裬q��������ɨ�裬ֱ������ָ��ͬһ��㣨p==q,��ѭ��˫�����н���������Ϊ����ʱ��
//�����ڣ�p->next==q��q->prior==p,��ѭ��˫�����н�����Ϊż��ʱ��Ϊֹ����������ָ���ֵ��ͬ�������������ȥ��
//���򷵻�0.���Ƚ�ȫ����ȣ��򷵻�1.
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

//������ѭ������������ͷָ��ֱ�Ϊh1��h2����дһ�������� ����h2���ӵ�����h1֮��Ҫ�����Ӻ�������Ա���ѭ��������ʽ
//�㷨˼�룺���ҵ������βָ�룬����һ�������βָ����ڶ��������ͷָ����������������ʹ֮��Ϊѭ����
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


//����һ����ͷ����ѭ������������ֵ��Ϊ�����������һ���㷨�������ҳ��������н��ֵ��С�Ľ�㲢�����
//Ȼ�󽫸ý�����ɾ����ֱ���������Ϊֹ����ɾ����ͷ���
void Del_All(LinkList &L)
{
	LNode *p;
	LNode *pre;
	while(L->next!=NULL)
	{
		p=L;
		pre=L;
		while(p)//����
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


//��ͷָ��ΪL�Ĵ���ͷ���ķ�ѭ��˫��������ÿ������г���pred��ǰ��ָ�룩��data�����ݣ���next�����ָ�룩���⣬
//����һ������Ƶ����freq������������ǰ����ֵ����ʼ��Ϊ�㡣ÿ���������н���һ��Locate(L, x)����ʱ��
//��Ԫ��ֵΪx�Ľ����freq���ֵ��1����ʹ�������еĽ�㱣�ְ�����Ƶ�ȷ������ݼ�����˳�����У�ͬʱ������ʵĽ������Ƶ����ͬ�Ľ��ǰ�棬
//�Ա�ʹƵ�����ʵĽ�����ǿ�����ͷ���Ա�д��������Ҫ���Locate(L, x)������㷨�����㷨Ϊ�������̣������ҵ����ĵ�ַ������Ϊָ���͡�
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
//�㷨˼�룺������˫�������в�������ֵΪx�Ľ�㣬�鵽�󣬽�����������ժ�£�Ȼ����˳�Ž���ǰ�������ҽ��Ĳ���λ�á�
//��Ƶ�ȵݼ���������ͬƵ�ȵĵ�һ��������ǰ�ҵ���һ������Ƶ�ȴ�Ľ�㣬����λ��Ϊ�ý��֮�󣩣������뵽��λ�á�
DLinkList Locate(DLinkList &L, ElemType x)
{
	DNode *p=L->next, *q;
	while(p  &&  p->data!=x)
		p=p->next;
	if(!p)
	{
		printf("������ֵΪx�Ľ��\n");
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


//��֪һ������ͷ���ĵ��������ṹΪdata��link��
//���������ֻ������ͷָ��list���ڲ��ı������ǰ���£������һ�������ܸ�Ч���㷨�����������е�����k��λ���ϵĽӵ㣬
//kΪ�������������ҳɹ����㷨����ýڵ��data���ֵ��������1������ֻ����0.
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

//������ô�ͷ���ĵ������浥�ʣ���������������ͬ�ĺ�׺ʱ����ɹ�����ͬ�ĺ�׺�洢�ռ䣬���磬loading��being��
//��str1��str2�ֱ�ָ�������������ڵ������ͷ��㣬������ṹΪdata��next��
//�����һ��ʱ���Ͼ����ܸ�Ч���㷨���ҳ���str1��str2��ָ����������ͬ��׺����ʼλ�á�
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
