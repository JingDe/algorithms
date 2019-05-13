#include<stdio.h>
#include<algorithm>
#include<string.h>

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


void debug_print(int A[], int n)
{
	for(int i=0; i<n; ++i)
		printf("%d\t", A[i]);
	printf("\n");
}

// O(n*n)
int lis1(int A[], int n)
{
	int dp[n];
	memset(dp, 0, sizeof(dp)); // 初始化为1
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


// O(n*n)
int lis2(int A[], int n)
{
	int dp[n+1]; // dp[k]表示长度为k的所有递增子序列的其中最小的最末元素
	int k=1;
	// dp[0]=INT_MIN; int32_t INT_MIN=1<<31;
	dp[0]=1<<31;
	dp[1]=A[0];
	for(int i=1; i<n; ++i)
	{
		if(dp[k]<A[i])
			dp[++k]=A[i];
		else
		{
			// O(n)
			int c=1;
			for(; c<=k; ++c)
			{
				if(dp[c]>A[i])
					break;
			}
			dp[c]=A[i];
		}
	}
	debug_print(dp, k+1);
	return k;
}

// O(nlogn)
int lis3(int A[], int n)
{
	int dp[n+1];
	int k=1;
	// dp[0]=INT_MIN; int32_t INT_MIN=1<<31;
	dp[0]=1<<31;
	dp[1]=A[0];
	for(int i=1; i<n; ++i)
	{
		if(dp[k]<A[i])
			dp[++k]=A[i];
		else
		{
			// auto iter=std::lower_bound();
			//int pos=std::lower_bound(dp+1, dp+k, A[i])-dp-1;
			int pos=std::lower_bound(dp, dp+k+1, A[i])-dp;
			dp[pos]=A[i];
		}
	}
	debug_print(dp, k+1);
	return k;
}

void test_lis()
{
	{
		int A[]={3, 5, 7, 9, 1, 2, 4, 6, 11, 10};
		int sz=sizeof(A)/sizeof(A[0]);
		int r1=lis1(A, sz);
		int r2=lis2(A, sz);
		int r3=lis3(A, sz);
		printf("%d, %d, %d\n", r1, r2, r3);
	}
	
	{
		int A[]={3, 5, 1, 7,11,  10, 9, 2, 6, 4};
		int sz=sizeof(A)/sizeof(A[0]);
		int r1=lis1(A, sz);
		int r2=lis2(A, sz);
		int r3=lis3(A, sz);
		printf("%d, %d, %d\n", r1, r2, r3);
	}
	{
		int A[]={2, 1, 5, 3, 6, 4, 8, 9, 7};
		int sz=sizeof(A)/sizeof(A[0]);
		int r1=lis1(A, sz);
		int r2=lis2(A, sz);
		int r3=lis3(A, sz);
		printf("%d, %d, %d\n", r1, r2, r3);
	}
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

// p是按照身高排序的person数组，返回体重满足递增的最长子序列的长度
int lis_solve(person p[], int sz)
{
	if(sz<1)
		return 0;
	int dp[sz];
	dp[0]=1<<31;
	int k=1;
	dp[1]=p[0].weight;
	for(int i=1; i<sz; ++i)
	{
		if(p[i].weight>dp[k])
		{
			dp[++k]=p[i].weight;
		}
		else
		{
			int c=1;
			for(; c<=k; ++c)
				if(dp[c]>p[i].weight)
					break;
			dp[c]=p[i].weight;
		}
	}
	debug_print(dp, k+1);
	return k;
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
	
	int r2=lis_solve(p, sz);
	printf("%d\n", r2);
	
}



int main()
{
	{
		test_lis();
	}
	{	
		solve();
	}
	
	return 0;
}
