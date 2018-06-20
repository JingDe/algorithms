//图的邻接矩阵存储结构定义
#define MaxVertexNum 100
typedef char VertextType;
typedef int EdgeType;
typedef struct{
	VertexType Vex[MaxVertexNum];
	EdgeType Edge[MaxVertexNum][MaxVertexNum];
	int vexnum, arcnum;
}MGraph;



//图的邻接表存储结构定义：
#define MaxVertexNum 100
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *next;
	//InfoType info;
}ArcNode;

typedef struct VNode{
	VertexType data;
	ArcNode *first;
}VNode, AdjList[MaxVettexNum];

typedef struct{
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;



//图的十字链表存储结构定义
#define MaxVertexNum 100
typedef struct ArcNode{
	int tailvex, headvex;
	struct ArcNode *hlink, *tlink;
	//InfoType info;
}ArcNode;
typedef struct VNode{
	VertexType data;
	ArcNode *firstin, *firstout;
}VNode;
typedef struct{
	VNode xlist[MaxVertexNum];
	int vexnum, arcnum;
}GLGraph;





//图的邻接多重表存储结构定义：
#define MaxVertexNum 100
typedef struct ArcNode{
	bool mark;
	int ivex, jvex;
	struct ArcNode *ilink, *jlink;
	//InfoType info;
}ArcNode;
typedef struct VNode{
	VertexType data;
	ArcNode *firstedge;
}VNode;
typedef struct{
	VNode adjmulist[MaxVertexNum];
	int vexnum, arcnum;
}AMLGraph;




//图的邻接表表示转换成矩阵表示
void Convert(ALGraph &G, int arcs[M][N])
{//将邻接表表示的图G转换为邻接矩阵arcs
	for(i=0; i<n; i++)
	{
		p=(G->v[i]).firstarc;
		whilep!=NULL)
		{
			arcs[i][p->data]=1;
			p=p->nextarc;
		}
	}
}