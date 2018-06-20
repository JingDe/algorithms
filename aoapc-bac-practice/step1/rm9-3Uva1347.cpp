//旅行
//状态d(i,j)表示第一个人走到i,第二个人走到j，还需要走多长的距离
//决策：第一个人能不能走i+1？从状态无法判断
//状态d(i,j)表示1~max(i,j)全部走过，且两个人的当前位置分别为i,j，还需
//走多长的距离。
//d(i,j)=d(j,i)，规定在状态中i>j。
//决策：如果走到i+2,状态变成“1-i, i+2，但是i+1没走过”，无法表示成状态。
//禁止这样的决策！只允许其中一人走到i+1,状态只能转移到d(i+1,j)或d(i+1,i)
//边界：d(n-1,j)=dist(n-1,n)+dist(j,n),dist(a,b)表示点a和b之间的距离。
//所求结果：dist(1,2)+dist(2,1)
//状态总数：O(n*n)，每个状态的决策只有两个，总时间复杂度O(n*n).

#include<cmath>
#include<algorithm>

const int maxn=50+5;
double x[maxn],y[maxn],dist[maxn][maxn],d[maxn][maxn];

int main()
{
	int n;
	while(scanf("%d", &n)==1)
	{
		for(int i=1; i<=n; i++)
			scanf("%lf%lf", &x[i], &y[i]);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				dist[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		for(int i=n-1; i>=2; i--)
			for(int j=1; j<i; j++)
			{
				if(i==n-1)  d[i][j]=dist[i][n]+dist[j][n];
				else  d[i][j]=min(dist[i][i+1]+d[i+1][j], dist[j][i+1]+d[i+1][i]);
			}
		printf("%.2lf\n", dist[1][2]+d[2][1]);
	}
	return 0;
}
