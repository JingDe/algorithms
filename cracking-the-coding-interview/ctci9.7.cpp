#include<stdio.h>
#include<algorithm>


int max(int a, int b)
{
	return a>b ? a : b;
}

int max(int a[], int n)
{
	if(n<=0)
		return -1;
	int res=a[0];
	for(int i=1; i<n; ++i)
		if(a[i]>res)
			res=a[i];
	return res;
}

// LIS
int lis1(int A[], int n)
{
	int dp[n];
	dp[0]=1;
	for(int i=1; i<n; ++i)
	{
		for(int j=0; j<i; ++j)
		{
			if(A[j]<A[i])
				dp[i]=max(dp[j]+1, dp[i]);
		}
	}
	return max(dp, n);
}

int lis2(int A[], int n)
{
	return A[0];
}

// ======================================

struct person{
	int height;
	int weight;
	person(){}
	person(int h, int w):height(h),weight(w){}
	person& operator=(const person& rhs)
	{
		height=rhs.height;
		weight=rhs.weight;
		return *this;
	}
};

// std::sort, Compare返回true表示lhs<rhs。
bool operator<(const person& lhs, const person& rhs)
{
	if(lhs.height<rhs.height)
		return true;
	else if(lhs.height>rhs.height)
		return false;
	
	if(lhs.weight<rhs.weight)
		return true;
	else
		return false;
}

void debug_print(person p[], int n)
{
	for(int i=0; i<n; ++i)
		printf("<%d, %d>\t", p[i].height, p[i].weight);
	printf("\n");
}

void solve()
{
	person p[6];
	p[0]=person(65, 100);
	p[1]=person(70, 150);
	p[2]=person(56, 90);
	p[3]=person(75, 190);
	p[4]=person(60, 95);
	p[5]=person(68, 110);
	int sz=sizeof(p)/sizeof(p[0]);
	
	std::sort(p, p+sz);
	debug_print(p, sz);
	
}

int main()
{
	{	
		solve();
	}
	
	return 0;
}
