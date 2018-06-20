//�鲢Merge
ElemType *B=(ElemType*)malloc((n+1)*sizeof(ElemType));
void Merge(ElemType A[], int low, int mid, int high)
{
	//��A������A[low ... mid]��A[mid+1 ... high]�������򣬽����Ǻϲ���һ�������
	for(int k=low; k<=high; k++)
		B[k]=A[k];
	for(i=low, j=mid+1, k=i; i<=mid  &&  j<=high; k++)
	{
		if(B[i]<=B[j])
			A[k]=B[i];
		else
			A[k]=B[j++];
	}
	while(i<=mid)
		A[k++]=B[i++];
	while(j<=high)
		A[k++]=B[j++];
}





//�ݹ���ʽ��2-·�鲢����
void MergeSort(ElemType A[], int low, int high)
{
	if(low<high)
	{
		int mid=(low+high)/2;
		MergeSort(A, low, mid);
		MergeSort(A, mid+1, high);
		Merge(A, low, mid, high);
	}
}