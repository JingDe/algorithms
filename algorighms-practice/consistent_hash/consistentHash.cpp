#include<stdio.h>
#include<string>

extern int stringHashFunction(std::string s);

void test_stringHash()
{
	setHashFunctionSeed("123456789012345678");
	
	std::string s="wangjing";
	int hashValue=stringHashFunction(s);
	printf("%s hashValue %s\n", s.c_str(), hashValue.c_str());
}

int main()
{
	{
	test_stringHash();
	}
	
	
	return 0;
}