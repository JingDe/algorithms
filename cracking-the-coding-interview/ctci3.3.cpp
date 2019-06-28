//#include<stack>
#include<vector>
#include<stdio.h>
#include<iostream>
#include<memory>
#include<assert.h>

// template<typename T>
// class SetOfStacks{
// private:
	// std::vector<std::stack<T> > stacks; // std::stack不会满
	// int cur;
	
// public:
	// SetOfStacks();
	// ~SetOfStacks();
	
	// void Push(T);
	// T& Top();
	// void Pop();
	// void PopAt(int );
// };

class Stack{
private:
	enum { sz=5 };
	int buf[sz];
	int cnt;

public:
	Stack();
	~Stack();
	
	void Push(int);
	int& Top();
	void Pop();
	bool Empty() { return cnt==0; }
	bool Full() { return cnt>=sz; }
	int Size() { return cnt; }
};

Stack::Stack():cnt(0)
{}

Stack::~Stack()
{}

void Stack::Push(int val)
{
	if(!Full())
	{
		buf[cnt++]=val;
	}
}

int& Stack::Top()
{
	return buf[cnt-1];
}

void Stack::Pop()
{
	if(!Empty())
	{
		cnt--;
	}
}

class SetOfStacks{
private:
	std::vector<std::shared_ptr<Stack> > stacks;
	int curStack; // 当前stack编号

public:
	SetOfStacks();
	~SetOfStacks();
	
	void Push(int);
	int& Top();
	void Pop();
	void PopAt(int);
	bool Empty();
	void debug();
};


SetOfStacks::SetOfStacks():curStack(-1)
{
	std::shared_ptr<Stack> s0(new Stack());
	stacks.push_back(s0);
	// stacks.push_back(std::make_shared<Stack>());
	curStack=0;
}

SetOfStacks::~SetOfStacks()
{}

void SetOfStacks::Push(int t)
{
	if(stacks[curStack]->Full()==false)
	{
		stacks[curStack]->Push(t);
		return;
	}
	stacks.push_back(std::shared_ptr<Stack>(new Stack()));
	curStack=stacks.size()-1; // curStack++; assert(curStack==stacks.size()-1);
	stacks[curStack]->Push(t);
}

int& SetOfStacks::Top()
{
	while(stacks[curStack]->Empty())
	{
		curStack--;
		stacks.pop_back();
		assert(curStack==stacks.size()-1);
	}
	return stacks[curStack]->Top();
}

void SetOfStacks::Pop()
{
	if(Empty())
		return;
	while(stacks[curStack]->Empty())
	{
		curStack--;
		stacks.pop_back();
		assert(curStack==stacks.size()-1);
	}
	if(Empty())
		return;
	stacks[curStack]->Pop();
}

void SetOfStacks::PopAt(int i)
{
	if(stacks[i]->Empty()==false)
		stacks[i]->Pop();
}

bool SetOfStacks::Empty()
{
	return curStack<0;
}

void SetOfStacks::debug()
{
	for(std::vector<std::shared_ptr<Stack> >::const_iterator it=stacks.cbegin(); it!=stacks.cend(); it++)
		printf("stack %d has %d, ", it-stacks.cbegin(), (*it)->Size());
	printf("\n");
}

int main()
{
	{
		SetOfStacks ss;
		int a[]={1,2,3,4,5,6,7,8,9,0};
		for(int i=0; i<sizeof(a)/sizeof(a[0]); i++)
			ss.Push(a[i]);
		ss.debug();
	}
	return 0;
}
