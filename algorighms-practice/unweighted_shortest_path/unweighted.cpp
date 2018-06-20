void Graph::unweighted(Vertex s)
{
	Queue<Vertex> q;
	
	for each Vertex v
		v.dist=INFINITY;
	
	s.dist=0;
	q.enqueue{s};
	
	while(!q.isEmpty())
	{
		Vertex v=q.dequeue();
		
		for each Vertex w adjacent to v
			if(w.dist==INFINITY)
			{
				w.dist=v.dist+1;
				w.path=v;
				q.enqueue(w);
			}
	}
}

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