#include<stdio.h>
#include<iostream>
#include<math.h>
#include<stdlib.h>


bool sameSign1(int a, int b);
bool sameSign2(int a, int b); 

int divide1(int dividend, int divisor) {
	bool negative=false;
	if(dividend>0  &&  divisor<0  ||  dividend<0  &&  divisor>0)
		negative=true;
	int a=abs(dividend); // -2147483648 runtime_error
	int b=abs(divisor);
	int res=0;
	while(a>b)
	{
		res++;
		a-=b;
	}
	if(negative)
		res = res*(-1);
	return res;
}


int divide2(int dividend, int divisor) {
	bool positive=sameSign1(dividend, divisor);
	int a=dividend;
	int res=0;
	while(sameSign1(dividend, a))
	{
		if(positive)
		{
			a=a-divisor;
			++res;
		}
		else
		{
			a=a+divisor;
			--res;
		}
	}
	return res;
}

bool sameSign1(int a, int b)
{
	int c= a^b;
	printf("%x ^ %x is %x\n", a, b, c);
	if((a ^ b)>=0)
		return true;
	return false;
}

bool sameSign2(int a, int b)
{
	int a2=a>>31;
	int b2=b>>31;
	int c= (a>>31) ^ (b>>31);
	printf("%x %x\n", a, b);
	printf("%x ^ %x is %x\n", a2, b2, c);
	
	c= a2 ^ b2;
	printf("%x ^ %x is %x\n", a2, b2, c);
	
	if( (a>>31) ^ (b>>31)==0)
		return true;
	return false;
}

void test_sameSign()
{
	std::cout<<sameSign1(1, -1)<<std::endl;
	std::cout<<sameSign2(1, -1)<<std::endl;
}

void test_binary()
{
	int32_t a=-1;
	printf("-1 is %x\n", a);
	
}



// 参考方法
int divide3(int dividend, int divisor) {
	if(dividend ==  INT_MIN  &&  divisor==-1)
		return INT_MAX;
	long dvd=labs(dividend);
	long dvs=labs(divisor);
	int ans=0;
	// ???
	int sign= dividend > 0 ^ divisor > 0 ? -1 : 1;	
	while(dvd>=dvs)
	{
		long temp=dvs, m=1;
		while(temp << 1  <= dvd)
		{
			temp <<=1;
			m<<=1;
		}
		dvd -= temp;
		ans +=m;
	}
	return sign*ans;
}


int divide4(int dividend, int divisor) {
	if(dividend==0)
		return 0;
	if(divisor==0)
		return INT_MAX;
	
	double t1=log(fabs(dividend));
	double t2=log(fabs(divisor));
	long long result=double(exp(t1-t2));
	
}


int divide5(int dividend, int divisor) {
	if(!divisor  ||  (dividend==INT_MIN  &&  divisor==-1))
		return INT_MAX;
	
	int sign=((dividend<0) ^ (divisor<0)) ? -1 : 1;
	long long m=labs(dividend);
	long long n=labs(divisor);
	int result=0;
	
	while(m>=n)
	{
		long long temp=n, count=1;
		while(m>=(temp<<1))
		{
			
		}
	}
}

int divide6(int dividend, int divisor) 
{
	long long result=0;
	long long m=abs((long long )dividend);
	long long n=abs((long long) divisor);
	while(m>=n)
	{
		long long s=n, power=1;
		while((s<<1) <= m)
		{
			s<<=1;
			power<<=1;
		}
		result+=power;
		m-=s;
	}
	if((dividend>0) ^ (divisor>0))
		reult =-result;
	return result>INT_MAX ? INT_MAX: result;
}

void test()
{
	// 
	{
		int dividend=1, divisor=-1;
		int sign= dividend > 0 ^ divisor > 0 ? -1 : 1;	
		std::cout<<dividend<<", "<<divisor<<", "<<sign<<std::endl;
	}
	
	{
		int dividend=-1, divisor=-1;
		int sign= dividend > 0 ^ divisor > 0 ? -1 : 1;	
		std::cout<<dividend<<", "<<divisor<<", "<<sign<<std::endl;
	}
	{
		int dividend=1, divisor=1;
		int sign= dividend > 0 ^ divisor > 0 ? -1 : 1;	
		std::cout<<dividend<<", "<<divisor<<", "<<sign<<std::endl;
	}
}


int main()
{
	// test_binary();
	
	// test_sameSign();
	
	test();
	
	return 0;
}
