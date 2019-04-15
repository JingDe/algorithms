#include<iostream>
#include<exception>
#include<stdio.h>
#include<stdexcept>
#include<assert.h>

// 使用一个数组实现三个栈

const static int DEFAULT_LEN=200;

// 将数组平均划分为3部分
class ThreeStack1
{
private:
	const int LEN;
	int* stack;
	
	int begin1, cur1, max1;
	int begin2, cur2, max2;
	int begin3, cur3, max3;
	
public:
	ThreeStack1();
	ThreeStack1(int n);
	~ThreeStack1();
	void Push(int data, int no);
	int& Top(int no) throw(std::out_of_range);
	void Pop(int no) throw(std::runtime_error);
	bool Empty(int no);
	bool Full(int no);
	int Size(int no);
};

ThreeStack1::ThreeStack1():LEN(DEFAULT_LEN)
{
	stack=new int[LEN];
	int stack_size=LEN/3;
	begin1=0, cur1=begin1, max1=stack_size;
	begin2=max1+1, cur2=begin2, max2=begin2+stack_size;
	begin3=max2+1, cur3=begin3, max3=LEN-1;
	printf("[%d-%d], [%d-%d], [%d-%d]\n", begin1, max1, begin2, max2, begin3, max3);
}

ThreeStack1::ThreeStack1(int n):LEN(n)
{
	stack=new int[LEN];
	int stack_size=LEN/3;
	begin1=0, cur1=begin1, max1=stack_size;
	begin2=max1+1, cur2=begin2, max2=begin2+stack_size;
	begin3=max2+1, cur3=begin3, max3=LEN-1;
	printf("[%d-%d], [%d-%d], [%d-%d]\n", begin1, max1, begin2, max2, begin3, max3);
}

ThreeStack1::~ThreeStack1()
{
	delete[] stack;
}

void ThreeStack1::Push(int data, int no)
{
	if(Full(no)==0)
	{
		if(no==1)
		{
			stack[cur1++]=data;
		}
		else  if(no==2)
			stack[cur2++]=data;
		else
			stack[cur3++]=data;
	}
		
}

int& ThreeStack1::Top(int no) throw(std::out_of_range)
{
	if(Empty(no)==0)
	{
		if(no==1)
			return stack[cur1-1];
		else if(no==2)
			return stack[cur2-1];
		else
			return stack[cur3-1];
	}
	throw std::out_of_range("call Top to empty stack");
}

void ThreeStack1::Pop(int no) throw(std::runtime_error)
{
	if(Empty(no)==0)
	{
		if(no==1)
			cur1--;
		else if(no==2)
			cur2--;
		else
			cur3--;
	}
	throw std::runtime_error("call Pop to empty stack");	
}

bool ThreeStack1::Empty(int no)
{
	if(no==1  &&  cur1==begin1) return true;
	if(no==2  &&  cur2==begin2) return true;
	if(no==3  &&  cur3==begin3) return true;
	return false;
}

bool ThreeStack1::Full(int no)
{
	if(no==1  &&  cur1>max1) return true;
	if(no==2  &&  cur2>max2) return true;
	if(no==3  &&  cur3>max3) return true;
	return false;
}

int ThreeStack1::Size(int  no) //throw(std::runtime_error)
{
	if(no==1)
		return cur1-begin1;
	else if(no==2)
		return cur2-begin2;
	else if(no==3)
		return cur3-begin3;
	// else
		// throw std::runtime_error;
}

// --------------------------------------------------
// 不划分数组，记录栈中元素所在的栈编号
struct StackElem{
	int data;
	int preIdx; // 栈中前一个元素的下标
	StackElem(int d, int i):data(d),preIdx(i){}
};
class ThreeStack2
{
private:
	const int LEN;
	StackElem **buf;
	
	int cur; // next available position in buf
	int top[3]; // top element index for 3 stacks
	int sz[3];
	
public:
	ThreeStack2();
	~ThreeStack2();
	void Push(int data, int no);
	int& Top(int no);
	void Pop(int no);
	int Size(int no);
	bool Empty(int no);
	bool Full(int no);
	void Print();
	void PrintLink(int no);
};

ThreeStack2::ThreeStack2():LEN(DEFAULT_LEN),cur(0),top({-1,-1,-1}),sz({0,0,0})
{	
	buf=new StackElem*[LEN];
	for(int i=0; i<LEN; i++)
	{
		buf[i]=NULL;
	}
	// memset(buf, 0, sizeof(buf[0]));
}

ThreeStack2::~ThreeStack2()
{
	for(int i=0; i<LEN; i++)
	{
		if(buf[i]!=NULL)
			delete buf[i];
	}
	delete []buf;
}

void ThreeStack2::Push(int data, int no)
{
	if(Full(no)==0)
	{
		StackElem *node=new StackElem(data, top[no]);
		assert(buf[cur]==NULL);
		buf[cur]=node;
		top[no]=cur;
		sz[no]++;
		while(buf[cur]!=NULL  &&  cur<LEN)
			cur++;
		assert(cur==LEN  ||  (buf[cur]==NULL  &&  cur<LEN));
	}
}

int& ThreeStack2::Top(int no)
{
	if(Empty(no)==false)
	{
		return buf[top[no]]->data;
	}
}

void ThreeStack2::Pop(int no)
{
	if(Empty(no)==false)
	{
		int top_idx=top[no];
		top[no]=buf[top_idx]->preIdx;
		sz[no]--;
		delete buf[top_idx];
		buf[top_idx]=NULL;
		
		if(top_idx<cur)
		{
			cur=top_idx;
		}
	}
}

bool ThreeStack2::Empty(int no)
{
	//return (top[no]==-1) ? true : false;
	return (sz[no]==0) ? true : false;
}

bool ThreeStack2::Full(int no)
{
	return (cur>=LEN) ? true : false;
}

int ThreeStack2::Size(int no)
{
	return sz[no];
}

void ThreeStack2::Print()
{
	//printf("cur=%d, top=%d, %d, %d, sz=%d, %d, %d\n", cur, top[0], top[1], top[2], sz[0], sz[1], sz[2]);
	
	PrintLink(0);
	PrintLink(1);
	PrintLink(2);
}

void ThreeStack2::PrintLink(int no)
{
	printf("stack %d:", no);
	int idx=top[no];
	if(idx>=0)
	{
		printf("%d", idx);
		idx=buf[idx]->preIdx;
	}
	while(idx>=0)
	{
		printf("->%d", idx);
		idx=buf[idx]->preIdx;
	}
	printf("\n");
}

int main()
{
	/* {
		ThreeStack1 s;
		s.Push(1, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Push(2, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Push(3, 1);
		std::cout<<s.Top(1)<<std::endl;
		
		std::cout<<s.Size(1)<<" "<<s.Size(2)<<" "<<s.Size(3)<<std::endl;
	} */
	
	{
		ThreeStack2 s;
		s.Push(1, 0);
		std::cout<<s.Top(0)<<std::endl;
		s.Push(2, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Push(3, 2);
		std::cout<<s.Top(2)<<std::endl;
		s.Print();
		
		s.Push(4, 0);
		std::cout<<s.Top(0)<<std::endl;		
		s.Push(5, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Push(6, 2);
		std::cout<<s.Top(2)<<std::endl;		
		s.Print();
		
		s.Pop(0);
		s.Print();
		
		s.Push(8, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Print();
		
		s.Pop(1);
		std::cout<<s.Top(1)<<std::endl;
		s.Print();
		
		s.Push(9, 2);
		std::cout<<s.Top(2)<<std::endl;
		s.Print();
	}
	return 0;
}