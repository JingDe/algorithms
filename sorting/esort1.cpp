

class InputFile
{
public:
	InputFile(const char* filename)
		:file_(fopen(filename, "rb"))
	{
		assert(file_);
		setbuffer(file_, buffer_, sizeof buffer_);
	}
	
	~InputFile()
	{
		fclose(file_);
	}
	
	bool readLine(std::string* line)
	{
		char buf[256];
		if(fgets_unlocked(buf, sizeof buf, file_)) // 读到eof、读到256-1个字符、读到\n时，读取终止。
		// 最后添加一个\0 
		// 读到\n时，最后为\n\0， 
		{
			line->assign(buf);
			return true;
		}
		else
			return false;
	}
	
	int read(char* buf, int size)
	{
		return fread_unlocked(buf, 1, size, file_);// 读size个1字节，不添加\0，需要调用者根据返回值添加0 
		// 返回读到的对象个数 
	}
	
private:
	FILE* file_;
	char buffer_[64*1024];
	
	InputFile(const InputFile&);
	InputFile& operator=(const InputFile&);
}

class OutputFile
{
public:
	OutputFile(const char* filename)
		:file_(fopen(filename, "wb")) 
	{
		assert(file_);
		setbuffer(file_, buffer_, sizeof buffer_);
	}
	
	~OutputFile()
	{
		fclose(file_);
	}
	
	void writeLine(const std::string& line)
	{
		if(line.empty())
			fwrite_unlocked("\n", 1, 1, file_);
		else if(line[line.size()-1]=='\n')
			fwrite_unlocked(line.c_str(), 1, line.size(), file_);
		else
		{
			fwrite_unlocked(line.c_str(), 1, line.size(), file_);
			fwrite_unlocked("\n", 1, 1, file_);
		}
	}
	
private:
	FILE* file_;
	char buffer_[64*1024];
	
	DISALLOW_COPY(OutputFile);
}

const bool kUseReadLine=false;
const int kBatchRecords=10000000;

void readInput(InputFile& in, std::vector<std::string>* data)
{
	int64_t totalSize=0;
	data->clear();
	data->reserve(kBatchRecords);
	
	for(int i=0; i<kBatchRecords; ++i)
	{
		
	}
}

int sortSplit(const char* filename)
{
	std::vector<std::string> data;
	
	InputFile in(filename);
	int batch=0;
	while(true)
	{
		readInput(in, &data);
		
		if(data.empty())
			break;
		
		
	}
	
	return batch;
}

int main(int argc, char* argv[])
{
	bool kKeepIntermediateFiles=false;
	
	{
		size_t kOneGB=1024*1024*1024;
		rlimit rl={3.0*kOneGB, 3.0*kOneGB };
		setrlimit(RLMIT_AS, &rl);
	}
	
	int batch=sortSplit(argv[1]);
	
}
