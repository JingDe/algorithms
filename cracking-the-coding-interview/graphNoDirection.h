
#ifndef CTCI_GRAPH_NODIRECTION_H
#define CTCI_GRAPH_NODIRECTION_H

#include<string>
#include<map>

typedef  int VertexType;
typedef  int WeightType;

#define INT_MAX ~(1<<31)

class Graph{
protected:
	int nvex, nedge;
	const static int INVALID_EDGE=INT_MAX;
	
public:
	Graph();
	virtual ~Graph();
	
	virtual void Init(std::string filename)=0;
	int vexNum(){ return nvex; }
	int edgeNum() { return nedge; }
	virtual int weight(int a, int b)=0;
	
	virtual int FirstNeighbor(int v)=0;
	virtual int NextNeighbor(int v, int w)=0;
	
	virtual void debug_print()=0;
	
	void DFSTraverse();
	void DFS(int v, std::map<int, bool> visited);
	void DFS2(int v, std::map<int, bool> visited);
	
	void BFSTraverse();
	void BFS(int v, std::map<int, bool> visited);
	
	bool hasPathDFS(int a, int b);
	bool hasPathBFS(int a, int b);
	
	bool BFS_for_solution(int v, int d, std::map<int, bool> visited);
};


// 图的邻接矩阵定义
class MGraph: public Graph{
private:
	//int vertex[N]; // 顶点的data
	//std::vector<VertexType> vertex;
	VertexType* vertex;
	
	//int edge[N][N]; // 边的weight
	//std::vector<WeightType> edge;
	WeightType** edge;
	
	//int nvex, nedge;
	
	void initEdge();
	
	
public:
	MGraph();
	virtual ~MGraph();
	//bool hasPathDFS(int a, int b);
	
	virtual void Init(std::string fileanme);
	virtual int weight(int a, int b);
	virtual void debug_print();
	
	virtual int FirstNeighbor(int v);
	virtual int NextNeighbor(int v, int w);
};


// ==============================================
// 图的邻接表定义
// 顶点节点
struct AdjNode{
	int idx; // 边关联的节点
	WeightType weight;
	struct AdjNode* nextEdge;
	
	AdjNode(int i, int w):idx(i),weight(w),nextEdge(NULL){}
};

// 边节点
struct VertexNode{
	VertexType data;
	struct AdjNode* firstEdge;
	
	VertexNode():data(-1),firstEdge(NULL){}
};

//typedef struct VertexNode[100] AdjGraph;
class AdjGraph: public Graph{
private:
	//VertexNode graph[N];
	VertexNode* graph;
	//int nvex, nedge;
	
public:
	AdjGraph();
	~AdjGraph();
	//bool hasPathDFS(int a, int b);
	
	virtual void Init(std::string filename);
	virtual int weight(int a, int b);
	virtual void debug_print();
	
	virtual int FirstNeighbor(int v);
	virtual int NextNeighbor(int v, int w);
};


#endif