

#include"graphNoDirection.h"
#include<stdio.h>
#include<map>

#define INT_MIN 1<<31

// 无向图，节点a到达节点b的最短路径长度，不可达时返回-1
// int shortestPath(Graph* g, int a, int b)
// {
	// int nvex=g.vexNum();
	// int dp[nvex]; 
	// int pbn[nvex]; //path before node
	// for(int i=0; i<nvex; ++i)
	// {
		// dp[i]=INT_MIN;
		// pbn[i]=-1;
	// }
	
	// dp[a]=0;
	// pbn[a]=-1;
	
	// for(int i=0; i<nvex; ++i)
	// {
		// if(dp[i]==INT_MIN) // not visited
		// {
			
		// }
	// }
	
// }

void dijkstra(Graph* g, int nvex, int a, int dp[], int path[]);

void print_path(int path[], int n, int dst)
{
	printf("%d", dst);
	for(int i=dst; i>=0  &&  path[i]>=0; i=path[i])
		printf("<——%d", path[i]);
	printf("\n");
}

void print_path(int path[], int n, int dst, Graph* g)
{
	printf("%d", dst);
	for(int i=dst; i>=0  &&  path[i]>=0; i=path[i])
		printf("<—(%d)—%d", g->weight(path[i], i), path[i]);
	printf("\n");
}

int shortestPath(Graph* g, int a, int b)
{
	int nvex=g->vexNum();
	int dp[nvex]; // dp[k]表示节点a到k的最短路径
	int path[nvex]; // path[k]表示节点a到节点k的最短路径上的前一节点
	dijkstra(g, nvex, a, dp, path);
	
	for(int i=0; i<nvex; ++i)
	{
		printf("dp[%d]=%d\n", i, dp[i]);
		if(dp[i]!=INT_MAX)
			printf("path[%d]=%d\n", i, path[i]);
	}
		
	if(dp[b]<INT_MAX)
	{
		print_path(path, nvex, b); // 输出a到b的最短路径
		print_path(path, nvex, b, g);
	}
	else
	{
		printf("no path from %d to %d\n", a, b);
	}
	return dp[b];
}

void dijkstra(Graph* g, int nvex, int a, int dp[], int path[])
{
	std::map<int, bool> visited;
	for(int i=0; i<nvex; ++i)
	{
		dp[i]=g->weight(a, i);
		path[i]=a;
	}
	dp[a]=0;
	path[a]=-1;
	visited[a]=true;
		
	for(int nvisited=1; nvisited<nvex; ++nvisited)
	{
		int shortest=-1;
		for(int i=0; i<nvex; ++i)
		{
			if(visited[i]==false)
			{
				if(shortest<0  ||  dp[shortest]>dp[i])
				{
					shortest=i;
				}
			}
		}
		visited[shortest]=true;
		printf("choose %d, %d\n", shortest, dp[shortest]);
		
		for(int v=g->FirstNeighbor(shortest); v>0; v=g->NextNeighbor(shortest, v))
		{
			printf("%d has neighbor %d, %d(%d)\n", shortest, v, dp[v], path[v]);
			if(dp[v]>dp[shortest]+g->weight(shortest,v))
			{
				dp[v]=dp[shortest]+g->weight(shortest, v);
				path[v]=shortest;
				printf("set %d to %d(%d)\n", v, dp[v], shortest);
			}
		}
	}
	
}

void test_shortestPath()
{
	Graph* mg=new MGraph;
	mg->Init("graph_nodirection.txt");
	mg->debug_print();
	
	shortestPath(mg, 6, 7);
	
	printf("\n");
	shortestPath(mg, 1, 7);
	delete mg;
}

int main()
{
	test_shortestPath();
	
	return 0;
}
