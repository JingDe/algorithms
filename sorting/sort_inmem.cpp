

// 外部排序
// 每一个文件的记录：key+value，key10字节，value90字节
// 要求按照key排序，获得输出文件 

const int kKeySize=10;
const int kRecordSize=100;
const bool kUseReadLine=false;

#define DISALLOW_COPY_CONS(TypeName) TypeName(const TypeName&)=delete
#define DISALLOW_COPY_ASSIGN(TypeName) TypeName& opreator=(const TypeName&)=delete

#define DISALLOW_COPY(TypeName) DISALLOW_COPY_CONS(TypeName); DISALLOW_COPY_ASSIGN(TypeName)
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) TypeName()=delete; DISALLOW_COPY_AND_ASSIGN(TypeName)

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

// 读取文件filename，将所有记录存储到data中 
void readInput(const char* filename, std::vector<std::string>* data)
{
	InputFile in(filename);
	std::string line;
	int64_t totalSize=0;
	data->reserve(10000000);
	
	if(kUseReadLine)
	{
		while(in.readLine(&line))
		{
			totalSize+=line.size();
			data->push_back(line);
		}
	}
	else
	{
		char buf[kRecordSize];
		while(int n=in.read(buf, sizeof buf))
		{
			totalSize+=n;
			line.assign(buf, n);
			data->push_back(line);
		}
	}
} 

struct Key{
	char key[kKeySize];
	int index;
	
	Key(const std::string& record, int idx):index(idx)
	{
		memcpy(key, record.data(), sizeof key);
	}
	
	bool operator<(const Key& rhs) const
	{
		return memcmp(key, rhs.Key, sizeof key)<0; //按照key排序 
	}
};

// // 取data中每条记录的key部分，并排序到keys中 
void sort(const std::vector<std::string>& data, std::vector<Key>* keys) 
{
	keys->reserve(data.size());
	for(size_t i=0; i<data.size(); ++i)
		keys->push_back(Key(data[i], i));
	
	std::sort(keys->begin(), keys->end());
}

int main(int argc, char* argv[]) 
{
	bool kSortDummyData=false;
	
	{
		size_t kOneGB=1024*1024*1024;
		rlimit rl={ 3.0*kOneGB, 3.0*kOneGB}; // 软软限制是内核强加给相应资源的限制值，硬限制是软限制的最大值。
		// 非授权调用进程只可以将其软限制指定为0~硬限制范围中的某个值，同时能不可逆转地降低其硬限制。
		// 授权进程可以任意改变其软硬限制。
		setrlimit(RLIMIT_AS, &rl);// 设置进程的虚拟内存的字节数
	}
	
	std::vector<int> dummyData;
	
	if(kSortDummyData)
	{
		dummyData.resize(10000000);
		for(std::vector<int>::iterator it=dummyData.begin(); it!=dummyData.end(); ++it)
		{
			*it=rand();
		}
	}
	
	// 读取输入文件argv[1]的所有记录到data中 
	std::vector<std::string> data;	
	readInput(argv[1], &data);
	
	// 取data中每条记录的key部分，并排序到keys中 
	std::vector<Key> keys;
	sort(data, &keys);
	
	// 输出
	{
		OutputFile out("output");
		for(std::vector<Key>::iterator it=keys.begin(); it!=keys.end(); ++it)
			out.writeLine(data[it->index]);
	}
	
	return 0;
}
