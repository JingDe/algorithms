#include<string>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<vector>

int comp_char(const void* a, const void* b);


// 
bool comp_string(const std::string& s1, const std::string& s2)
{
	std::string s3=s1;
	std::sort(s3.begin(), s3.end());// 字典序排序
	
	std::string s4=s2;
	std::sort(s4.begin(), s4.end());
	return s3<s4; // 字典序比较std::string
}

bool comp_string2(std::string s1, std::string s2)
{
	std::sort(s1.begin(), s1.end());
	std::sort(s2.begin(), s2.end());
	return s1<s2;
}

bool comp_string3(std::string s1, std::string s2)
{
	// 以下几种方式？？
	std::sort(s1.begin(), s1.end());
	std::sort(&s1[0], &s1[0]+s1.length());
	std::sort(const_cast<char*>(s1.c_str()), const_cast<char*>(s1.c_str())+s1.size());
	std::sort(const_cast<char*>(s1.data()), const_cast<char*>(s1.data())+s1.length());
	std::qsort((void*)const_cast<char*>(s1.c_str()), s1.size(), 1, comp_char);
		
	std::sort(s2.begin(), s2.end());
	return s1<s2;
}

void test_comp_string3()
{
	{
		std::string s1="8932547";
		std::sort(s1.begin(), s1.end());
		printf("%s\n", s1.c_str());
	}
	{
		std::string s1="8932547";
		std::sort(&s1[0], &s1[0]+s1.length());
		printf("%s\n", s1.c_str());
	}
	{
		std::string s1="8932547";
		std::sort(const_cast<char*>(s1.c_str()), const_cast<char*>(s1.c_str())+s1.size());
		printf("%s\n", s1.c_str());
	}
	{
		std::string s1="8932547";
		std::sort(const_cast<char*>(s1.data()), const_cast<char*>(s1.data())+s1.length());
		printf("%s\n", s1.c_str());
	}
	{
		std::string s1="8932547";
		std::qsort((void*)const_cast<char*>(s1.c_str()), s1.size(), 1, comp_char);
		printf("%s\n", s1.c_str());
	}
}

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
	std::sort(array.begin(), array.end(), comp_string2);
	for(int i=0; i<array.size(); i++)
	{
		printf("%s, ", array[i].c_str());
	}
	printf("\n");
}

// ==================================================================================================
void print_vector(const std::vector<std::string>& vec)
{
	int cnt=0;
	for(std::vector<std::string>::const_iterator it=vec.begin(); it!=vec.end(); ++it)
	{
		std::string str=*it;
		printf("%d[%s], ", ++cnt, str.c_str());
	}
	printf("\n");
}

void test_vector_of_string()
{
	std::vector<std::string> vec;
	printf("vec capacity=%d, vec.size=%d\n", vec.capacity(), vec.size());
	// vec.emplace(vec.end(), "string01");
	// printf("vec capacity=%d, vec.size=%d\n", vec.capacity(), vec.size());
	vec.push_back(std::string("string01"));
	printf("vec capacity=%d, vec.size=%d\n", vec.capacity(), vec.size());
	print_vector(vec);
	
	vec.reserve(6);
	printf("vec capacity=%d, vec.size=%d\n", vec.capacity(), vec.size());
	print_vector(vec);
	
	vec.resize(9);
	printf("vec capacity=%d, vec.size=%d\n", vec.capacity(), vec.size());
	print_vector(vec);
	
	vec.push_back(std::string("string01"));
	printf("vec capacity=%d, vec.size=%d\n", vec.capacity(), vec.size());
	print_vector(vec);
}



// ==================================================================

int comp_char(const void* a, const void* b)
{
	const char c=*((const char*)a);
	const char d=*((const char*)b);
	return c-d; // 返回负数表示a小于b
}

int comp_charstr(const void* s1, const void* s2)
{
	char s3[strlen((const char*)s1)+1];
	//memcpy(s3, s1, strlen(s1));		s3[strlen(s1)]=0;
	strcpy(s3, (const char*)s1);
	std::qsort((void*)s3, strlen(s3), 1, comp_char);
	
	char s4[strlen((const char*)s2)+1];
	strcpy(s4, (const char*)s2);
	std::qsort((void*)s4, strlen(s4), 1, comp_char);
	
	return strcmp(s3, s4);
}

int comp_charstr2(const void* s1, const void* s2)
{
	const char* c1=*((const char**)(s1));
	const char* c2=*((const char**)s2);
	//printf("before comp_charstr2 : %s, %s\n", c1, c2);
	
	//std::string s3((const char*)s1);
	std::string s3((const char*)c1);
	std::sort(s3.begin(), s3.end());
	
	std::string s4((const char*)c2);
	std::sort(s4.begin(), s4.end());
	if(s3<s4)
	{
		//printf("%s < %s\n", s3.c_str(), s4.c_str());
		return -1;
	}
	else if(s3==s4)
	{
		//printf("%s == %s\n", s3.c_str(), s4.c_str());
		return 0;
	}
	else
	{
		//printf("%s > %s\n", s3.c_str(), s4.c_str());
		return 1;
	}
}

void solution3(char** array, int row, int col)
{
	//std::sort(array, array+3, comp_charstr2);
	std::qsort((void*)array, row, sizeof(char*), comp_charstr2);
	for(int i=0; i<row; i++)
		printf("%d[%s], ", 1+i, array[i]);
	printf("\n");
}


// ================================================================================================
int main()
{
	{
		test_vector_of_string();
	}
	
	{
		test_comp_string3();
	}
	{
		std::string s[] = {
			"axyz", "abc", "yzax", "bac", "zyxa", "fg", "gf"
		};
		solution1(s, 7);
	}
	
	{
		std::vector<std::string> vec{"axyz", "abc", "yzax", "bac", "zyxa", "fg", "gf"};
		solution2(vec);
	}
	{
		char array[7][5]={"axyz", "abc", "yzax", "bac", "zyxa", "fg", "gf"};
		//solution3(array, 7, 5); // array类型char (*)[5]
		//solution3(&array[0], 7, 5); // &array[0]类型char (*)[5]。array[0]类型是char*。
		
	}
	
	
	{
		printf("\n================test3===============\n");
		//char array[7][5]={"axyz", "abc", "yzax", "bac", "zyxa", "fg", "gf"};
		char **array=new char*[7];
		for(int i=0; i<7; i++)
			array[i]=new char[5];
		strcpy(array[0], "axyz");
		strcpy(array[1], "abc");
		strcpy(array[2], "yzax");
		strcpy(array[3], "bac");
		strcpy(array[4], "zyxa");
		strcpy(array[5], "fg");
		strcpy(array[6], "gf");
		
		solution3(array, 7, 5);
		delete[] array;
	}
	
	return 0;
}