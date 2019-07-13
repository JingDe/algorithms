
class Solution {
public:
    string longestPalindrome(string s) {
        int sz=s.size();
		int res=sz;
		for(; res>1; --res)
		{
			for(int start=0; start<=sz-res; ++start)
			{
				string ss=s.substr(start, res);
				if(isPalindrome(ss))
				{
					return res;
				}
			}
		}
		return 1;
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
};