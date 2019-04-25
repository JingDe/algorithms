#include<stdio.h>
#include<stack>
#include<queue>
#include<functional>

// 
std::stack<int> sortStack(std::stack<int> os)
{
	std::stack<int> as;
	while(!os.empty())
	{
		int data=os.top();
		os.pop();
		//printf("current data %d\n", data);
		
		while(!as.empty()  &&  as.top()>data)
		{
			os.push(as.top());
			as.pop();
		}
		as.push(data);
	}
	return as;
}

void printStack(std::stack<int> st)
{
	while(!st.empty())
	{
		printf("%d ", st.top());
		st.pop();
	}
	printf("\n");
}

std::stack<int> pqSolution(std::stack<int> os)
{
	
	//std::priority_queue<int, std::vector<int>, std::greater<int> > pq;
	std::priority_queue<int> pq;
	
	std::stack<int> res;
	
	while(!os.empty())
	{
		pq.push(os.top());
		os.pop();
	}
	while(!pq.empty())
	{
		//printf("%d ", pq.top());
		res.push(pq.top());
		pq.pop();
	}
	//printf("\n");
	return res;
}

int main()
{
	{
		std::stack<int> os({3,1,4,1,5,9,2,6});
		std::stack<int> ss=sortStack(os);
		printStack(ss);
	}
	{
		std::stack<int> os({3,1,4,1,5,9,2,6});
		std::stack<int> ss=pqSolution(os);
		printStack(ss);
	}
	return 0;
}