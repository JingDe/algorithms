
bool isPrime(int n)
{
	if(n<=1)
		return false;
	for(int i=2; i*i<=n; i++)
		if(num % i == 0)
			return false;
	return true;
}



int countPrimes(int n) {
	bool prime[n+1];
	memset(prime, 0, sizeof(prime)); // 
	
	for(int i=2; i<sqrt(n); i++)
	{
		for(int j=i; j*i<n; j++)
			prime[j*i]=true; // 1表示非质数
	}
	int ans=0;
	for(int i=1; i<n; i++)
		if(prime[i]==false)
			++ans;
	return ans;
}


int countPrimes(int n) 
{
	bool isPrime[n];
	for(int i=2; i<n; i++)
		isPrime[i]=true;
	
	for(int i=2; i*i<n; i++)
	{
		if(!isPrime[i])
			continue;
		for(int j=i*i; j<n; j+=i)
		{
			isPrime[j]=false;
		}
	}
	int count=0;
	for(int i=2; i<n; i++)
		if(isPrime[i])
			count++;
	return count;
}