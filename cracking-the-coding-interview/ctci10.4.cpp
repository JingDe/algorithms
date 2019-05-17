#include<stdio.h>
#include<cstdlib>
#include<algorithm>

const static int INT_MAX=~(1<<31);

void swap(int &a, int &b)
{
	a = a^b;
	b = b^a;
	a = a^b;
}

int flipsign(int a)
{
	int d = (a<0)  ? 1 : -1;
	int opa=0;
	while(a != 0)
	{
		a += d;
		opa += d;
	}
	return opa;
}

int abs(int a)
{
	if(a<0)
		return flipsign(a);
	else
		return a;
}

bool opsign(int a, int b)
{
	// if( (a^b)  &  (1<<31) ) // 当异或的第31位是1
	// if( (a^b) >> 31 ) // 
	if((a<b  &&  b>0)  ||  (a>0  &&  b<0))
		return true;
	return false;
}

int add(int a, int b)
{
	return a+b;
}

int multi(int a, int b)
{
	int a1=abs(a);
	int b1=abs(b);
	if(a1>b1)
	{
		swap(a1, b1);
		// assert(a1<=b1);
	}
	// 
	int res=0;
	for(int i=0; i<a1; ++i)
		res=add(res, b1);
	
	if(opsign(a, b))
		//res*=(-1); // 不能使用乘法
		res=flipsign(res);
	return res;
}

int minus(int a, int b)
{
	// a-b
	return add(a, flipsign(b));
}

int divide(int a, int b)
{
	if(b==0)
		return INT_MAX;
	int a1=abs(a);
	int b1=abs(b);
	
	int res=0;
	while(a1>=b1)
	{
		a1=minus(a1, b1);
		++res;
	}
	if(opsign(a, b))
		res=flipsign(res);
	return res;
}

int main()
{
	int res=add(8, 9);
	printf("%d\n", res);
	
	res=minus(8, 9);
	printf("%d\n", res);
	
	res=multi(4, -5);
	printf("%d\n", res);
	
	res=divide(9, -4);
	printf("%d\n", res);
	
	return 0;
}
