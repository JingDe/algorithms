
#include<stdio.h>
#include<string>
#include<map>

using std::string;
using std::map;

// enum{
	// I=1,
	// V=5,
	// X=10,
	// L=50,
	// C=100,
	// D=500,
	// M=1000,
	
	
	// IV=4,
	// IX=9,
	// XL=40,
	// XC=90,
	// CD=400,
	// CM=900,
	
// };

class Solution {
public:
    std::map<char, int> c2int;
	std::map<string, int> str2int;
	int biggest=0;

	void init_map()
	{
		c2int['I']=1;
		c2int['V']=5;
		c2int['X']=10;
		c2int['L']=50;
		c2int['C']=100;
		c2int['D']=500;
		c2int['M']=1000;
		
		str2int["IV"]=4;
		str2int["IX"]=9;
		str2int["XL"]=40;
		str2int["XC"]=90;
		str2int["CD"]=400;
		str2int["CM"]=900;
	}
	
	bool parse(int nchar, char c1, char c2, int& ret)
	{
		ret=0;
		if(nchar==2)
		{
			string s=string(1, c1)+string(1, c2);
			if(str2int.find(s)!=str2int.end())
			{
				ret=str2int[s];
				return true;
			}
		}
		else if(nchar==1)
		{
			if(c2int.find(c1)!=c2int.end())
			{
				ret=c2int[c1];
				return true;
			}
		}
		return false;
	}
    
    int romanToInt(string s) {
        init_map();
		
        int res=0;
		int len=s.size();
		int tmp=0;
		for(int i=0; i<len; ++i)
		{
			if(i<len-1  &&  parse(2, s[i], s[i+1], tmp))
			{
				res+=tmp;
				++i;
			}
			else if(parse(1, s[i], s[i], tmp))
			{
				res+=tmp;
			}
			else
				return -1;
		}
		return res;
    }
};

int main()
{
	Solution solu;
	string s="MCMXCIV";
	int ret=solu.romanToInt(s);
	printf("%d\n", ret);
	
	return 0;
}