

// 方法一：回溯，保存中间结果
int UNKNOWN=-1;
	
int uniquePaths(int m, int n) {
	//int paths[m][n]; // path[i][j]表示从i,j位置到达终点的路径个数
	vector<vector<int> > paths(m, vector<int>(n));
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			paths[i][j]=UNKNOWN;
	paths[m-1][n-1]=1;
	
	backtracking(0, 0, m, n, paths);
	return paths[0][0];
}

void backtracking(int r, int c, int m, int n, vector<vector<int>>& paths)
{
	if(paths[r][c]!=UNKNOWN)
		return;
	
	if(r+1<m)
		backtracking(r+1, c, m, n, paths);
	if(c+1<n)
		backtracking(r, c+1, m, n, paths);
	
	paths[r][c]=0;
	if(r+1<m)
		paths[r][c]+=paths[r+1][c];
	if(c+1<n)
		paths[r][c]+=paths[r][c+1];
}

// 方法二：回溯，不保存中间结果
int uniquePaths(int m, int n) {
	int path=backtracking(0, 0, m, n);
	return path;
}

int backtracking(int r, int c, int m, int n)
{	
	if(r==m-1  &&  c==n-1)
		return 1;
	int path=0;
	if(r+1<m)
		path+=backtracking(r+1, c, m, n);
	if(c+1<n)
		path+=backtracking(r, c+1, m, n);

	return path;
}


// 方法三：动态规划，从终点到起点
int uniquePaths(int m, int n) {
	vector<vector<int> > paths(m, vector<int>(n));
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			paths[i][j]=UNKNOWN;
	paths[m-1][n-1]=1;
	
	for(int r=m-1; r>=0; --r)
		for(int c=n-1; c>=0; --c)
		{
			if(r==m-1  &&  c==n-1)
				continue;
			paths[r][c]=0;
			if(r+1<m)
				paths[r][c]+=paths[r+1][c];
			if(c+1<n)
				paths[r][c]+=paths[r][c+1];
		}
	return paths[0][0];
}



// 方法四：从起点到终点动态规划
int uniquePaths(int m, int n) {
	vector<vector<int> > paths(m, vector<int>(n)); // path[i][j]表示从起点到达i,j位置的路径的个数
	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			paths[i][j]=UNKNOWN;
	paths[0][0]=1;
	
	for(int r=0; r<m; ++r)
		for(int c=0; c<n; ++c)
		{
			if(r==0  &&  c==0)
				continue;
			
			paths[r][c]=0;
			if(r-1>=0)
				paths[r][c]+=paths[r-1][c];
			if(c-1>=0)
				paths[r][c]+=paths[r][c-1];
		}
	return paths[m-1][n-1];
}
