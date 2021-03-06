

#include"graphNoDirection.h"
#include<stdio.h>
#include<map>
#include<stdlib.h>

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

void print_path1(int path[], int n, int dst, int src)
{
	printf("%d", dst);
	int i=dst;
	for(; i>=0  &&  path[i]>=0  &&  i!=src; i=path[i])
		printf("<——%d", path[i]);
	printf("<——%d", src);
	printf("debug %d %d %d %d\n", i, path[abs(i)], src, path[src]);
	printf("\n");
}

void print_path(int path[], int n, int dst, Graph* g)
{
	printf("%d", dst);
	for(int i=dst; i>=0  &&  path[i]>=0; i=path[i])
		printf("<—(%d)—%d", g->weight(path[i], i), path[i]);
	printf("\n");
}


void print_path2(int path[], int n, int dst, int src, Graph* g)
{
	for(int node=dst; node>=0; node=path[node])
		printf("%d<——", node);
		// printf("%d<—(%d)—", node, g->weight(path[node], node));
	printf("%d\n", src);
}

void printPath(int path[], int nvex)
{
	for(int i=0; i<nvex; ++i)
		printf("cur path[%d]=%d\n", i, path[i]);
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
			printf("\tpath[%d]=%d\n", i, path[i]);
	}
		
	if(dp[b]<INT_MAX)
	{
		printf("path from %d to %d, weight=%d:\n", a, b, dp[b]);
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
		printf("choose %d, %d(%d)\n", shortest, dp[shortest], path[shortest]);
		
		for(int v=g->FirstNeighbor(shortest); v>=0; v=g->NextNeighbor(shortest, v))
		{
			//printf("%d has neighbor %d, %d(%d)\n", shortest, v, dp[v], path[v]);
			if(visited[v]==false  &&  dp[v]>dp[shortest]+g->weight(shortest,v))
			{
				dp[v]=dp[shortest]+g->weight(shortest, v);
				path[v]=shortest;
				//printf("set %d to %d(%d)\n", v, dp[v], shortest);
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


// ==============================

void randomSetS(int S[], int n);
int randomSetM(int S[], int n);

struct State{
	int node;
	int money;
	State():node(-1),money(INT_MIN){}
	State(int n, int m):node(n),money(m){}
};

// S[k]表示走过节点k需要花费的钱, M表示从开始节点a出发时有钱M。
// 求从a到b是否有路径以及花费最小钱的最短路径
int shortestPathMoneyLimited(Graph* g, int a, int b, int *S, int M)
{
	int nvex=g->vexNum();
	if(a<0  ||  a>=nvex  ||  b<0  ||  b>=nvex)
		return INT_MAX;
	
	// int dp[nvex][M]={INT_MAX}; // 
	// int path[nvex]={-1}; // path[k]表示节点a到节点k的最短路径上的前一节点
	// bool visited[nvex][M]={false};
	int dp[nvex][M+1]; // 
	//int path[nvex]; // path[k]表示节点a到节点k的最短路径上的前一节点
	//int path[nvex][M+1]; // 记录某个状态的前一个节点
	State path[nvex][M+1]; 
	bool visited[nvex][M];
	for(int i=0; i<nvex; ++i)
		for(int j=0; j<M+1; ++j)
		{
			dp[i][j]=INT_MAX;
			visited[i][j]=false;
			//path[i][j]=-1;
			path[i][j]=State(-1, M);
		}
	// for(int i=0; i<nvex; ++i)
		// path[i]=-1;
	
	
	//dp[a][M]=0;
	dp[a][M-S[a]]=0; // pass node-a cost S[a] dollar
	printf("init dp[%d][%d]=%d\n", a, M-S[a], dp[a][M-S[a]]);
	//path[a]=-1;
	//path[a][M-S[a]]=-1;

	
	// while(true)
	int nvisited=1;
	for(nvisited=1; nvisited<nvex*(M+1); ++nvisited)
	{
		int node=-1, money=-1;
		for(int i=0; i<nvex; ++i)
		{
			for(int j=0; j<M+1; ++j)
			{
				//if(dp[i][j]!=INT_MAX)
				//	printf("found dp[%d][%d]=%d\n", i, j, dp[i][j]);
				if(visited[i][j]==false)
				{					
					if( (node<0  &&  dp[i][j]!=INT_MAX)  ||  (node>=0  &&  money>=0  &&  dp[i][j]<dp[node][money]))
					{
						node=i, money=j;
						//printf("found dp[%d][%d]=%d\n", i, j, dp[i][j]);
					}
				}
			}
		}		
		if((node<0  ||  money<0)  ||  dp[node][money]==INT_MAX)
		{
			printf("no adjacent node\n");
			break;
		}		
		visited[node][money]=true;
		printf("\tchoose min [%d][%d]=%d(%d)\n", node, money, dp[node][money], path[node]);
		
		for(int v=g->FirstNeighbor(node); v>=0; v=g->NextNeighbor(node, v))
		{
			//printf("%d has neighbor %d\n", node, v);
			//if(money>=S[v])
			//	printf("(%d, %d+%d)\n", dp[v][money-S[v]], dp[node][money], g->weight(node, v));
			if(money>=S[v]  &&  visited[v][money-S[v]]==false  &&  dp[v][money-S[v]]>dp[node][money]+g->weight(node, v))
			{
				dp[v][money-S[v]]=dp[node][money]+g->weight(node, v);
				//path[v]=node;
				//path[v][money-S[v]]=node; 
				path[v][money-S[v]]=State(node, money); // 记录使得状态dp[v][money-S[v]]更新的前一状态dp[node][money]
				//updatePath(v, path, dp); // 更新path[v]为使得dp[v][?]最小的node??
				printf("\t\tset neighbor dp[%d][%d] to %d(%d)\n", v, money-S[v], dp[v][money-S[v]], node);
			}
		}
	}
	printf("nvisited=%d, of %d\n", nvisited, nvex*(M+1));
	
	int min=-1;
	for(int i=0; i<M; ++i)
		if((min<0  &&  dp[b][i]!=INT_MAX)  ||  (min>=0  &&  dp[b][i]<=dp[b][min])) // 选择剩余钱最多的最短路径
		{
			min=i;
			printf("check dp[%d][%d]=%d\n", b, i, dp[b][i]);
		}
	if(min<0  ||  dp[b][min]==INT_MAX)
		printf("no  path from %d to %d\n", a, b);
	else
	{
		printf("the shortest path from %d to %d is %d, left money %d\n", a, b, dp[b][min], min);

		// int path2[nvex];
		// for(int i=0; i<nvex; ++i)
		// {
			// int min=INT_MAX;
			// for(int j=0; j<M+1; ++j)
			// {
				//printf("path[%d][%d]=%d\n", i, j, path[i][j]);
				// if(path[i][j]>0  &&  path[i][j]<min)
					// min=path[i][j];
			// }
			// path2[i]= (min==INT_MAX) ?  -1  :  min;
			//printf("path2[%d]=%d\n", i, path2[i]);
		// }
		// path2[a]=-1;
		// printPath(path2, nvex); // 打印path数组
		//print_path(path2, nvex, b);
		//print_path(path, nvex, b); // 输出a到b的最短路径
		//print_path1(path, nvex, b, a);
		//print_path(path, nvex, b, g);
		//print_path2(path, nvex, b, a, g);
		
		// 从状态dp[b][min]的path[b][min]向前获取完整路径
		printf("%d", b);
		for(State state=path[b][min]; state.node>=0; state=path[state.node][state.money])
		{
			printf("<——%d", state.node);
		}
		printf("\n");
	}
	
	if(min==M-S[6]-S[4]-S[7]  &&  dp[b][min]==g->weight(6, 4)+g->weight(4, 7))
		printf("ok\n");
	return dp[b][min];
}



void test_shortestPathMoneyLimited()
{
	Graph* mg=new MGraph;
	mg->Init("graph_nodirection.txt");
	mg->debug_print();
	
	int nvex=mg->vexNum();
	int S[nvex];
	randomSetS(S, nvex);	
	int M=randomSetM(S, nvex);	
	printf("M=%d\n", M);
	
	shortestPathMoneyLimited(mg, 6, 7, S, M);
	delete mg;
}

int randomSetM(int S[], int n)
{
	int sum=0;
	for(int i=0; i<n; ++i)
		sum+=S[i];
	//return sum*(0.8);
	return sum;
}

void randomSetS(int S[], int n)
{
	int seed=time(NULL); // epoch至今的秒数
	srand(seed);
	for(int i=0; i<n; ++i)
	{
		S[i]=rand()%5;
		printf("S[%d]=%d\n", i, S[i]);
	}
}



int main()
{
	test_shortestPath();
	
	printf("\n\n********with money limited*****\n");
	test_shortestPathMoneyLimited();
	
	return 0;
}
