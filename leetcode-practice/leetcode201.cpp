

int rangeBitwiseAnd(int m, int n) {
	return (n>m) ? (rangeBitwiseAnd(m>>1, n>>1)<<1) : m;
}

int rangeBitwiseAnd(int m, int n)
{
	int step=0;
	while(m!=n)
	{
		step++;
		m=m>>1;
		n=n>>1;
	}
	return m<< step;
}