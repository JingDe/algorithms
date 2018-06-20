class Solution {
public:
    bool isPalindrome(string s) {
        int len=s.length();
        int i=0, j=len-1;
        while(i<j)
        {
        	char left=s[i];
        	while(isalnum(left)==0  &&  i<j)
        		left=s[++i];
        	char right=s[j];
        	while(isalnum(right)==0  &&  i<j)
        		right=s[--j];
            
            if(tolower(left)!=tolower(right))
            {             
                return false;
            }
            
        	i++;
        	j--;
		}
		return true;
    }
};
