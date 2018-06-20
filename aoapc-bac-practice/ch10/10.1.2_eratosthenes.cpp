#include<iostream>
#include<cmath>
#include<cstring>

/*
// 求1-n的素数表 
memset(vis, 0, sizeof(vis));
for(int i=2; i<=n; i++)
	for(int j=i*2; j<=n; j+=i)
		vis[j]=1;
		
// 求1-n的素数表 
int m=sqrt(n+0.5);
memset(vis, 0, sizeof(vis));
for(int i=2; i<=m; i++)
	if(!vis[i])
		for(int j=i*i; j<=n; j+=i)
			vis[j]=1;
*/


const long long int MMAX=std::pow(10, 4);
const long long int TMAX=sqrt(MMAX);
// 求[n, m]内的无平方因子的数 的个数 
long long int solution2(long long int n, long long int m)
{
	std::cout<<"solution2:\n";
	return 0;
}

	// 求 2- 根号m 的素数p
	//  p*p 在 [4, m]之间
	// 筛掉[n, m]内的 p*p 的倍数
long long int solution(long long int n, long long int m)
{
	std::cout<<"solution:\n";
	long long int result=0;
	
	long long int t=sqrt(m); 
	long long int x=sqrt( t+0.5);
	
	long long int res[MMAX];
	long long int vis[TMAX];
	memset(vis, 0, sizeof(vis));
	memset(res, 0, sizeof(res));
	
	
	for(long long int i=2; i<=x; i++)
		if(!vis[i])
			for(long long int j=i*i; j<=t; j+=i)
				vis[j]=1;
	
	
	for(long long int i=2; i<=t  &&  !vis[i]; i++)
	{
		for(long long int j=i*i; j>=n  &&  j<=m; j+=i*i)
			res[j]=1;
	}
	
	for(long long int i=n; i<=m; i++)
		if(res[i]==0)
			result++;
	return result;
}

int main()
{
	long long int m=std::pow(10, 4);
	long long int n=0;

	std::cout<<"["<<n<<", "<<m<<"]"<<"内的无平方因子的数的个数 : \n";
	std::cout<<solution(n, m)<<std::endl;
	
	return 0;
}
