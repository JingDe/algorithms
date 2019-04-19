#include<stdio.h>
#include<string.h>

typedef long long ll;
long long zuheshu(int a, int b);

ll getPath(ll m, ll n){
    if(m == 1 || n == 1) return 1;
    else return getPath(m-1, n) + getPath(m, n-1);
}


const int m=40;
const int n=50;
long long path[m+1][n+1];

long long computePath(int x, int y)
{
	if(x==1  ||  y==1)
		return 1;
	// 初始化第一行为1，第一列为1
	for(int col=1; col<=y; ++col)
		path[1][col]=1;
	for(int row=1; row<=x; ++row)
		path[row][1]=1;
	
	//if(x<y)
	{
		// 从第1行开始计算
		for(int i=2; i<=x; ++i)
		{
			for(int j=1; j<=y; ++j)
			{
				path[i][j]=path[i-1][j]+path[i][j-1];
			}
		}
	}
	// else
	// {
		//从第1列开始计算
		// for(int col=2; col<=y; ++col)
		// {
			// for(int row=1; row<=x; ++row)
			// {
				// path[row][col]=path[row-1][col]+path[row][col-1];
			// }
		// }
	// }
	return path[x][y];
}

long long solution1(int x, int y)
{
	memset(path, 0, sizeof(path));
	return computePath(x, y);
}

// 转换为计算 C(m-1+n-1, m-1)=(m-1+n-1)! / ( (m-1)! * (n-1)! )
long long solution2(int m, int n)
{
	return zuheshu(m-1+n-1, m-1);
}

// C(a, b) = a! / (b!*(a-b)!)
long long zuheshu(int a, int b)
{
	long long res=1;
	if(b<a-b)
		b=a-b;
	for(int i=1; i<=a-b; i++)
	{
		res =res*(i+b)/i;
	}
	return res;
}

ll fact(ll n){
    if(n == 0) return 1;
    else return n*fact(n-1);
}
ll path1(ll m, ll n){
    return fact(m-1+n-1)/(fact(m-1)*fact(n-1));
}

// 从(m, n)坐标开始搜索一条路径
void getOnePath()
{
	
}


// 从(1, 1)坐标开始搜索所有路径


int main()
{
	{
		printf("%lld, %lld, %lld\n", getPath(2, 3), solution1(2,3), solution2(2,3));
		printf("%lld, %lld, %lld\n", getPath(2, 30), solution1(2,30), solution2(2, 30));
		printf("%lld, %lld, %lld\n", getPath(20, 3), solution1(20,3), solution2(20, 3));
		//printf("%lld, %lld\n", getPath(22, 33), solution1(22,33));
		printf("%lld, %lld\n", solution1(22,33), solution2(22, 33));
		//printf("%lld\n", getPath(22, 33));
	}
	
	{
		
	}
	return 0;
}