
#define MAX_VERTEX 20


// 图的邻接矩阵表示
template<typename T>
class MGraph{
public:
	//int edge[MAX_VERTEX][MAX_VERTEX];
	vector<vector<int>> edge; // edge[i][j]表示图中顶点值为vertexVal[i]和vertexVal[j]的两个顶点之间是否相邻（权重是多少）
	vector<T> vertexVal;
	int nVertex;
	int nEdge;
};

// 图的邻接表表示


template<typename T>
class AdjGraph{
public:
	struct EdgeNode{
		int adj;
		EdgeNode* next;
	};

	struct VertexNode{
		T val;
		EdgeNode* firstEdge;
	};
	
	//VertexNode* graph[MAX_VERTEX];
	vector<VertexNode*> vertexNodes;
	int nVertex;
};


struct NodeLevel{
	int nodeIdx;
	int level;
    NodeLevel(int n, int l)
    {
        nodeIdx=n;
        level=l;
    }
};

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	MGraph<string> graph;
	createGraph(beginWord, wordList, graph);

	queue<NodeLevel> Q; // queue的每一个元素表示，图中的对应节点的下标, graph.vertexVal[]的下标
	Q.push(NodeLevel(0, 1)); // 第一个元素是beginWord，也是BFS遍历的起点
	bool visited[graph.nVertex];
	memset(visited, 0, sizeof(visited));
	visited[0]=true;

	while(!Q.empty())
	{
		NodeLevel cur=Q.front();
		Q.pop();

		if(graph.vertexVal[cur.nodeIdx]==endWord)
			return cur.level;

		for(int i=0; i<graph.nVertex; ++i)
		{
			if(visited[i])
				continue;
			if(graph.edge[cur.nodeIdx][i])
			{
				Q.push(NodeLevel(i, cur.level+1));
				visited[i]=true;
			}
		}
	}
	return 0;
}

void createGraph(string& beginWord, vector<string>& wordList, MGraph<string>& graph)
{
	// 将beginWord和wordList中的所有单词作为图的节点
	// 相差一个字符的单词，相连
	graph.nVertex=1+wordList.size();
	vector<vector<int>> tmp(graph.nVertex, vector<int>(graph.nVertex));
	graph.edge.swap(tmp);

	graph.vertexVal.push_back(beginWord);
	for(int i=0; i<wordList.size(); ++i)
		graph.vertexVal.push_back(wordList[i]);

	graph.nEdge=0;

	for(int i=0; i<graph.nVertex; ++i)
	{
		for(int j=0; j<graph.nVertex; ++j)
		{
			if(diffOneChar(graph.vertexVal[i], graph.vertexVal[j]))
			{
				graph.edge[i][j]=graph.edge[j][i]=1;
				graph.nEdge+=2;
			}
		}
	}
}
bool diffOneChar(const string& s1, const string& s2)
{
	int diffCnt=0;
	for(int i=0; i<s1.size(); ++i)
	{
		if(s1[i]!=s2[i])
		{
			diffCnt++;
			if(diffCnt>1)
				return false;
		}
	}
	return true;
}
