
class Solution {
public:
    int strStr(string haystack, string needle) {
        // 返回needle在haystack中首次出现的位置，否则-1
		// 方法一：简单的模式匹配算法 
		// return simple(haystack, needle);
		 
		// 方法二：KMP算法
		int strStr(string haystack, string needle) {
        int len2=needle.size();
		int *next=new int[len2+1]; // 注意长度 
		get_next(needle, next);
        printNext(next, len2+1);
		int result=KMP(haystack, needle, next);
        std::cout<<result<<std::endl;
        delete []next;
        return result;
    }
    int KMP(const string& haystack, const string& needle, int *next)
	{
		int len1=haystack.size();
    	int len2=needle.size();
    	int i=0, j=0;
    	while(j<len2  &&  i<len1)
    	{
    		if(j==-1  ||  haystack[i]==needle[j])
    		{
    			i++;
    			j++;
			}
			else
			{
				j=next[j];
			}
		}
		if(j==len2)
			return i-len2;
		return -1;
	}
	
	// 此计算next数组的函数实际计算到next[len2]了 
	void get_next(const string& needle, int *next)
	{
		int len2=needle.size();
		next[0]=-1;
		
		//next[1]=0;
		//int i=1, j=0;
		int i=0, j=-1;
		
		while(i<len2)
		{
			if(j==-1  ||  needle[i]==needle[j])	
			{
				i++;
				j++;
				next[i]=j;
			}
			else
			{
				j=next[j];
			}
		}
	}
    void printNext(int *next, int len2)
    {
        for(int i=0; i<len2; i++)
            std::cout<<next[i]<<" ";
        std::cout<<std::endl;
    }
    
    int simple(const string& haystack, const string& needle)
    {
    	int len1=haystack.size();
    	int len2=needle.size();
    	int i=0, j=0;
    	while(j<len2  &&  i<len1)
    	{
    		if(haystack[i]==needle[j])
    		{
    			i++;
    			j++;
			}
			else
			{
				i=i-j+1;
				j=0;
			}
		}
		if(j==len2)
			return i-len2;
		return -1;
	}
	
};


class Solution {
public:
    int strStr(string haystack, string needle) {
        int len2=needle.size();
		int *next=new int[len2];
		get_next(needle, next);
        printNext(next, len2);
		int result=KMP(haystack, needle, next);
        std::cout<<result<<std::endl;
        delete []next;
        return result;
    }
    int KMP(const string& haystack, const string& needle, int *next)
	{
		int len1=haystack.size();
    	int len2=needle.size();
    	int i=0, j=0;
    	while(j<len2  &&  i<len1)
    	{
    		if(j==-1  ||  haystack[i]==needle[j])
    		{
    			i++;
    			j++;
			}
			else
			{
				j=next[j];
			}
		}
		if(j==len2)
			return i-len2;
		return -1;
	}
	
	void get_next(const string& needle, int *next)
	{
		int len2=needle.size();
		next[0]=-1;
		
		//next[1]=0;
		//int i=1, j=0;
		int i=0, j=-1;
		
		while(i<len2-1)
		{
			if(j==-1  ||  needle[i]==needle[j])	
			{
				i++;
				j++;
				next[i]=j;
			}
			else
			{
				j=next[j];
			}
		}
	}
    void printNext(int *next, int len2)
    {
        for(int i=0; i<len2; i++)
            std::cout<<next[i]<<" ";
        std::cout<<std::endl;
    }
};
