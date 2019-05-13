#include"graphNoDirection.h"
#include<stdio.h>

#include<string>
#include<map>
#include<queue>
#include<stack>
#include<stdio.h>
#include<iostream>

Graph::Graph():nvex(0),nedge(0)
{}

Graph::~Graph()
{}

void Graph::debug_print()
{
	printf("Graph: %d vertex, %d edge\n", nvex, nedge);
	
}

// DFS遍历
bool Graph::hasPathDFS(int a, int b)
{
	//bool visited[N]={false};
	//std::vector<int> visited;
	std::map<int, bool> visited; // bool默认初始化为false
	
	DFS(a, visited);
	if(visited[b])
		return true;
	
	//memset(visited, false, sizeof(visited));
	for(std::map<int, bool>::iterator it=visited.begin(); it!=visited.end(); ++it)
		it->second=false;
	
	DFS(b, visited);
	if(visited[a])
		return true;
	
	return false;
}


void Graph::DFSTraverse()
{
	//bool visited[N]={false};
	std::map<int, bool> visited;
	for(int v=0; v<nvex; ++v)
		if(!visited[v])
			DFS(v, visited);
}

void Graph::DFS(int v, std::map<int,bool> visited)
{
	visited[v]=true;
	for(int w=FirstNeighbor(v); w>=0; w=NextNeighbor(v, w))
		if(!visited[w])
			DFS(w, visited);
}

// DFS的非递归实现
void Graph::DFS2(int v, std::map<int,bool> visited)
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
	//bool visited[N]={false};
	std::map<int, bool> visited;
	// BFS(a, visited);
	// if(visited[b])
		// return true;
	if(BFS_for_solution(a, b, visited))
		return true;
	
	//memset(visited, false, sizeof(visited));
	for(std::map<int, bool>::iterator it=visited.begin(); it!=visited.end(); ++it)
		it->second=false;
		
	// BFS(b, visited);
	// if(visited[a])
		// return true;
	if(BFS_for_solution(b, a, visited))
		return true;
	
	return false;
}

void Graph::BFS(int v, std::map<int,bool> visited)
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

bool Graph::BFS_for_solution(int a, int d, std::map<int,bool> visited)
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
	//bool visited[N]={false};
	std::map<int,bool> visited;
	for(int v=0; v<nvex; ++v)
		if(!visited[v])
			BFS(v, visited);
}



MGraph::MGraph():Graph(),vertex(NULL),edge(NULL)/* nvex(0),nedge(0) */
{
}

MGraph::~MGraph()
{
	// 
	if(vertex!=NULL)
		delete []vertex;
	if(edge!=NULL)
	{
		for(int i=0; i<nvex; ++i)
			delete []edge[i];
		delete [] edge;
	}
}

void MGraph::Init(std::string filename)
{
	FILE *f=freopen(filename.c_str(), "r", stdin);
	if(f==NULL)
	{
		perror("Init failed");
		return ;
	}
	int m, u, v, w;
	std::cin>>nvex>>nedge;
	
	// allocate memory for vertex and edge
	edge=new WeightType*[nvex];
	for(int i=0; i<nvex; ++i)
		edge[i]=new WeightType[nvex];
	initEdge();
	
	for(int i=0; i<nedge; ++i){
		std::cin>>u>>v>>w;
		edge[u][v] = w;
		edge[v][u]=w;
	}
	for(int i=0; i<nvex; ++i)
	{
		edge[i][i]=0;
	}
	fclose(stdin);
}

void MGraph::debug_print()
{
	printf("MGraph: %d vertex, %d edge\n", nvex, nedge);
	for(int i=0; i<nvex; ++i)
		for(int j=i+1; j<nvex; ++j)
			if(edge[i][j]!=INVALID_EDGE)
				printf("edge[%d, %d]=%d\n", i, j, edge[i][j]);
}

void MGraph::initEdge()
{
	for(int i=0; i<nvex; ++i)
		for(int j=0; j<nvex; ++j)
			edge[i][j]=INVALID_EDGE;
}

int MGraph::weight(int a, int b)
{
	if(a<0  ||  a>=nvex  ||  b<0  ||  b>=nvex)
		return INVALID_EDGE;
	return edge[a][b];
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


AdjGraph::AdjGraph():Graph(),graph(NULL)/* nvex(0),nedge(0) */
{
	
}

AdjGraph::~AdjGraph()
{
	if(graph==NULL)
		return;
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
	delete []graph;
}

void AdjGraph::Init(std::string filename)
{
	FILE *f=freopen(filename.c_str(), "r", stdin);
	if(f==NULL)
	{
		perror("Init failed");
		return ;
	}
	int m, u, v, w;
	std::cin>>nvex>>nedge;
	
	// allocate memory for graph
	graph=new VertexNode[nvex];
	
	for(int i=0; i<nedge; ++i){
		std::cin>>u>>v>>w;
		
		AdjNode* head=graph[u].firstEdge;
		AdjNode* n=new AdjNode(v, w);
		if(head!=NULL)
			n->nextEdge=head;
		graph[u].firstEdge=n;
		
		head=graph[v].firstEdge;
		n=new AdjNode(u, w);
		if(head!=NULL)
			n->nextEdge=head;
		graph[v].firstEdge=n;
	}
	fclose(stdin);
}

void AdjGraph::debug_print()
{
	printf("AdjGraph: %d vertex, %d edge\n", nvex, nedge);
}

int AdjGraph::weight(int a, int b)
{
	if(a<0  ||  a>=nvex  ||  b<0  ||  b>=nvex)
		return INVALID_EDGE;
	AdjNode *head=graph[a].firstEdge;
	while(head)
	{
		if(head->idx==b)
			return head->weight;
		head=head->nextEdge;
	}
	return INVALID_EDGE;
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