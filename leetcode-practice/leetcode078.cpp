
vector<vector<int>> subsets(vector<int>& nums) {
	int n=nums.size();
	int max=pow(2, n)-1;
	
	vector<vector<int> > ans;
	for(int a=0; a<=max; ++a)
	{
		vector<int> numSet;
		getSet(numSet, a, n, nums); // 根据整数a的二进制表示低n位，创建一个nums的子集numSet
		ans.push_back(numSet);
	}
	return ans;
}

void getSet(vector<int>& numSet, int a, int n, const vector<int>& nums)
{
	numSet.clear();
	for(int i=0; i<n; ++i)
	{
		if(a  &  (1<<i))
			numSet.push_back(nums[i]);
	}
}


vector<vector<int>> subsets(vector<int>& nums) {
	vector<vector<int>> ans;
	
	vector<int> numSet;
	for(int i=0; i<nums.size(); ++i)
	{		
		numSet.push_back(nums[i]);
		backtracking(ans, numSet, i, nums);
		
		numSet.pop_back();
		backtracking(ans, numSet, i, nums);
	}
	return ans;
}

void backtracking(vector<vector<int>>& ans, vector<int> numSet, int num, const vector<int>& nums)
{
	if(num==nums.size()-1)
	{
		ans.push_back(numSet);
		return;
	}	
	for(int i=num+1; i<nums.size(); ++i)
	{
		numSet.push_back(nums[i]);
		backtracking(ans, numSet, i, nums);
		
		numSet.pop_back();
		backtracking(ans, numSet, i, nums);
	}
}

Your input
[1,2,3]
Output
[[1,2,3],[1,2],[1,3],[1],[1,3],[1],[2,3],[2],[3],[],[3],[],[2,3],[2],[3],[],[3],[]]
Expected
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]



// 增量构造法
vector<vector<int>> subsets(vector<int>& nums) 
{
	vector<vector<int>> ans;
	vector<int> numSet;
	backtracking2(ans, nums, numSet, 0);
	return ans;
}

void backtracking2(vector<vector<int>>& ans, const vector<int>& nums, vector<int> numSet, int cur)
{
	ans.push_back(numSet);
	
	for(int i=cur; i<nums.size(); ++i)
	{
		numSet.push_back(nums[i]);
		backtracking2(ans, nums, numSet, i+1);
		numSet.pop_back();
	}
}



// 位向量法
vector<vector<int>> subsets(vector<int>& nums) 
{
	vector<vector<int>> ans;
	bool choose[nums.size()];
	memset(choose, 0, sizeof(choose));
	backtracking3(ans, choose, nums, 0);
	return ans;
}

void backtracking3(vector<vector<int>>& ans, bool choose[], const vector<int>& nums, int cur)
{
	if(cur==nums.size())
	{
		vector<int> numSet;
		for(int i=0; i<nums.size(); ++i)
		{
			if(choose[i])
				numSet.push_back(nums[i]);
		}
		ans.push_back(numSet);
		return;
	}
	choose[cur]=0;
	backtracking3(ans, choose, nums, cur+1);
	choose[cur]=1;
	backtracking3(ans, choose, nums, cur+1);
}







