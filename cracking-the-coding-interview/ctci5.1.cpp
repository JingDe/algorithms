#include<iostream>
#include<stdio.h>
#include<stdint.h>
#include<bitset>

// 将n中的第i到j位设置为m的所有位
int update_bits1(int n, int m, int i, int j)
{
	// 获得mask 111...+(i位0...j位0)+111...
	//unsigned int mask=UINT_MAX;
	unsigned int mask2=~0;
	
	// std::cout<<std::hex<<"mask=0X"<<mask2<<std::endl<<std::dec;
	// std::cout<<std::oct<<"mask=0"<<mask2<<std::endl<<std::dec;
	
	{
	//mask2=mask2-((1<<j+1)-1) + ((1<<i)-1);
	}
	{
		mask2=mask2-((1<<j+1)-1) ;
		mask2 = mask2 | ((1<<i)-1);
	}
	printf("mask=0X%X\n", mask2);
	
	int ret= (n&mask2) | (m<<i);
	printf("RES1 0X%X -> 0X%X\n", n, ret);
}

// 先将n的低i位保存，再将n的低j位清0，最后将n或上m<<i加上保存的低i位
void update_bits2(int n, int m, int i, int j)
{
	int lowi = n & ((1<<i+1)-1);
	int res = (n >> (j+1)) << (j+1);
	res = res | (m<<i);
	res = res+lowi;
	printf("RES2 0X%X -> 0X%X\n", n, res);
}

void test_binary_print()
{
	int n=0b10000000000;
	int m=0B10101;
	std::cout<<n<<"\t"<<m<<std::endl;
	std::cout<<std::hex<<"0X"<<n<<"\t"<<"0x"<<m<<std::endl<<std::dec;
	printf("n=0%o, m=0%o\n", n, m);
	printf("n=0X%X, m=0X%X\n", n, m);
}

void test_bitset()
{
	int d=42;
	std::cout<<"d="<<d<<"="<<std::bitset<32>(d)<<std::endl;
}

int main()
{
	{
		test_bitset();
	}
	
	{
		int n=0b10000000000;
		int m=0B10101;
		// std::cout<<n<<"\t"<<m<<std::endl;
		// std::cout<<std::hex<<"0X"<<n<<"\t"<<"0x"<<m<<std::endl<<std::dec;
		// printf("n=0%o, m=0%o\n", n, m);
		// printf("n=0X%X, m=0X%X\n", n, m);
		
		update_bits1(n, m, 2, 6);
		update_bits2(n, m, 2, 6);
	}
	return true;
}

