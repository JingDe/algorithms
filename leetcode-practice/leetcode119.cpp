
vector<int> generate(int rowIndex) {
	vector<vector<int> > triangle;
	triangle.resize(rowIndex+1);
	
	for(int line=0; line<rowIndex+1; ++line)
	{
		triangle[line].resize(line+1);
		triangle[line][0]=triangle[line][line]=1;
		
		for(int c=1; c<line; ++c)
		{
			triangle[line][c]=triangle[line-1][c-1]+triangle[line-1][c];
		}
	}
	return triangle[rowIndex1];
}


vector<int> generate(int rowIndex) 
{
	vector<int> ans;
	ans.reserve(rowIndex+1);
	int a=1;
	ans.push_back(1);
	for(int i=1; i<=n; ++i)
	{
		a=a*(n-i+1)/i;
		ans.push_back(a);
	}
	return ans;
}

vector<int> generate(int rowIndex) 
{
	vector<int> ans;
	ans.reserve(rowIndex+1);

	long long a=1;
	for(int i=0; i<=n; ++i)
	{
		ans.push_back(a);
		a=a*(n-i)/(i+1);
	}
	return ans;
}

vector<int> generate(int rowIndex) 
{
	vector<int> ans(rowIndex+1, 1);
	
	for(int i=0; i<=rowIndex; i++)
	{
		for(int j=i-1; j>=1; j--)
			res[j]=res[j]+res[j-1];
	}
	return res;
}