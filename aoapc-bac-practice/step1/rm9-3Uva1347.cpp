//����
//״̬d(i,j)��ʾ��һ�����ߵ�i,�ڶ������ߵ�j������Ҫ�߶೤�ľ���
//���ߣ���һ�����ܲ�����i+1����״̬�޷��ж�
//״̬d(i,j)��ʾ1~max(i,j)ȫ���߹����������˵ĵ�ǰλ�÷ֱ�Ϊi,j������
//�߶೤�ľ��롣
//d(i,j)=d(j,i)���涨��״̬��i>j��
//���ߣ�����ߵ�i+2,״̬��ɡ�1-i, i+2������i+1û�߹������޷���ʾ��״̬��
//��ֹ�����ľ��ߣ�ֻ��������һ���ߵ�i+1,״ֻ̬��ת�Ƶ�d(i+1,j)��d(i+1,i)
//�߽磺d(n-1,j)=dist(n-1,n)+dist(j,n),dist(a,b)��ʾ��a��b֮��ľ��롣
//��������dist(1,2)+dist(2,1)
//״̬������O(n*n)��ÿ��״̬�ľ���ֻ����������ʱ�临�Ӷ�O(n*n).

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
