#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=100+5;

struct Building{
	int id;
	double x, y, w, d, h;
	bool operator <(const Building b) const
	{
		if(x<b.x  ||  (x==b.x  &&  y<b.y) )
			return true;
		return false;
	}
}b[maxn];

int n;
double x[2*maxn];

bool cover(int i, double mx)
{
	if(b[i].x<=mx  &&  b[i].x+b[i].w>=mx)
		return true;
	return false;
}

bool visible(int i, double mx)
{
	if(!cover(i, mx))
		return false;
	for(int j=0; j<n; j++)
		if(b[j].h>=b[i].h  &&  cover(j, mx)  &&  b[j].y<b[i].y)
			return false;
	return true;
}

int main()
{
	
	int kase=0;

	while(scanf("%d", n)==1  &&  n)
	{
		for(int i=0; i<n; i++)
		{
			scanf("%lf%lf%lf%lf%lf", &b[i].x, &b[i].y, &b[i].w, &b[i].d, &b[i].h);
			b[i].id=i+1;
			x[i*2]=b[i].x;
			x[i*2+1]=b[i].x+b[i].w;
		}

		sort(b, b+n);
		sort(x, x+2*n);
		int m=unique(x, x+2*n)-x;

		if(kase++) 
			printf("\n"); 
		printf("For map #%d, the visible buildings are numbered as follows:\n%d", kase, b[0].id);

		for(i=1; i<n; i++)
		{
			bool vis=false;
			for(int j=0; j<m-1; j++)
			{
				if(visible(i, (x[j]+x[j+1])/2 ))
				{
					vis=true;
					break;
				}
			}
			if(vis)
				printf("   %d", b[i].id);
		}

		printf("\n");
	}
	return 0;
}