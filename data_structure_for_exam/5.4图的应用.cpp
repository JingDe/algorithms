//��������
bool TopologicalSort(Graph G)
{
	//���G�����������У�����true�����򷵻�false����ʱG�д��ڻ�
	InitStack(S);//��ʼ��ջ���洢���Ϊ0�Ķ���
	for(int i=0; i<G.vexnum; i++)
		if(indegree[i]==0)
			Push(S, i);//���������Ϊ0�Ķ����ջ
	int count=0;//��������¼��ǰ�Ѿ�����Ķ�����
	while(!IsEmpty(S))//ջ���գ���������Ϊ0�Ķ���
	{
		Pop(S, i);//ջ��Ԫ�س�ջ
		Print[count++]=i;//�������i
		for(p=G.vertices[i].firstarc; p; p=p->nextarc)
		{//������iָ��Ķ������ȼ�1�����ҽ���ȼ�Ϊ0�Ķ���ѹ��ջS
			v=p->adjvex;
			if(!(--indegree[v]))
				Push(S, v);
		}
	}
	if(count<G.vexnum)//����ʧ�ܣ�����ͼ���л�·
		return false;
	else//��������ɹ�
		return true;
}






//DFSʵ�������޻�ͼ��������
bool visited[MAX_VERTEX_NUM];//���ʱ������
void DFSTraverse(Graph G)
{
	//��ͼG���б��������ʺ���Ϊvisit()
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













bool closed[N]={false};//��closed���ʼ��Ϊfalse
int Min[N]={INF};//��ӦDijkstra�еĴ�start������������������·�������Prim�㷨����С�������ıߡ���ʼ����ʱ�򣬶���Ϊ������

closed[start]=true;
Min[start]=0;

for(int i=1; i<N; i++)
{
	int k=-1;
	for(int j=0; j<N; i++)
		if(!closed[j]  &&  (k==-1  ||  Min[k]>Min[j]))
			k=j;
	closed[k]=true;
	//�õ���k�����￼����ͼ����ͨ�ģ�������Ϊkһ���Ǵ��ڵģ��������ж�����
	

	
	for(int j=0; j<N; j++)
	{
		//Dijkstra�㷨��Ӧ�ĸ���Min�㷨
		if(Min[j]>Min[k]+G[k][j])
			Min[j]=Min[k]+G[k][j];

		//Prim�㷨��Ӧ�ĸ���Min�㷨
		if(Min[j]>G[k][j])
			Min[j]=G[k][j];
	}
}









//ȡx���ڽӽ��y����һ���ڽӶ���
//�ڽӾ���
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
//�ڽӱ�
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