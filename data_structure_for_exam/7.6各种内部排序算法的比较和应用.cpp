//˳���������A[]��ʾ������Ԫ�ش洢�������±�1~m+n�ķ�Χ�ڣ�
//ǰm��Ԫ�ص������򣬺�n��Ԫ�ص����������һ���㷨��ʹ������˳�������
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







//��������
void CountSort(RecType A[], RecType B[], int n)
{
	//���������㷨����A�м�¼�������B��
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