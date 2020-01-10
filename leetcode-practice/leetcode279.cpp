
int numSquares(int n) {
	int dp[n+1];
	dp[0]=0;
	
	for(int i=1; i<=n; ++i)
	{
		dp[i]=i;
		for(int j=1; j*j<=i; j++)
		{
			dp[i]=min(dp[i], dp[i-j*j]+1);
		}
	}
	return dp[n];
}

int numSquares(int n) 
{
	std::queue<pair<int, int> > Q; // 节点表示数字和层数
	Q.push(std::make_pair(n, 1));

	set<int> visited;
	while(!Q.empty())
	{
		std::pair<int,int> cur=Q.front();
		Q.pop();

		for(int i=0; i*i<=cur.first; i++)
		{
			if(cur.first-i*i==0)
				return cur.second;
			Q.push(std::make_pair(cur.first-i*i, cur.second+1));
		}
	}
	return -1;
}

int numSquares(int n) 
{
	std::queue<pair<int, int>> Q;
	Q.push(std::make_pair(0, 0));
	
	set<int> visited;
	visited.insert(0);
	
	while(!Q.empty())
	{
		std::pair<int, int> cur=Q.front();
		Q.pop();
		// if(cur.first==n)
			// return cur.second;
		
		//for(int i=1; cur.first+i*i <= n; i++)
		for(int i=0; cur.first+i*i <= n; i++)
		{
			if(cur.first+i*i==n)
				return cur.second+1;
			
			if(visited.count(cur.first+i*i)==0)
			{
				Q.push(std::make_pair(cur.first+i*i, cur.second+1));
				visited.insert(cur.first+i*i);
			}
		}
	}
	return -1;
}

////////////////////////////
// 静态动态规划
int numSquares(int n) 
{
	if(n<=0)
		return 0;
	
	/*dp[i]表示结果。static数组避免多次调用此函数重复计算。*/
	static vector<int> dp({0});
	
	/*拓展直到遇到n*/
	while(dp.size() <= n)
	{
		int m=dp.size();
		
		// 计算dp[m]，并压入dp[]
		int squares=INT_MAX;
		for(int i=1; i*i<=m; ++i)
		{
			squares=min(squares, dp[m-i*i]+1);
		}
		dp.push_back(squares);
	}
	return dp[n];
}

int numSquares(int n) 
{
	static vector<int> dp({0});
	int m=dp.size();
	dp.resize(max(m, n+1), INT_MAX);
	
	for(int i=1, i2; (i2=i*i)<=n; ++i)
		for(int j=max(m, i2); j<=n; ++j)
			if(dp[j] > dp[j-i2]+1)
				dp[j] = dp[j-i2]+1;
	return dp[n];
}

/////////////////
// BFS
int numSquares(int n) 
{
	if(n<=0)
		return 0;
	
	/*保存所有小于等于n的完全平方数*/
	vector<int> perfectSquares;
	/*dp[i-1]等于i对应的结果*/
	vector<int> dp(n);
	
	for(int i=1; i*i<=n; ++i)
	{
		perfectSquares.push_back(i*i);
		dp[i*i-1]=1;
	}
	
	if(perfectSquares.back()==n)
		return 1;
	
	std::queue<int> Q;
	for(auto& i : perfectSquares)
		Q.push(i);
	
	int curr=1;
	while(!Q.empty())
	{
		curr++;
		
		int sz=Q.size();
		for(int i=0; i<sz; ++i)
		{
			int tmp=Q.front();
			
		}
	}
}

///////////////// 数学方法
int numSquares(int n) 
{
	if(sqrt(n) * sqrt(n) == n)
		return 1;
	
	int n1=n;
	//while(n1 % 4==0)
	while((n1 & 3)==0)
		//n1 /= 4;
		n1 >>= 2;
	//if((n1-7)%8 == 0)
	//if(n % 8 ==7)
	if((n & 7) == 7)
		return 4;
	
	for(int i=1; i*i<=n; i++)
	{
		int left=n-i*i;
		if(sqrt(left) * sqrt(left) == left)
			return 2;
	}
	
	return 3;
}
