class Solution {
public:
    string reverseString(string s) {
        string res;
        int len=s.size();
        for(int i=len-1; i>=0; i--)
        {
        	res.push_back(s[i]);
		}
		return res;
    }
};
