#include<string>
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<iostream>

using std::string;

void test()
{
	string s="12345";
	std::string s2="";
	printf("[%s], size=%d\n", s.c_str(), s.size());
	printf("s2 [%s], size=%d\n", s2.c_str(), s2.size());
	std::cout<<"["<<s<<"]\t["<<s2<<"]"<<std::endl;

	s[2]='\t';
	printf("[%s], size=%d\n", s.c_str(), s.size());
	s2=s;
	printf("s2 [%s], size=%d\n", s2.c_str(), s2.size());
	std::cout<<"["<<s<<"]\t["<<s2<<"]"<<std::endl;

	s[2]='\0';
	printf("[%s], size=%d\n", s.c_str(), s.size());
	s2=s;
	printf("s2 [%s], size=%d\n", s2.c_str(), s2.size());
	std::cout<<"["<<s<<"]\t["<<s2<<"]"<<std::endl;
}

std::string solution1(std::string str)
{
	int sz=str.size();
	int last=0;
	int cur=0;
	while(cur<sz)
	{
		bool duplicate=false;
		for(int i=0; i<last; i++)
			if(str[i]==str[cur])
			{
				duplicate=true;
				break;
			}
		if(duplicate)
		{
			cur++;
		}
		else
		{
			str[last++]=str[cur++];
		}
	}
	// str[last]='\0';
	// str.resize(last+1);
	str.resize(last);
	
	return str;
}

string solution1_2(string s)
{
	int len = s.length();
    if(len < 2) return s;
    string str = "";
	for(int i=0; i<len; i++)
	{
		if(s[i]!='\0')
		{
			str +=s[i];
			for(int j=i+1; j<len; j++)
				if(s[j]==s[i])
					s[j]='\0';
		}
	}
	return str;
}
void solution1_3(char s[])
{
    int len = strlen(s);
    if(len < 2) return;
    int p = 0;
    for(int i=0; i<len; ++i)
    {
        if(s[i] != '\0')
        {
            s[p++] = s[i];
            for(int j=i+1; j<len; ++j)
                if(s[j]==s[i])
                    s[j] = '\0';
        }
    }
    s[p] = '\0';
}

// 256字符，bitmap
std::string solution2(std::string str)
{
	//uint32_t *bitmap=new uint32_t[256];
	bool bitmap[256]={0};
	memset(bitmap, 0, sizeof(bitmap));
	int last=0;
	for(int i=0; i<str.size(); i++)
	{
		char c=str[i];
		uint32_t x=static_cast<unsigned char>(c);
		if(bitmap[x]==0)
		{
			str[last++]=c;
			bitmap[x]=true;
		}
	}
	//delete bitmap;
	// str[last]='\0';
	// str.resize(last+1);
	str.resize(last);
	
	return str;
}

// 26个字母，bitmap
std::string solution3(std::string str)
{
	uint32_t bitmap=0;
	int last=0;
	for(int i=0; i<str.size(); i++)
	{
		char c=str[i];
		uint32_t x=c-'a';
		if((bitmap & (1<<x))==0)
		{
			str[last++]=c;
			bitmap |= 1<<x;
		}
	}
	// str[last]='\0';
	// str.resize(last+1);
	str.resize(last);
	
	return str;
}

void solution3_2(char s[])
{
	int len=strlen(s);
	if(len<2) return;
	int check=0, p=0;
	for(int i=0; i<len; ++i)
	{
		int v=(int)(s[i]-'a');
		if( (check & (1<<v)) ==0)
		{
			s[p++]=s[i];
			check |= 1<<v;
		}
	}
	s[p]='\0';
}

int main()
{
	test();
	
	string s1 = "abcde";
    string s2 = "aaabbb";
    string s3 = "";
    string s4 = "abababc";
    string s5 = "ccccc";
	printf("\nsolution1\n");
	std::string res=solution1(s1);
	printf("(%s), size=%d\n", res.c_str(), res.size());
	res=solution1(s2);
	printf("(%s), size=%d\n", res.c_str(), res.size());
	res=solution1(s3);
	printf("(%s), size=%d\n", res.c_str(), res.size());
	printf("%s\n", solution1(s4).c_str());
	printf("%s\n", solution1(s5).c_str());
	
	printf("\nsolution2\n");
	printf("%s\n", solution2(s1).c_str());
	printf("%s\n", solution2(s2).c_str());
	printf("%s\n", solution2(s3).c_str());
	printf("%s\n", solution2(s4).c_str());
	printf("%s\n", solution2(s5).c_str());
	
	printf("\nsolution3\n");
	printf("%s\n", solution3(s1).c_str());
	printf("%s\n", solution3(s2).c_str());
	printf("%s\n", solution3(s3).c_str());
	printf("%s\n", solution3(s4).c_str());
	printf("%s\n", solution3(s5).c_str());
	return 0;
}