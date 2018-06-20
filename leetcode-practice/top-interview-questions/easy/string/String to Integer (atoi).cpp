#include<iostream>
#include<string>
#include<cassert>

using std::string;

class Solution {
public:
    int myAtoi(string str) {
    	// 忽略开头的空格，一个正负号加上尽可能长的数字串
		// 忽略后面的字符
		// 如果开头的空格之后的连续子串不是数字返回0，如果不存在这样的子串返回0 
        int len=str.size();
        int i=0;
        int positive=1;
        
        while(str[i]==' '  &&  i<len)
        	i++;
        if(i>=len)
        	return 0;
        if(!isdigit(str[i])  &&  !isSign(str[i]))
        	return 0;
        if(i<len-1  &&  !isdigit(str[i])  &&  !isdigit(str[i+1]))
        	return 0;
        if(i<len-1  &&  isSign(str[i]))
        {
            if(str[i]=='-')
                positive=-1;
            i++;
        }
         	
        int j, res=0;
		j=i; 
        while(j<len  &&  isdigit(str[j]))
        {
        	int t=str[j]-'0';
        	        	
        	if(Overflow(res, t, positive)==true) // 当前res，符号positive，添加t判断将不将溢出 
        	{
        		if(positive==1)
        			return INT_MAX;
        		else
        			return INT_MIN;
			}
			
        	res=res*10+t;  	
			j++;
		}
		return (res*positive);
    }
    bool isSign(char c) 
    {
    	return (c=='+'  ||  c=='-');
	}
	bool Overflow(int curr, int delta, int positive) // 该函数认为-2147483648即INT_MIN溢出，但不影响返回值INT_MIN 
	{
		if(curr>INT_MAX/10  ||  (curr==INT_MAX/10  &&  delta>INT_MAX % 10))
			return true;
		return false;
	}
};


string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

int main()
{
	std::cout<<"INT_MAX="<<INT_MAX<<", INT_MIN="<<INT_MIN<<std::endl;
	
	Solution s;
	std::cout<<"      -11919730356x"<<" -->> "<<s.myAtoi("      -11919730356x")<<std::endl;
	
	//std::cout<<s.Overflow(1191973035, 6, -1)<<std::endl;
	
	//std::cout<<s.Overflow(214748364, 8, -1)<<std::endl;
	
	system("pause");
	return 0;
} 
