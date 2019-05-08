#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

// 外部排序一个大文件

//int size=2*1024*1024;// kb
//int mem_limit=; // 内存限制，小文件大小
int batch_cnt=10000; // 一个小文件保存的字符串个数

const std::string tmp_dir="/tmp/"; // 中间文件和结果文件路径
const std::string result_file="9.4.out.txt";

bool readline(FILE* f, std::string &line);
FILE* create_tmp_file(int number);
void outputTmpfile(const std::vector<std::string>& lines, FILE* file);
void rm_tmpfiles(int number);


int splitSort(FILE* file);
int splitSort2(FILE* file);
void merge(int cnt);

std::string to_string(int number)
{
	std::string s;
	//std::string es="";
	while(number)
	{
		char c=(number%10)+'0';
		s=c+s;
		number=number/10;
	}
	return s;
}


// 从FILE*对应的文件，读取一行长度不确定的字符串
bool readline(FILE* f, std::string &line)
{
	line.clear();
	if(f==NULL)
		return false;
	char c;
	while(fscanf(f, "%c", &c)!=EOF)
	{
		if(c!='\n'  &&  c!='\r')
			line.append(1, c);
		else
		{
			//printf("get [%c]\n", c);
			// if(c=='\n')
				// printf("get \\n\n");
			// else
				// printf("get \\r\n");
			return true;
		}
	}
	return false;
}

// 分块读取一个大文件，每次排序输出一个小文件
// int splitSort(FILE* file)
// {
	// int cnt=0;
	// std::vector<std::string> lines;
	// std::string line;
	// FILE* tmpfile=NULL;
	// while(readline(file, line))
	// {
		// if(lines.size()<batch_cnt)
			// lines.push_back(line);
		// else
		// {
			// std::sort(lines.begin(), lines.end());
			// tmpfile=create_tmp_file(cnt);
			// outputTmpfile(lines, tmpfile);
			// fclose(tmpfile);
			// ++cnt;
			
			// lines.clear();
		// }
	// }
	// if(!lines.empty())
	// {
		// std::sort(lines.begin(), lines.end());
		// tmpfile=create_tmp_file(cnt);
		// outputTmpfile(lines, tmpfile);
		// fclose(tmpfile);
		// ++cnt;
	// }
	// return cnt;
// }

// 分块读取一个大文件，每次排序输出一个小文件
int splitSort2(FILE* file)
{
	int cnt=0;
	std::vector<std::string> lines;
	std::string line;
	FILE* tmpfile=NULL;
	bool got=true;
	while(true)
	{
		got=readline(file, line);
		if(got)
			lines.push_back(line);
		
		if((got==false  &&  !lines.empty())  ||  lines.size()>=batch_cnt)
		{
			std::sort(lines.begin(), lines.end());
			tmpfile=create_tmp_file(cnt);
			outputTmpfile(lines, tmpfile);
			fclose(tmpfile);
			++cnt;
			
			lines.clear();
		}
		
		if(got==false)
			break;
	}
	return cnt;
}

FILE* create_tmp_file(int number)
{
	//std::string filename="9.4_tmp"+std::to_string(number)+".txt";
	std::string filename="9.4_tmp"+to_string(number)+".txt";
	std::string path=tmp_dir+"/"+filename;
	//int fd=creat(path.c_str(), S_IRWXU);// linux
	FILE* f=fopen(path.c_str(), "w");
	if(f==NULL)
	{
		perror("fopen");
		return f;
	}
	printf("create temp file %s ok\n", path.c_str());
	return f;
}

void outputTmpfile(const std::vector<std::string>& lines, FILE* file)
{
	if(file==NULL)
		return;
	for(int i=0; i<lines.size(); ++i)
	{
		std::string s=lines[i];
		s=s+"\n"; // linux \n, windows \r\n
		size_t sz=fwrite(const_cast<char*>(s.c_str()), 1, s.length(), file);
		if(sz<s.length())
		{
			printf("fwrite %d < %d\n", sz, s.length());
			return;
		}
		
	}
}

void rm_tmpfiles(int number)
{
	
}




// 归并cnt个有序小文件，输出一个有序大文件
void merge(int cnt)
{
	printf("merge to file %s\n", result_file.c_str());
}

void solve()
{
	//FILE* f=fopen("9.4.in");
	FILE* f=freopen("9.4.in", "r", stdin);
	if(f==NULL)
	{
		perror("freopen");
		return;
	}
	int cnt=splitSort2(f);
	//fclose(f);
	fclose(stdin);
	merge(cnt);
	rm_tmpfiles(cnt);
}

void test_readline()
{
	FILE* f=freopen("readline_test.in", "r", stdin);
	if(f==NULL)
	{
		perror("freopen");
		return;
	}
	std::string line;
	while(readline(f, line))
	{
		printf("[%s]\n", line.c_str());		
	}
	fclose(stdin);
}

void test_middle_dir_not_exist()
{
	// 当/disk0目录下不存在norah目录时，fopen或者open能否创建/disk0/norah/9.4.log文件
	std::string filename="/disk0/norah/9.4.log";
	std::string filename2="/disk0/norah/9.4.log2";
	int fd=open(filename.c_str(), O_RDONLY | O_CREAT, S_IRWXU);
	if(fd<0)
	{
		perror("open");
	}
	
	FILE* f=fopen(filename2.c_str(), "r");
	if(f==NULL)
	{
		perror("fopen");
	}
}

void test_outputTmpfile()
{
	std::vector<std::string> svec;
	svec.push_back("111");
	svec.push_back("111");
	svec.push_back("111");
	svec.push_back("111");
	
	FILE* f=fopen("tmpfile.txt", "w");
	if(f==NULL)
	{
		perror("fopen");
		return;
	}
	outputTmpfile(svec, f);
}

int main(int argc, char* argv[])
{
	if(argc>1)
	{
		batch_cnt=atoi(argv[1]);
	}
	
	{
		//test_readline();
		//test_middle_dir_not_exist();
		test_outputTmpfile();
	}
	
	
	{
		//solve();
	}
	return 0;
}
