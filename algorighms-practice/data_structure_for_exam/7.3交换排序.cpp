//ð������
void BubbleSort(ElemType A[], int n)
{
	//��ð����������A�е�Ԫ�ذ���С��������
	for(i=0; i<n-1; i++)
	{
		flag=false;
		for(j=n-1; j>i; j--)
			if(A[j-1].key>A[j].key)
			{
				swap(A[j-1], A[j]);
				flag=true;
			}
		if(flag==false)
			return ;
	}
}


//��������
void QuickSort(ElemType A[], int low, int high)
{
	if(low<high)
	{
		int pivotpos=Partition(A, low, high);
		QuickSort(A, low, pivotpos-1);
		QuickSort(A, pivotpos+1, high);
	}
}


//���ֲ���
int Partition(ElemType A[], int low, int high)
{
	ElemType pivot=A[low];
	while(low<high)
	{
		while(low<high  &&  A[high]>=pivot)
			--high;
		A[low]=A[high];
		while(low<high  &&  A[low]<=pivot)
			++low;
		A[high]=A[low];
	}
	A[low]=pivot;
	return low;
}







//˫��ð�������㷨���������������������ɨ�裬����һ�˰ѹؼ�������Ԫ�ط���
//���е�����棬�ڶ��˰ѹؼ�����С��Ԫ�ط������е���ǰ�档��˷������С�
void bubble2(int A[], int low, int high)
{
	for(int i=0; i<n-1; i++)
	{
		if(i%2==0)//��i�ˣ�iΪ�������ˣ�˵����ߺ��ұ߷ֱ��ź���i/2��i/2��Ԫ��
		{
			
		}
		else//��i�ˣ�iΪż�����ˣ���ߺ��ұ߷ֱ��ź���(i+1)/2��(i-1)/2��Ԫ��
		{

		}
	}
}

void BubbleSort(ElemType A[], int n)
{
	//˫��ð��
	int low=0, high=n-1;
	bool flag=true;
	while(low<high  &&  flag)
	{
		flag=false;
		for(i=low; i<high; i++)
			if(a[i]>a[i+1])
			{
				swap(a[i], a[i+1]);
				flag=true;
			}
		high--;
		for(i=high; i>low; i--)
			if(a[i]<a[i-1])
			{
				swap(a[i], a[i-1]);
				flag=true;
			}
		low++;
	}
}









//��֪���Ա�˳��洢����ÿ��Ԫ�ض��ǲ���ͬ��������Ԫ�أ���ư����������ƶ�������ż��ǰ�ߵ���
void move(ElemType A[], int len)
{
	int i=0, j=len-1;
	while(i<j)
	{
		while(i<j  &&  A[i]%2!=0)
			i++;
		while(i<j  &&  A[j]%2!=1)
			j--;
		if(i<j)
		{
			Swap(A[i], A[j]);
			i++;
			j--;
		}
	}
}









//���±�д��������Ļ����㷨��ʹ֮ÿ��ѡȡ������ֵ��������شӵ�ǰ�ӱ���ѡ���.
int Partition2(ElemType A[], int low, int high)
{
	int rand_Index=low+rand()%(high-low+1);
	Swap(A[rand_Index], A[low]);

	ElemType pivot=A[low];
	int i=low;
	for(int j=low+1; j<=high; j++)
		if(A[j]<pivot)
			swap(A[++i], A[j]);
	swap(A[i], A[low]);
	return i;
}








//��дһ���㷨��ʹ֮�ܹ�������L[1...n]���ҳ���kС��Ԫ��
void kth_elem(int a[], int low, int high, int k)
{
	int pivot=a[low];
	int low_temp=low;
	int high_temp=high;
	while(low<high)
	{
		while(low<high  &&  a[high]>=pivot)
			--high;
		a[low]=a[high];
		while(low<high  &&  a[low]<=pivot)
			++low;
		a[high]=a[low];
	}
	a[low]=pivot;
	//���漴Ϊ���������еĻ����㷨
	//���¾��Ǳ��㷨˼��������������
	if(low==k)
		return a[low];
	else if(low>k)
		return kth_elem(a, low_temp, low-1, k);
	else
		return kth_elem(a, low+1, high_temp, k-low);
}













//�����������⣺����һ�����ɺ졢�ס���������ɫ��������ɵ��������У�
//���дһ��ʱ�临�Ӷ�ΪO(n)���㷨��ʹ����Щ���鰴�졢�ס�����˳���ź�
typedef enum{RED, WHITE, BLUE} color;//����ö������
void Flag_Arrange(color a[], int n)
{
	int i=0, j=0, k=n-1;
	while(j<=k)
	{
		switch(a[j])
		{
		case RED:
			Swap(a[i], a[j]); i++; j++;
			break;
		case WHITE:
			j++;
			break;
		case BLUE:
			Swap(a[j], a[k]);k--;
			break;
			//����û��j++����Է�ֹ������a[j]��Ϊ��ɫ�����
		}
	}
}

