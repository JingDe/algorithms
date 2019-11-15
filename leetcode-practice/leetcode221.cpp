

int maximalSquare(vector<vector<char>>& matrix) {
	int row=matrix.size();
	if(row==0)
		return 0;
	int col=matrix[0].size();
	if(col==0)
		return 0;

	int ans=0;
	int dp[row][col];
	memset(dp, 0, sizeof(dp));
	for(int j=0; j<col; ++j)
	{
		dp[0][j]=matrix[0][j]-'0';
		printf("dp[0][%d] = %d\n", j, dp[0][j]);
		ans=std::max(dp[0][j], ans);
	}
	for(int i=0; i<row; ++i)
	{
		dp[i][0]=matrix[i][0]-'0';
		printf("dp[%d][0] = %d\n", i, dp[i][0]);
		ans=std::max(dp[i][0], ans);
	}

	for(int i=1; i<row; ++i)
	{
		for(int j=1; j<col; ++j)
		{
			if(matrix[i][j]-'0'==0)
				dp[i][j]=0;
			else
			{
				int x=1;
				for( x=1; x<=j  &&  matrix[i][j-x]-'0'==1; x++)
				{}
				int y=1;
				for( y=1; y<=i  &&  matrix[i-y][j]-'0'==1; y++)
				{}
				dp[i][j]=std::min(std::min(x, y), dp[i-1][j-1]+1);
				printf("%d,%d : x=%d, y=%d, dp[%d][%d]=%d -> %d\n", i, j, x, y, i-1, j-1, dp[i-1][j-1], dp[i][j]);
				ans=std::max(dp[i][j], ans);
			}
		}
	}
	return ans*ans;
}

// 暴力法
int maximalSquare(vector<vector<char>>& matrix) 
{
	int rows=maxtrix.length;
	int cols=rows>0 ?  matrix[0].size() : 0;
	
	int maxsqlen=0;
	for(int i=0; i<rows; ++i)
	{
		for(int j=0; j<cols; ++j)
		{
			if(matrix[i][j]=='1')
			{
				int sqlen=1; // 从正方形的长度为1开始遍历
				bool flag=true;
				while(sqlen+i<rows  &&  sqlen+j<cols  && flag)
				{
					for(int k=j; k<=sqlen+j; k++)
					{
						if(matrix[i+sqlen][j]=='0')
						{
							flag=false;
							break;
						}
					}
					for(int k=i; k<=sqlen+i; k++)
					{
						if(matrix[k][j+sqlen]=='0')
						{
							flag=false;
							break;
						}
					}
					if(flag)
						sqlen++;					
				}
				if(maxsqlen<sqlen)
					maxsqlen=sqlen;
			}
		}
	}
	return maxsqlen*maxsqlen;
}

// 动态规划：二维
int maximalSquare(vector<vector<char>>& matrix) {
	if(matrix.size()==0  ||  matrix[0].size()==0)
		return 0;
	int rows=matrix.size();
	int cols=matrix[0].size();


	int ans=0;
	int dp[rows][cols];
	memset(dp, 0, sizeof(dp));
	for(int j=0; j<col; ++j)
	{
		dp[0][j]=matrix[0][j]-'0';
		ans=std::max(dp[0][j], ans);
	}
	for(int i=0; i<row; ++i)
	{
		dp[i][0]=matrix[i][0]-'0';
		ans=std::max(dp[i][0], ans);
	}

	for(int i=1; i<row; ++i)
	{
		for(int j=1; j<col; ++j)
		{
			if(matrix[i][j]-'0')
			{
				dp[i][j]=std::min(std::min(dp[i-1][j], dp[i-1][j-1]), dp[i][j-1])+1;
				ans=std::max(dp[i][j], ans);
			}
		}
	}
	
	return ans*ans;
}

// 一维动态规划
int maximalSquare(vector<vector<char>>& matrix) 
{
	if(matrix.size()==0  ||  matrix[0].size()==0)
		return 0;
	int rows=matrix.size();
	int cols=matrix[0].size();
	
	int ans=0;
	int dp[cols];
	memset(dp, 0, sizeof(dp));
	
	for(int row=0; row<rows; ++row)
	{
		for(int col=0; col<cols; ++col)
		{
			if(matrix[i][j]-'0')
			{
				dp[col]=
			}
		}
	}
}

int maximalSquare(vector<vector<char>>& matrix) 
{
	int rows=matrix.size();
	int cols=rows>0 ? matrix[0].size() :  0;
	
	int dp[cols+1];
	memset(dp, 0, sizeof(dp));
	
	int maxsqlen=0;
	int prev=0;
	for(int i=1; i<=rows; ++i)
	{
		for(int j=1; j<=cols; ++j)
		{
			int temp=dp[j]; // temp保存的是dp[i-1][j]
			if(matrix[i-1][j-1]=='1')
			{
				dp[j]=std::min(std::min(dp[j-1], prev), dp[j])+1;
				// min(dp[i][j-1], prev, dp[i-1][j]) + 1
				maxsqlen=std::max(maxsqlen, dp[j]);
			}
			else
			{
				dp[j]=0;
			}
			prev=temp; // 求出了dp[i][j], prev保存了dp[i-1][j], 下一个求dp[i][j+1]
		}
	}
	return maxsqlen*maxsqlen;
}