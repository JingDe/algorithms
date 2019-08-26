
// 回溯法
vector<vector<string>> partition(string s) {
	vector<vector<string>> ans;
	vector<string> cur;
	backtracking(s, 0, cur, ans);
	return ans;
}

void backtracking(const string& s, int start, vector<string> cur, vector<vector<string>>& ans)
{
	if(start>=s.size())
	{
		ans.push_back(cur);
		return;
	}
	
	for(int len=1; len<s.size()-start; len++)
	{
		string tmp=s.substr(start, len);
		if(isPalindrome(tmp))
		{
			cur.push_back(tmp);
			backtracking(s, start+len, cur, ans);
		}
	}
}

bool isPalindrome(const string& s)
{
	for(int i=0; i<s.size()/2; ++i)
		if(s[i]!=s[s.size()-1-i])
			return false;
	return true;
}