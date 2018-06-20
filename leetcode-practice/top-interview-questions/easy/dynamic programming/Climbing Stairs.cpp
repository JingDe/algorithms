class Solution {
public:
	// 回溯法，超时 
    int climbStairs(int n) {        
		int result=0;
		int cur_sum=0;
		std::vector<int> cur;
		
		helper(n, &result, &cur_sum, cur);
		
		return result;
    }    
    void helper1(int n, int * result, int *cur_sum, std::vector<int> &cur)
    {
    	if(*cur_sum==n)
    		*result++;
    	else
    	{
    		for(int i=1; i<=2; i++)
    		{
    			if(*cur_sum+i<=n)
    			{
    				cur.push_back(i);
    				*cur_sum+=i;
    				helper(n, result, cur_sum, cur);
    				
    				cur.pop_back();
    				*cur_sum-=i;
				}
			}
		}
	}
	
	// 暴力求解 
	int climbStairs(int n)
	{
		return helper2(0, n);
	}
	int helper2(int cur, int n) //  
	{
		if(cur>n)
			return 0;
		if(cur==n)
			return 1;
		return helper2(cur+1, n)+helper2(cur+2, n);
	}
	
	// 有状态递归
	int climbStairs(int n) 
	{
		int state[n]; // state[i]记录共i个台阶的所有路径数目 
		memset(state, 0, sizeof state);
		return helper3(0, n, state);
	}
	int helper3(int cur, int n, int state[])  
	{
		if(cur>n) 
			return 0;
		if(cur==n)
			return 1;
		if(state[cur]>0)
			return state[cur];
		state[cur]=helper3(cur+1, n, state)+helper3(cur+2, n, state);
		return state[cur];
	}
	
	// 动态规划
	int climbStairs(int n) 
	{
		if(n==1)
			return 1;

		int dp[n];
		memset(dp, 0, sizeof dp);
		dp[0]=1;
		dp[1]=2;
		for(int i=2; i<n; i++)
			dp[i]=dp[i-1]+dp[i-2];
		return dp[n-1];
	}
	
	// 动态规划，二
	int climbStairs(int n) 
	{
		if(n==1)
			return 1;
		if(n==2)
			return 2;
			
		int dp[n+1];
		memset(dp, 0, sizeof dp);
		dp[n]=0;
		dp[n-1]=1;
		dp[n-2]=2;
		for(int i=n-3; i>=0; i--)
		{
			dp[i]=dp[i+1]+dp[i+2];
		}
		return dp[0];
	}
	
	// 斐波那契数  
	int climbStairs(int n)
	{
		if(n==1)
			return 1; 
		int first, second;
		first=1;
		second=2;
		for(int i=3; i<=n; i++)
		{
			int temp=first+second;
			first=second;
			second=temp;
		}
		return second;
	}
};
