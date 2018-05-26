//顺序表用数组A[]表示，表中元素存储在数组下标1~m+n的范围内，
//前m个元素递增有序，后n个元素递增有序，设计一个算法，使得整个顺序表有序。
void Insert_Sort(ElemType A[], int m, int n)
{
	int i, j;
	for(i=m+1; i<=m+n; i++)
	{
		A[0]=A[i];
		for(j=i-1; A[j]>A[0]; j--)
			A[j+1]=A[j];
		A[j+1]=A[0];
	}
}







//计数排序
void CountSort(RecType A[], RecType B[], int n)
{
	//计数排序算法，将A中记录排序放入B中
	int cnt;
	for(i=0; i<n; i++)
	{
		for(j=0, cnt=0; j<n; j++)
			if(A[j].key<A[i].key)
				cnt++;
		B[cnt]=A[i];
	}
}



void CountSort2(RecType a[], RecType B[], int n)
{
	for(i=0; i<n; i++)
		a[i].count=0;
	for(i=0; i<n; i++)
		for(j=i+1; j<n; j++)
		{
			if(a[i].key<a[j].key)
				a[j].count++;
			else
				a[i].count++;
		}
	for(i=0; i<n; i++)
		B[a[i].count]=a[i];
}