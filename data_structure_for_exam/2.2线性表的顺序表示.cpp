//˳�����:��̬����
#define MaxSize 50
typedef struct{
	ElemType data[MaxSize];
	int length;
}SqList;

//˳����壺��̬����
#define InitSize 100
typedef sturct{
	ElemType *data;
	int MaxSize, length;
}SqList;
//��ʼ��̬����
L.data=(ElemType*)malloc(sizeof(ElemType)*InitSize);
//C++��ʽ
L.data=new ElemType[InitSize];

//�������
bool ListInsert(SqList &L, int i, ElemType e)
{
	if(i<1  ||  i>L.length+1)
		return false;
	if(L.length>=MaxSize)
		return false;
	for(int j=L.length; j>=i; j--)
		L.data[j]=L.data[j-1];
	L.data[i-1]=e;
	L.length++;
	return true;
}
//ɾ������
bool ListDelete(SqlList &L, int i, int &e)
{
	if(i<1 || i>L.length)
		return false;
	e=L.data[i-1];
	for(int j=i; i<L.length; i++)
		L.data[j-1]=L.data[j];
	L.length--;
	return true;
}
//��ֵ����
int LocateElem(SqList L, ElemType e)
{
	int i;
	for(i=0; i<L.length; i++)
		if(L.data[i]==e)
			return i+1;
	return 0;
}


//��˳�����ɾ����СֵԪ�أ����ɺ������ر�ɾԪ�ص�ֵ���ճ���λ�������һ��Ԫ�������˳���Ϊ������ʾ������Ϣ���˳�����
bool deleteMinimum(SqList L, ElemType &e)
{
	if(L.length==0)
		return false;
	int index, min=L[0];//����
	for(int i=1; i<L.length; i++)
	{
		if(L[i]<min)
		{
			index=i;
			min=L[i];
		}
	}
	L[index]=L[length-1];
	L.length--;
	return true;
}

bool Del_Min(sqList &l, ElemType &value)
{
	if(L.length==0)
		return false;
	ElemType min=L.data[0];
	int index=0;
	for(int i=1; i<L.length; i++)
	{
		if(L.data[i]<min)
		{
			index=i;
			min=L.data[i];
		}
	}
	L.data[index]=L.data[length-1];
	L.length--;
	return true;
}

//���һ����Ч�㷨,��˳��������Ԫ������,Ҫ���㷨�ռ临�Ӷ�ΪO(1)
void reverse(SqList &L)
{
	int times=L.length/2;
	for(int i=0; i<times; i++)
	{
		int temp=L.data[i];//����
		L.data[i]=L.data[length-1-i];//����
		L.data[length-1-i]=temp;
	}
}

void reverse(SqList &L)
{
	ElemType temp;
	for(int i=0; i<L.length/2; i++)
	{
		temp=L.data[i];
		L.data[i]=L.data[L.length-1-i];
		L.data[L.length-1-i]=temp
	}
}

//����Ϊn��˳���L����дһ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�ΪO(1)���㷨�����㷨ɾ�����Ա�������ֵΪx������Ԫ��
void Del_x(SqlList &L)
{
	for(int i=0; i<L.length; i++)
	{
		if(L[i]==x)
		{
			L[i]=L[l.length-1];//���󣬼��ⷨ��
			l.length--;
		}
	}
}
//�ⷨһ����K��¼˳���L�в�����x��Ԫ�ظ���������Ҫ�����Ԫ�ظ���������ɨ��L��ͳ��K������������x��Ԫ����ǰ����
//Kλ���ϣ�����޸�L�ĳ���
void del_x_1(SqlList &L, Elemtype x)
{
	int k=0;
	for(i=0; i<L.length; i++)
		if(L.data[i]!=x)
		{
			L.data[k]=L.data[i];
			k++;
		}
	L.length=k;
}
//�ⷨ������K��¼˳���L�е���x��Ԫ�ظ�������ɨ��L��ͳ��k������������x��Ԫ��ǰ��k��λ�ã�����޸�L�ĳ���
void del_x_2(SqlList &L, Elemtype x)
{
	int k=0, i=0;
	while(i<L.length)
	{
		if(L.data[i]==x)
			k++;
		else
			L.data[i-k]=L.data[i];
		i++;
	}
	L.length=L.length-k;
}
//�ⷨ������ͷβ����ָ�룬���������м��ƶ��������������ֵx��Ԫ��ʱ��ֱ�ӽ����Ҷ�ֵ��x��Ԫ��������ֵΪx������Ԫ��λ�ã�
//ֱ����ָ������������ı�Ԫ�ص����λ��
void del_x_3(sqlList &L, Elemtype x)
{
	int i=0, j=L.length-1;
	int k=0;
	while(i<j)
	{
		while(L[j]==x  &&  j>i)
		{
			j--;
			k++;
		}
		while(i<j  &&  L[i]!=x)
			i++;
		if(L[i]==x  &&  i<j)
		{
			L[i]=L[j];
			j--;
		}
	}
	L.length=L.length-k;
}

//������˳�����ɾ����ֵ�ڸ���s��t֮�������Ԫ�أ����s��t���������˳���Ϊ������ʾ������Ϣ���˳�����
bool del_s_t(SqlList &L, Elemtype s, Elemtype t)
{
	if(s>=t  ||  L.length==0)
		return false;
	int l=0;
	while(l<L.length)
	{
		if(L[i]<s)
			l++;
		else
			break;
	}
	if(l==L.length  ||  L[l]>=t)//�����ж�
		return true;
	int r=l;
	while(r<L.length)
	{
		if(L[r]<t)
			r++;
		else
			break;
	}
	//if(l==r)   return true;
	for(int i=r; i<L.length; i++)
	{
		L[l++]=L[i];
	}
}

bool Del_s_t2(sqlList &L, Elemtype s, Elemtype t)
{
	int i, j;
	if(s>=t  ||  L.length==0)
		return false;
	for(i=0; i<L.length  &&  L.data[i]<s; i++);

	if(i>=L.length)
		return false;

	for(j=i; j<L.length  &&  L.data[j]<=t; j++);
//if(i==j)   return true;
	for(; j<L.length; i++,j++)
		L.data[i]=L.data[j];
	return true;
}


//��˳�����ɾ��������ֵ�ڸ���ֵs��t֮�䣨����s��t��Ҫ��s<t��������Ԫ�أ����s��t���������˳���Ϊ������ʾ������Ϣ���˳�����
bool Del_s_t3(sqlList &L, Elemtype s, Elemtype t)
{
	if(s>=t  ||  L.length==0)
		return false;
	int k=0;
	for(int i=0; i<L.length; i++)
	{
		if(L[i]<=s  &&  L[j]>=t)
		{
			L[k]=L[i];
			k++;
		}
	}
	L.length=L.length-k;
}
//�㷨˼�룺��ǰ���ɨ��˳���L����k��¼��Ԫ����s��t֮��Ԫ�صĸ�������ʼʱk=0�������ڵ�ǰɨ���Ԫ�أ�����ֵ����s��t֮�䣬
//��ǰ��k��λ�ã�����ִ��k++����������ÿ������s��t֮���Ԫ�ؽ��ƶ�һ�Σ������㷨Ч�ʸߡ�
bool Del_s_t(sqlList &L, ELemtype s, Elemtype t)
{
	int i, k=0;
	if(L.length==0  ||  s>=t)
		return false;
	for(i=0; L.length; i++)
	{
		if(L.data[i]>=s  &&  L.data[i]<=t)
			k++;
		else
			L.data[i-k]=L.data[i];
	}
	L.length-=k;
	return true;
}


//������˳�����ɾ��������ֵ�ظ���Ԫ�أ�ʹ��������Ԫ�ص�ֵ����ͬ
void delete_same(sqlList &L)
{
	int i=0, j=0;
	while(i<L.length)
	{
		while(L[j]==L[i]  &&  j<L.length)
			j++;
		L[i++]=L[j];
	}
	L.length=i;//+1
}
//�޸�
void delte_same(sqlList &L)
{
	int i=0, j=0;
	while(j<L.length)
	{
		if(L[j]==L[i])
			j++;
		else
			L[i++]=L[j++];
	}
	L.length=i+1;
}
//�޸�
void delete_same(sqlList &L)
{
	int i=0, j=0;
	while(j<L.length)
	{
		if(L[j]!=L[i])
			L[i++]=L[j];
		j++;
	}
	L.length=i+1;
}
//�㷨˼�룺������ֱ�Ӳ��������˼�룬��ʼʱ����һ��Ԫ�ؿ������ظ��������֮��˳�������жϺ����Ԫ���Ƿ���ǰ����ظ������
//�����һ��Ԫ����ͬ�������ͬ���������жϣ������ͬ����뵽ǰ��ķ��ظ����������ֱ���жϵ�������βΪֹ��
bool Delete_Same(SeqList &L)
{
	if(L.length==0)
		return false;
	int i, j;
	for(i=0,j=1; j<L.length; j++)
		if(L.data[i]!=L.data[j])
			L.data[++i]=L.data[j];
	L.length=i+1;
}


//����������˳���ϲ���һ���µ�����˳������ɺ������ؽ��˳���
void merge(sqlList &L1, sqlList &L2)
{
	sqlList L3=new sqlList[L1.length+L2.length];
	for(int i=0,j=0,k=0; i<L1.length  &&  j<L2.length;)
	{
		if(L1[i]<L2[j])
			L3[k++]=L1[i++];
		else
			L3[k++]=L2[j++];
	}
	L3.length=L1.length+L2.length;
}
bool Merge(SeqList A, SeqList B, SeqList C)
{
	if(A.length+B.length>C.maxSize)
		return false;
	int i=0,j=0,k=0;
	while(i<A.length  &&  j<B.length)
	{
		if(A.data[i]<=B.data[j])
			C.data[k++]=A.data[i++];
		else
			C.data[k++]=B.data[j++];
	}
	while(i<A.length)
		C.data[k++]=A.data[i++];
	while(j<B.length)
		C.data[k++]=B.data[j++];
	C.length=k;
	return true;
}


//��֪��һλ����A[m+n]�����δ�����������Ա�a1,a2,a3,��am���ͣ�b1,b2,��bn�����Ա�дһ��������
//������������˳����λ�û�����������b1,b2,��bn���ŵ���a1,a2,a3,��am��ǰ��
typedef int DataType;
void Reverse(DataType A[], int left, int right,  int arraySize)
{//��ת(aleft, aleft+1, aleft+2,...aright)Ϊ(aright, aright-1,...aleft)
	if(left>=right  ||  right>=arraySize)
		return;
	int mid=(left+right)/2;
	for(int i=0; i<=mid-left; i++)
	{
		DataType temp=A[left+i];
		A[left+i]=A[right-i];
		A[right-i]=temp;
	}
}
void Exchange(DataType A[], int m, int n, int arraySize)
{
	Reverse(A, 0, m+n-1, arraySize);
	Reverse(A, 0, n-1, arraySize);
	Reverse(A, n, m+n-1, arraySize);
}

//���Ա�a1,a2,a3,��an����Ԫ�ص��������Ұ�˳��洢�ڼ�����ڡ�Ҫ�����һ�㷨���������ʱ���ڱ��в�����ֵΪx��Ԫ�أ�
//���ҵ���������Ԫ��λ���ཻ�������Ҳ������������в�ʹ����Ԫ���Ե�������
void select_x(seqList &L, Elemtype x)
{
	for(int i=0; i<L.length  &&  L[i]<x; i++);

	if(i>=L.length)
	{
		L[L.length++]=x;
		return;
	}

	if(L[i]==x)
	{
		if(i!=L.length-1)
		{
			Elemtype tmp=L[i];
			L[i]=L[i+1];
			L[i+1]=tmp;
		}
	}
	else
	{
		for(int j=L.length-1; j>=i; j--)
		{
			L[j+1]=L[j];
			L[i]=x;
		}
	}
}
//�㷨˼�룺˳��洢�����Ա�������򣬿���˳����ң������۰���ҡ���ĿҪ�������ٵ�ʱ�䣬���۰����
void SearchExchangeInsert(Elemtype A[], Elemtype x)
{
	int low=0,high=n-1,mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(A[mid]==x)
			break;
		else if(A[mid]<x)
			low=mid+1;
		else
			high=mid-1;
	}
	if(A[mid]==x  &&  mid!=n-1)
	{
		t=A[mid];
		A[mid]=A[mid+1];
		A[mid+1]=t;
	}
	if(low>high)
	{
		for(int i=n-1; i>high; i--)
			A[i+1]=A[i];
		A[i+1]=x;
	}
}

//�轫n(n>1)��������ŵ�һά����R�С������һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨����R�б��������ѭ������P��0<p<n����λ�ã�
//����R�е������ɣ�X0��X1, �� Xn-1���任Ϊ��XP, XP+1, �� Xn-1, X0, X1, ��, Xp-1��
void Reverse(int R[], int from, int to)
{
	int i,temp;
	for(i=0; i<(to-from)/2; i++)
	{
		temp=R[from+1];
		R[form+1]=R[to-i];
		R[to-i]=temp;
	}
}
void Converse(int R[], int n, int p)
{
	Reverse(R, 0, p-1);
	Reverse(R, p, n-1);;
	Reverse(R, 0, n-1);
}
//��⣺������������ʵ��
//�㷨˼�룺������СΪP�ĸ�������S����R��ǰP�����������ݴ���S�У�ͬʱ��R�к�n-p���������ƣ�Ȼ��S���ݴ��p�������ηŻ�R�еĺ�����Ԫ��
//ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�O(p)


//һ������ΪL��L>=1������������S�����ڵ�>L/2 ��λ�õ�����ΪS����λ�����������е���λ���Ǻ���������Ԫ�ص��������е���λ����
//�����������ȳ���������A��B�������һ����ʱ��Ϳռ������涼�����ܸ�Ч���㷨���ҳ���������A��B����λ��
int M_Search(int A[], int B[], int n)
{
	int s1=0, d1=n-1, m1, s2=0, d2=n-1, m2;
	while(s1!=d1  ||  s2!=d2)
	{
		m1=(s1+d1)/2;
		m2=(s2+d2)/2;
		if(A[m1]==B[m2])
			return A[m1];
		if(A[m1]<B[m2])
		{
			if((s1+d1)%2==0)//��Ԫ�ظ���Ϊ����
			{
				s1=m1;
				d2=m2;
			}
			else			//��Ԫ�ظ���Ϊż��
			{
				s1=m1+1;
				d2=m2;
			}
		}
		else
		{
			if((s2+d2)%2==0)
			{
				d1=m1;
				s2=m2;
			}
			else
			{
				d1=m1;
				d2=m2+1;
			}
		}
	}
	return A[s1]<B[s2]?  A[s1] : B[s2];
}

//��֪һ����������A={a0, a1, ��, an-1}������0<ai<n(0<=i<n)��������ap1=ap2=��=apm=x��m>n/2(0<p<n, 1<=k<m),���xΪA����Ԫ�ء�
//����A�е�n��Ԫ�ر�����һ��һά�����У������һ�������ܸ�Ч���㷨���ҳ�A����Ԫ�ء������ڣ��������Ԫ�أ��������-1��
//�㷨�Ĳ����Ǵ�ǰ���ɨ������Ԫ�أ���ǳ�һ�����ܳ�Ϊ��Ԫ�ص�Ԫ��Num��Ȼ�����¼�����ȷ��Num�Ƿ�����Ԫ�ء�
//�㷨������������
//1) ѡȡ��ѡ����Ԫ�أ�����ɨ�����������е�ÿ������������һ������������Num���浽c�У���¼Num�ĳ��ִ���Ϊ1��
//����������һ�������Ե���Num���������1�����������1������������0ʱ������������һ���������浽c�У�
//�������¼�Ϊ1����ʼ��һ�ּ��������ӵ�ǰλ�ÿ�ʼ�ظ��������̣�ֱ��ɨ����ȫ������Ԫ�ء�
//2)�ж�c��Ԫ���Ƿ�����������Ԫ�أ��ٴ�ɨ������飬ͳ��c��Ԫ�س��ֵĴ�����������n/2����Ϊ��Ԫ�أ����������в�������Ԫ��
int Majority(int A[], int n)
{
	int i,c,count=1;
	c=A[0];
	for(i=1; i<n; i++)
	{
		if(A[i]==c)
			count++;
		else
		{
			if(count>0)
				count--;
			else
			{
				c=A[i];
				count=1;
			}
		}
	}
	if(count>0)
	{
		for(i=count=0; i<n; i++)
			if(A[i]==c)
				count++;
	}
	if(count>n/2)
		return c;
	else
		return -1;
}