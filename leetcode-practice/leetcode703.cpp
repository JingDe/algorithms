


class KthLargest {
private:
	int k;
	std::vector<int> nums;
	int kCached;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
		this->nums.swap(nums);
		//std::make_heap(this->nums.begin(), this->nums.end());
		kCached=INT_MIN;
    }
    
    int add(int val) {
        nums.push_back(val);
		if(kCached==INT_MIN  ||  kCached<=val)
		{			
			kCached=getKth();
		}
		return kCached;
    }
	int getKth()
	{
		debug_print();
		std::push_heap(nums.begin(), nums.end());
		for(int i=0; i<k-1; ++i)
		{
			std::make_heap(nums.begin(), nums.end()-i);			
		}
		debug_print();
		int ans=nums.front();
		return ans;
	}
	void debug_print()
	{
		for(int i=0; i<nums.size(); ++i)
			printf("%d, ", nums[i]);
		printf("[%d]\n", nums.size());
	}
};

class KthLargest {
private:
	int k;
	std::vector<int> nums; // 大根堆
	int kCached;
	
public:
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
		this->nums.swap(nums);
		//std::make_heap(this->nums.begin(), this->nums.end());
		kCached=INT_MIN;
    }
    
    int add(int val) {
		if(kCached!=INT_MIN  &&  kCached<=val)
			nums.push_back(val);
		if(kCached==INT_MIN  ||  kCached<=val)
		{			
			kCached=getKth();
		}
		return kCached;
    }
	int getKth()
	{
		//debug_print();
		std::make_heap(nums.begin(), nums.end());
		nums.resize(k);
		//debug_print();
		for(int i=0; i<k-1; ++i)
		{
			std::pop_heap(nums.begin(), nums.end()-i);			
		}
		//debug_print();
		int ans=nums.front();
		return ans;
	}
	void debug_print()
	{
		for(int i=0; i<nums.size(); ++i)
			printf("%d, ", nums[i]);
		printf("[%d]\n", nums.size());
	}
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
 
// 优先队列方法 
class KthLargest {
private:
	priority_queue<int, vector<int>, greater<int> >  pq; // 最小元素优先队列
	int size;
	
public:
    KthLargest(int k, vector<int>& nums) 
	{
		size=k;
		for(int i=0; i<nums.size(); i++)
		{
			pq.push(nums[i]);
			if(pq.size()>k)
				pq.pop(); // 弹出第k+1, k+2, ...的元素
		}
	}
	int add(int val) 
	{
		pq.push(val);
		if(pq.size()>size)
			pq.pop();
		return pq.top();
	}
 }
 
class KthLargest {
private:
	int k;
	std::vector<int> nums; // 大根堆
	int kCached;
	
public:
    KthLargest(int k, vector<int>& nums) {
        this->k=k;
		this->nums.swap(nums);
		//std::make_heap(this->nums.begin(), this->nums.end());
		kCached=INT_MIN;
    }
    
    int add(int val) {
		if(kCached!=INT_MIN  &&  kCached<=val)
			nums.push_back(val);
		
		{			
			kCached=getKth();
		}
		return kCached;
    }
	int getKth()
	{
		//debug_print();
		std::make_heap(nums.begin(), nums.end());
		nums.resize(k);
		//debug_print();
		for(int i=0; i<k-1; ++i)
		{
			std::pop_heap(nums.begin(), nums.end()-i);			
		}
		//debug_print();
		int ans=nums.front();
		return ans;
	}
	void debug_print()
	{
		for(int i=0; i<nums.size(); ++i)
			printf("%d, ", nums[i]);
		printf("[%d]\n", nums.size());
	}
};