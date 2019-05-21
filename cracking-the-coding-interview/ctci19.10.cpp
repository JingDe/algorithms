#include<stdlib.h>

const static int INT_MAX=~(1<<31);

// rand7等概率地返回1~7的整数
int rand7()
{
	srand(time(NULL));
	int x=RAND_MAX;
	while(x>7)
		x=rand();
	return x;
}

// 使用rand7生成rand5
int rand5()
{
	int x=INT_MAX;
	while(x>5)
		x=rand7();
	return x;
}

int Rand5()
{
	srand(time(NULL));
	int x=RAND_MAX;
	while(x>5)
		x=rand();
	return x;
}

// 使用rand25生成rand7
int rand7()
{
	int x=INT_MAX;
	while(x>7)
		x=5*(Rand5()-1)+Rand5(); // rand25
	return x;
}


int Rand7()
{
	int x=INT_MAX;
	while(x>21) // Rand21()
		x=5*(Rand5()-1)+Rand5();
	return x%7 + 1; // Rand7()
}

