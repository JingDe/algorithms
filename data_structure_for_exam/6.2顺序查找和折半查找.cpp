//一般线性表的顺序查找
typedef struct{//查找表的数据结构
	ElemType *elem;//元素存储空间基址，建表时按实际长度分配，0号单元留空
	int TableLen;//表的长度
}SSTable;
int Search_Seq(SSTable ST, ElemType key)
{
	//在顺序表ST中顺序查找关键字为key的元素。若找到则返回该元素在表中的位置
	ST.elem[0]=key;//"哨兵"
	for(i=ST.TableLen; ST.elem[i]!=key; --i)//从后往前找
		;
	return i;//若表中不存在关键字为key的元素，将查找到i为0时退出for循环
}







//折半查找
int Binary_Search(SeqList L, ElemType key)
{
	//在有序表L中查找关键字为key的元素，若存在则返回其位置，不存在则返回-1
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
















//折半查找的递归算法：
typedef struct{//查找表的数据结构
	ElemType *elem;//存储空间基址，建表时按实际长度分配，0号留空
	int length;//表的长度
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




//线性表中各结点的检索概率不等，则可用如下策略提高顺序检索的效率：若找到指定的结点，将该结点和前驱结点（若存在）交换，
//使得经常被检索的结点尽量位于表的前端。设计在顺序结构和链式结构的线性表上实现上述策略的顺序检索算法。
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