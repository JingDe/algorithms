//顺序表定义:静态分配
#define MaxSize 50
typedef struct{
	ElemType data[MaxSize];
	int length;
}SqList;

//顺序表定义：动态分配
#define InitSize 100
typedef sturct{
	ElemType *data;
	int MaxSize, length;
}SqList;
//初始动态分配
L.data=(ElemType*)malloc(sizeof(ElemType)*InitSize);
//C++方式
L.data=new ElemType[InitSize];

//插入操作
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
//删除操作
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
//按值查找
int LocateElem(SqList L, ElemType e)
{
	int i;
	for(i=0; i<L.length; i++)
		if(L.data[i]==e)
			return i+1;
	return 0;
}


//从顺序表中删除最小值元素，并由函数返回被删元素的值，空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出运行
bool deleteMinimum(SqList L, ElemType &e)
{
	if(L.length==0)
		return false;
	int index, min=L[0];//错了
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

//设计一个高效算法,将顺序表的所有元素逆置,要求算法空间复杂度为O(1)
void reverse(SqList &L)
{
	int times=L.length/2;
	for(int i=0; i<times; i++)
	{
		int temp=L.data[i];//错了
		L.data[i]=L.data[length-1-i];//错了
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

//长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，该算法删除线性表中所有值为x的数据元素
void Del_x(SqlList &L)
{
	for(int i=0; i<L.length; i++)
	{
		if(L[i]==x)
		{
			L[i]=L[l.length-1];//错误，见解法三
			l.length--;
		}
	}
}
//解法一：用K记录顺序表L中不等于x的元素个数（即需要保存的元素个数），边扫描L边统计K，并将不等于x的元素向前放置
//K位置上，最后修改L的长度
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
//解法二：用K记录顺序表L中等于x的元素个数，边扫描L边统计k，并将不等于x的元素前移k个位置，最后修改L的长度
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
//解法三，设头尾两个指针，从两端向中间移动，凡遇到最左端值x的元素时，直接将最右端值非x的元素左移至值为x的数据元素位置，
//直到两指针相遇，但会改变元素的相对位置
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

//从有序顺序表中删除其值在给定s与t之间的所有元素，如果s或t不合理或者顺序表为空则显示出错信息并退出运行
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
	if(l==L.length  ||  L[l]>=t)//若不判断
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


//从顺序表中删除所有其值在给定值s与t之间（包含s和t，要求s<t）的所有元素，如果s或t不合理或者顺序表为空则显示出错信息并退出运行
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
//算法思想：从前向后扫描顺序表L，用k记录下元素在s到t之间元素的个数（初始时k=0）。对于当前扫描的元素，若其值不在s到t之间，
//则前移k个位置；否则执行k++。由于这样每个不在s到t之间的元素仅移动一次，所有算法效率高。
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


//从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同
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
//修改
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
//修改
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
//算法思想：用类似直接插入排序的思想，初始时将第一个元素看做非重复的有序表。之后顺序依次判断后面的元素是否与前面非重复有序表
//的最后一个元素相同，如果相同则继续向后判断，如果不同则插入到前面的非重复有序表的最后，直至判断到整个表尾为止。
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


//将两个有序顺序表合并成一个新的有序顺序表，并由函数返回结果顺序表。
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


//已知在一位数组A[m+n]中依次存放着两个线性表（a1,a2,a3,…am）和（b1,b2,…bn）。试编写一个函数，
//将数组中两个顺序表的位置互换，即将（b1,b2,…bn）放到（a1,a2,a3,…am）前面
typedef int DataType;
void Reverse(DataType A[], int left, int right,  int arraySize)
{//逆转(aleft, aleft+1, aleft+2,...aright)为(aright, aright-1,...aleft)
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

//线性表（a1,a2,a3,…an）中元素递增有序且按顺序存储于计算机内。要求设计一算法完成用最少时间在表中查找数值为x的元素，
//若找到将其与后继元素位置相交换，若找不到将其插入表中并使表中元素仍递增有序
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
//算法思想：顺序存储的线性表递增有序，可以顺序查找，可以折半查找。题目要求用最少的时间，用折半查找
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

//设将n(n>1)个整数存放到一维数组R中。试设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移P（0<p<n）个位置，
//即将R中的数组由（X0，X1, … Xn-1）变换为（XP, XP+1, … Xn-1, X0, X1, …, Xp-1）
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
//另解：借助辅助数组实现
//算法思想：创建大小为P的辅助数组S，将R中前P个整数依次暂存在S中，同时将R中后n-p个整数左移，然后将S中暂存的p个数依次放回R中的后续单元。
//时间复杂度为O(n)，空间复杂度O(p)


//一个长度为L（L>=1）的升序序列S，处在第>L/2 个位置的数称为S的中位数。两个序列的中位数是含它们所有元素的升序序列的中位数。
//现在有两个等长升序序列A和B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数
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
			if((s1+d1)%2==0)//若元素个数为奇数
			{
				s1=m1;
				d2=m2;
			}
			else			//若元素个数为偶数
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

//已知一个整数序列A={a0, a1, …, an-1}，其中0<ai<n(0<=i<n)。若存在ap1=ap2=…=apm=x且m>n/2(0<p<n, 1<=k<m),则称x为A的主元素。
//假设A中的n个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。若存在，则输出该元素，否则输出-1。
//算法的策略是从前向后扫描数组元素，标记出一个可能成为主元素的元素Num。然后重新计数，确认Num是否是主元素。
//算法分以下两步：
//1) 选取候选的主元素：依次扫描所给数组中的每个整数，将第一个遇到的整数Num保存到c中，记录Num的出现次数为1；
//若遇到的下一个整数仍等于Num，则计数加1，否则计数减1；当计数减到0时，将遇到的下一个整数保存到c中，
//计数重新记为1，开始新一轮计数，即从当前位置开始重复上述过程，直到扫描完全部数组元素。
//2)判断c中元素是否是真正的主元素：再次扫描该数组，统计c中元素出现的次数，若大于n/2，则为主元素；否则，序列中不存在主元素
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