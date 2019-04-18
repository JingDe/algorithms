#include<stdio.h>

void test_unsigned()
{
	unsigned int u1=-1;
	printf("%ud, 0x%x\n", u1, u1); // 0xffffffff
}


int main()
{
	test_unsigned();
	
	return 0;
}