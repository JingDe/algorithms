
#include<string>
#include<stdio.h>

using std::string;

class Solution {
public:
	// 暴力解法
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
	
	// expand Around Center解法
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
		return s.substr(start, end-start+1);
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


// 再次分析暴力解法-》动态规划-》动态规划空间复杂度优化
string longestPalindrome4(string s)
{
	int length=s.size();
	bool P[length][length];
	int maxLen=0;
	string maxPal;
	for(int len=1; i<=length; len++)
	{
		for(int start=0; start<length; start++)
		{
			int end=start+len-1;
			if(end>=length)
				break;
			P[start][end]=(len==1  ||  len==2  ||  P[start+1][end-1]  &&  s[start]==s[end]);
			if(P[start][end]  &&  len>maxLen)
				maxPal=s.substr(start, len);
		}
	}
	return maxPal;
}
// 时间复杂度O(n*n)
// 空间复杂度O(n*n)

// 优化空间复杂度
string longestPalindrome4(string s)
{
	if(s.empty())
		return s;
	int n=s.length();
	string res;
	bool P[n];
	for(int i=n-1; i>=0; i--)
	{
		for(int j=n-1; j>=i; j--)
		{
			P[j]= (s[i]==s[j]  &&  (j-i<3  ||  P[j-1]));
			if(P[j]  &&  j-i+1>res.size())
				res=s.substr(i, j-i+1);
		}
	}
	return res;
}




// 最长公共子串解法
// 错误：
string longestPalindrome4(string s)
{
	if(s.empty())
		return s;
	string origin=s;
	string reverse=s;
	std::reverse(reverse.begin(), reverse.end());
	
	int length=s.length();
	int arr[length][length]; // 动态规划求解s和reverse的最长公共子串
	// arr[i][j]，表示s[0~i]和reverse[0~j]的，分别以s[i]和reverse[j]字符结尾的，最长公共子串长度
	memset(arr, 0, sizeof(arr));
	
	int maxLen=0;
	int maxEnd=0;
	for(int i=0; i<length; ++i)
	{
		for(int j=0; j<length; j++)
		{
			if(origin[i]==reverse[j])
			{
				if(i==0  ||  j==0)
					arr[i][j]=1;
				else
					arr[i][j]=arr[i-1][j-1]+1;
			}
			// else
				// arr[i][j]=0;
			
			if(arr[i][j]>maxLen)
			{				
				// TODO
				// 还需要判断 reverse倒置前的子串是否和origin的下标对应
				// origin[?~i] reverse[?~j]，长度maxLen
				// origin[i-maxLen+1 ... i]
				// reverse[j-maxLen+1 ... j], 倒置前的下标范围[len-1-(j) ... len-1-(j-maxLen+1)]
				// 判断len-1-j是否等于i-arr[i][j]+1
				
				maxLen=arr[i][j];
				maxEnd=i; // 当前最长公共子串的结尾字符的位置				
			}
			
		}
	}
	return s.substr(maxEnd-maxLen+1, maxLen);
}

string longestPalindrome4(string s)
{
	if(s.empty())
		return s;
	string origin=s;
	string reverse=s;
	std::reverse(reverse.begin(), reverse.end());
	
	int length=s.length();
	int arr[length][length]; // 动态规划求解s和reverse的最长公共子串
	// arr[i][j]，表示s[0~i]和reverse[0~j]的，分别以s[i]和reverse[j]字符结尾的，最长公共子串长度
	memset(arr, 0, sizeof(arr));
	
	int maxLen=0;
	int maxEnd=0;
	for(int i=0; i<length; ++i)
	{
		for(int j=0; j<length; j++)
		{
			if(origin[i]==reverse[j])
			{
				if(i==0  ||  j==0)
					arr[i][j]=1;
				else
					arr[i][j]=arr[i-1][j-1]+1;
			}
			// else
				// arr[i][j]=0;
			
			if(arr[i][j]>maxLen)
			{
				// 还需要判断 reverse倒置前的子串是否和origin的下标对应
				// origin[?~i] reverse[?~j]，长度maxLen
				// origin[i-maxLen+1 ... i]
				// reverse[j-maxLen+1 ... j], 倒置前的下标范围[len-1-(j) ... len-1-(j-maxLen+1)]
				// 判断len-1-j是否等于i-arr[i][j]+1
				
				int beforeRev = length-1-j;
				if(beforeRev == i-arr[i][j]+1)
				// if(beforeRev+arr[i][j]-1 == i)
				{				
					maxLen=arr[i][j];
					maxEnd=i; // 当前最长公共子串的结尾字符的位置				
				}
			}
			
		}
	}
	return s.substr(maxEnd-maxLen+1, maxLen);
}
// 时间O(n*n)
// 空间O(n*n)


// 最长公共子串解法，优化空间复杂度
// 根据dp[][]下标dp, i从小到大，j从大到小
string longestPalindrome4(string s)
{
	if(s.empty())
		return s;
	string origin=s;
	string reverse=s;
	std::reverse(reverse.begin(), reverse.end());
	
	int length=s.length();
	int arr[length];
	memset(arr, 0, sizeof(arr));
	
	int maxLen=0;
	int maxEnd=0;
	for(int i=0; i<length; ++i)
	{
		for(int j=length-1; j>=0; --j)
		{
			if(origin[i]==reverse[j])
			{
				if(i==0  ||  j==0)
					arr[j]=1;
				else
					arr[j]=arr[j-1]+1;
			}
			else
				arr[j]=0;
			
			if(arr[j]>maxLen)
			{
				int beforeRev = length-1-j;
				if(beforeRev+arr[j]-1 == i)
				{				
					maxLen=arr[j];
					maxEnd=i; 			
				}
			}
			
		}
	}
	return s.substr(maxEnd-maxLen+1, maxLen);
}



