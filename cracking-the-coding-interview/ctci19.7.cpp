
const static int INT_MIN=1<<31;

bool g_invalid=false;

int maxSeqSum(int arr[], int n)
{
	if(arr==NULL  ||  n<=0)
	{
		g_invalid=true;
		return 0;
	}
	g_invalid=false;
	
	int cursum=0;
	int maxsum=INT_MIN;
	for(int i=0; i<n; ++i)
	{
		if(cursum<=0)
			cursum=arr[i];
		else
			cursum+=arr[i];
		if(cursum>maxsum)
			maxsum=cursum;
	}
	// if(maxsum<0)
		// maxsum=0;
	return maxsum;
}

void solve()
{
	int a[] = {
        2, -8, 3, -2, 4, -10
    };
	int sz=sizeof(a)/sizeof(*a);
	int maxsum=maxSeqSum(a, sz);
	if(g_invalid)
		printf("invalid input\n");
	else
		printf("%d\n", maxsum);
	
}

int main()
{
	solve();
	
	return 0;
}