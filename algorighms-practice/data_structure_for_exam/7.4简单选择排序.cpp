//简单选择排序
void SelectSort(ElemType A[], int n)
{
	for(i=0; i<n-1; i++)
	{
		min=i;
		for(j=i+1; j<n; j++)
			if(A[j]<A[min])
				min=j;
		if(min!=i)
			swap(A[i], A[min]);
	}
}





//建立大根堆
void BuildMaxHeap(ElemType A[], int len)
{
	for(int i=len/2; i>0; i--)
		AdjustDown(A, i, len);
}
void AdjustDown(ElemType A[], int k, int len)
{
	//函数AdjustDown将元素i向下进行调整
	A[0]=A[k];//A[0]暂存
	for(i=2*k; i<=len; i*=2)//沿key较大的子结点向下筛选
	{
		if(i<len  &&  A[i]<A[i+1])
			i++;
		if(A[0]>=A[i])
			break;
		else
		{
			A[k]=A[i];
			k=i;
		}
	}
	A[k]=A[0];
}











//堆排序
void HeapSort(ElemType A[], int len)
{
	BuildMaxHeap(A, len);
	for(i=len; i>1; i--)//n-1趟的交换和建堆过程
	{
		print(A[1]);
		swap(A[i], A[1]);
		AdjustDown(A, 1, i-1);
	}
}







//堆的向上调整
void AdjustUp(ElemType A[], int k)
{
	//参数k为向上调整的结点，也为堆的元素个数
	A[0]=A[k];
	int i=k/2;
	while(i>0  &&  A[i]<A[0])
	{
		A[k]=A[i];
		k=i;
		i=k/2;
	}
	A[k]=A[0];
}




//单链表的简单选择排序
void selectSort(LinkedList& L)
{
	//对不带表头结点的单链表L执行简单选择排序
	LinkNode *h=L, *p, *q, *r, *s;
	L=NULL;
	while(h!=NULL)
	{
		p=s=h;
		q=r=NULL;
		//指针s和r记忆最大结点和其前驱；p为工作指针，q为其前驱
		while(p!=NULL)
		{
			if(p->data>s->data)
			{
				s=p;r=q;
			}
			q=p;
			p=p->link;
		}

		if(s==h)
			h=h->link;
		else
			r->link=s->link;
		s->link=L;
		L=s;
	}
}





//判断一个数据序列是否构成一个小根堆
bool IsMinHeap(ElemType A[], int len)
{
	if(len%2==0)//len为偶数，有一个单分支结点
	{
		if(A[len/2]>A[len])
			return false;
		for(i=len/2-1; i>=1; i--)
			if(A[i]>A[2*i]  ||  A[i]>A[2*i+1])
				return false;
	}
	else//len为奇数时，没有单分支结点
	{
		for(i=len/2; i>=1; i--)
			if(A[i]>A[2*i]  ||  A[i]>A[2*i+1])
				return false;
	}
	return true;
}