
// 暴力法
int majorityElement(vector<int>& nums) {
	for(int i=0; i<nums.size(); ++i)
	{
		int val=nums[i];
		int count=0;
		
		for(int j=0; j<nums.size(); ++j)
		{
			if(nums[j]==val)
				count++;
		}
		if(count>=nums.size()/2)
			return val;
	}
	return 0;
}

// 哈希表
int majorityElement(vector<int>& nums) {
	if(nums.empty())
		return 0;
	map<int, int> occur;
	int max_occur=nums[0];
	for(int i=1; i<nums.size(); ++i)
	{
		occur[nums[i]]++;
		if(occur[nums[i]]>occur[max_occur])
			max_occur=nums[i];
	}
	return max_occur;
}

// 排序
int majorityElement(vector<int>& nums) 
{
	std::sort(nums.begin(), nums.end());
	return nums[nums.size()/2];
}

// 随机化
int majorityElement(vector<int>& nums) {
	if(nums.empty())
		return 0;
	int len=nums.size();
	while(true)
	{
		int idx=std::rand()%len;
		if(occurCount(nums[idx], nums) > nums.size()/2)
			return nums[idx];
		std::swap(nums[idx], nums[len-1]);
		len--;
	}
	return 0;
}
int occurCount(int val, const vector<int>& nums)
{
	int cnt=0;
	for(int i=0; i<nums.size(); ++i)
		if(nums[i]==val)
			++cnt;
	return cnt;
}

// 分治
int majorityElement(vector<int>& nums) 
{
	return helper(nums, 0, nums.size()-1);
}

int helper(const vector<int>& nums, int start, int end)
{
	if(start>end)
		return 0;
	if(start==end)
		return nums[start];
	int mid=start+(end-start)/2;
	int left=helper(nums, start, mid);
	int right=helper(nums, mid+1, end);
	if(left==right)
		return left;
	int left_cnt=occurCount(left, nums, start, mid);
	int right_cnt=occurCount(right, nums, mid+1, end);
	return left_cnt>right_cnt ? left : right;
}
int occurCount(int val, const vector<int>& nums, int start, int end)
{
	int cnt=0;
	for(int i=start; i<=end; ++i)
		if(nums[i]==val)
			++cnt;
	return cnt;
}


// 投票算法
int majorityElement(vector<int>& nums) 
{
	if(nums.empty())
		return 0;
	int candidate=0;
	int counter=0;
	for(int i=0; i<nums.size(); ++i)
	{
		if(counter==0)
		{
			candidate=nums[i];
			counter++;
		}
		else
		{
			if(nums[i]==candidate)
				counter++;
			else
				counter--;
		}
	}
	return candidate;
}