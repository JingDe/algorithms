#include<string>
#include<stdio.h>
#include<algorithm>

std::string replaceSpace(std::string str)
{
	std::string res;
	int spaceCnt=std::count(str.begin(), str.end(), ' ');
	res.resize(str.size()+2*spaceCnt);
	
	int j=res.size()-1;
	for(int i=str.size()-1; i>=0; --i)
	{
		if(str[i]!=' ')
			res[j--]=str[i];
		else
		{
			res[j--]='0';
			res[j--]='2';
			res[j--]='%';
		}
	}
	//printf("j=%d\n", j);
	return res;
}

int main()
{
	{
		std::string str=" 1abc 22";
		std::string res=replaceSpace(str);
		printf("%s(%d) ——> %s(%d)\n", str.c_str(), str.size(), res.c_str(), res.size());
	}
	
	{
		std::string str="  ";
		std::string res=replaceSpace(str);
		printf("%s(%d) ——> %s(%d)\n", str.c_str(), str.size(), res.c_str(), res.size());
	}
	return 0;
}