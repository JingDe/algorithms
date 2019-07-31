
vector<string> generateParenthesis(int n)
{
	std::vector<std::string> res;
	helper(res, n, 0, 0, "");
	return res;
}

void helper(vector<string>& res, int n, int curL, int curR, string s)
{
	if(curL==n  &&  curR==n)
	{
		res.push_back(s);
		return;
	}
	if(curL<n)
	{
		helper(res, n, curL+1, curR, s+"(");
	}
	
	if(curR<n  &&  curR<curL)
	{
		helper(res, n, curL, curR+1, s+")");
	}
}

// ["(())","()()"]
// ["((()))","(()())","(())()","()(())","()()()"]


