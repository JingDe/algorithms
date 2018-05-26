//BFS
bool visited[MAX_VERTEX_NUM];
void BFSTraverse(Graph G)
{
	//��ͼ���й�����ȱ���������ʺ���Ϊvisit()
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



//BFS��ⵥԴ���·����
void BFS_MIN_Distance(Graph G, int u)
{
	//d[i]��ʾ��u��i�������·��
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




//DFS�㷨��
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



//�ж�����ͼG�Ƿ�Ϊһ����
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
	//������ȱ���ͼG�� ͳ�Ʒ��ʹ��Ķ������ͱ�����ͨ��Vnum��Enum����
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




///DFS�㷨�ķǵݹ�ʵ��
void DFS_Non_RC(AGraph& G, int v)
{
	//�Ӷ���v��ʼ�����������������һ�α���һ����ͨ���������н��
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





//�ֱ����DFS��BFS�жϣ��Ƿ���ڶ���vi��vj��·��
//DFS
int visited[MAXSIZE]={0};

int Exist_Path_DFS(ALGraph G, int i, int j)
{//DFS�ж�����ͼG�ж���vi������vj�Ƿ���·�������򷵻�1�����򷵻�0
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
{//BFS�ж�����ͼG�ж���vi������vj�Ƿ���·�������򷵻�1�����򷵻�0
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








//����ڽӱ��ʾ��ͼ�У�����u��v�����м�·��
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