
int numTrees(int n) 
{
	if(n==0)
		return 1;
	//return ((2*n-1)/(n+1)) * (2*numTrees(n-1));
	long long C=((2*n-1)/(n+1)) * (2*numTrees(n-1));
	return (int) C;
}

int numTrees(int n) 
{
	long long C=1;
	for(int i=0; i<n; ++i)
	{
		C = C*2*(2*i+1)/(i+2);
	}
	return (int) C;
}

int numTrees(int n) 
{
	int G[n+1];
	G[0]=1;
	G[1]=1;
	
	for(int k=2; k<=n; ++k)
	{
		int sum=0;
		for(int i=1; i<=k; ++i)
		{
			sum+=G[i-1]*G[k-i];
		}
		G[k]=sum;
	}
	return G[n];
}