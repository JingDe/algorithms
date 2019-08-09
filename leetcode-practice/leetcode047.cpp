
// version 1 
// 使用visited数组：当原始数组有重复元素的时候，会出现重复序列
vector<vector<int>> permuteUnique(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
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
Your input
[1,1,2]
Output
[[1,1,2],[1,2,1],[1,1,2],[1,2,1],[2,1,1],[2,1,1]]

Your input
[1,1,1]
Output
[[1,1,1],[1,1,1],[1,1,1],[1,1,1],[1,1,1],[1,1,1]]

// version a

// vector<vector<int>> permuteUnique(vector<int>& nums) {
	// std::sort(nums.begin(), nums.end());
	// vector<vector<int> > permutations;
	
	// vector<int> visited(nums.size());
		// for(int j=0; j<nums.size(); ++j)
			// visited[j]=0;
	// vector<int> currSeq;
	// currSeq.reserve(nums.size());
	// backtracking(permutations, currSeq, visited, nums);
	// return permutations;
// }

// void backtracking(vector<vector<int> >& permutations, vector<int>& currSeq, vector<int>& visited, const vector<int>& nums)
// {
	// if(currSeq.size()==nums.size())
	// {
		// permutations.push_back(currSeq);
		// return;
	// }
	// for(int i=0; i<nums.size(); ++i)
	// {
		// if(i==0  ||  nums[i]!=nums[i-1])
		// {
			// if(visited[i]==0)
			// {
				// currSeq.push_back(nums[i]);
				// visited[i]=1;
				// backtracking(permutations, currSeq, visited, nums);
				// currSeq.pop_back();
				// visited[i]=0;
			// }
		// }
	// }
// }


// version 2
// 不使用visited数组，遍历判断某个元素是否出现过时，当原始数组有重复元素的时候，输出集中没有排列


vector<vector<int>> permuteUnique(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	vector<vector<int> > permutations;
	for(int i=0; i<nums.size(); ++i)
	{
		
		vector<int> currSeq;
		currSeq.reserve(nums.size());
		currSeq.push_back(nums[i]);
		backtracking(permutations, currSeq, nums);
	}
	return permutations;
}

void backtracking(vector<vector<int> >& permutations, vector<int>& currSeq, const vector<int>& nums)
{
	if(currSeq.size()==nums.size())
	{
		permutations.push_back(currSeq);
		return;
	}
	for(int i=0; i<nums.size(); ++i)
	{
		bool ok=true;
		for(int j=0; j<currSeq.size(); ++j)
			if(currSeq[j]==nums[i])
				ok=false;
			
		if(ok)
		{
			currSeq.push_back(nums[i]);
			backtracking(permutations, currSeq, nums);
			currSeq.pop_back();
		}
	}
}

// version 3 不使用visited数组
// 遍历是检查某个数已经出现的次数，和原始数组中出现的次数，当次数没超过，就继续递归
// 问题：会出现重复序列


vector<vector<int>> permuteUnique(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	vector<vector<int> > permutations;
	for(int i=0; i<nums.size(); ++i)
	{		
		vector<int> currSeq;
		currSeq.reserve(nums.size());
		currSeq.push_back(nums[i]);
		backtracking(permutations, currSeq, nums);
	}
	return permutations;
}

void backtracking(vector<vector<int> >& permutations, vector<int>& currSeq, const vector<int>& nums)
{
	if(currSeq.size()==nums.size())
	{
		permutations.push_back(currSeq);
		return;
	}
	for(int i=0; i<nums.size(); ++i)
	{
		int totalCount=0;
		for(int k=0; k<nums.size(); ++k)
			if(nums[k]==nums[i])
				totalCount++;
		
		int occurCount=0;
		for(int j=0; j<currSeq.size(); ++j)
			if(currSeq[j]==nums[i])
				occurCount++;
			
		if(totalCount>occurCount)
		{
			currSeq.push_back(nums[i]);
			backtracking(permutations, currSeq, nums);
			currSeq.pop_back();
		}
	}
}

Your input
[1,1,2]
Output
[[1,1,2],[1,1,2],[1,2,1],[1,2,1],[1,1,2],[1,1,2],[1,2,1],[1,2,1],[2,1,1],[2,1,1],[2,1,1],[2,1,1]]


// version 4 不使用visited数组
// 遍历之前，先判断选择当前元素是否会产生重复序列，如果当前元素与前一个位置的元素相同，选择当前元素的结果必然包含在选择此前一个元素的结果集中，重复
// 遍历时检查某个数已经出现的次数，和原始数组中出现的次数，当次数没超过，就继续递归

vector<vector<int>> permuteUnique(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	vector<vector<int> > permutations;
	
	vector<int> currSeq;
	currSeq.reserve(nums.size());
	backtracking(permutations, currSeq, nums);
	return permutations;
}

void backtracking(vector<vector<int> >& permutations, vector<int>& currSeq, const vector<int>& nums)
{
	if(currSeq.size()==nums.size())
	{
		permutations.push_back(currSeq);
		return;
	}
	for(int i=0; i<nums.size(); ++i)
	{
		if(i==0  ||  nums[i]!=nums[i-1])
		{
			int totalCount=0;
			for(int k=0; k<nums.size(); ++k)
				if(nums[k]==nums[i])
					totalCount++;
			
			int occurCount=0;
			for(int j=0; j<currSeq.size(); ++j)
				if(currSeq[j]==nums[i])
					occurCount++;
				
			if(totalCount>occurCount)
			{
				currSeq.push_back(nums[i]);
				backtracking(permutations, currSeq, nums);
				currSeq.pop_back();
			}
		}
	}
}