
int minPathSum(vector<vector<int>>& grid) {
	if(grid.empty())
		return 0;
	int m=grid.size();
	int n=grid[0].size();
	
	int dp[m][n];
	memset(dp, 0, sizeof(dp));
	dp[m-1][n-1]=grid[m-1][n-1];
	
	for(int r=m-1; r>=0; --r)
		for(int c=n-1; c>=0; --c)
		{
			if(r==m-1  &&  c==n-1)
				continue;
			dp[r][c]=INT_MAX;
			if(r+1<m)
				dp[r][c]=std::min(dp[r][c], dp[r+1][c]+grid[r][c]);
			if(c+1<n)
				dp[r][c]=std::min(dp[r][c], dp[r][c+1]+grid[r][c]);
			/* if(r+1==m)
				dp[r][c]=dp[r][c+1]+grid[r][c];
			else if(c+1==n)
				dp[r][c]=dp[r+1][c]+grid[r][c]; */
			
		}
	return dp[0][0];
}