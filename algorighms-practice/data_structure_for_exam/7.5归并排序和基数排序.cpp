//归并Merge
ElemType *B=(ElemType*)malloc((n+1)*sizeof(ElemType));
void Merge(ElemType A[], int low, int mid, int high)
{
	//表A的两段A[low ... mid]和A[mid+1 ... high]各自有序，将它们合并成一个有序表
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





//递归形式的2-路归并排序
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