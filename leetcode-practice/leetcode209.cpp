
int minSubArrayLen(int s, vector<int>& nums) {
	if(nums.empty())
		return 0;
	int ans=0;
	int start=0;
	int end=0;
	int sum=nums[0];
	while(true)
	{
		while(sum<s  &&  end<nums.size()-1)
		{
			sum+=nums[++end];
		}
		if(sum<s)
			break;
		if(ans==0  ||  ans > end-start+1)
			ans=end-start+1;
		
		int tmp=start;
		while(sum>=s)
		{
			sum-=nums[start++];
		}
		if(ans > end-start+2)
			ans=end-start+2;
		
		if(start==tmp)
			start++;
	}
	return ans;
}

// 暴力法
int minSubArrayLen(int s, vector<int>& nums)
{
	int ans=INT_MAX;
	for(int i=0; i<nums.size(); ++i)
		for(int j=i; j<nums.size(); ++j)
		{
			int sum=getSum(nums, i, j);
			if(sum>=s  &&  ans>j-i+1)
			{
				ans=j-i+1;
				break;
			}
		}
	return ans;
}

// 暴力法的优化
int minSubArrayLen(int s, vector<int>& nums)
{
	if(nums.empty())
		return 0;
	int ans=INT_MAX;
	int sum[nums.size()];
	sum[0]=nums[0];
	for(int i=1; i<nums.size(); ++i)
	{
		sum[i]=sum[i-1]+nums[i];
	}
	
	for(int i=0; i<nums.size(); ++i)
		for(int j=i; j<nums.size(); ++j)
		{
			int sum=sum[j]-sum[i]+nums[i];
			if(sum>=s  &&  ans>j-i+1)
			{
				ans=j-i+1;
				break;
			}
		}
	return ans;
}

// 二分法
int minSubArrayLen(int s, vector<int>& nums)
{
	if(nums.empty())
		return 0;
	int ans=INT_MAX;
	//int sums[nums.size()];
	vector<int> sums(n+1, 0); // sums[i]表示前i个元素的总和（0到i-1）
	//sums[0]=nums[0];
	sums[0]=0;
	for(int i=1; i<nums.size(); ++i)
	{
		//sums[i]=sums[i-1]+nums[i];
		sums[i]=sums[i-1]+nums[i-1];
	}
	
	for(int i=1; i<=nums.size(); ++i)
	{
		// 从i到j的子数组和，sums[j]-sums[i]+nums[i]=sums[j]-sums[i-1]
		// 找到最小的j，满足 sums[j]-sums[i-1]>=s, sums[j]>=sums[i-1]+s
		int to_find = s+sums[i-1];
		auto bound = std::lower_bound(sums.begin(), sums.end(), to_find);
		if(bound!=sums.end())
			ans=std::min(ans, static_cast<int>(bound-(sums.begin()+i-1)));
	}
	return ans!=INT_MAX ? ans : 0;
}

