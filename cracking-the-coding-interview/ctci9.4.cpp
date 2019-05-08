

// 外部排序一个大文件

//int size=2*1024*1024;// kb
//int mem_limit=; // 内存限制，小文件大小
int batch_cnt=1000; // 一个小文件保存的字符串个数

const std::string tmp_dir="/tmp/"; // 中间文件和结果文件路径
const std::string result_file=tmp_dir+"9.4.out.txt";

// 从FILE*对应的文件，读取一行长度不确定的字符串
bool readline(FILE* f, std::string &line)
{
	line.clear();
	if(f==NULL)
		return;
	char c;
	while(fscanf(f, "%c", &c)!=EOF)
	{
		if(c!='\n'  &&  c!='\r')
			line.append(1, c);
		else
		{
			printf("get %c\n", c);
			return true;
		}
	}
	return false;
}

// 分块读取一个大文件，每次排序输出一个小文件
int splitSort(FILE* file)
{
	int cnt=0;
	std::vector<std::string> lines;
	std::string line;
	FILE* tmpfile=NULL;
	while(readline(file, line))
	{
		if(lines.size()<batch_cnt)
			lines.push_back(line);
		else
		{
			std::sort(lines.begin(), lines.end());
			tmpfile=create_tmp_file(cnt);
			outputTmpfile(lines, tmpfile);
			fclose(tmpfile);
			++cnt;
			
			lines.clear();
		}
	}
	if(!lines.empty())
	{
		std::sort(lines.begin(), lines.end());
		tmpfile=create_tmp_file(cnt);
		outputTmpfile(lines, tmpfile);
		fclose(tmpfile);
		++cnt;
	}
	return cnt;
}

// 分块读取一个大文件，每次排序输出一个小文件
int splitSort2(FILE* file)
{
	int cnt=0;
	std::vector<std::string> lines;
	std::string line;
	FILE* tmpfile=NULL;
	while()
	{
		if(readline(file, line)==false  ||  lines.size()>=batch_cnt)
		{
			std::sort(lines.begin(), lines.end());
			tmpfile=create_tmp_file(cnt);
			outputTmpfile(lines, tmpfile);
			fclose(tmpfile);
			++cnt;
			
			lines.clear();
		}
		else
			lines.push_back(line);
	}
	return cnt;
}

FILE* create_tmp_file(int number)
{
	std::string filename="9.4_tmp"+std::to_string(number)+“.txt”;
	std::string path=tmp_dir+"/"+filename;
	FILE* f=creat(path.c_str(), S_IRWXU);
	if(f==NULL)
	{
		perror("creat");
		return f;
	}
	printf("create temp file %s ok\n", path.c_str());
	return f;
}

void outputTmpfile(const std::vector<std::string>& lines, FILE* file)
{
	
}

void rm_tmpfiles(int number)
{
	
}


// 归并cnt个有序小文件，输出一个有序大文件
void merge(int cnt)
{
	
}

void solve()
{
	//FILE* f=fopen("9.4.in");
	FILE* f=freopen("9.4.in", 'r', stdin);
	if(f==NULL)
	{
		perror("fopen");
		return;
	}
	int cnt=splitSort(f);
	//fclose(f);
	fclose(stdin);
	merge(cnt);
}

void test_readline()
{
	FILE* f=freopen("readline_test.in", 'r', stdin);
	if(f==NULL)
	{
		perror("fopen");
		return;
	}
	std::string line;
	while(readline(file, line))
	{
		printf("%s\n", line.c_str());		
	}
	fclose(stdin);
}

int main(int argc, char* argv[])
{
	if(argc>1)
	{
		batch_cnt=atoi(argv[1]);
	}
	
	{
		test_readline();
	}
	{
		solve();
	}
	return 0;
}
