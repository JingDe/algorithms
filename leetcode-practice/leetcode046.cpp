
vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int> > permutations;
	std::sort(nums.begin(), nums.end());
	do
	{
		permutations.push_back(nums);
	}while(next_permutation(nums.begin(), nums.end()));
	return permutations;
}


vector<vector<int>> permute(vector<int>& nums) 
{	
	vector<vector<int> > permutations;
	for(int i=0; i<nums.size(); ++i)
	{
		vector<int> visited(nums.size());
		for(int j=0; j<nums.size(); ++j)
			visited[j]=0;
		
		vector<int> currSeq;
		currSeq.reserve(nums.size());
		currSeq.push_back(nums[i]);
		visited[i]=1;
		backtracking(permutations, currSeq, visited, nums);
	}
	return permutations;
}

void backtracking(vector<vector<int> >& permutations, vector<int>& currSeq, vector<int>& visited, const vector<int>& nums)
{
	if(currSeq.size()==nums.size())
	{
		permutations.push_back(currSeq);
		return;
	}
	for(int i=0; i<nums.size(); ++i)
	{
		if(visited[i]==0)
		{
			currSeq.push_back(nums[i]);
			visited[i]=1;
			backtracking(permutations, currSeq, visited, nums);
			currSeq.pop_back();
			visited[i]=0;
		}
	}
}