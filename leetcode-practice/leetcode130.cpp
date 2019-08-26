


bool checkEdge(int i, int j, int m, int n)
{
	if(i==0  ||  i==m-1  ||  j==0  || j==n-1)
		return true;
	return false;
}
void solve(vector<vector<char>>& board) {
	if(board.empty())
		return;
	int m=board.size();
	int n=board[0].size();
	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			bool isEdge=checkEdge(i, j, m, n);
			if(isEdge  &&  board[i][j]=='O')
				//dfs(board, i, j);
				dfs2(board, i, j);	
				bfs(board, i, j);
				bfs2(board, i, j);
		}
	}
	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(board[i][j]=='O')
				board[i][j]='X';
			if(board[i][j]=='#')
				board[i][j]='O';
		}
	}
}

// DFS递归
void dfs(vector<vector<char>>& board, int i, int j)
{
	if(i<0  ||  j<0  ||  i>=board.size()  ||  j>=board[0].size()  ||  board[i][j]=='X'  ||  board[i][j]=='#')
		return;
	
	board[i][j]='#';
	dfs(board, i-1, j);
	dfs(board, i+1, j);
	dfs(board, i, j-1);
	dfs(board, i, j+1);
}

// DFS非递归
struct Point{
	int x, int y;
	Point(int x, int y)
	{
		this->x=x;
		this->y=y;
	}
};

void dfs2(vector<vector<char>>& board, int i, int j)
{
	int m=board.size();
	int n=board[0].size();
	stack<Point> S;
	S.push(Point(i, j));
	while(!S.empty())
	{
		Point cur=S.top();
		S.pop();

		board[cur.x][cur.y]='#';

		if(cur.x>0  &&  board[cur.x-1][cur.y]=='O')
			S.push(Point(cur.x-1, cur.y));
		if(cur.x+1<m  &&  board[cur.x+1][cur.y]=='O')
			S.push(Point(cur.x+1, cur.y));
		if(cur.y>0  &&  board[cur.x][cur.y-1]=='O')
			S.push(Point(cur.x, cur.y-1));
		if(cur.y+1<n  &&  board[cur.x][cur.y+1]=='O')
			S.push(Point(cur.x, cur.y+1));
	}
}
// DFS非递归的另一种写法
void dfs3(vector<vector<char>>& board, int i, int j)
{
	int m=board.size();
	int n=board[0].size();
	stack<Point> S;
	S.push(Point(i, j));
	while(!S.empty())
	{
		Point cur=S.top();
		//S.pop();

		board[cur.x][cur.y]='#';

		if(cur.x>0  &&  board[cur.x-1][cur.y]=='O')
		{
			S.push(Point(cur.x-1, cur.y));
			continue;
		}
		if(cur.x+1<m  &&  board[cur.x+1][cur.y]=='O')
		{
			S.push(Point(cur.x+1, cur.y));
			continue;
		}
		if(cur.y>0  &&  board[cur.x][cur.y-1]=='O')
		{
			S.push(Point(cur.x, cur.y-1));
			continue;
		}
		if(cur.y+1<n  &&  board[cur.x][cur.y+1]=='O')
		{
			S.push(Point(cur.x, cur.y+1));
			continue;
		}
		S.pop();
	}
}


// BFS非递归
void bfs2(vector<vector<char>>& board, int i, int j)
{
	int m=board.size();
	int n=board[0].size();
	queue<Point> Q;
	Q.push(Point(i, j));
	while(!Q.empty())
	{
		Point cur=Q.front();
		Q.pop();
		
		board[cur.x][cur.y]='#';

		if(cur.x>0  &&  board[cur.x-1][cur.y]=='O')
			Q.push(Point(cur.x-1, cur.y));
		if(cur.x+1<m  &&  board[cur.x+1][cur.y]=='O')
			Q.push(Point(cur.x+1, cur.y));
		if(cur.y>0  &&  board[cur.x][cur.y-1]=='O')
			Q.push(Point(cur.x, cur.y-1));
		if(cur.y+1<n  &&  board[cur.x][cur.y+1]=='O')
			Q.push(Point(cur.x, cur.y+1));
	}
}
void bfs2(vector<vector<char>>& board, int i, int j)
{
	int m=board.size();
	int n=board[0].size();
	queue<Point> Q;
	Q.push(Point(i, j));
	board[i][j]='#';
	while(!Q.empty())
	{
		Point cur=Q.front();
		Q.pop();
		
		//board[cur.x][cur.y]='#';

		if(cur.x>0  &&  board[cur.x-1][cur.y]=='O')
		{
			board[cur.x-1][cur.y]='#';
			Q.push(Point(cur.x-1, cur.y));
		}
		if(cur.x+1<m  &&  board[cur.x+1][cur.y]=='O')
		{
			board[cur.x+1][cur.y]='#';
			Q.push(Point(cur.x+1, cur.y));
		}
		if(cur.y>0  &&  board[cur.x][cur.y-1]=='O')
		{
			board[cur.x][cur.y-1]='#';
			Q.push(Point(cur.x, cur.y-1));
		}
		if(cur.y+1<n  &&  board[cur.x][cur.y+1]=='O')
		{
			board[cur.x][cur.y+1]='#';
			Q.push(Point(cur.x, cur.y+1));
		}
	}
}

// BFS递归
// void bfs(vector<vector<char>>& board, int i, int j)
// {
	// if(i<0  ||  j<0  ||  i>=board.size()  ||  j>=board[0].size()  ||  board[i][j]=='X'  ||  board[i][j]=='#')
		// return;
	// board[i][j]='#';
	
	// bfs(board, i-1, j);
	// bfs(board, i+1, j);
	// bfs(board, i, j-1);
	// bfs(board, i, j+1);
// }


// 并查集方法
class UnionFind{
	vector<int> parents;
	UnionFind(int totalNodes)
	{
		parents.reserve(totalNodes);
		for(int i=0; i<totalNodes; ++i)
			parents[i]=i;
	}
	void Union(int m, int n)
	{
		int root1=find(m);
		int root2=find(n);
		if(root1 !=root2)
			parents[root2]=root1;
	}
	int find(int node)
	{
		while(parents[node]!=node)
		{
			parents[node]=parents[parents[node]];
			node=parent[node];
		}
		return node;
	}
	bool isConnected(int m, int n)
	{
		return find(m)==find(n);
	}
};


void solve(vector<vector<char>>& board)
{
	if(board.empty())
		return ;
	int rows=board.size();
	cols=board[0].size();

	UnionFind uf(rows*cols+1);
	int dummyNode=rows*cols; // 虚拟节点，作为所有边界O节点的父节点

	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<cols; ++j)
		{
			if(board[i][j]=='O')
			{
				// 边界上的O，和dummyNode合并成一个连通区域
				if(i==0  ||  i==rows-1  ||  j==0  ||  j==cols-1)
					uf.Union(node(i, j), dummyNode);
				else
				{
					// 和上下左右的O连成一个连通区域
					if(i>0  &&  board[i-1][j]=='O')
						uf.Union(node(i, j), node(i-1, j));
					if(i<rows-1  &&  board[i+1][j]=='O')
						uf.Union(node(i, j), node(i+1, j));
					if(j>0  &&  board[i][j-1]=='O')
						uf.Union(node(i, j), node(i, j-1));
					if(j<cols-1  &&  board[i][j+1]=='O')
						uf.Union(node(i, j), node(i, j+1));
				}
			}
		}
	}

	for(int i=0; i<rows; ++i)
		for(int j=0; j<cols; ++j)
		{
			if(uf.isConnected(node(i,j), dummyNode))
				board[i][j]='O';
			else
				board[i][j]='X';
		}
}

int node(int i, int j)
{
	return i*cols+j;
}

// union find 实现2
class UnionFind
{
private:
	int* id;     // id[i] = parent of i
	int* rank;  // rank[i] = rank of subtree rooted at i (cannot be more than 31)
	int count;    // number of components
public:
	UnionFind(int N)
	{
		count = N;
		id = new int[N];
		rank = new int[N];
		for (int i = 0; i < N; i++) {
			id[i] = i;
			rank[i] = 0;
		}
	}
	~UnionFind()
	{
		delete [] id;
		delete [] rank;
	}
	int find(int p) {
		while (p != id[p]) {
			id[p] = id[id[p]];    // path compression by halving
			p = id[p];
		}
		return p;
	}
	int getCount() {
		return count;
	}
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}
	void Union(int p, int q) {
		int i = find(p);
		int j = find(q);
		if (i == j) return;
		if (rank[i] < rank[j]) id[i] = j;
		else if (rank[i] > rank[j]) id[j] = i;
		else {
			id[j] = i;
			rank[i]++;
		}
		count--;
	}
};