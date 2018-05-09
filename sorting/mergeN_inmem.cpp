
// 内存里的归并排序 
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib> 
#include<iterator>

typedef int Record;
typedef std::vector<Record> File; // 使用记录数组表示磁盘上一个文件 

// 堆的元素 
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
		return value>rhs.value; // 创建一个小根堆 
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
	
	// 根据inputs.begin()到inputs.end()之间元素创建一个大根堆，使用元素的operator<运算符排序 
	std::make_heap(inputs.begin(), inputs.end());
	
	while(!inputs.empty()) 
	{
		std::pop_heap(inputs.begin(), inputs.end()); //取出堆顶元素，方法是：
			// 交换第一个元素和最后一个元素，然后将第一个元素和倒数第二个元素重建堆 
		output.push_back(inputs.back().value);// 输出堆顶元素的一条记录到输出文件 
		
		if(inputs.back().next()) 
			std::push_heap(inputs.begin(), inputs.end()); // pop_heap的逆过程，重建小根堆 
		else
			inputs.pop_back(); // 弹出	
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
		std::generate(file.begin(), file.end(), &rand); // 使用函数对象rand，为file元素赋值 
		std::sort(file.begin(), file.end());
		files[i].swap(file); // vector::swap，交换两个vector的元素，常量时间，不涉及单个元素的移动拷贝交换，迭代器和引用不失效 
	}
	
	File output=mergeN(files); 
	
	std::copy(output.begin(), output.end(), std::ostream_iterator<Record>(std::cout, "\n"));
	
	return 0;
}
