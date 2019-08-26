
int minimumTotal(vector<vector<int>>& triangle) {
	int row=triangle.size();
	int dp[row][row];
	memset(dp, 0, sizeof(dp));
	for(int i=0; i<row; ++i)
		dp[row-1][i]=triangle[row-1][i];
	for(int r=row-2; r>=0; r--)
	{
		for(int c=0; c<=r; ++c)
			dp[r][c]=min(dp[r+1][c], dp[r+1][c+1])+triangle[r][c];
	}
	return dp[0][0];
}

// 优化空间到O(row)
int minimumTotal(vector<vector<int>>& triangle) {
	int row=triangle.size();
	
	int dp[row];
	memset(dp, 0, sizeof(dp));
	for(int i=0; i<row; ++i)
		dp[i]=triangle[row-1][i];
		
	for(int r=row-2; r>=0; r--)
	{
		for(int c=0; c<=r; ++c)
			dp[c]=min(dp[c], dp[c+1])+triangle[r][c];
	}
	return dp[0];
}

