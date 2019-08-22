
string getPermutation(int n, int k) {
	std::vector<int> seq;
	for(int i=1; i<=n; ++i)
		seq.push_back(i);
	
	int cur=0;
	while(++cur<k)
	{
		next_permutation(seq.begin(), seq.end());
	}
	string ans;
	for(int i=0; i<n; ++i)
	{
		ans=ans+std::to_string(seq[i]);
	}
	return ans;
}

string getPermutation(int n, int k) {
	//bool visited[n];
	//memset(visited, 0, sizeof(visited));
	vector<int> visited(n+1, 0);

	int counter=0;
	string ans;

	vector<int> seq;
	for(int i=1; i<=n; ++i)
	{
		visited[i]=true;
		seq.push_back(i);
		iteratePermutation(visited, n, seq, 1, counter, k, ans);

		if(ans.empty()==false)
			break;
		
		visited[i]=false;
		seq.pop_back();
	}
	return ans;
}

void iteratePermutation(vector<int>& visited, int n, vector<int>& seq, int number, int& counter, int k, string& ans)
{
	if(number==n)
	{
		if(++counter==k)
		{
			ans=getDesc(seq, n);
			return;
		}
	}
	else
	{
		for(int i=1; i<=n; ++i)
		{
			if(visited[i]==false)
			{
				visited[i]=true;
				seq.push_back(i);
				iteratePermutation(visited, n, seq, number+1, counter, k, ans);
				if(ans.empty()==false)
					return;

				visited[i]=false;
				seq.pop_back();
			}
		}
	}
}

string getDesc(const vector<int>& seq, int n)
{
	string ans;
	for(int i=0; i<n; ++i)
	{
		ans=ans+std::to_string(seq[i]);
	}
	return ans;
}