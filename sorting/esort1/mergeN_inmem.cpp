
// �ڴ���Ĺ鲢���� 
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib> 
#include<iterator>

typedef int Record;
typedef std::vector<Record> File; // ʹ�ü�¼�����ʾ������һ���ļ� 

// �ѵ�Ԫ�� 
struct Input{
	Record value;
	size_t index;
	const File* file;
	
	explicit Input(const File* f):value(-1), index(0), file(f)
	{
	}
	
	bool next()
	{
		if(index<file->size())
		{
			value=(*file)[index];
			++index;
			return true;
		}
		else
			return false;
	}
	
	bool operator<(const Input& rhs) const 
	{
		return value>rhs.value; // ����һ��С���� 
	}
};

File mergeN(const std::vector<File>& files)
{
	File output;
	std::vector<Input> inputs;
	
	for(size_t i=0; i<files.size(); ++i)
	{
		Input input(&files[i]);
		if(input.next())
			inputs.push_back(input);
	}
	
	// ����inputs.begin()��inputs.end()֮��Ԫ�ش���һ������ѣ�ʹ��Ԫ�ص�operator<��������� 
	std::make_heap(inputs.begin(), inputs.end());
	
	while(!inputs.empty()) 
	{
		std::pop_heap(inputs.begin(), inputs.end()); //ȡ���Ѷ�Ԫ�أ������ǣ�
			// ������һ��Ԫ�غ����һ��Ԫ�أ�Ȼ�󽫵�һ��Ԫ�غ͵����ڶ���Ԫ���ؽ��� 
		output.push_back(inputs.back().value);// ����Ѷ�Ԫ�ص�һ����¼������ļ� 
		
		if(inputs.back().next()) 
			std::push_heap(inputs.begin(), inputs.end()); // pop_heap������̣��ؽ�С���� 
		else
			inputs.pop_back(); // ����	
	}
	
	return output; 
}

int main()
{
	const int kFiles=25;
	std::vector<File> files(kFiles);
	for(int i=0; i<kFiles; i++)
	{
		File file(rand() % 1000);
		std::generate(file.begin(), file.end(), &rand); // ʹ�ú�������rand��ΪfileԪ�ظ�ֵ 
		std::sort(file.begin(), file.end());
		files[i].swap(file); // vector::swap����������vector��Ԫ�أ�����ʱ�䣬���漰����Ԫ�ص��ƶ����������������������ò�ʧЧ 
	}
	
	File output=mergeN(files); 
	
	std::copy(output.begin(), output.end(), std::ostream_iterator<Record>(std::cout, "\n"));
	
	return 0;
}
