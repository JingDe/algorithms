#include<string>
#include<algorithm>
#include<stdio.h>
#include<vector>

// stl next_permutation
void arrange1(const std::string& s)
{
	std::string str=s;
	std::sort(str.begin(), str.end());
	do{
		printf("%s\n", str.c_str());
	}while(std::next_permutation(str.begin(), str.end()));
}


// ===============================================================================
void get_permutation(const std::string& str, int cur, std::string& ang);
void get_permutation2(const std::string& str, int cur, std::string& ang);

void arrange2(const std::string& s)
{
	std::string ang;
	std::string str=s;
	std::sort(str.begin(), str.end());
	get_permutation2(str, 0, ang);
}

// 有重复元素时，会有重复排列
// void get_permutation(const std::string& str, int cur, std::string& ang)
// {
	// if(cur==str.size())
	// {
		// printf("%s\n", ang.c_str());
		// return;
	// }
	// for(int i=0; i<str.size(); i++) // 在str中寻找出现次数多于在ang中出现次数的字符
	// {
		// int c1=std::count(str.begin(), str.end(), str[i]);
		// int c2=std::count(ang.begin(), ang.end(), str[i]);
		////printf("%s has %d %c, %s has %d %c\n", str.c_str(), c1, str[i], ang.c_str(), c2, str[i]);
		// if( c1 > c2 )
		// {
			// ang.append(1, str[i]);
			// get_permutation(str, cur+1, ang);
			// ang.resize(ang.size()-1);
		// }
	// }
// }

void get_permutation2(const std::string& str, int cur, std::string& ang)
{
	if(cur==str.size())
	{
		printf("%s\n", ang.c_str());
		return;
	}
	for(int i=0; i<str.size(); i++) // 在str中寻找出现次数多于在ang中出现次数的字符
	{
		if(i!=0  &&  str[i]==str[i-1])
			continue;
		int c1=std::count(str.begin(), str.end(), str[i]);
		int c2=std::count(ang.begin(), ang.end(), str[i]);
		//printf("%s has %d %c, %s has %d %c\n", str.c_str(), c1, str[i], ang.c_str(), c2, str[i]);
		if( c1 > c2 )
		{
			ang.append(1, str[i]);
			get_permutation2(str, cur+1, ang);
			ang.resize(ang.size()-1);
		}
	}
}

// =====================================================================
void printArrange(const std::vector<std::string> &permu);
std::vector<std::string> get_permutation3(const std::string& str, int cur);

void arrange3(const std::string& s)
{
	std::string str=s;
	//std::sort(str.begin(), str.end());
	std::vector<std::string> permu=get_permutation3(str, 0);
	printArrange(permu);
}

void printArrange(const std::vector<std::string> &permu)
{
	printf("%d permutation\n", permu.size());
	for(std::vector<std::string>::const_iterator it=permu.begin(); it!=permu.end(); ++it)
	{
		printf("%s\n", it->c_str());
	}
	printf("\n");
}

// 有重复子集
std::vector<std::string> get_permutation3(const std::string& str, int cur)
{
	std::vector<std::string> permu;
	if(cur==str.size()-1)
	{
		std::string s;
		s.assign(1, str[str.size()-1]);
		permu.push_back(s);
		return permu;
	}
	std::vector<std::string> res=get_permutation3(str, cur+1);
	for(std::vector<std::string>::iterator it=res.begin(); it!=res.end(); ++it)
	{
		std::string s=*it;
		//for(std::string::iterator it2=s.begin(); it2!=s.end(); ++it2)
		for(int i=0; i<=s.size(); ++i)
		{
			std::string s2=s;
			s2.insert(i, 1, str[cur]);
			permu.push_back(s2);
		}
	}
	return permu;
}


int main()
{
	// {
		// std::string s1="bdcae";
		// std::string s2="bbcad";
		// printf("%s permutation:\n", s1.c_str());
		// arrange1(s1);
		// printf("%s permutation:\n", s2.c_str());
		// arrange1(s2);
	// }
	{
		std::string s1="bdcae";
		std::string s2="bbcad";
		printf("%s permutation:\n", s1.c_str());
		arrange2(s1);
		printf("%s permutation:\n", s2.c_str());
		arrange2(s2);
	}
	{
		std::string s1="bdcae";
		std::string s2="bbcad";
		printf("%s permutation:\n", s1.c_str());
		arrange3(s1);
		printf("%s permutation:\n", s2.c_str());
		arrange3(s2);
	}
	
	{
		std::string s1="bdcae";
		std::string s2="bbcad";
		printf("%s permutation:\n", s1.c_str());
		arrange3_1(s1);
		printf("%s permutation:\n", s2.c_str());
		arrange3_1(s2);
	}
	return 0;
}