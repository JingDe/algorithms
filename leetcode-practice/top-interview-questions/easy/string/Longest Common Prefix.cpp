class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n=strs.size();
        if(n==0)
            return string();
        int len=0;
        int len1=strs[0].size();
        while(len<len1)
        {
        	char x=strs[0][len]; 
        	// 循环的每一趟，比较每个string的第len个字符 
        	for(int i=1; i<n; i++) 
        	{
        		if(len>=strs[i].length() || strs[i][len]!=x)
        			return string(strs[0], 0, len);
    
			}
			len++;
		}
		return string(strs[0], 0, len);
    }
};
