
// �Ż��ֿ��������ˮ��
// ����߳��ص����ж�дIO���ڴ�������

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
const int kBatchRecords=10000000; // �ֿ�Ĵ�С

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
		if(fgets_unlocked(buf, sizeof buf, file_)) // ����eof������256-1���ַ�������\nʱ����ȡ��ֹ��
		// ������һ��\0 
		// ����\nʱ�����Ϊ\n\0�� 
		{
			line->assign(buf);
			return true;
		}
		else
			return false;
	}
	
	int read(char* buf, int size)
	{
		return fread_unlocked(buf, 1, size, file_);// ��size��1�ֽڣ������\0����Ҫ�����߸��ݷ���ֵ���0 
		// ���ض����Ķ������ 
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


// ��ȡ�����ļ�������ȡkBatchRecords����¼��data�� 
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
	
	bool operator<(const Key& rhs) const // �ֿ�����ʱ����С�������� 
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


// Task�������ֿ�����Ĳ���
// �ȵ���read 
// ����sort�����ź����������data_�� 
// ����writeд 
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
		readInput(in, &data_); // ���ļ�in��һ�鵽data_�� 
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

// ���̶߳�д���̳߳����ڴ������� 
int sortSplit(const char* filename) 
{
	InputFile in(filename);
	BlockingQueue<TaskPtr> queue; // ����ź����task
	ThreadPool threadPool;
	threadPool.start(2);
	int active=0;
	
	{
		TaskPtr task(new Task(&queue));
		if(task->read(in))
		{
			threadPool.run(std::bind(&Task::sort, task)); // sort�󣬽�taskѹ��queue 
			active++;
		}
		else
			return 0;
			
		TaskPtr task2(new Task(&queue));
		if(task2->read(in))
		{
			threadPool.run(std::bind(&Task::sort, task2)); // sort�󣬽�taskѹ��queue 
			active++;
		}
	}
	
	int batch=0;
	while(active>0)
	{
		TaskPtr task=queue.take();
		active--;
		
		task->write(batch++);
		
		// ���˿�ʼ�׶Σ��������̶߳�д��֮��һ���߳���sort 
		if(task->read(in))
		{
			threadPool.run(std::bind(&Task::sort, task));
			active++; 
		}
	}
	return batch;
}


// �����ļ���һ����¼ 
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
	
	// ��·�鲢ʱ������С���� 
	bool operator<(const Record& rhs)  const
	{
		return memcmp(data, rhs.data, kKeySize)>0;
	}
};

// ��·�鲢batch�������ļ� 
void merge(const int batch) 
{
	typedef std::shared_ptr<InputFile> InputFilePtr;
	std::vector<InputFilePtr> inputs;// ���������ļ� 
	
	std::vector<Record> keys;// ��ǰ���е�����Ԫ�� 
	
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
	
	// ��·�鲢�Ĺ��̣�����С���ѣ�ÿ��ȡ���Ѷ�Ԫ�ص�һ����¼�����������ļ�
	// ���Ѷ�Ԫ��û�и����¼����ɾ�������򽫶Ѷ�Ԫ�����²���Ѷ� 
	// ֱ���ѱ�Ϊ��Ϊֹ 
	OutputFile out("output");
	std::make_heap(keys.begin(), keys.end());
	while(!keys.empty())
	{
		std::pop_heap(keys.begin(), keys.end());
		out.writeRecord(keys.back().data); //ȡ���Ѷ�Ԫ��
		
		if(keys.back().next()) 
		{
			std::push_heap(keys.begin(), keys.end());
		}
		else
			keys.pop_back();
	}
}


// �ⲿ�����ļ�argv[1] 
int main(int argc, char* argv[])
{
	bool kKeepIntermediateFiles=false;
	
	{ // ���ý��������ַ�ռ�Ϊ3GB 
		size_t kOneGB=1024*1024*1024;
		rlimit rl={4.0*kOneGB, 4.0*kOneGB };
		setrlimit(RLIMIT_AS, &rl);
	}
	
	// �ȷֿ��������batch������С�ļ� 
	int batch=sortSplit(argv[1]);
	
	if (batch == 0)
	{
	}
	if(batch==1) 
	{
		unlink("output"); // ���ļ�ϵͳ��ɾ��output��ɾ��output�ļ� 
		rename(TMP_DIR"tmp0", "output");
	}
	else
	{
		merge(batch); // ���·�鲢		
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
