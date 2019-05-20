#include<stdio.h>

// n的阶乘，末尾的0的个数
int numOf0(int n)
{
	if(n<0)
		return -1;
	int res=0;
	while(n>=5)
	{
		res+=n/5;
		n=n/5;
	}
	return res;
}

int numOfZero2(int n)
{
	if(n<0)
		return -1;
	int res=0;
	while((n=n/5)>0)
	{
		res+=n;
	}
	return res;
}

int main()
{
	printf("%d, %d\n", numOf0(23), numOfZero2(23));
	
	printf("%d, %d\n", numOf0(27), numOfZero2(27));
	
	return 0;
}