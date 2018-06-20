
// 优化分块排序的流水线
// 多个线程重叠进行读写IO与内存中排序

#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<memory>

#include<unistd.h>
#include<sys/resource.h>

#include"BlockingQueue.h"
#include"ThreadPool.h"

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

void sortWithKeys(const std::vector<std::string>& data, std::vector<Key>* keys)
{
  keys->clear();
  keys->reserve(data.size());

  for (size_t i = 0; i < data.size(); ++i)
  {
    keys->push_back(Key(data[i], i));
  }

  std::sort(keys->begin(), keys->end());
}

typedef std::vector<std::string> Data;

class Task;
typedef std::shared_ptr<Task> TaskPtr;


// Task类描述分块排序的操作
// 先调用read 
// 调用sort排序，排好序后数据在data_中 
// 调用write写 
class Task : public std::enable_shared_from_this<Task> {
public:
	Task(BlockingQueue<TaskPtr>* queue)
		:queue_(queue),
		id_(s_created++),
		sorted_(false)
	{
		
	}
	
	~Task()
	{
	}
	
	bool read(InputFile& in)
	{
		sorted_=false;
		readInput(in, &data_); // 读文件in的一块到data_中 
		return !data_.empty();
	}
	
	void sort()
	{
		assert(!sorted_);
		sortWithKeys(data_, &keys_);
		sorted_=true;
		queue_->put(shared_from_this());
	}
	
	void write(int batch)
	{
		assert(sorted_);
		
		{
			char output[256];
			snprintf(output, sizeof output, "tmp%d", batch);
			
			OutputFile out(output);
			for(std::vector<Key>::iterator it=keys_.begin(); it!=keys_.end(); ++it)
				out.writeLine(data_[it->index]);
		}
	}
	
	const Data& data() const
	{
		return data_;
	}
	
private:
	Data data_;
	std::vector<Key> keys_;
	BlockingQueue<TaskPtr>* queue_;
	int id_;
	bool sorted_;
	
	static int s_created;
};

int Task::s_created=0;

// 主线程读写，线程池在内存中排序 
int sortSplit(const char* filename) 
{
	InputFile in(filename);
	BlockingQueue<TaskPtr> queue; // 存放排好序的task
	ThreadPool threadPool;
	threadPool.start(2);
	int active=0;
	
	{
		TaskPtr task(new Task(&queue));
		if(task->read(in))
		{
			threadPool.run(std::bind(&Task::sort, task)); // sort后，将task压入queue 
			active++;
		}
		else
			return 0;
			
		TaskPtr task2(new Task(&queue));
		if(task2->read(in))
		{
			threadPool.run(std::bind(&Task::sort, task2)); // sort后，将task压入queue 
			active++;
		}
	}
	
	int batch=0;
	while(active>0)
	{
		TaskPtr task=queue.take();
		active--;
		
		task->write(batch++);
		
		// 除了开始阶段，正常主线程读写，之后一个线程在sort 
		if(task->read(in))
		{
			threadPool.run(std::bind(&Task::sort, task));
			active++; 
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
		rlimit rl={4.0*kOneGB, 4.0*kOneGB };
		setrlimit(RLIMIT_AS, &rl);
	}
	
	// 先分块排序，输出batch个有序小文件 
	int batch=sortSplit(argv[1]);
	
	if (batch == 0)
	{
	}
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
