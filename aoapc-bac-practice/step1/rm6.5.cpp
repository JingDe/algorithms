#include<stdio.h>
#include<algorithm>
using namespace std;

const int maxn=100000+5;
int n, left[maxn], right[maxn];

inline void link(int x, int y)
{
	left[y]=x;
	right[x]=y;
}

int main()
{
	int m, kase=0;
	while(scanf("%d%d", &n, &m)==2  &&  n)
	{
		for(int i=1; i<=n; i++)
		{
			left[i]=i-1;
			right[i]=(i+1)%(n+1);
		}
		left[0]=n;
		right[0]=1;

		int inv=0;
		int op, X, Y;
		while(m--)
		{
			scanf("%d", &op);
			if(op==4)	{inv=!inv; continue;}
			else
			{
				scanf("%d%d", &X, &Y);
				if(op == 3  &&  right[Y] == X)	swap(X, Y); 
                if(op != 3  &&  inv)	 op = 3 - op; 
				if(op == 1  &&  X == left[Y]) continue; 
		        if(op == 2  &&  X == right[Y]) continue; 


				int LX = left[X], RX = right[X], LY = left[Y], RY = right[Y];
				if(op==1)
				{
					//link(LY, X);link(X, Y);link(LX, RX);
					link(LX, RX); link(LY, X); link(X, Y);
				}
				else if(op==2)
				{
					//link(Y, X);link(X, RY);link(LX, RX);
					link(LX, RX); link(Y, X); link(X, RY);
				}
				else if(op==3)
				{
					if(left[Y]==X){//link(LX, Y);link(Y, X);link(X, RY);
					link(LX, Y); link(Y, X); link(X, RY); }
					else{//link(LY, X);link(X, RY);link(LX, Y);link(Y, RX);
					link(LX, Y); link(Y, RX); link(LY, X); link(X, RY); }
				}
			}
		}

		int b=0;
		__int64 res=0;
		for(i=1; i<=n; i++)
		{
			b=right[b];
			if(i%2==1)
				res+=b;
		}
		if(n%2==0  &&  inv)
			res=(__int64)n*(n+1)/2 - res;
		printf("Case %d: %11d\n", ++kase, res);
	}
	return 0;
}