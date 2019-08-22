int numDecodings(string s) {
	if(s.empty())
		return 0;
	int sz=s.size();
	long long dp[sz];
	memset(dp, 0, sizeof(dp));
	dp[0]=1;

	for(int i=1; i<sz; ++i)
	{
		dp[i]=dp[i-1];
		/* if(check(s, i-1, 2))
		{
			if(i>=2)
				dp[i]+=dp[i-2];// dp[-1]=0
			else
				dp[i]+=1;
		} */
		int ret=check2(s, i-1, 2);
		if(ret==0)
			return 0;
		else if(ret==3)
		{
			if(i>=2)
				dp[i]+=dp[i-2];
			else
				dp[i]+=1;
		}
			
		printf("dp[%d]=%lld\n", i, dp[i]);
	}
	return dp[sz-1];
}

bool check(string s, int pos, int cnt) // 检查字符串s的pos开始的cnt位子串，表示的整数是否在10到26之间
{
	string subS=s.substr(pos, cnt);
	int x=atoi(subS.c_str());
	if(x>=10  &&  x<=26)
		return true;
	return false;
}

int check2(string s, int pos, int cnt)
{
	string subS=s.substr(pos, cnt);
	int x=atoi(subS.c_str());
	
	if(x==0)
		return 1;
	
	if(s[0]=='0'  &&  s[1]!='0')
		return 2;
	if(s[0]!='0'  &&  s[1]=='0'  &&  x>26)
		return 2;
	if(s[0]!='0'  &&  s[1]!='0'  &&  x>26)
		return 2;
	
	return 3;
}

// 递归方法
int numDecodings(string s)
{
	if(s.empty())
		return 0;
	return digui(s, 0);
}

int digui(string& s, int start) // 从start开始的子串的编码的个数
{
	if(start==s.size())
		return 1;
	// 以0开始的编码不存在
	if(s[start]=='0)
		return 0;
	
	int ans1=digui(s, start+1);
	int ans2=0;
	if(start<s.size()-1)
	{
		int ten=s[start]-'0'; // 不等于0
		int one=s[start+1]-'0';
		if(ten*10+one<=26)
		{
			ans2=digui(s, start+2);
		}
	}
	return ans1+ans2;
}


// 动态规划
int numDecodings(string s)
{
	if(s.empty())
		return 0;
	int len=s.size();
	int dp[len+1];
	memset(dp, 0, sizeof(dp));
	
	dp[len]=1; // 避免特殊处理	
	if(s[len-1]=='0')
		dp[len-1]=0;
	else
		dp[len-1]=1;
	
	for(int i=len-2; i>=0; --i)
	{
		if(s[i]=='0')
		{
			dp[i]=0;
			continue;
		}
		if((s[i]-'0')*10+s[i+1]-'0' <= 26)
			dp[i]=dp[i+1]+dp[i+2];
		else
			dp[i]=dp[i+1];
	}
	return dp[0];
}


