#include<string>
#include<stdio.h>
#include<algorithm>

int comp_char(const void* a, const void* b)
{
	char c1=*(static_cast<const char*>(a));
	char c2=*(static_cast<const char*>(b));
	return c1>c2;
	// 若a小于b,返回负数
}

// 先排序再比较是否相等
bool isAnagram1(const std::string& s1, const std::string& s2)
{
	std::string s3=s1, s4=s2;
	printf("%s, %s\n", s3.c_str(), s4.c_str());
	std::sort(s3.begin(), s3.end());
	std::sort(s4.begin(), s4.end());
	
	qsort((void*)const_cast<char*>(s3.c_str()), s3.size(), 1, comp_char);
	qsort((void*)const_cast<char*>(s3.c_str()), s3.size(), 1, &comp_char);
	
	
	printf("%s, %s\n", s3.c_str(), s4.c_str());
	if(s3==s4)
		return true;
	return false;
}

// 比较统计出来的字符出现次数是否相等
// bool isAnagram2(const std::string& s1, const std::string& s2)
// {
	// int cnt[256]={0};
	// for(int i=0; i<s1.size(); i++)
	// {
		// char c=s1[i];
		// int x=static_cast<unsigned int>(c);
		// cnt[x]++;
	// }
	// for(int i=0; i<s2.size(); i++)
	// {
		// char c=s2[i];
		// int x=static_cast<unsigned int>(c);
		// cnt[x]--;
	// }
	// for(int i=0; i<256; i++)
		// if(cnt[i])
		// {
			// printf("%d, %d not 0\n", i, cnt[i]);
			// return false;
		// }
	// return true;
// }

bool isAnagram2(const std::string& s1, const std::string& s2)
{
	if(s1.size()!=s2.size())
		return false;
	int cnt[256]={0};
	for(int i=0; i<s1.size(); i++)
	{
		char c=s1[i];
		int x=static_cast<unsigned int>(c);
		cnt[x]++;
		
		c=s2[i];
		x=static_cast<unsigned int>(c);
		cnt[x]--;
	}
	for(int i=0; i<256; i++)
		if(cnt[i])
		{
			printf("%d, %d not 0\n", i, cnt[i]);
			return false;
		}
	return true;
}

int main()
{
	{
		std::string s1="abbcc";
		std::string s2="abcdd";
		std::string s3="abddc";
		printf("%s %s, %d\n", s1.c_str(), s2.c_str(), isAnagram1(s1, s2));
		printf("%s %s, %d\n", s2.c_str(), s3.c_str(), isAnagram1(s2, s3));
		
		printf("%s %s, %d\n", s1.c_str(), s2.c_str(), isAnagram2(s1, s2));
		printf("%s %s, %d\n", s2.c_str(), s3.c_str(), isAnagram2(s2, s3));
	}
	
	return 0;
}