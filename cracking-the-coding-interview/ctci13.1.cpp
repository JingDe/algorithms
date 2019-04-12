
#include<string>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<fstream>

char* file=NULL;
const int k=5; // 要求文件最后k行内容
const int MAX_LINE=200; // 一行数组最大长度

// istream
void solution()
{
	char res[k][MAX_LINE]={0};
	int cur=0; // cur表示下一行存储位置
	
	FILE* f=freopen(file, "r", stdin);
	if(f==NULL)
		return;
	
	std::string line;
	int lines=0;
	while(getline(std::cin, line))
	{
		printf("getline %s\n", line.c_str());
		memcpy(res[cur], line.c_str(), line.size());
		res[cur][line.size()]=0;
		cur= (cur+1)%k;
		lines++;
	}
	fclose(stdin);
	
	int start=0;
	int resLines=lines;
	if(lines>k)
	{
		start=cur;
		resLines=k;
	}
	for(int i=0; i<resLines; i++)
	{
		printf("%d: %s\n", i, res[start]);
		start=(start+1)%k;
	}
	// for(int i=0; i<k; i++)
	// {
		// printf("%d: %s\n", i, res[cur]);
		// cur=(cur+1)%k;
	// }
}

// ifstream
void solution2(std::ifstream &fin, int k)
{
	std::string line[k];
	int lines=0;
	std::string tmp;
	while(getline(fin, tmp))
	{
		line[lines%k]=tmp;
		++lines;
	}
	int start, cnt;
	if(lines<k)
	{
		start=0;
		cnt=lines;
	}
	else
	{
		start=lines%k;
		cnt=k;
	}
	for(int i=0; i<cnt; ++i)
	{
		std::cout<<line[(start+i)%k]<<std::endl;
	}	
}


int main(int argc, char** argv)
{
	std::string fileName="input13.1.txt";
	if(argc>1)
	{
		fileName=argv[1];
	}
	printf("fileName %s\n", fileName.c_str());
	file=const_cast<char*>(fileName.c_str());
	
	{
		solution();
	}
	
	{
		printf("solution2\n");
		std::ifstream fin(fileName.c_str());
		solution2(fin, k);
	}
	
	return 0;
}

