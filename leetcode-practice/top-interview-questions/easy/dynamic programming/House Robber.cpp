class Solution {
public:
    int rob(vector<int>& nums) {
        int len=nums.size();
        if(len==0)
        	return 0;
        if(len==1)
        	return nums[0];
        	
        int dp[len];
        dp[0]=nums[0];
        dp[1]=nums[1];
        for(int i=2; i<len; i++)
        {
        	dp[i]=nums[i];
        	for(int j=i-2; j>=0; j--)
        		if(dp[j]+nums[i]>dp[i])	
        			dp[i]=dp[j]+nums[i];
		}
		
		int result=INT_MIN;
		for(int i=0; i<len; i++)
			if(dp[i]>result)
				result=dp[i];
		return result;
    }
};
