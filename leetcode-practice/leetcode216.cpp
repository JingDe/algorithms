

// k个数，相加之和为n
vector<vector<int>> combinationSum3(int k, int n) {
	vector<vector<int>> ans;
	vector<int> vec;
	backtracking(k, n, vec, 0, 1, ans);
	return ans;
}

void backtracking(int k, int n, vector<int> curVec, int curSum, int curPos, vector<vector<int>>& ans)
{
	if(curVec.size()==k  &&  curSum==n)
	{
		ans.push_back(curVec);
		return;
	}
	if(curVec.size()==k)
		return;
	if(curSum>n)
		return;
	
	for(int i=curPos; i<=9; i++)
	{
		// 剪枝，判断当前curVec.size()个元素、总和已达到curSum、的情况下，如果添加一个i，最大能达到多少、最小能达到多少
		// 总和肯定不小于  curSum+(k-curVec.size())*i
		int minSum=curSum+(k-curVec.size())*i;
		if(minSum>n)
			break;
		
		curVec.push_back(i);
		backtracking(k, n, curVec, curSum+i, i+1, ans);
		curVec.pop_back();
	}
}

