#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1000;

int main()
{
	int n, q, x, a[maxn], kase=0;
	while(scanf("%d%d", &n, &q)==2  &&  n)
	{
		for(int i=0; i<n; i++)
			scanf("%d", &a[i]);
		printf("CASE# %d:\n", ++kase);

		sort(a, a+n);//若对vector排序，用sort(v.begin(), v.end())
		while(q--)
		{
			scanf("%d", &x);
			int p=lower_bound(a, a+n, x)-a;//查找大于或者等于x的第一个位置
			if(a[p]==x)
				printf("%d found at %d\n", x, p+1);
			else
				printf("%d not found\n", x);
		}
	}
	return 0;
}