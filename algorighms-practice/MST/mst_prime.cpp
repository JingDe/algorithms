/*
POJ 1233 还是畅通工程

最小生成树
Prime算法的时间复杂度为O(|V|^2)，不依赖于|E|，
因此适用于求解边稠密的图的最小生成树。

输入：
3 
1 2 1 
1 3 2 
2 3 4
4 
1 2 1 
1 3 4 
1 4 1 
2 3 3 
2 4 2 
3 4 5 
0

输出：输出最小的公路总长度。最小生成树的权重。
3
5
*/

#include<iostream>
#include<cstring>
#include<cstdint>

const static int N=100;

int graph[N][N];// 图的邻接矩阵表示
int dmin[N];// prime算法，用来记录到达当前点的边的最小权值
//std::set<int> // 代替dmin??

bool visited[N];// 表示当前点是否已确定dmin值
int left;// 表示剩余未确定dmin的节点的个数


void print(int n)
{
	std::cout<<"debug print\n";
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
			std::cout<<graph[i][j]<<" ";
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
}

void makeGraph(int n)
{
    memset(graph, -1, sizeof(graph));
    memset(visited, false, sizeof(visited));
    
    int line=(n)*(n-1)/2;
    for(int i=0; i<line; i++)
    {        
            int x, y, w;
            //std::cin>>x;
            //std::cin>>y;
            //std::cin>>graph[x][y];
			scanf("%d %d %d", &x, &y, &w);
			graph[x][y]=w;
            graph[y][x]=w;
    }
    
    memset(dmin, -1, sizeof(dmin));
    dmin[1]=0;
    for(int i=1; i<=n; i++)
    {
        graph[i][i]=0;
        dmin[i]=graph[1][i];
    }
	
	//print(n);
}

int getmin(int n)
{
    int min=-1;
    int ret;
    for(int i=2; i<=n; i++)
    {
        if(visited[i]==false  )
        {            
            if(min!=-1  &&  dmin[i]>0  &&  dmin[i]<min)
            {
                min=dmin[i];
                ret=i;
            }
            else if(min==-1  &&  dmin[i]>0)
            {
                min=dmin[i];
                ret=i;
            }
        }
    }
    return ret;
}

void update(int n, int start)
{
    for(int i=2; i<=n; i++)
    {
		// dijkstra算法：求单源最短路径
        //if(visited[i]==false  &&  graph[start][i]>0  && dmin[i]>dmin[start]+graph[start][i])
        //    dmin[i]=dmin[start]+graph[start][i];
	
		// prime算法：求最小生成树
		if(visited[i]==false  &&  graph[start][i]>0  && dmin[i]>graph[start][i])
            dmin[i]=graph[start][i];
    }
}

int solve(int n)
{
	// 集合U，包含所有dmin确定的点；
	// 集合V，包含所有dmin未确定的点。
	
	// 初始加入U中的点只有一个，点1
    left=n-1;
    int result=0; // 保留最小权重和的结果，初始为0
    while(left>0)
    {
        int m=getmin(n);// 获得V中（visited为false）dmin值最小的下标
		//std::cout<<n-left<<" : "<<m<<", weight= "<<dmin[m]<<std::endl;
        visited[m]=true;
        result+=dmin[m];
        
        // 更新剩余节点的dmin
        update(n, m);
        left--;
    }
    return result;
}

int main()
{
    int n;
	int res;
	
    while(std::cin>>n  && n)
	//while(scanf("%d", &n)  &&  n)
    {
        makeGraph(n);
        
        res=solve(n);
        std::cout<<res<<std::endl;
    }
    return 0;
}
