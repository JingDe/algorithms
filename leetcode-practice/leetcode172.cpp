

int trailingZeroes(int n) {
	return n==0 ? 0 : n/5+trailingZeroes(n/5);
}

int trailingZeroes(int n)
{
	int result=0;
	for(long long i=5; n/i>0; i*=5) // 当n>=1808548329, i>INT_MAX
		result+= n/i;
	return result;
}

int trailingZeroes(int n)
{
	int sum=0;
	int tmp=0;
	while(n/5>0)
	{
		tmp=n/5;
		sum+=tmp;
		n=tmp;
	}
	return sum;
}