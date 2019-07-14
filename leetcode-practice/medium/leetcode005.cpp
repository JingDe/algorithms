
#include<string>
#include<stdio.h>

using std::string;

class Solution {
public:
    string longestPalindrome1(string s) {
        int sz=s.size();
		int res=sz;
		for(; res>1; --res)
		{
			for(int start=0; start<=sz-res; ++start)
			{
				string ss=s.substr(start, res);
				printf("%s\n", ss.c_str());
				/* if(isPalindrome(ss))
				{
					return ss;
				} */
			}
		}
		return s.substr(0, 1);
    }
	bool isPalindrome(const string& s)
	{
		int sz=s.size();
		for(int i=0; i<sz/2; ++i)
		{
			if(s[i]!=s[sz-1-i])
				return false;
		}
		return true;
	}
	
	// 最长公共子串解法
	/* string longestPalindrome2(string s)
	{
		string revs=reverseString(s);
		string subs;
		
		int curMaxLen=-1;
		int curEndi=0;
		int curEndj=0;
		while(true)
		{
			curMaxLen=lcSubstr(s, revs, subs, curMaxLen, curEndi, curEndj);
			
			if(isPalindrome(subs))
				return subs;
			
			
		}
	}
	
	int lcSubstr(const std::string& A, const std::string& B, std::string& subs, int curMaxSz, int curEndi, int curEndj)
	{
		int res=0;
		int endi=0;
		int endj=0;
		
		int sz1=A.size();
		int sz2=B.size();
		
		int d[MAXSZ+1][MAXSZ+1]={0};
		for(int i=0; i<MAXSZ; ++i)
			d[i][0]=d[0][i]=0;
		// memset(d, 0, sizeof(d));
		for(int i=0; i<sz1; ++i)
			for(int j=0; j<sz2; ++j)
			{
				if(A[i]==B[j])
				{
					d[i+1][j+1]=d[i][j]+1;
					//res=std::max(res, d[i+1][j+1]);
					if(d[i+1][j+1]>res)
					{
						res=d[i+1][j+1];
						endi=i;
						endj=j;
					}
				}
				else
				{
					d[i+1][j+1]=0;
				}
			}
		
		// from endj and endj of A and B, get AS and BS
		subs=A.substr(endi-res+1, res);
		
		return res;
	} */
	
	// 使用动态规划求回文串
	string longestPalindrome3(string s) {
		if(s.empty())
            return "";
        
		int len=s.length();
        bool dp[len][len]={false};

		string substr;
		
		for(int i=0; i<len; ++i)
		{
			dp[i][i]=true;
		}
		substr=s.substr(0, 1);
		for(int i=0; i<len-1; ++i)
		{
			dp[i][i+1]= (s[i]==s[i+1]);
			if(dp[i][i+1])
			{
				substr=s.substr(i, 2);
			}
		}
		
		for(int sz=3; sz<=len; ++sz)
			for(int i=0; i<=len-sz; ++i)
			{
				dp[i][i+sz-1]= (dp[i+1][i+sz-2]  &&  s[i]==s[i+sz-1]);
				if(dp[i][i+sz-1])
					substr=s.substr(i, sz);
			}
		return substr;
	}
	
	string longestPalindrome4(string s) {
		if(s.empty())
			return "";
		int start=0, end=0;
		for(int i=0; i<s.length(); ++i)
		{
			int len1=expandAroundCenter(s, i, i);
			int len2=expandAroundCenter(s, i, i+1);
			int len=std::max(len1, len2);
			if(len > end-start)
			{
				start=i-(len-1)/2;
				end=i+len/2;
			}
		}
		return s.substr(start, end+1);
	}
	// T=O(n)
	int expandAroundCenter(string s, int left, int right)
	{
		int L=left, R=right;
		while(L>=0  &&  R<s.length()  &&  s[L]==s[R])
		{
			L--;
			R++;
		}
		return R-L-1;
	}
};

void test()
{
	Solution s;
	string str="abacdfgdcaba";
	s.longestPalindrome1(str);

}

int main()
{
	test();
	
	return 0;
}