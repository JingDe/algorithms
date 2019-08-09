
double myPow(double x, int n) {
	if(x==0)
		return 0;
	long long N=n;
	if(n<0)
	{
		N=-n;
		x=1/x;
	}
	double res=x;
	while(--N>0)
		res=res*x;
	return res;
}

double myPow(double x, int n) {
	if(x==0)
		return 0;
	long long N=n;
	if(n<0)
	{
		N=-N;
		x=1/x;
	}
	return helper(x, N);
}

double helper(double x, long long n)
{
	if(n==0)
		return 1;
	if(n==1)
		return x;
	if(n%2)
	{
		double A=helper(x, (n-1)/2); // n/2
		return A*A*x;
	}
	else
	{
		double A=helper(x, n/2);
		return A*A;
	}
}



double myPow(double x, int n) {
	long long N=n;
	if(N<0)
	{
		x=1/x;
		N=-N;
	}
	double ans=1;
	double current_product=x;
	for(long long i=N; i; i/=2)
	{
		if( (i%2) == 1)
			ans = ans * current_product;
		current_product = current_product * current_product;
	}
	return ans;
}
