

// 不使用if-else和比较运算符，返回a/b中的较大值
int max1(int a, int b)
{
	int z=a-b;
	// 判断z正负，z最高位是1还是0
	int k= (z>>31) &  1;
	return a-k*z; 
}

int max2(int a, int b)
{
	int c[2]={a, b};
	int z=a-b;
	z=(z>>31) & 1;
	return c[2];
}

