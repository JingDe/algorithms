#include<stdio.h>
#include<string>

bool isSubstr(const std::string& s, const std::string& sub);

void isRotateStr(const std::string& s1, const std::string& s2)
{
	if(s1.size()!=s2.size()  ||  s1.empty())
		return;
	std::string s=s1+s1;
	if(isSubstr(s, s2))
	{
		printf("%s %s is rotateStr\n", s1.c_str(), s2.c_str());
	}
}

bool isSubstr(const std::string& s, const std::string& sub)
{
	if(s.find(sub)!=std::string::npos)
		return true;
	return false;
}

int main()
{
	{
		std::string s1="waterbottle";
		std::string s2="terbottlewa";
		isRotateStr(s1, s2);
	}
	{
		std::string s1="waterbottle";
		std::string s2="terbottleab";
		isRotateStr(s1, s2);
	}
	{
		std::string s1="waterbottle";
		std::string s2="terbottle";
		isRotateStr(s1, s2);
	}
	return 0;
}