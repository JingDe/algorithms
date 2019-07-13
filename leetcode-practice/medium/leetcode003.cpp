
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int res=0;
		int sz=s.size();
		
		int start=0;
		for(int i=0; i<sz; ++i)
		{
			char c=s[i];
			int j=i-1;
			for(; j>=start  &&  s[j]!=c; --j)
			{
				
			}
			start=j+1;
			res=max(res, i-start+1);
		}
		
		return res;
	}
    // int lengthOfLongestSubstring(string s) {
        // std::set<char> curSet;
		// int res=0;
		// int cur=0;
		
		// int sz=s.size();
		// for(int i=0; i<sz; ++i)
		// {
			// char c=s[i];
			// if(curSet.count(c))
			// {
				// cur=1;
				// curSet.clear();
				// curSet.insert(c);
				// res=std::max(res, cur);
			// }
			// else
			// {
				// cur+=1;
				// curSet.insert(c);
				// res=std::max(res, cur);
			// }
		// }
		
		// return res;
    // }
};