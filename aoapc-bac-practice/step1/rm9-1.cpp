//填表法：对于每个状态i，找到f(i)依赖的所有状态，在某些情况下并不方便。
//刷表法：对于每个状态i，更新f(i)所影响到的状态。更新公式，而非状态转移方程。
//注意，只有当每个状态所依赖的状态对它的影响相互独立时才能用刷表法。
//城市里的间谍
//时间为天然的序。影响决策的只有当前时间和所处的车站，所以用d(i,j)表示时刻i,
//你在车站j（编号1-n），最少还需要等待多长时间。边界条件是：d(T,n)=0,
//其他d(T,i)(i不等于n)，为正无穷。
//决策1：等一分钟
//决策2：搭乘往右开的火车（如果有）
//决策3：搭乘往左开的火车（如果有）
/*
for(int i=1; i<=n-1; i++)
	dp[T][i]=INF;
dp[T][n]=0;

for(int i=T-1; i>=0; i--)
	for(int j=1; j<=n;; j++)
	{
		dp[i][j]=dp[i+1][j]+1;//决策1
		if(j<n  &&  has_train[i][j][0]  &&  i+t[j]<=T)
			dp[i][j]=min(dp[i][j], dp[i+t[j]][j+1]);//决策2
		if(j>0  &&  has_train[i][j][1]  &&  i+t[j-1]<=T)
			dp[i][j]=min(dp[i][j], dp[i+t[j-1]][j-1]);//决策3
	}
cout<<"Case Number "<<++kase<<": ";
if(dp[0][1]>=INF)
	cout<<"impossible\n";
else
	cout<<dp[0][1]<<endl;
*/


#include<cstring>;

const int maxn=50+5;
const int maxt=200+5;
const int INF=1000000000;

int t[maxn], has_train[maxt][maxn][2];
int dp[maxt][maxn];

int main()
{
	int kase=0, n, T;
	while(cin>>n>>T  &&  n)
	{
		int M1, M2, d;
		for(int i=1; i<=n-1; i++)
			cin>>t[i];
		memset(has_train, 0, sizeof(has_train));
		cin>>M1;
		while(M1--)
		{
			cin>>d;
			for(int j=1; j<=n-1; j++)
			{
				if(d<=T)	has_train[d][j][0]=1;
				d += t[j];
			}
		}
		cin>>M2;
		while(M2--)
		{
			cin>>d;
			for(int j=n-1; j>=1; j--)
			{
				if(d<=T)	has_train[d][j+1][1]=1;
				d += t[j];
			}
		}

		for(int i=1; i<=n-1; i++)  dp[T][i]=INF;
		dp[T][n]=0;
		for(int i=T-1; i>=0; i--)
			for(int j=1; j<=n; j++)
			{
				dp[i][j]=dp[i+1][j]+1;
				if(j<n  &&  has_train[i][j][0]  &&  i+t[j]<=T)
					dp[i][j]=min(dp[i+t[j]][j+1]);
				if(j>1  &&  has_train[i][j][1]  &&  i+t[j-1]<=T)
					dp[i][j]=min(dp[i][j], dp[i+t[j-1]][j-1]);
			}
		cout<<"Case Number "<<++kase<<": ";
		if(dp[0][1]>=INF)  cout<<"impossible\n";
		else  cout<<dp[0][1]<<endl;
	}
	return 0;
}



