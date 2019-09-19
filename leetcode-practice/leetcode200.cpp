
// DFS
int numIslands(vector<vector<char>>& grid) {
	int ans=0;
	int row=grid.size();
	if(row==0)
		return 0;
	int col=grid[0].size();
	vector<vector<int>> visited(row, vector<int>(col, 0));
	for(int i=0; i<row; ++i)
		for(int j=0; j<col; ++j)
			if(visited[i][j]==false  &&  grid[i][j]=='1')
			{
				dfs(grid, row, col, i, j, visited);
				ans++;
			}
	return ans;
}
// DFS递归
void dfs1(const vector<vector<char>>& grid, int row, int col, int i, int j, vector<vector<int>>& visited)
{
	visited[i][j]=true;
	if(i-1>=0  &&  visited[i-1][j]==false  &&  grid[i-1][j]=='1')
		dfs(grid, row, col, i-1, j, visited);
	if(i+1<row  &&  visited[i+1][j]==false  &&  grid[i+1][j]=='1')
		dfs(grid, row, col, i+1, j, visited);
	if(j-1>0  &&  visited[i][j-1]==false  &&  grid[i][j-1]=='1')
		dfs(grid, row, col, i, j-1, visited);
	if(j+1<col  &&  visited[i][j+1]==false  &&  grid[i][j+1]=='1')
		dfs(grid, row, col, i, j+1, visited);
}
// DFS非递归,方法一
void dfs2(const vector<vector<char>>& grid, int row, int col, int i, int j, vector<vector<int>>& visited)
{
	stack<pair<int,int>> S;
	S.push(std::make_pair<int,int>(i, j));
	while(!S.empty())
	{
		std::pair<int, int> tmp=S.top();
		S.pop();
		visited[tmp.first][tmp.second]=true;
		
		// TODO
		i=tmp.first;
		j=tmp.second;
		
		if(i-1>=0  &&  visited[i-1][j]==false  &&  grid[i-1][j]=='1')
			S.push(std::make_pair<int,int>(i-1, j));
		if(i+1<row  &&  visited[i+1][j]==false  &&  grid[i+1][j]=='1')
			S.push(std::make_pair<int,int>(i+1, j));
		if(j-1>=0  &&  visited[i][j-1]==false  &&  grid[i][j-1]=='1')
			S.push(std::make_pair<int,int>(i, j-1));
		if(j+1<col  &&  visited[i][j+1]==false  &&  grid[i][j+1]=='1')
			S.push(std::make_pair<int,int>(i, j+1));
	}
}

// DFS非递归,方法2
void dfs3(const vector<vector<char>>& grid, int row, int col, int i, int j, vector<vector<int>>& visited)
{
	stack<pair<int,int>> S;
	S.push(std::make_pair<int,int>(i, j));
	while(!S.empty())
	{
		std::pair<int, int> tmp=S.top();
		visited[tmp.first][tmp.second]=true;		
		
		// TODO
		i=tmp.first;
		j=tmp.second;
		
		if(i-1>=0  &&  visited[i-1][j]==false  &&  grid[i-1][j]=='1')
		{
			S.push(std::make_pair<int,int>(i-1, j));
			continue;
		}
		if(i+1<row  &&  visited[i+1][j]==false  &&  grid[i+1][j]=='1')
		{
			S.push(std::make_pair<int,int>(i+1, j));
			continue;
		}
		if(j-1>=0  &&  visited[i][j-1]==false  &&  grid[i][j-1]=='1')
		{
			S.push(std::make_pair<int,int>(i, j-1));
			continue;
		}
		if(j+1<col  &&  visited[i][j+1]==false  &&  grid[i][j+1]=='1')
		{
			S.push(std::make_pair<int,int>(i, j+1));
			continue;
		}
		
		S.pop();		
	}
}

[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]
[["1","1","1"],["0","1","0"],["1","1","1"]]

// BFS
int numIslands(vector<vector<char>>& grid) {
	int ans=0;
	int row=grid.size();
	if(row==0)
		return 0;
	int col=grid[0].size();
	vector<vector<int>> visited(row, vector<int>(col, 0));
	for(int i=0; i<row; ++i)
		for(int j=0; j<col; ++j)
			if(visited[i][j]==false  &&  grid[i][j]=='1')
			{
				bfs(grid, row, col, i, j, visited);
				ans++;
			}
	return ans;
}

void bfs()
{
	
}