

// 图的邻接矩阵定义
// 顶点节点，边节点
struct AdjNode{
	int idx;
	struct AdjNode* next;
};

typedef struct VertexNode[100] AdjGraph;
struct VertexNode{
	int data;
	struct AdjNode* firstEdge;
};


bool hasPath(int a, int b)
{}
