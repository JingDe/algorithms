//直接插入排序
void InsertSort(ElemType A[], int n)
{
	int i, j;
	for(i=2; i<=n; i++)
		if(A[i].key<A[i-1].key)
		{
			A[0]=A[i];
			for(j=i-1; A[0].key<A[j].key; --j)
				A[j+1]=A[j];
			A[j+1]=A[0];
		}
}



//折半插入排序
void InsertSort(ElemType A[], int n)
{
	int i, j, low, high, mid;
	for(i=2; i<=n; i++)
	{
		A[0]=A[i];
		low=1;
		high=i-1;
		while(low<=high)
		{
			mid=(low+high)/2;
			if(A[mid].key>A[0].key)
				high=mid-1;
			else
				low=mid+1;
		}
		for(j=i-1; j>=high+1; --j)
			A[j+1]=A[j];
		A[high+1]=A[0];
	}
}




//希尔排序
void ShellSort(ElemType A[], int n)
{
	//对顺序表作希尔插入排序，与直接插入排序相比，作了以下修改：
	//1. 前后记录位置的增量是dk，不是1
	//2. A[0]只是暂存单元，不是哨兵，当j<0时，插入位置已到
	for(dk=len/2; dk>=1; dk=dk/2)
		for(i=dk+1; i<=n; i++)
			if(A[i].key<A[i-dk].key)
			{
				A[0]=A[i];
				for(j=i-dk;  j>0  &&  A[0].key<A[j].key;  j-=dk)
					A[j+dk]=A[j];
				A[j+dk]=A[0];
			}
}