

// 方法一： 实现堆数据结构
int findKthLargest(vector<int>& nums, int k) 
{
	if(nums.empty())
		return 0;
	
	int cur=-1;
	vector<int> minHeap;
	
	while(++cur<nums.size())
	{
		printf("check %d\n", checkMinHeap(minHeap));
		if(minHeap.size()<k)
		{
			insertHeap(minHeap, nums[cur]);
		}
		else
		{
			if(getHeapFirst(minHeap)>=nums[cur])
				continue;
			deleteHeapFirst(minHeap);
			printf("check %d\n", checkMinHeap(minHeap));
			insertHeap(minHeap, nums[cur]);
		}
	}
	
	return getHeapFirst(minHeap);
}

// minHeap从0开始存储元素，下标为a的节点的子节点的下标分别是2a+1和2a+2
// 下标为x的节点的父节点下标是(x-1)/2
void insertHeap(vector<int>& minHeap, int key)
{
	minHeap.push_back(key);
	adjustUp(minHeap);
}
// 将minHeap最后一个元素向上调整到合适位置
// void adjustUp(vector<int>& minHeap)
// {
	// int val=minHeap.back();
	// int idx=minHeap.size()-1;
	
	// int parent=(idx-1)/2;
	// while(parent>=0  &&  minHeap[parent]>val)
	// {
		// minHeap[idx]=minHeap[parent];
		// idx=parent;
		// if(idx==0)
			// break;
		// parent=(idx-1)/2;
	// }
	// minHeap[idx]=val;
// }
void adjustUp(vector<int>& minHeap)
{
	int val=minHeap.back();
	int idx=minHeap.size()-1;
	
	int parent=(idx-1)/2;
	while(idx>0  &&  minHeap[parent]>val)
	{
		minHeap[idx]=minHeap[parent];
		idx=parent;
		parent=(idx-1)/2;
	}
	minHeap[idx]=val;
}

int getHeapFirst(const vector<int>& minHeap)
{
	return minHeap[0];
}

void deleteHeapFirst(vector<int>& minHeap)
{
	if(minHeap.size()==1)
	{
		minHeap.clear();
		return;
	}
	minHeap[0]=minHeap.back();
	minHeap.pop_back();
	
	adjustDown(minHeap, 0);
}

void adjustDown(vector<int>& minHeap, int root)
{
	int val=minHeap[root];
	int cur=root*2+1;
	while(cur<minHeap.size())
	{
		if(cur+1<minHeap.size()  &&  minHeap[cur]>minHeap[cur+1])
			cur++;
		if(minHeap[cur]>=val)
			break;
		minHeap[root]=minHeap[cur];
		root=cur;
		cur=cur*2+1;
	}
	minHeap[root]=val;
}

bool find(vector<int>& minHeap, int key)
{
	return findFromRoot(minHeap, 0, key);
}

bool findFromRoot(vector<int>& minHeap, int root, int key)
{
	if(root>=minHeap.size())
		return false;
	
	if(minHeap[root]==key)
		return true;
	if(minHeap[root]>key)
		return false;
	if(root*2<minHeap.size()  &&  findFromRoot(minHeap, root*2, key))
		return true;
	if(root*2+1<minHeap.size()  &&  findFromRoot(minHeap, root*2+1, key))
		return true;
	return false;
}

bool checkMinHeap(const std::vector<int>& minHeap)
{
	for(int i=0; i*2+1<minHeap.size(); i++)
	{
		if(minHeap[i*2+1]<minHeap[i])
			return false;
		if(i*2+2<minHeap.size()  &&  minHeap[i*2+1]<minHeap[i])
			return false;
	}
	return true;
}
