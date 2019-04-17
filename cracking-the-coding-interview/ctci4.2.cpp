#include<string.h>
#include<stdint.h>
#include<stdio.h>
#include<stack>
#include<assert.h>
#include<iostream>
#include<errno.h>
#include<queue>

class Graph{
protected:
	enum { N=100 };
	int nvex, nedge;
	
public:
	Graph();
	virtual ~Graph();
	
	virtual void Init()=0;
	
	virtual int FirstNeighbor(int v)=0;
	virtual int NextNeighbor(int v, int w)=0;
	
	void DFSTraverse();
	void DFS(int v, bool visited[]);
	void DFS2(int v, bool visited[]);
	
	void BFSTraverse();
	void BFS(int v, bool visited[]);
	
	bool hasPathDFS(int a, int b);
	bool hasPathBFS(int a, int b);
	
	bool BFS_for_solution(int v, int d, bool visited[]);
};
Graph::Graph():nvex(0),nedge(0)
{}

Graph::~Graph()
{}

// DFS遍历
bool Graph::hasPathDFS(int a, int b)
{
	bool visited[N]={false};
	DFS(a, visited);
	if(visited[b])
		return true;
	
	memset(visited, false, sizeof(visited));
	DFS(b, visited);
	if(visited[a])
		return true;
	
	return false;
}


void Graph::DFSTraverse()
{
	bool visited[N]={false};
	for(int v=0; v<nvex; ++v)
		if(!visited[v])
			DFS(v, visited);
}

void Graph::DFS(int v, bool visited[])
{
	visited[v]=true;
	for(int w=FirstNeighbor(v); w>=0; w=NextNeighbor(v, w))
		if(!visited[w])
			DFS(w, visited);
}

// DFS的非递归实现
void Graph::DFS2(int v, bool visited[])
{
	// 使用stack，使得先入栈的同一层次节点先进后出，后入栈的儿子节点后进先出
	std::stack<int> S;
	S.push(v);
	while(!S.empty())
	{
		int v=S.top();
		S.pop();
		visited[v]=true;
		for(int w=FirstNeighbor(v); w>=0; w=NextNeighbor(v, w))
			if(!visited[w])
				S.push(w);
	}
}


// BFS遍历
bool Graph::hasPathBFS(int a, int b)
{
	bool visited[N]={false};
	// BFS(a, visited);
	// if(visited[b])
		// return true;
	if(BFS_for_solution(a, b, visited))
		return true;
	
	memset(visited, false, sizeof(visited));
	// BFS(b, visited);
	// if(visited[a])
		// return true;
	if(BFS_for_solution(b, a, visited))
		return true;
	
	return false;
}

void Graph::BFS(int v, bool visited[])
{
	std::queue<int> Q;
	Q.push(v);
	while(!Q.empty())
	{
		int v=Q.front();
		Q.pop();
		visited[v]=true;
		
		for(int w=FirstNeighbor(v); w>=0; w=NextNeighbor(v, w))
			if(!visited[w])
				Q.push(w);
	}
}

bool Graph::BFS_for_solution(int a, int d, bool visited[])
{
	std::queue<int> Q;
	Q.push(a);
	while(!Q.empty())
	{
		int v=Q.front();
		Q.pop();
		visited[v]=true;
		
		for(int w=FirstNeighbor(v); w>=0; w=NextNeighbor(v, w))
		{
			if(w==d)
				return true;
			if(!visited[w])
				Q.push(w);
		}
	}
	return false;
}

void Graph::BFSTraverse()
{
	bool visited[N]={false};
	for(int v=0; v<nvex; ++v)
		if(!visited[v])
			BFS(v, visited);
}


// 图的邻接矩阵定义
class MGraph: public Graph{
private:
	enum { N=100 };
	int vertex[N]; // 定点的data
	int edge[N][N]; // 边的weight
	//int nvex, nedge;
	
public:
	MGraph();
	virtual ~MGraph();
	//bool hasPathDFS(int a, int b);
	
	virtual void Init();
	
	virtual int FirstNeighbor(int v);
	virtual int NextNeighbor(int v, int w);
};

MGraph::MGraph():Graph()/* nvex(0),nedge(0) */
{
	memset(vertex, 0, sizeof(vertex));
	memset(edge, -1, sizeof(edge));
}

MGraph::~MGraph()
{}

void MGraph::Init()
{
	FILE *f=freopen("4.2.in", "r", stdin);
	if(f==NULL)
	{
		perror("Init failed");
		return ;
	}
	int m, u, v, w;
	std::cin>>nvex>>nedge;
	for(int i=0; i<nedge; ++i){
		std::cin>>u>>v>>w;
		edge[u][v] = w;
	}
	fclose(stdin);
}

int MGraph::FirstNeighbor(int v)
{
	//assert(v<nvex);
	if(v>=nvex)
		return -1;
	for(int j=0; j<nvex; j++)
		if(edge[v][j]>0)
			return j;
	return -1;
}

int MGraph::NextNeighbor(int v, int w)
{
	//assert(v<nvex  &&  w<nvex  &&  edge[v][w]>0);
	if(v>=nvex  ||  w>=nvex  ||  edge[v][w]<0)
		return -1;
	for(int j=w+1; j<nvex; j++)
		if(edge[v][j]>0)
			return j;
	return -1;
}

// ==============================================
// 图的邻接表定义
// 顶点节点，边节点
struct AdjNode{
	int idx;
	int weight;
	struct AdjNode* nextEdge;
	
	AdjNode(int i, int w):idx(i),weight(w),nextEdge(NULL){}
};

//typedef struct VertexNode[100] AdjGraph;
struct VertexNode{
	int data;
	struct AdjNode* firstEdge;
	
	VertexNode():data(-1),firstEdge(NULL){}
};

class AdjGraph: public Graph{
private:
	enum { N=100 };
	VertexNode graph[N];
	//int nvex, nedge;
	
public:
	AdjGraph();
	~AdjGraph();
	//bool hasPathDFS(int a, int b);
	
	virtual void Init();
	
	virtual int FirstNeighbor(int v);
	virtual int NextNeighbor(int v, int w);
};

AdjGraph::AdjGraph():Graph()/* nvex(0),nedge(0) */
{
	
}

AdjGraph::~AdjGraph()
{
	for(int i=0; i<nvex; i++)
	{
		AdjNode* head=graph[i].firstEdge;
		AdjNode *p;
		while(head)
		{
			p=head->nextEdge;
			delete head;
			head=p;
		}
	}
}

void AdjGraph::Init()
{
	FILE *f=freopen("4.2.in", "r", stdin);
	if(f==NULL)
	{
		perror("Init failed");
		return ;
	}
	int m, u, v, w;
	std::cin>>nvex>>nedge;
	for(int i=0; i<nedge; ++i){
		std::cin>>u>>v>>w;
		
		AdjNode* head=graph[u].firstEdge;
		AdjNode* n=new AdjNode(v, w);
		if(head!=NULL)
			n->nextEdge=head;
		graph[u].firstEdge=n;
	}
	fclose(stdin);
}

int AdjGraph::FirstNeighbor(int v)
{
	AdjNode *head=graph[v].firstEdge;
	if(head)
		return head->idx;
	return -1;
}

int AdjGraph::NextNeighbor(int v, int w)
{
	AdjNode *head=graph[v].firstEdge;
	while(head  &&  head->idx!=v)
		head=head->nextEdge;
	if(head  &&  head->idx==v  &&  head->nextEdge)
		return head->nextEdge->idx;
	return -1;
}

// =========================================================


void test_memset()
{
	int a[3][4];
	printf("sizeof a[][]=%d, sizeof a[]=%d, sizeof a[][]=%d, sizeof int=%d\n", sizeof(a), sizeof(a[0]), sizeof(a[0][0]), sizeof(int));
	memset(a, 0, sizeof(a)); // 复制0（int转换到unsigned char)到a指向的连续多少个字节
	//memset(a, 0, 3*4*sizeof(int));
	
	int **b=new int*[3];
	printf("sizeof b[][]=%d, sizeof int**=%d, sizeof b[]=%d, sizeof int*=%d, sizeof void*=%d\n", sizeof(b), sizeof(int**), sizeof(b[0]), sizeof(int*), sizeof(void*));
	//memset(b, 0, sizeof(int*)*3);
	memset(b, 0, sizeof(b[0])*3);
	for(int i=0; i<3; i++)
	{
		b[i]=new int[4];
		printf("sizeof b[][]=%d, sizeof b[]=%d\n", sizeof(b[i][0]), sizeof(b[i]));
		memset(b[i], 0, sizeof(b[i][0])*4);
	}	
}

void change_pointer_arg(bool state[], int sz)
{
	state[1]=1;
	state[3]=1;
}

void change_pointer_arg2(bool state[], int sz)
{
	state[5]=1;
}

void print_pointer_arg(bool state[], int sz)
{
	for(int i=0; i<sz; i++)
		printf("%d ", state[i]);
	printf("\n");
}

void test_pointer_arg()
{
	bool state[6]={0};
	int sz=sizeof(state)/sizeof(state[0]);
	print_pointer_arg(state, sz);
	change_pointer_arg(state, sz);
	print_pointer_arg(state, sz);
}

int main()
{
	{
		//test_memset();
		test_pointer_arg();
	}
	
	{
		printf("\n-------------- MGraph DFS------------\n");
		// MGraph DFS
		Graph *mg=new MGraph();
		mg->Init();
		std::cout<<mg->hasPathDFS(0, 3)<<std::endl;
		std::cout<<mg->hasPathDFS(1, 3)<<std::endl;
		std::cout<<mg->hasPathDFS(2, 3)<<std::endl;
	}
	
	{
		printf("\n-------------- MGraph BFS------------\n");
		// MGraph BFS
		Graph *mg=new MGraph();
		mg->Init();
		std::cout<<mg->hasPathBFS(0, 3)<<std::endl;
		std::cout<<mg->hasPathBFS(1, 3)<<std::endl;
		std::cout<<mg->hasPathBFS(2, 3)<<std::endl;
	}
	
	{
		// AdjGraph DFS
		printf("\n-------------- AdjGraph DFS------------\n");
		Graph *mg=new AdjGraph();
		mg->Init();
		std::cout<<mg->hasPathDFS(0, 3)<<std::endl;
		std::cout<<mg->hasPathDFS(1, 3)<<std::endl;
		std::cout<<mg->hasPathDFS(2, 3)<<std::endl;
	}
	
	{
		printf("\n-------------- AdjGraph BFS------------\n");
		// AdjGraph BFS
		Graph *mg=new AdjGraph();
		mg->Init();
		std::cout<<mg->hasPathBFS(0, 3)<<std::endl;
		std::cout<<mg->hasPathBFS(1, 3)<<std::endl;
		std::cout<<mg->hasPathBFS(2, 3)<<std::endl;
	}
	return 0;
}