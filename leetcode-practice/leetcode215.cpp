

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        
    }
};


// 方法一： 实现堆数据结构



// 方法二：使用make_heap等
int findKthLargest(vector<int>& nums, int k) 
{
	if(nums.empty())
		return 0;
	
	int cur=-1;
	std::vector<int> maxHeap;
	
	while(++cur<nums.size())
	{
		if(std::find(maxHeap.begin(), maxHeap.end(), nums[cur])!=maxHeap.end())
			continue;
		if(maxHeap.size()<k)
		{
			maxHeap.push_back(nums[cur]);
			std::push_heap(maxHeap.begin(), maxHeap.end());
		}
		else
		{			
			if(maxHeap[0]<nums[cur])
				continue;			
			std::pop_heap(maxHeap.begin(), maxHeap.end());
			maxHeap.back()=nums[cur];
			std::push_heap(maxHeap.begin(), maxHeap.end());
		}
	}
	
	return maxHeap[0];
}

int findKthLargest(vector<int>& nums, int k) 
{
	if(nums.empty())
		return 0;
	
	int cur=-1;
	std::vector<int> minHeap;
	
	while(++cur<nums.size())
	{
		// if(std::find(minHeap.begin(), minHeap.end(), nums[cur])!=minHeap.end())
			// continue;
		if(minHeap.size()<k)
		{
			minHeap.push_back(nums[cur]);
			std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
		}
		else
		{			
			if(minHeap[0]>nums[cur])
				continue;			
			std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
			minHeap.back()=nums[cur];
			std::push_heap(minHeap.begin(), minHeap.end(), std::greater<int>());
		}
	}
	
	return minHeap[0];
}

// 方法三：使用priority_queue
int findKthLargest(vector<int>& nums, int k) 
{
	if(nums.empty())
		return 0;
	
	int cur=-1;
	std::priority_queue<int> maxQueue;
	std::set<int> elems;
	
	while(++cur<nums.size())
	{
		if(elems.count(nums[cur]))
			continue;
		if(maxQueue.size()<k)
		{
			maxQueue.push(nums[cur]);
		}
		else
		{
			if(maxQueue.top()<=nums[cur])
				continue;			
			maxQueue.pop();
			maxQueue.push(nums[cur]);
		}
	}
	
	return maxQueue.top();
}


int findKthLargest(vector<int>& nums, int k) 
{
	if(nums.empty())
		return 0;
	
	int cur=-1;
	std::priority_queue<int, std::vector<int>, std::greater<int>> minQueue;
	std::set<int> elems;
	
	while(++cur<nums.size())
	{
		print(minQueue);
		if(elems.count(nums[cur]))
			continue;
		if(minQueue.size()<k)
		{
			minQueue.push(nums[cur]);
		}
		else
		{
			if(minQueue.top()>=nums[cur])
				continue;			
			elems.erase(minQueue.top());	
			minQueue.pop();
			minQueue.push(nums[cur]);
			elems.insert(nums[cur]);
		}
	}
	
	return minQueue.top();
}

void print(const std::priority_queue<int, std::vector<int>, std::greater<int>>& minQueue)
{
	std::priority_queue<int, std::vector<int>, std::greater<int>> tmp=minQueue;
	while(tmp.empty()==false)
	{
		printf("%d, ", tmp.top());
		tmp.pop();
	}
	printf("\n");
}

