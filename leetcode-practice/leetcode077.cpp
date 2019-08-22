
vector<vector<int>> combine(int n, int k) {
	if(n<0  ||  k<0  ||  n<k)
		return vector<vector<int>>();

	bool visited[n];
	memset(visited, 0, sizeof(visited));
	vector<vector<int> > ans;

	for(int i=0; i<n; ++i)
	{
		vector<int> seq;
		seq.push_back(i+1);
		visited[i]=true;
		backtracking(ans, visited, seq, i, n, k);

		visited[i]=false;
	}
	return ans;
}

void backtracking(vector<vector<int> >& ans, bool visited[], vector<int> seq, int num, int n, int k)
{
	if(seq.size()==k)
	{
		ans.push_back(seq);
	}
	else
	{
		for(int i=num+1; i<n; ++i)
		{
			if(visited[i]==false)
			{
				visited[i]=true;
				seq.push_back(i+1);
				backtracking(ans, visited, seq, i, n, k);

				visited[i]=false;
				seq.pop_back();
			}
		}
	}
}