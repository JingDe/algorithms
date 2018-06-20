
void Graph::printPath(Vertex v)
{
	if(v.path!=NOT_A_VERTEX)
	{
		printPath(v.path);
		cout<<" to ";
	}
	cout<<v;
}

void Graph::dijkstra(Vertex s)
{
	for each Vertex v
	{
		v.dist=INFINITY;
		v.known=false;
	}
	
	s.dist=0;
	
	for(; ;)
	{
		Vertex v=smallest unknown distance vertex;
		if(v==NOT_A_VERTEX)
			break;//所有顶点的最短路径都已知，算法终止
		v.known=true;//v的最短路径已知
		
		for each Vertex w adjacent to v
			if(!w.known)
				if(v.dist+cvw < w.dist)
				{//更新剩下顶点的当前最短路径，和前驱结点
					decrease(w.dist to v.dist+cvw);
					w.path=v;
				}
	}
}