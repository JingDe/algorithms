

/*
堆排序：
构造初始堆
删除元素
插入元素
堆排序

数据结构：数组A[], A[i]的儿子节点是A[2i]和A[2i+1].

*/

/*
构造一个大根堆：
n个节点，A[1]~A[n]
最后一个节点的父节点是A[n/2].对A[n/2]为根的子树筛选，使该子树成为堆。
依次对A[n/2-1]到A[1]为根的子树进行筛选，将左右子树中较大值与之交换，交换后如果破坏下一级的堆，对下一级调整。直到调整到A[1]。
即从A[n/2]到A[1]调用AdjustDown方法。

AdjustDown(ElementType A[], int len, int k); 对A[k]为根的子树向下调整，使A[k]为根的子树成为大根堆。
算法：
当前节点从A[k]开始，取当前节点的较大的子节点（沿着key较大的子节点向下筛选），若该较大子节点大于val(原来的A[k])，将其上移，当前节点指向该子节点，
直到某一当前节点的两个子节点都小于val，或者当前节点到达叶节点，则当前节点赋值为val。
*/


/*
插入元素：
先将新元素插入到堆的末端，再对新节点执行向上调整。

AdjustUp(ElementType A[], int k)：将堆底元素A[k]向上调整。
算法：
从新节点开始，如果val（新节点的值）大于当前节点的父节点的值，则将父节点下移，当前节点指向父节点
直到当前某一节点的父节点的值大于val，或者当前节点到达根节点，则将当前节点赋值为val。
*/


/*
删除元素：删除堆顶元素
将堆顶元素与末端元素A[n]交换，再对A[1]调用AdjustDown(A[], n-1, 1)方法。

删除堆中某个元素A[k]：
只可能将被删除元素作为堆顶的子树的堆性质破坏
将堆底元素A[n]赋值给A[k]，对A[k]调用AdjustDown(A[], n-1, k)方法。
*/


/*
堆排序：
首先构建大根堆。每次取出堆顶的最大元素，然后将堆底元素移到堆顶，对堆顶元素执行AdjustDown，重新构建大根堆。
循环取出堆顶元素，直到堆空。
*/

// 将数组A[1]~A[len]构建成一个大根堆
void BuildMaxHeap(ElementType A[], int len);
// 将A[k]节点为根的子树，构建成一个大根堆
void AdjustDown(ElementType A[], int len, int k);
// 对大根堆A[1]~A[k-1]，将堆底元素A[k]调整到堆中合适位置
void AdjustUp(ElementType A[], int k);
// 对无序数组A[]采用堆排序方法，输出从大到小元素序列
void HeapSort(ElementType A[], int len);


// 实现，调用方保证A[k]不是叶节点，k*2一定<=len
void AdjustDown(ElementType A[], int len, int k)
{
	int val=A[k];
	int cur=k*2; 
	while(cur<=len)
	{
		if(cur<len  &&  A[cur]<A[cur+1])
			cur++;
		if(A[cur]<=val)
			break;
		A[k]=A[cur];
		k=cur; // k是当前节点
		cur=cur*2; // cur是较大的儿子节点
	}
	A[k]=val;
}

void AdjustUp(ElementType A[], int k)
{
	int val=A[k];
	int parent=k/2;
	while(parent>=1  &&  A[parent]<val)
	{
		A[k]=A[parent];
		k=parent;
		parent=k/2;
	}
	A[k]=val;
}

void BuildMaxHeap(ElementType A[], int len)
{
	for(int i=len/2; i>=1; i--1) // 从第一个非叶子节点开始向下调整
		AdjustDown(A, len, i);
}

void HeapSort(ElementType A[], int len)
{
	BuildMaxHeap(A, len);
	while(len>1)
	{
		printf("%d\n", A[1]);
		A[1]=A[len--];
		AdjustDown(A, len, 1);
	}
}


void Insert(ElementType A[], int len, ElementType val)
{
	A[len+1]=val;
	AdjustUp(A, len+1);
}

void Delete(ElementType A[], int len, int pos)
{
	A[pos]=A[len--];
	AdjustDown(A, len, pos);
}

//查找大根堆A[1]~A[len]，判断元素key是否存在
// bool find(ElementType A[], int len, int key)
// {
	// if(len<1)
		// return false;
	// if(A[1]==key)
		// return true;
	// if(A[1]<key)
		// return false;
	// if(2<=len  &&  findFromRoot(A, len, 2, key))
		// return true;
	// if(3<=len  &&  findFromRoot(A, len, 3, key);
		// return true;
	// return false;
// }

// bool findFromRoot(ElementType A[], int len, int root, int key)
// {
	// if(A[root]==key)
		// return true;
	// if(A[root]<key)
		// return false;
	// if(root*2<=len  &&  findFromRoot(A, len, root*2, key))
		// return true;
	// if(root*2+1<=len  &&  findFromRoot(A, len, root*2+1, key);
		// return true;
	// return false;
// }

bool find(ElementType A[], int len, int key)
{
	return findFromRoot(A, len, 1, key);
}

bool findFromRoot(ElementType A[], int len, int root, int key)
{
	if(root>len)
		return false;
	
	if(A[root]==key)
		return true;
	if(A[root]<key)
		return false;
	if(root*2<=len  &&  findFromRoot(A, len, root*2, key))
		return true;
	if(root*2+1<=len  &&  findFromRoot(A, len, root*2+1, key);
		return true;
	return false;
}

/*
堆排序的空间复杂度：O(1)
时间复杂度：建堆O(n), n-1次向下调整o(nlogn)。总的时间复杂度在最好、最坏和平均情况下都是O(nlogn)。
不稳定。
*/


// make_heap等方法实现的堆
//构造一个最大堆
std::vector<ElementType> maxHeap
std::make_heap(maxHeap.begin(), maxHeap.end());
// 构造一个最小堆
std::vector<ElementType> minHeap;
std::make_heap(minHeap.begin(), minHeap.end(), std::greater<int>());

// 删除堆顶元素
std::pop_heap(maxHeap.begin(), maxHeap.end());
std::pop_heap(maxHeap.begin(), maxHeap.end(), std::greater<int>());

// 插入堆底元素
std::push_heap(maxHeap.begin(), maxHeap.end());
std::push_heap(maxHeap.begin(), maxHeap.end(), std::greater<int>());

void BuildMaxHeap(std::vector<ElementType>& vex)
{
	std::make_heap(vex.begin(), vex.end());
}

void HeapSort(std::vector<ElementType> vex)
{
	BuildMaxHeap(vex);
	for(int i=0; i<vex.size(); ++i)
	{
		printf("%d\n", vex.front());
		std::pop_heap(vex.begin(), vex.end());
	}
}
