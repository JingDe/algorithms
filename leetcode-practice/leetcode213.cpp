int rob(vector<int>& nums) {
	if(nums.empty())
		return 0;
	if(nums.size()==1)
		return nums[0];
	return std::max(rob198(nums, 0, nums.size()-2), rob198(nums, 1, nums.size()-1));
}

int rob198(vector<int>& nums, int start, int end) {
	if(start>end  ||  end>=nums.size())
		return 0;

	int len=end-start+1;
	if(len==0)
		return 0;
	if(len==1)
		return nums[start];
	// if(len==2)
		// return std::max(nums[start], nums[end]);

	int dp[len];
	dp[0]=nums[start];
	dp[1]=nums[start+1];
	for(int i=2; i<len; i++)
	{
		dp[i]=nums[i];
		for(int j=i-2; j>=0; j--)
			if(dp[j]+nums[start+i]>dp[i])	
				dp[i]=dp[j]+nums[start+i];
	}

	int result=INT_MIN;
	for(int i=0; i<len; i++)
		if(dp[i]>result)
			result=dp[i];
	return result;
}