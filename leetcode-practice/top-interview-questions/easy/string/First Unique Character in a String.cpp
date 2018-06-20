class Solution {
public:
    int firstUniqChar(string s) {
        int len=s.length();
        for(int i=0; i<len; i++)
        {
        	string::iterator rpos=std::find(s.begin()+i+1, s.end(), s[i]);
        	string::iterator lpos;
        	if((rpos==s.end())  &&  (lpos=std::find(s.begin(), s.begin()+i, s[i])) == s.begin()+i)
        	{
        		return i;
			}
		}
		return -1;
    }
};
