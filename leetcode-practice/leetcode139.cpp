

// 暴力法：时间复杂度：O(n^n)
bool wordBreak(string s, vector<string>& wordDict) {
	return backtracking(s, 0, wordDict);
}

bool backtracking(const string& s, int start, vector<string>& wordDict)
{
	if(start>=s.size())
	{
		return true;
	}
	
	for(int i=0; i<wordDict.size(); ++i)
	{
		string word=wordDict[i];
		if(word.size() > s.size()-start)
			continue;
		if(strncmp(s.c_str()+start, word.c_str(), word.size())==0)
		{
			if(backtracking(s, start+word.size(), wordDict))
			{
				return true;
			}
		}
	}
	return false;
}

// 记忆化回溯
enum{
	UNKNOWN=0,
	YES=1,
	NO=2,
};
bool wordBreak(string s, vector<string>& wordDict) 
{
	int memo[s.size()];
	memset(memo, 0, sizeof(memo));
	
	// backtracking(s, 0, wordDict, memo);
	// return memo[0];
	return backtracking(s, 0, wordDict, memo);
}

bool backtracking(const string& s, int start, const vector<string>& wordDict, int memo[])
{
	if(start>=s.size())
	{
		return true;
	}
	if(memo[start]!=UNKNOWN)
		return memo[start]==YES;
	for(int i=0; i<wordDict.size(); ++i)
	{
		string word=wordDict[i];
		if(word.size() > s.size()-start)
			continue;
		if(strncmp(s.c_str()+start, word.c_str(), word.size())==0)
		{
			if(backtracking(s, start+word.size(), wordDict, memo))
			{
				memo[start]=YES;
				return true;
			}
		}
	}
	memo[start]=NO;
	return false;
}

// BFS
// 时间复杂度O(n^n)
bool wordBreak(string s, vector<string>& wordDict) 
{
	queue<int> Q;
	Q.push(0);
	while(!Q.empty())
	{
		int pos=Q.front();
		Q.pop();
		
		if(pos>=s.size())
			return true;
		
		for(int i=0; i<wordDict.size(); ++i)
		{
			if(wordDict[i].size()<=s.size()-pos  &&  strncmp(s.c_str()+pos, wordDict[i].c_str(), wordDict[i].size())==0)
			{
				Q.push_back(pos+wordDict[i].size());
			}
		}
	}
	return false;
}

// BFS 时间复杂度O(n^2)
bool wordBreak(string s, vector<string>& wordDict) 
{
	queue<int> Q;
	Q.push(0);
	int visited[s.size()];
	memset(visited, 0, sizeof(visited));
	while(!Q.empty())
	{
		int pos=Q.front();
		Q.pop();
		
		if(pos>=s.size())
			return true;
		
		if(visited[pos]==true)
			continue;
		
		for(int i=0; i<wordDict.size(); ++i)
		{
			if(wordDict[i].size()<=s.size()-pos  &&  strncmp(s.c_str()+pos, wordDict[i].c_str(), wordDict[i].size())==0)
			{
				Q.push_back(pos+wordDict[i].size());
			}
		}
		visited[pos]=true;
	}
	return false;
}

bool wordBreak(string s, vector<string>& wordDict) 
{
	set<string> wordDictSet(wordDict.begin(), wordDict.end());
	bool dp[s.size()+1];
	memset(dp, 0, sizeof(dp));
	dp[0]=true;
	for(int i=1; i<=s.size(); i++)
	{
		for(int j=0; j<i; ++j)
		{
			string s2=s.substr(j, i-j);
			if(dp[j]  &&  wordDictSet.find(s2)!=wordDictSet.end())
			{
				dp[i]=true;
				break;
			}
		}
	}
	return dp[s.size()];
}