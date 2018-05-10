

// �ⲿ����
// ÿһ���ļ��ļ�¼��key+value��key10�ֽڣ�value90�ֽ�
// Ҫ����key���򣬻������ļ� 

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

// ��ȡ�ļ�filename�������м�¼�洢��data�� 
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
		return memcmp(key, rhs.Key, sizeof key)<0; //����key���� 
	}
};

// // ȡdata��ÿ����¼��key���֣�������keys�� 
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
		rlimit rl={ 3.0*kOneGB, 3.0*kOneGB}; // �����������ں�ǿ�Ӹ���Ӧ��Դ������ֵ��Ӳ�����������Ƶ����ֵ��
		// ����Ȩ���ý���ֻ���Խ���������ָ��Ϊ0~Ӳ���Ʒ�Χ�е�ĳ��ֵ��ͬʱ�ܲ�����ת�ؽ�����Ӳ���ơ�
		// ��Ȩ���̿�������ı�����Ӳ���ơ�
		setrlimit(RLIMIT_AS, &rl);// ���ý��̵������ڴ���ֽ���
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
	
	// ��ȡ�����ļ�argv[1]�����м�¼��data�� 
	std::vector<std::string> data;	
	readInput(argv[1], &data);
	
	// ȡdata��ÿ����¼��key���֣�������keys�� 
	std::vector<Key> keys;
	sort(data, &keys);
	
	// ���
	{
		OutputFile out("output");
		for(std::vector<Key>::iterator it=keys.begin(); it!=keys.end(); ++it)
			out.writeLine(data[it->index]);
	}
	
	return 0;
}
