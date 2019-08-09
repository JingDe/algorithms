
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int> > combinations;
	
	for(int i=0; i<candidates.size(); ++i)
	{
		vector<int> currConbination;
		currConbination.push_back(candidates[i]);
		backtracking(combinations, currConbination, candidates[i], candidates, target);
	}
	return combinations;
}

void backtracking(vector<vector<int> >& combinations, vector<int>& currConbination, int currSum, const vector<int>& candidates, int target)
{
	if(currSum==target)
	{
		combinations.push_back(currConbination);
		return;
	}
	for(int i=0; i<candidates.size(); ++i)
	{
		if(currSum+candidates[i]<=target)
		{
			currConbination.push_back(candidates[i]);
			backtracking(combinations, currConbination, currSum+candidates[i], candidates, target);
			currConbination.pop_back();
		}
	}
}


// version 2
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int> > combinations;
	
	std::sort(candidates.begin(), candidates.end());
	for(int i=0; i<candidates.size(); ++i)
	{
		if(i==0  ||  candidates[i]!=candidates[i-1])
		{
			vector<int> currConbination;
			currConbination.push_back(candidates[i]);
			backtracking(combinations, currConbination, candidates[i], candidates, target, i);
		}
	}
	return combinations;
}

void backtracking(vector<vector<int> >& combinations, vector<int>& currConbination, int currSum, const vector<int>& candidates, int target, int lastIdx)
{
	if(currSum==target)
	{
		combinations.push_back(currConbination);
		return;
	}
	for(int i=lastIdx; i<candidates.size(); ++i)
	{
		if(i!=lastIdx  &&  candidates[i]==candidates[i-1])
			continue;
		if(currSum+candidates[i]<=target)
		{
			currConbination.push_back(candidates[i]);
			backtracking(combinations, currConbination, currSum+candidates[i], candidates, target, i);
			currConbination.pop_back();
		}
	}
}
