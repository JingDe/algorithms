#include<string>
#include<stdio.h>

bool isPalindrome(const std::string& s)
{
	int sz=s.size();
	for(int i=0; i<sz/2; ++i)
	{
		if(s[i]!=s[sz-1-i])
			return false;
	}
	return true;
}

void test()
{
	std::string s="abcd";
	bool ret=isPalindrome(s);
	printf("%s, %d\n", s.c_str(), ret);
	
	s="aba";
	ret=isPalindrome(s);
	printf("%s, %d\n", s.c_str(), ret);
	
	s="abba";
	ret=isPalindrome(s);
	printf("%s, %d\n", s.c_str(), ret);
}

int main()
{
	test();
	
	return 0;
}
	