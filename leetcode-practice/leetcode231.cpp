

bool isPowerOfTwo(int n) {
	while(n>1)
	{
		int a=n%2;
		if(a)
			return false;
		n=n/2;
	}
	return true;
}


bool isPowerOfTwo(int n) {
	// 所有比特都为1的int
	int max_mask=~0; //0xFFFFFFFF;
	int lowest_mask=0x1;
	printf("%d&mask : %d\n", n, n & lowest_mask);
	int tmp=n & lowest_mask;
	printf("tmp=%d\n", tmp);
	if(n  &  lowest_mask == 0)
		printf("true\n");
	else
		printf("false\n");
	while(n  &  lowest_mask == 0) // 当n的最低位比特是0的话, 将n右移一位比特
	{
		n=n>>1;
		printf("%d&mask : %d\n", n, n & lowest_mask);
	}
	printf("n=%d\n", n);
	if((n  &  max_mask) == n)
		return true;
	return false;
}

bool isPowerOfTwo(int n) 
{
	if(n>0  &&  (n & (n-1)) ==0)
		return true;
	return false;
}