
void Graph::weightedNegative(Vertex s)
{
	Queue<Vertex> q;
	
	for each Vertex v
		v.dist=INFINITY;
		
	s.dist=0;
	
	while(!q.isEmpty())
	{
		Vertex v=q.dequeue();
		
		for each Vertex w adjacent to v//每边不止执行一次更新w的操作
			if(v.dist+cvw < w.dist)
			{
				w.dist=v.dist+cvw;
				w.path=v;
				if(w is not already in q)
					q.enqueue(w);
			}
	}
}