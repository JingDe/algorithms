class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len=nums.size();
        if(len==0)
        	return 0;
        	
        int dp[len];
        dp[0]=nums[0];
        for(int i=1; i<len; i++)
        {        	
    		if(dp[i-1]+nums[i]>nums[i])
				dp[i]=dp[i-1]+nums[i];
			else
				dp[i]=nums[i];
		}
		
		int max=INT_MIN;
		for(int i=0; i<len; i++)
			if(dp[i]>max)
				max=dp[i];
		return max;
    }
    
    int maxSubArray(vector<int>& nums)
    {
    	int len=nums.size();
    	return helper(nums, 0, len-1);
	}
	int helper(vector<int>& nums, int left, int right)
	{
		if(left>right)
			return INT_MIN;
        else if(left==right)
            return nums[left];
		int mid=left+(right-left)/2;
		int res1=helper(nums, left, mid); // ²»ÄÜÊÇmid-1 
		int res2=helper(nums, mid+1, right);
		int res3=helper2(nums, left, right);
        std::cout<<res1<<" "<<res2<<" "<<res3<<std::endl;
		return std::max(std::max(res1, res2), res3);
	}
	int helper2(vector<int>& nums, int left, int right)
	{
		if(left>right)
			return INT_MIN;
        else if(left==right)
            return nums[left];
		int mid=left+(right-left)/2;

		int lsum=INT_MIN;
		int rsum=INT_MIN;
		int sum=0;
		for(int i=mid; i>=left; i--)
		{
			sum+=nums[i];
			if(lsum<sum)
				lsum=sum;
		}
		
		sum=0;
		for(int i=mid+1; i<=right; i++)
		{
			sum+=nums[i];
			if(rsum<sum)
				rsum=sum;
		}
		
		return lsum+rsum;
	}
};
