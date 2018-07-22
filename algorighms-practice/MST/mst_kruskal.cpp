
/*
Kruskal算法，求最小生成树
算法思想：
不优先考虑联通的情况，而是优先考虑寻找最小的边，再判断是否满足最少连通。

实现：
使用堆来存放边的集合，每次选择最小权值需要O(log|E|)的时间

已选择的所有边可以看成若干个等价类，一个连通分量一个等价类，每次添加新的边使用union操作


实现思路：
//先从输入构造用邻接矩阵表示的图，
再将所有的边构造成最小堆。
同时将顶点初始化成并查集。

每次选择最小边，
	如果这条边的两个顶点在不同的子树中，
		则：将边添加到最终的MST中，同时两个顶点合并到同一个子树中
	从堆中删除该边。
直到所有顶点都在同一个子树中


考虑：
堆的实现：
	map：有序关联容器，按照key排序。查找、删除、插入复杂度为O(logN)
		std::map<int, std::pair<int, int> >
		key是边的权重，pair是两个顶点
	make_heap

*/

#include<iostream>
#include<map>
#include<utility>
#include<cstdlib>

const static int N=100;

std::multimap<int, std::pair<int, int> > graph;
int ufset[N];

int find(int x)
{
	while(ufset[x]>-1)
		x=ufset[x];
	return x;
}

void Union(int a, int b)
{
	int rootA=find(a);
	int rootB=find(b);
	if(rootA!=rootB)
		ufset[rootA]=rootB;
}

void debug_print()
{
	int w, e1, e2;
	
	for(std::multimap<int, std::pair<int, int> >::const_iterator it=graph.begin();
		it!=graph.end(); it++)
	{
		w=it->first;
		e1=it->second.first;
		e2=it->second.second;
		
		//printf("%d, %d : %d\n", e1, e2, w);
	}
}

void make_graph(int n)
{
	graph.clear();
	
	int count=n*(n-1)/2;
	int e1, e2, w;
	for(int i=0; i<count; i++)
	{
		std::cin>>e1>>e2>>w;
		// graph[w]=std::make_pair(e1, e2); // 不适用multimap
		graph.insert(std::make_pair(w, std::make_pair(e1, e2)));
	}
	
	for(int i=0; i<n; i++)
	{
		ufset[i]=-1;
	}
	
	//debug_print();
}

int solve(int n)
{
	int res=0;
	int e1, e2, w;
	
	// n个节点要连通，选择n-1条边
	for(int c=0; c<n-1; )
	{
		w=graph.begin()->first;
		e1=graph.begin()->second.first;
		e2=graph.begin()->second.second;
		
		//printf("%d —— %d : %d\n", e1, e2, w);
		
		// graph.erase(w); 
		graph.erase(graph.begin());
		
		if(find(e1)!=find(e2))
		{
			// 两个不连通的节点
			Union(e1, e2);
			res+=w;
			
			//printf("%d —— %d : %d, %d\n", e1, e2, w, res);
			
			c++;
		}
	}
	return res;
}

int main()
{
	int n;
	int res;
	
	while(std::cin>>n  &&  n)
	{
		make_graph(n);
		
		res=solve(n);
		std::cout<<res<<std::endl;
	}
	
	return 0;
}

