//ͼ���ڽӾ���洢�ṹ����
#define MaxVertexNum 100
typedef char VertextType;
typedef int EdgeType;
typedef struct{
	VertexType Vex[MaxVertexNum];
	EdgeType Edge[MaxVertexNum][MaxVertexNum];
	int vexnum, arcnum;
}MGraph;



//ͼ���ڽӱ�洢�ṹ���壺
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



//ͼ��ʮ������洢�ṹ����
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





//ͼ���ڽӶ��ر�洢�ṹ���壺
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




//ͼ���ڽӱ��ʾת���ɾ����ʾ
void Convert(ALGraph &G, int arcs[M][N])
{//���ڽӱ��ʾ��ͼGת��Ϊ�ڽӾ���arcs
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