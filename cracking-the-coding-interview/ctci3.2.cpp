
#include<stack>
#include<iostream>
#include<stdio.h>
#include<stdexcept>
#include<assert.h>

using std::cout;
using std::endl;

template<class T>
class MinStack{
private:
	std::stack<T> dataS; // std::stack<T, std::deque<T> > dataS;
	std::stack<T> minS;
	
public:
	MinStack();
	~MinStack();
	void Push(T);
	T& Top() throw(std::runtime_error);
	void Pop();
	T Min() throw(std::runtime_error);
	void debug();
};

template<class T>
MinStack<T>::MinStack()
{}

template<class T>
MinStack<T>::~MinStack()
{}

template<class T>
void MinStack<T>::Push(T t)
{
	dataS.push(t);
	if(minS.empty()  ||  minS.top()>t)
	{
		minS.push(t);
		return;
	}
}

template<class T>
T& MinStack<T>::Top() throw(std::runtime_error)
{
	if(dataS.empty())
		throw std::runtime_error("call top on empty stack");
	return dataS.top();
}

template<class T>
void MinStack<T>::Pop() // 当数据栈入栈两个最小值0 0，最小栈入栈一个0时，要弹出第一个0时，需要检查第二个数据决定是否弹出等于0的最小栈栈顶元素
{
	if(dataS.empty())
		return;
	T& top_val=dataS.top();
	dataS.pop();
	
	if(dataS.empty())
	{
		assert(minS.size()==1);
		minS.pop();
		return;
	}
	int& new_top_val=dataS.top();
	if(top_val==minS.top()  &&  new_top_val!=minS.top())
		minS.pop();
}

template<class T>
T MinStack<T>::Min() throw(std::runtime_error)
{
	if(minS.empty())
		throw std::runtime_error("call Min on empty stack");
	return minS.top();
}

template<class T>
void MinStack<T>::debug()
{
	if(dataS.empty())
		printf("empty stack\n");
	else
		printf("sz=%d, %d, top=%d, %d\n", dataS.size(), minS.size(), dataS.top(), minS.top());
}

void test_stackSTL()
{
	std::stack<int> s;
	s.push(1);
	std::cout<<s.top()<<std::endl;
	s.top()=2;
	std::cout<<s.top()<<std::endl;
	
	std::stack<int> emptyS;
	//std::cout<<emptyS.top()<<std::endl; // segment Fault
}

int main()
{
	test_stackSTL();
	
	{
		MinStack<int> ms;
		ms.Push(4);
		ms.debug();
		ms.Push(4);
		ms.debug();
		ms.Push(1);
		ms.debug();
		ms.Push(0);
		ms.debug();
		ms.Push(0);
		ms.debug();
		
		ms.Pop();
		ms.debug();
		
		ms.Pop();
		ms.debug();
		


	}
	
	
	{
		std::cout<<"test3"<<std::endl;
				//cout<<MIN_INT<<endl;
		MinStack<int> mystack;//StackWithMin mystack;
		for(int i=0; i<20; ++i)
			mystack.Push(i);
		cout<<mystack.Min()<<" "<<mystack.Top()<<endl;
		mystack.Push(-100);
		mystack.Push(-100);
		cout<<mystack.Min()<<" "<<mystack.Top()<<endl;
		mystack.Pop();
		cout<<mystack.Min()<<" "<<mystack.Top()<<endl;

	}
	
	return 0;
}