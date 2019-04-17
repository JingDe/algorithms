#include<stdio.h>
#include<string.h>

const int MAXN=100;


long long fb[MAXN]={0};
long long fibonacci_n1(int n)
{
	if(n<1)
		return -1;
	if(n==1  ||  n==2)
	{
		fb[n]=1;
		return 1;
	}
	if(fb[n]>0)
		return fb[n];
	return fibonacci_n1(n-1)+fibonacci_n1(n-2);
}

long long fibonacci_n2(int n)
{
	if(n<1)
		return -1;
	if(n==1  ||  n==2)
		return 1;
	int a=1, b=1, c=0;
	for(int i=3; i<=n; i++)
	{
		c=a+b;
		a=b;
		b=c;
	}
	return c;
}

void test_memset_minus1()
{
	int array[10]={0};
	memset(array, -1, sizeof(array));
	for(int i=0; i<sizeof(array)/sizeof(array[0]); i++)
		printf("%d, %c\n", array[i], array[i]);
	printf("\n");
	
	char c=(char)-1;
	printf("c=%c, %d\n", c, (int)c);
	
	char c2=static_cast<unsigned char>(c);
	printf("c2= %c, %d\n", c, (int)c);
	printf("c2-'a'=%d", c2-'a');
	
	int i=c2;
	printf("%d\n", i);
	
	unsigned int i2=c2;
	printf("%u\n", i2);
}

int main()
{
	{
		test_memset_minus1();
	}
	
	{
		memset(fb, 0, sizeof(fb));
		printf("fibonacci 1=%lld\n", fibonacci_n1(1));
		printf("fibonacci 3=%lld\n", fibonacci_n1(3));
		printf("fibonacci 11=%lld\n", fibonacci_n1(11));
	}
	
	{
		printf("fibonacci 1=%lld\n", fibonacci_n2(1));
		printf("fibonacci 3=%lld\n", fibonacci_n2(3));
		printf("fibonacci 11=%lld\n", fibonacci_n2(11));
	}
	
	return 0;
}