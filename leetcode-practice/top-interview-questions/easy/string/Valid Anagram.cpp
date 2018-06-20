class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s);
    	sort(t);
    	
        int len1=s.size();
        int len2=t.size();
        if(len1!=len2)
        	return false;
        for(int i=0; i<len1; i++)
        	if(s[i]!=t[i])
        		return false;
        return true;
    }
    void sort(string& s)
	{
		std::qsort(const_cast<char*>(s.data()), s.size(), sizeof(char), [](const void* a, const void* b){
    		int arg1=*static_cast<const char*>(a);
    		int arg2=*static_cast<const char*>(b);
    		if(arg1<arg2)  return -1;
    		if(arg1>arg2)  return 1;
    		return 0;
		});
    }
    bool isAnagram(string s, string t) {
    	int len1=s.size();
        int len2=t.size();
        if(len1!=len2)
        	return false;
        int counter[26];
        memset(counter, 0, sizeof(counter));
        for(int i=0; i<len1; i++)
        {
			counter[s[i]-'a']++;
        	counter[t[i]-'a']--;
        }
        for(int i=0; i<26; i++)
        	if(counter[i]!=0)
        		return false;
		return true; 
    }
    bool isAnagram(string s, string t) {
    	int len1=s.size();
        int len2=t.size();
        if(len1!=len2)
        	return false;
        int counter[26];
        memset(counter, 0, sizeof(counter));
        for(int i=0; i<len1; i++)
        {
			counter[s[i]-'a']++;        	
        }
        for(int i=0; i<len2; i++)
        {
        	counter[t[i]-'a']--;
        	if(counter[t[i]-'a'] < 0)
        		return false;
		}
        for(int i=0; i<26; i++)
        	if(counter[i]>0)
        		return false;
        return true;
    }
};
