#include<stdio.h>
#include<stack>
using namespace std;

const int MAXN=1000+10;
int n, target[MAXN];

int main()
{
	while(scanf("%d", &n)==1  &&  n)
	{
		stack<int> s;
		int A=1, B=1;
		for(int i=1; i<=n; i++)
			scanf("%d", &target[i]);

		bool ok=true;
		while(B<=n)
		{
			if(A==target[B])	{A++;B++;}
			else if(!s.empty()  &&  s.top()==target[B])		
				{	s.pop();	B++; }
			else if(A<=n)	{	s.push(A++);  }
			else	{ok=false; break; }
		}
		printf("%s\n", ok? "YES" :  "NO");
	}
	return 0;
}
