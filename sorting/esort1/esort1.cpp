#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<memory>

#include<unistd.h>
#include<sys/resource.h>

const int kRecordSize=100;
const int kKeySize=10;

const bool kUseReadLine=false;
const int kBatchRecords=10000000; // 分块的大小

#define DISALLOW_COPY_CONS(TypeName) TypeName(const TypeName&)=delete
#define DISALLOW_COPY_ASSIGN(TypeName) TypeName& operator=(const TypeName&)=delete

#define DISALLOW_COPY(TypeName) DISALLOW_COPY_CONS(TypeName); DISALLOW_COPY_ASSIGN(TypeName)

#define TMP_DIR "/tmp/"

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
};



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
	
	void writeRecord(char (&record)[kRecordSize])
	{
		fwrite_unlocked(record, 1, kRecordSize, file_);
	}
	
private:
	FILE* file_;
	char buffer_[64*1024];
	
	DISALLOW_COPY(OutputFile);
};


// 读取输入文件，最多读取kBatchRecords条记录到data中 
void readInput(InputFile& in, std::vector<std::string>* data)
{
	int64_t totalSize=0;
	data->clear();
	data->reserve(kBatchRecords);
	
	for(int i=0; i<kBatchRecords; ++i)
	{
		char buf[kRecordSize];
		if (int n=in.read(buf, sizeof buf))
		{
			assert(n==kRecordSize);
			totalSize+=n;
			data->push_back(std::string(buf, n));
		}
		else
			break; 
	}
}

struct Key{
	char key[kKeySize];
	int index;
	
	Key(const std::string& record, int idx)
		:index(idx)
	{
		memcpy(key, record.data(), sizeof key);
	}
	
	bool operator<(const Key& rhs) const // 分块排序时，从小到大排序 
	{
		return memcmp(key, rhs.key, sizeof key)<0;
	}
};

// 取data中每条记录的key部分，并排序到keys中 
void sort(const std::vector<std::string>& data, std::vector<Key>* keys) 
{
	keys->reserve(data.size());
	for(size_t i=0; i<data.size(); ++i)
		keys->push_back(Key(data[i], i));
	
	std::sort(keys->begin(), keys->end());
}

// 对文件filename分块读取，分块排序输出到batch个有序小文件 
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
		
		std::vector<Key> keys;
		sort(data, &keys);
		
		{
			char output[256];
			snprintf(output, sizeof output, TMP_DIR"tmp%d", batch++);
			
			OutputFile out(output);
			for(std::vector<Key>::iterator it=keys.begin(); it!=keys.end(); ++it)
				out.writeLine(data[it->index]);
		}
	}
	
	return batch;
}

// 描述文件的一条记录 
struct Record
{
	char data[kRecordSize];
	InputFile* input;
	
	Record(InputFile* in)
		:input(in)
	{
		
	}
	
	bool next()
	{
		return input->read(data, sizeof data)==kRecordSize;
	}
	
	// 多路归并时，建立小根堆 
	bool operator<(const Record& rhs)  const
	{
		return memcmp(data, rhs.data, kKeySize)>0;
	}
};

// 多路归并batch个有序文件 
void merge(const int batch) 
{
	typedef std::shared_ptr<InputFile> InputFilePtr;
	std::vector<InputFilePtr> inputs;// 所有输入文件 
	
	std::vector<Record> keys;// 当前堆中的所有元素 
	
	for(int i=0; i<batch; ++i) 
	{
		char filename[128];
		snprintf(filename, sizeof filename, TMP_DIR"tmp%d", i);
		//inputs.push_back(new InputFile(filename));
		inputs.push_back(std::make_shared<InputFile>(filename));
		Record rec(inputs.back().get());
		if(rec.next()) 
			keys.push_back(rec);
	}
	
	// 多路归并的过程：建立小根堆，每次取出堆顶元素的一条记录，输出到输出文件
	// 若堆顶元素没有更多记录，则删除；否则将堆顶元素重新插入堆顶 
	// 直到堆变为空为止 
	OutputFile out("output");
	std::make_heap(keys.begin(), keys.end());
	while(!keys.empty())
	{
		std::pop_heap(keys.begin(), keys.end());
		out.writeRecord(keys.back().data); //取出堆顶元素
		
		if(keys.back().next()) 
		{
			std::push_heap(keys.begin(), keys.end());
		}
		else
			keys.pop_back();
	}
}

// 外部排序文件argv[1] 
int main(int argc, char* argv[])
{
	bool kKeepIntermediateFiles=false;
	
	{ // 设置进程虚拟地址空间为3GB 
		size_t kOneGB=1024*1024*1024;
		rlimit rl={3.0*kOneGB, 3.0*kOneGB };
		setrlimit(RLIMIT_AS, &rl);
	}
	
	// 先分块排序，输出batch个有序小文件 
	int batch=sortSplit(argv[1]);
	
	if(batch==1) 
	{
		unlink("output"); // 从文件系统中删除output，删除output文件 
		rename(TMP_DIR"tmp0", "output");
	}
	else
	{
		merge(batch); // 后多路归并		
	} 
	
	if(!kKeepIntermediateFiles) 
	{
		for(int i=0; i<batch; i++)
		{
			char tmp[256];
			snprintf(tmp, sizeof tmp, TMP_DIR"tmp%d", i);
			unlink(tmp);
		}
	}
	
	return 0;
}
