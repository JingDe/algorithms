#include<stdio.h>
//#include<iostream>
#include<set>
#include<queue>
#include<vector>
using namespace std;

//typedef long long LL;long long int 是GCC（GNU C）的64位表示法
typedef __int64 LL;
const int coeff[3]={2, 3, 5};

int main()
{
	priority_queue<LL, vector<LL>, greater<LL> >  pq;
	set<LL> s;
	pq.push(1);
	s.insert(1);

	int i=1;
	while(true)
	{
		LL x=pq.top();
		pq.pop();
		if(i==1500)
		{
			printf("The 1500th ugly number is %d.\n", x);
			break;
		}
		for(int k=0; k<3; k++)
		{
			LL b=coeff[k]*x;
			if(!s.count(b))
			{	pq.push(b); s.insert(b); }
		}
		i++;
	}

	return 0;
}