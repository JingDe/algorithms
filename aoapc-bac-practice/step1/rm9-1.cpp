//���������ÿ��״̬i���ҵ�f(i)����������״̬����ĳЩ����²������㡣
//ˢ��������ÿ��״̬i������f(i)��Ӱ�쵽��״̬�����¹�ʽ������״̬ת�Ʒ��̡�
//ע�⣬ֻ�е�ÿ��״̬��������״̬������Ӱ���໥����ʱ������ˢ����
//������ļ��
//ʱ��Ϊ��Ȼ����Ӱ����ߵ�ֻ�е�ǰʱ��������ĳ�վ��������d(i,j)��ʾʱ��i,
//���ڳ�վj�����1-n�������ٻ���Ҫ�ȴ��೤ʱ�䡣�߽������ǣ�d(T,n)=0,
//����d(T,i)(i������n)��Ϊ�����
//����1����һ����
//����2��������ҿ��Ļ𳵣�����У�
//����3��������󿪵Ļ𳵣�����У�
/*
for(int i=1; i<=n-1; i++)
	dp[T][i]=INF;
dp[T][n]=0;

for(int i=T-1; i>=0; i--)
	for(int j=1; j<=n;; j++)
	{
		dp[i][j]=dp[i+1][j]+1;//����1
		if(j<n  &&  has_train[i][j][0]  &&  i+t[j]<=T)
			dp[i][j]=min(dp[i][j], dp[i+t[j]][j+1]);//����2
		if(j>0  &&  has_train[i][j][1]  &&  i+t[j-1]<=T)
			dp[i][j]=min(dp[i][j], dp[i+t[j-1]][j-1]);//����3
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



