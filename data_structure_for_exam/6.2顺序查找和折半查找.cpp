//һ�����Ա��˳�����
typedef struct{//���ұ�����ݽṹ
	ElemType *elem;//Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	int TableLen;//��ĳ���
}SSTable;
int Search_Seq(SSTable ST, ElemType key)
{
	//��˳���ST��˳����ҹؼ���Ϊkey��Ԫ�ء����ҵ��򷵻ظ�Ԫ���ڱ��е�λ��
	ST.elem[0]=key;//"�ڱ�"
	for(i=ST.TableLen; ST.elem[i]!=key; --i)//�Ӻ���ǰ��
		;
	return i;//�����в����ڹؼ���Ϊkey��Ԫ�أ������ҵ�iΪ0ʱ�˳�forѭ��
}







//�۰����
int Binary_Search(SeqList L, ElemType key)
{
	//�������L�в��ҹؼ���Ϊkey��Ԫ�أ��������򷵻���λ�ã��������򷵻�-1
	int low=0, high=L.TableLen-1, mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(L.elem[mid]==key)
			return mid;
		else if(L.elem[mid]>key)
			high=mid-1;
		else
			low=mid+1;
	}
	return -1;
}
















//�۰���ҵĵݹ��㷨��
typedef struct{//���ұ�����ݽṹ
	ElemType *elem;//�洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0������
	int length;//��ĳ���
}SSTable;
int BinSearchRec(SSTable ST, ElemType key, int low, int high)
{
	if(low<high)
		return 0;
	mid=(low+high)/2;
	if(key>ST.elem[mid])
		BinSearchRec(ST, key, mid+1, high);
	else if(key<ST.elem[mid])
		BinSearchRec(ST, key, low, mid-1);
	return mid;
}




//���Ա��и����ļ������ʲ��ȣ���������²������˳�������Ч�ʣ����ҵ�ָ���Ľ�㣬���ý���ǰ����㣨�����ڣ�������
//ʹ�þ����������Ľ�㾡��λ�ڱ��ǰ�ˡ������˳��ṹ����ʽ�ṹ�����Ա���ʵ���������Ե�˳������㷨��
int SeqSrch(RcdType R[], ElemType k)
{
	int i=0;
	while((R[i].key!=k)  &&  (i<n))
		i++;
	if(i<n  &&  i>0)
	{
		temp=R[i]; R[i]=R[i-1]; R[i-1]=temp;
		return --i;
	}
	else
		return -1;
}

typedef struct{
	ElemType data;
	struct LNode* next;
}LNode, *LinkList;
int LinkSrch(LinkList L, ElemType k)
{
	LNode* p, t;
	for(t=L, p=L->next; p  &&  p->data!=k; t=p, p=p->next)
		;
	if(!p)
		return -1;
	t->next=p->next;
	p->next=t;
	t=p;
}