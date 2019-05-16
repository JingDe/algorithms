#include<stdio.h>
#include<errno.h>
#include<string.h>

struct State{
	int number;
	int volume;
	State():number(0),volume(0){}
	State(int n, int v):number(n),volume(v){}
	State& operator=(const State& rhs)
	{
		number=rhs.number;
		volume=rhs.volume;
		return *this;
	}
};


// 0/1背包, n个物体，第i个的体积是V[i-1]、重量是W[i-1]。将其装入总容量为C的背包中，求最大重量
int beibao1(int V[], int W[], int n, int C)
{
	int dp[n+1][C+1]; // dp[i][j]表示将前i个物体装入容量为j的背包的最大重量
	// dp[0][]=0
	// dp[i][j]=max(dp[i-1][j], dp[i-1][j-V[i-1]]+W[i-1])
	bool take[n+1][C+1];
	State state[n+1][C+1];
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=C; ++j)
		{
			take[i][j]=false;
			state[i][j]= (i==0) ? State(-1, -1) : State(i-1, j);			
			dp[i][j]= (i==0) ? 0 : dp[i-1][j];
			
			if(i>0  &&  j>=V[i-1]  &&  dp[i-1][j-V[i-1]]+W[i-1]>dp[i][j])
			{
				dp[i][j]=dp[i-1][j-V[i-1]]+W[i-1];
				take[i][j]=true; // 状态dp[i][j]装入第i-1个物体
				state[i][j]=State(i-1, j-V[i-1]); // 状态dp[i][j]的前一状态是dp[i-1][j-V[i-1]]
			}
			//printf("dp[%d][%d]=%d\n", i, j, dp[i][j]);
		}
	
	// 打印路径方法一：
	printf("print result with take[]\n");
	for(int i=n, j=C; i>=1  &&  j>=0; --i)
	{
		if(take[i][j])
		{
			printf("(%d,%d)\t", V[i-1], W[i-1]);
			j=j-V[i-1];
		}
	}
	printf("\n");
	
	// 打印路径方法二：
	{
		printf("print result with State[][]\n");
		//State s=state[n][C];
		State s(n, C); // 从最终状态dp[n][C]开始
		//printf("s.number, s.volume = %d, %d, (%d, %d), %d\n", s.number, s.volume, n, C, dp[n][C]);
		for(; s.number>0; s=state[s.number][s.volume])
		{
			// 仍然根据dp[i][j]比较dp[i-1][j]判断是否装了V[i-1]W[i-1]
			if(dp[s.number][s.volume] > dp[s.number-1][s.volume])
				printf("%d(%d,%d)\t", s.number-1, V[s.number-1], W[s.number-1]);
		}
		printf("\n");
		//printf("s.number, s.volume = %d, %d, %d\n", s.number, s.volume, dp[s.number][s.volume]);
	}
	
	// 打印路径方法二.2：
	{
		printf("print result with State[][] 2\n");
		State s(n, C); // 从最终状态dp[n][C]开始
		State preState;
		for(; s.number>0; s=preState)
		{
			preState=state[s.number][s.volume];
			if(s.volume > preState.volume)
				printf("%d(%d,%d)\t", s.number-1, V[s.number-1], W[s.number-1]);
		}
		printf("\n");
	}
	
	return dp[n][C];
}

int beibao1_1(int V[], int W[], int n, int C)
{
	int dp[n+1][C+1]; // dp[i][j]表示将前i个物体装入容量为j的背包的最大重量
	// dp[0][]=0
	// dp[i][j]=max(dp[i-1][j], dp[i-1][j-V[i-1]]+W[i-1])	
	for(int i=0; i<=n; ++i)
		for(int j=0; j<=C; ++j)
		{
			dp[i][j]= (i==0) ? 0 : dp[i-1][j];
			if(i>0  &&  j>=V[i-1]  &&  dp[i-1][j-V[i-1]]+W[i-1]>dp[i][j])
			{
				dp[i][j]=dp[i-1][j-V[i-1]]+W[i-1];
			}
			//printf("dp[%d][%d]=%d\n", i, j, dp[i][j]);
		}
	
	// 打印实际取出的物体，从dp[n][C]开始，
	printf("print result with computation\n");
	bool take[n];
	int j=C;
	for(int i=n; i>0; --i)
	{
		take[i-1]=false;
		if(dp[i][j] > dp[i-1][j])
		{
			take[i-1]=true;
			j=j-V[i-1];
		}
	}
	for(int i=0; i<n; ++i)
		if(take[i])
			printf("%d(%d,%d)\t", i, V[i], W[i]);
	printf("\n");
	
	return dp[n][C];
}

void test_beibao1()
{
	FILE* f=freopen("data.in", "r", stdin);
	if(f==NULL)
	{
		perror("open data.in, ");
		return;
	}
	int n, C;
	while(scanf("%d %d", &n, &C)==2)
	{
		printf("n=%d C=%d\n", n, C);
		int V[n];
		int W[n];		
		for(int i=0; i<n; ++i)
		{
			scanf("%d %d", &(V[i]), &(W[i]));
			//printf("V[%d]=%d, W[%d]=%d\n", i, V[i], i, W[i]);
		}
		
		int ret=beibao1(V, W, n, C);
		printf("res %d\n\n", ret);
	}
}

void test_beibao1_1()
{
	FILE* f=freopen("data.in", "r", stdin);
	if(f==NULL)
	{
		perror("open data.in, ");
		return;
	}
	int n, C;
	while(scanf("%d %d", &n, &C)==2)
	{
		printf("n=%d C=%d\n", n, C);
		int V[n];
		int W[n];
		for(int i=0; i<n; ++i)
		{
			scanf("%d %d", &(V[i]), &(W[i]));
			//printf("V[%d]=%d, W[%d]=%d\n", i, V[i], i, W[i]);
		}
		
		int ret=beibao1_1(V, W, n, C);
		printf("res %d\n\n", ret);		
	}
}

int main()
{
	test_beibao1();
	
	printf("\n---------test 1-1----------\n");
	test_beibao1_1();
	
	return 0;
}