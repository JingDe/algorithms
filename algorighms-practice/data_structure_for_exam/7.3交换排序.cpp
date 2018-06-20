//冒泡排序
void BubbleSort(ElemType A[], int n)
{
	//用冒泡排序将序列A中的元素按从小到大排列
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


//快速排序
void QuickSort(ElemType A[], int low, int high)
{
	if(low<high)
	{
		int pivotpos=Partition(A, low, high);
		QuickSort(A, low, pivotpos-1);
		QuickSort(A, pivotpos+1, high);
	}
}


//划分操作
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







//双向冒泡排序算法，在正反两个方向交替进行扫描，即第一趟把关键字最大的元素放在
//序列的最后面，第二趟把关键字最小的元素放在序列的最前面。如此反复进行。
void bubble2(int A[], int low, int high)
{
	for(int i=0; i<n-1; i++)
	{
		if(i%2==0)//第i趟，i为奇数次趟，说明左边和右边分别排好了i/2和i/2个元素
		{
			
		}
		else//第i趟，i为偶数次趟，左边和右边分别排好了(i+1)/2和(i-1)/2个元素
		{

		}
	}
}

void BubbleSort(ElemType A[], int n)
{
	//双向冒泡
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









//已知线性表按顺序存储，且每个元素都是不相同的整数型元素，设计把所有奇数移动到所有偶数前边的算
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









//重新编写快速排序的划分算法，使之每次选取的枢轴值都是随机地从当前子表中选择的.
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








//编写一个算法，使之能够在数组L[1...n]中找出第k小的元素
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
	//上面即为快速排序中的划分算法
	//以下就是本算法思想中所述的内容
	if(low==k)
		return a[low];
	else if(low>k)
		return kth_elem(a, low_temp, low-1, k);
	else
		return kth_elem(a, low+1, high_temp, k-low);
}













//荷兰国旗问题：设有一个仅由红、白、蓝三种颜色的条块组成的条块序列，
//请编写一个时间复杂度为O(n)的算法，使得这些条块按红、白、蓝的顺序排好
typedef enum{RED, WHITE, BLUE} color;//设置枚举数组
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
			//这里没有j++语句以防止交换后a[j]仍为蓝色的情况
		}
	}
}

