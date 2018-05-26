//BFS
bool visited[MAX_VERTEX_NUM];
void BFSTraverse(Graph G)
{
	//对图进行广度优先遍历，设访问函数为visit()
	for(i=0; i<G.vexnum; ++i)
		visited[i]=FALSE;
	InitQueue(Q);
	for(i=0; i<G.vexnum; ++i)
		if(!visited[i])
			BFS(G, i);
}

void BFS(Graph G, int v)
{
	visit(v);
	visited[v]=TRUE;
	Enqueue(Q, v);
	while(!isEmpty(Q))
	{
		DeQueue(Q, v);
		for(w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
			if(!visited[w])
			{
				visit(w);
				visited[w]=TRUE;
				EnQueue(Q, w);
			}
	}
}



//BFS求解单源最短路径：
void BFS_MIN_Distance(Graph G, int u)
{
	//d[i]表示从u到i结点的最短路径
	for(i=0; i<G.vexnum; ++i)
		d[i]=BIGNUM;
	visited[u]=true;
	d[u]=0;
	EnQueue(Q, u);
	while(!IsEmpty(Q))
	{
		DeQueue(Q, u);
		for(w=FirstNeighbor(G, u); w>=0; w=NextNeighbor(G, u, w))
			if(!visited[w])
			{
				visited[w]=true;
				d[w]=d[u]+1;
				EnQueue(Q, w);
			}
	}
}




//DFS算法：
bool visited[MAX_VERTEX_NUM];
void DFSTraverse(Graph G)
{
	for(v=0; v<G.vexnum; ++v)
		visited[v]=false;
	for(v=0; v<G.vexnum; ++v)
		if(!visited[v])
			DFS(G, v);
}
void DFS(Graph G, int v)
{
	visit(v);
	visited[v]=true;
	for(w=FirstNeighbor(G,v); w>=0; w=NextNeighbor(G,v,w))
		if(!visited[w])
			DFS(G, w);
}



//判断无向图G是否为一棵树
bool isTree(Graph& G)
{
	for(i=1; i<=G.vexnum; i++)
		visited[i]=false;
	int Vnum=0, Enum=0;
	DFS(G, 1, Vnum, Enum, visited);
	if(Vnum==G.vexnum  &&  Enum==2*(G.vexnum-1))
		return true;
	else
		return false;
}

void DFS(Graph & G, int v, int& Vnum, int& Enum, int visited[])
{
	//深度优先遍历图G， 统计访问过的顶点数和边数，通过Vnum和Enum返回
	visited[v]=true;
	Vnum++;
	int w=FirstNeighbor(G, v);
	while(w!=-1)
	{
		Enum++;
		if(!visited[w])
			DFS(G, w, Vnum, Enum, visited);
		w=NextNeighbor(G, v, w);
	}
}




///DFS算法的非递归实现
void DFS_Non_RC(AGraph& G, int v)
{
	//从顶点v开始进行深度优先搜索，一次遍历一个连通分量的所有结点
	int w;
	InitStack(S);
	for(i=0; i<G.vexnum; i++)
		visited[i]=false;
	Push(S, v);
	visited[v]=true;
	while(!IsEmpty(S))
	{
		k=Pop(S);
		visit(k);
		for(w=FirstNeighbor(G, k); w>=0; w=NextNeighbor(G, k, w))
			if(!visited[w])
			{
				Push(S, w);
				visited[w]=true;
			}
	}
}





//分别采用DFS和BFS判断，是否存在顶点vi到vj的路径
//DFS
int visited[MAXSIZE]={0};

int Exist_Path_DFS(ALGraph G, int i, int j)
{//DFS判断有向图G中顶点vi到顶点vj是否有路径，是则返回1，否则返回0
	int p;
	if(i==j)
		return 1;
	else
	{
		visited[i]=1;
		for(p=FirstNeighbor(G, i); p>=0; p=NextNeighbor(G, i, p))
		{
			k=p.adjvex;
			if(!visited[p]  &&  Exist_Path_DFS(G, p, j))
				return 1;
		}
	}
	return 0;
}

//BFS
int visited[MAXSIZE]={0};
int Exist_Path_BFS(ALGraph G, int i, int j)
{//BFS判断有向图G中顶点vi到顶点vj是否有路径，是则返回1，否则返回0
	InitQueue(Q);
	EnQueue(Q, i);
	while(!isEmpty(Q))
	{
		DeQueue(Q, u);
		visited[u]=1;
		for(p=FirstNeighbor(G, i); p; p=NextNeighbor(G, i, p))
		{
			k=p.adjvex;
			if(k==j)
				return 1;
			if(!visited[k])
				EnQueue(Q, k);
		}
	}
	return 0;
}








//输出邻接表表示的图中，顶点u到v的所有简单路径
void FindPath(AGraph *G, int u, int v, int path[], int d)
{
	int w, i;
	ArcNode *p;
	temp=d;
	d++;
	path[d]=u;
	visited[u]=1;
	if(u==v)
		print(pth[]);
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		w=p->adjvex;
		if(visited[w]==0)
			FindPath(G, w, v, path, d);
		p=p->nextarc;
	}
	visited[u]=0;
	d=temp;
}