//��ѡ������
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





//���������
void BuildMaxHeap(ElemType A[], int len)
{
	for(int i=len/2; i>0; i--)
		AdjustDown(A, i, len);
}
void AdjustDown(ElemType A[], int k, int len)
{
	//����AdjustDown��Ԫ��i���½��е���
	A[0]=A[k];//A[0]�ݴ�
	for(i=2*k; i<=len; i*=2)//��key�ϴ���ӽ������ɸѡ
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











//������
void HeapSort(ElemType A[], int len)
{
	BuildMaxHeap(A, len);
	for(i=len; i>1; i--)//n-1�˵Ľ����ͽ��ѹ���
	{
		print(A[1]);
		swap(A[i], A[1]);
		AdjustDown(A, 1, i-1);
	}
}







//�ѵ����ϵ���
void AdjustUp(ElemType A[], int k)
{
	//����kΪ���ϵ����Ľ�㣬ҲΪ�ѵ�Ԫ�ظ���
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




//������ļ�ѡ������
void selectSort(LinkedList& L)
{
	//�Բ�����ͷ���ĵ�����Lִ�м�ѡ������
	LinkNode *h=L, *p, *q, *r, *s;
	L=NULL;
	while(h!=NULL)
	{
		p=s=h;
		q=r=NULL;
		//ָ��s��r������������ǰ����pΪ����ָ�룬qΪ��ǰ��
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





//�ж�һ�����������Ƿ񹹳�һ��С����
bool IsMinHeap(ElemType A[], int len)
{
	if(len%2==0)//lenΪż������һ������֧���
	{
		if(A[len/2]>A[len])
			return false;
		for(i=len/2-1; i>=1; i--)
			if(A[i]>A[2*i]  ||  A[i]>A[2*i+1])
				return false;
	}
	else//lenΪ����ʱ��û�е���֧���
	{
		for(i=len/2; i>=1; i--)
			if(A[i]>A[2*i]  ||  A[i]>A[2*i+1])
				return false;
	}
	return true;
}