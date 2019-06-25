#include<iostream>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<time.h>
#include<algorithm>

#define INT_MIN 1<<31

class Median{
private:
	std::priority_queue<int, std::vector<int>, std::less<int> > max_heap;
	std::priority_queue<int, std::vector<int>, std::greater<int> > min_heap;
	
public:
	void Insert(int v);
	int GetValue();
};

void Median::Insert(int v)
{
	if(max_heap.empty()  &&  min_heap.empty())
		max_heap.push(v);
	else if(!max_heap.empty()  &&  min_heap.empty())
		min_heap.push(v);
	else if(max_heap.empty()  &&  !min_heap.empty())
		max_heap.push(v);
	else
	{
		if(v<max_heap.top())
			max_heap.push(v);
		else
			min_heap.push(v);
	}
	
	while(max_heap.size()>min_heap.size()+1)
	{
		int data=max_heap.top();
		min_heap.push(data);
		max_heap.pop();
	}
	while(min_heap.size() > max_heap.size()+1)
	{
		int data=min_heap.top();
		max_heap.push(data);
		min_heap.pop();
	}
}

int Median::GetValue()
{
	if(max_heap.empty()  &&  min_heap.empty())
		return INT_MIN;
	if(max_heap.size() == min_heap.size())
		return (max_heap.top() + min_heap.top()) /2;
	else if(max_heap.size() >  min_heap.size())
		return max_heap.top();
	else
		return min_heap.top();
}

int main()
{
	srand(time(NULL));
	Median md;
	std::vector<int> vi;
	int num=rand() % 30;
	for(int i=0; i<num; ++i)
	{
		int data=rand() % 100;
		vi.push_back(data);
		md.Insert(data);
	}
	std::sort(vi.begin(), vi.end());
	for(int i=0; i<num; ++i)
		std::cout<<vi.at(i)<<" ";
	std::cout<<std::endl<<md.GetValue()<<std::endl;
	return 0;
}