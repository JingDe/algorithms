#include<cstdio>
#include<map>
#include<queue>
using namespace std;

const int maxt=1000+10;
map<int, int> team;

int main()
{
	int kase, t;
	queue<int> q, q2[maxt];

	kase=0;
	while(scanf("%d", &t)==1  &&  t)
	{
		printf("Scenario #%d:\n", kase++);
		for(int i=0; i<t; i++)
		{
			int n, x;
			scanf("%d", &n);
			while(n--)
			{
				scanf("%d", &x);
				team[x]=i;
			}
		}


		while(true)
		{
			char cmd[10];
			scanf("%s", cmd);
			if(cmd[0]=='S')
				break;
			else if(cmd[0]=='D')
			{
				if(q.empty())
					continue;
				int t=q.front();
				printf("%d\n", q2[t].front());
				q2[t].pop();
				if(q2[t].empty())
					q.pop();
			}
			else if(cmd[0]=='E')
			{
				int x;
				scanf("%d", &x);
				int b=team[x];
				if(q2[b].empty())
					q.push(b);
				q2[b].push(x);
			}
		}
	}
	return 0;
}