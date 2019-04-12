#include<iostream>
#include<exception>
#include<stdio.h>
#include<stdexcept>

// 使用一个数组实现三个栈

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
	int Top(int no) throw(std::out_of_range);
	void Pop(int no) throw(std::runtime_error);
	bool Empty(int no);
	bool Full(int no);
	int Size(int no);
};

ThreeStack1::ThreeStack1():LEN(200)
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
	if(Full(no)!=0)
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

int ThreeStack1::Top(int no) throw(std::out_of_range)
{
	if(Empty(no)!=0)
	{
		if(no==1)
			return stack[cur1-1];
		else if(no==2)
			return stack[cur2-1];
		else
			return stack[cur3-1];
	}
	throw std::out_of_range();
}

void ThreeStack1::Pop(int no) throw(std::runtime_error)
{
	if(Empty(no)!=0)
	{
		if(no==1)
			cur1--;
		else if(no==2)
			cur2--;
		else
			cur3--;
	}
	throw std::runtime_error();	
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
	int preIdx;
};
// class ThreeStack2
// {
// private:
	// const int LEN=200;
	// int stack[LEN];
	
// public:
	// ThreeStack2();
	// ~ThreeStack2();
	// void Push(int data, int no);
	// int Top(int data, int no);
	// void Pop(int no);
// };

int main()
{
	{
		ThreeStack1 s;
		s.Push(1, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Push(2, 1);
		std::cout<<s.Top(1)<<std::endl;
		s.Push(3, 1);
		std::cout<<s.Top(1)<<std::endl;
		
		std::cout<<s.Size(1)<<" "<<s.Size(2)<<" "<<s.Size(3)<<std::endl;
	}
	return 0;
}