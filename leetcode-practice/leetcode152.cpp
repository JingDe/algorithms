
int maxProduct(vector<int>& nums) {
	if(nums.empty())
		return 0;
	
	int dp[nums.size()];
	dp[0]=nums[0];
	int ans=dp[0];
	for(int i=1; i<nums.size(); ++i)
	{
		dp[i]=nums[i];
		if(dp[i-1]*nums[i] > nums[i])
			dp[i]=dp[i-1]*nums[i];
		if(dp[i]>ans)
			ans=dp[i];
	}
	return ans;
}


int maxProduct(vector<int>& nums) {
	int max, imax, imin;
	if(nums.empty())
		return 0;
	imax=nums[0];
	imin=nums[0];
	max=nums[0];
	for(int i=1; i<nums.size(); ++i)
	{
		if(nums[i]<0)
			std::swap(imax, imin);
		imax=std::max(imax*nums[i], imax);
		imin=std::min(imin*nums[i], imin);
		max=std::max(max, imax);
	}
	return max;
}