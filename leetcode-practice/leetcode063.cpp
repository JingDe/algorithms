

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
	if(obstacleGrid.empty())
		return 0;
	int m=obstacleGrid.size();
	int n=obstacleGrid[0].size();

	vector<vector<long long> > paths(m, vector<long long>(n)); // path[i][j]表示从起点到达i,j位置的路径的个数
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			paths[i][j]=0;
	if(obstacleGrid[0][0]==1)
		return 0;
	paths[0][0]=1;

	for(int r=0; r<m; ++r)
		for(int c=0; c<n; ++c)
		{
			if(r==0  &&  c==0)
				continue;
			if(obstacleGrid[r][c]==1)
			{
				paths[r][c]=0;
				continue;
			}
			paths[r][c]=0;
			if(r-1>=0  &&  obstacleGrid[r-1][c]==0)
				paths[r][c]+=paths[r-1][c];
			if(c-1>=0  &&  obstacleGrid[r][c-1]==0)
				paths[r][c]+=paths[r][c-1];
		}
	return paths[m-1][n-1];
}