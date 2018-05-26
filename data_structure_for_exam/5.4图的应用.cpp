//拓扑排序
bool TopologicalSort(Graph G)
{
	//如果G存在拓扑序列，返回true；否则返回false，这时G中存在环
	InitStack(S);//初始化栈，存储入度为0的顶点
	for(int i=0; i<G.vexnum; i++)
		if(indegree[i]==0)
			Push(S, i);//将所有入度为0的顶点进栈
	int count=0;//计数，记录当前已经输出的顶点数
	while(!IsEmpty(S))//栈不空，则存在入度为0的顶点
	{
		Pop(S, i);//栈顶元素出栈
		Print[count++]=i;//输出顶点i
		for(p=G.vertices[i].firstarc; p; p=p->nextarc)
		{//将所有i指向的顶点的入度减1，并且将入度减为0的顶点压入栈S
			v=p->adjvex;
			if(!(--indegree[v]))
				Push(S, v);
		}
	}
	if(count<G.vexnum)//排序失败，有向图中有回路
		return false;
	else//拓扑排序成功
		return true;
}






//DFS实现有向无环图拓扑排序
bool visited[MAX_VERTEX_NUM];//访问标记数组
void DFSTraverse(Graph G)
{
	//对图G进行遍历，访问函数为visit()
	for(v=0; v<G.vexnum; ++v)
		visited[v]=FALSE;
	time=0;
	for(v=0; v<G.vexnum; ++v)
		if(!visited[v])
			DFS(G, v);
}
void DFS(Graph G, int v)
{
	visited[v]=TRUE;
	visit(v);
	for(w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w))
		if(!visited[w])
			DFS(G, w);
	time=time+1;
	finishTime[v]=time;
}













bool closed[N]={false};//将closed表初始置为false
int Min[N]={INF};//对应Dijkstra中的从start点出发到其余各点的最短路径或加入Prim算法中最小生成树的边。初始化的时候，都置为正无穷

closed[start]=true;
Min[start]=0;

for(int i=1; i<N; i++)
{
	int k=-1;
	for(int j=0; j<N; i++)
		if(!closed[j]  &&  (k==-1  ||  Min[k]>Min[j]))
			k=j;
	closed[k]=true;
	//得到了k，这里考虑了图是连通的，所以认为k一定是存在的，而不加判定条件
	

	
	for(int j=0; j<N; j++)
	{
		//Dijkstra算法对应的更新Min算法
		if(Min[j]>Min[k]+G[k][j])
			Min[j]=Min[k]+G[k][j];

		//Prim算法对应的更新Min算法
		if(Min[j]>G[k][j])
			Min[j]=G[k][j];
	}
}









//取x的邻接结点y的下一个邻接顶点
//邻接矩阵
int NextNeighbor(MGraph& G, int x, int y)
{
	if(x!=-1  &&  y!=-1)
	{
		for(int col=y+1; col<G.vexnum; col++)
			if(G.Edge[x][col]>0  &&  G.Edge[x][col]<maxWeight)
				return col;
	}
	return -1;
}
//邻接表
int NextNeighbor(ALGraph& G, int x, int y)
{
	if(x!=-1)
	{
		ArcNode *p=G.vertices[x].first;
		while(p!=NULL  &&  p->data!=y)
			p=p->next;
		if(p!=NULL  &&  p->next!=NULL)
			return p->next->data;
	}
	return -1;
}