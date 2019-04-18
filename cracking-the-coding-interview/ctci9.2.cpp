#include<string>
#include<algorithm>


bool comp_string(const std::string& s1, const std::string& s2)
{
	std::string s3=s1;
	std::sort(s3.begin(), s3.end());// 字典序排序
	
	std::string s4=s2;
	std::sort(s4.begin(), s4.end());
	return s3-s4;
	// return s3>s4;
}

bool comp_string2(std::string s1, std::string s2)
{
	std::sort(s1.begin(), s1.end());// 字典序排序
	
	std::sort(s2.begin(), s2.end());
	return s1-s2;
}

bool comp_string3(std::string s1, std::string s2)
{
	std::sort(s1.c_str(), s1.c_str()+s1.size());// 字典序排序
	std::sort(s1.data(), s1.data()+s1.length());
	
	
	std::sort(s2.begin(), s2.end());
	return s1-s2;
}
// int array[] 的长度，sizeof(array)/sizeof(array[0])
// char array[] 的长度，sizoef(array)/sizeof(array[0])
void solution1(std::string array[], int sz)
{
	std::sort(array, array+sz, comp_string);
	for(int i=0; i<sz; i++)
	{
		printf("%s, ", array[i].c_str());
	}
	printf("\n");
}

void solution2(std::vector<std::string> array)
{
	std::sort(array.begin(), array.end(), comp_string);
	for(int i=0; i<sz; i++)
	{
		printf("%s, ", array[i].c_str());
	}
	printf("\n");
}





// ==================================================================

void solution3(char array[][])
{
	
}

bool comp(const char* s1, const char* s2)
{
	std::qsort(s1, strlen(s1), 1, comp_char);
	std::sort(s2, strlen(s2), 1, comp_char);
	return s3-s4;
	// return s3>s4;
}

bool comp_char(const void* a, const void* b)
{
	char c=*((const char*)a);
	char d=*((const char*)b);
	return c-d;
}


int main()
{
	{
		
	}
	
	return 0;
}