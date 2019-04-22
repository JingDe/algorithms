#include<stdio.h>
#include<string.h>
#include<list>
#include<stack>
#include<iostream>
#include<deque>
#include<queue>
#include<errno.h>

typedef long long ll;
long long zuheshu(int a, int b);

ll getPath(ll m, ll n){
    if(m == 1 || n == 1) return 1;
    else return getPath(m-1, n) + getPath(m, n-1);
}


const int m=40;
const int n=50;
long long path[m+1][n+1];

long long computePath(int x, int y)
{
	if(x==1  ||  y==1)
		return 1;
	// 初始化第一行为1，第一列为1
	for(int col=1; col<=y; ++col)
		path[1][col]=1;
	for(int row=1; row<=x; ++row)
		path[row][1]=1;
	
	//if(x<y)
	{
		// 从第1行开始计算
		for(int i=2; i<=x; ++i)
		{
			for(int j=1; j<=y; ++j)
			{
				path[i][j]=path[i-1][j]+path[i][j-1];
			}
		}
	}
	// else
	// {
		//从第1列开始计算
		// for(int col=2; col<=y; ++col)
		// {
			// for(int row=1; row<=x; ++row)
			// {
				// path[row][col]=path[row-1][col]+path[row][col-1];
			// }
		// }
	// }
	return path[x][y];
}

long long solution1(int x, int y)
{
	memset(path, 0, sizeof(path));
	return computePath(x, y);
}

// 转换为计算 C(m-1+n-1, m-1)=(m-1+n-1)! / ( (m-1)! * (n-1)! )
long long solution2(int m, int n)
{
	return zuheshu(m-1+n-1, m-1);
}

// C(a, b) = a! / (b!*(a-b)!)
long long zuheshu(int a, int b)
{
	long long res=1;
	if(b<a-b)
		b=a-b;
	for(int i=1; i<=a-b; i++)
	{
		res =res*(i+b)/i;
	}
	return res;
}

ll fact(ll n){
    if(n == 0) return 1;
    else return n*fact(n-1);
}
ll path1(ll m, ll n){
    return fact(m-1+n-1)/(fact(m-1)*fact(n-1));
}

// ========================================

//int** g_graph=NULL;
const int MAXM=200;
const int MAXN=140;
int g_graph[MAXM][MAXN];

class Point{
public:
	int x, y;
	Point(int x, int y):x(x),y(y){}
	Point& operator=(const Point& rhs)	
	{
		this->x=rhs.x;
		this->y=rhs.y;
		return *this;
	}
};

bool operator==(const Point& a, const Point& b)
{
	return (a.x==b.x  &&  a.y==b.y);
}

bool getPrePoint(const Point& p, std::list<Point>& nextPoint);

// 从(m, n)坐标开始搜索一条路径
// 回溯法。或称递归枚举算法，DFS算法
bool getOnePath(const Point& p, std::stack<Point>& curPath)
{
	printf("in getOnePath<%d,%d>\n", p.x, p.y);
	curPath.push(p);
	if(p.x==1  &&  p.y==1)
	{
		return true;
	}
	std::list<Point> nextPoint;
	if(!getPrePoint(p, nextPoint))
	{
		printf("p<%d,%d> has no nextPoint\n", p.x, p.y);
		curPath.pop();
		return false;
	}
	
	//printf("p<%d,%d> has %d nextPoint\n", p.x, p.y, nextPoint.size());
	for(std::list<Point>::iterator it=nextPoint.begin(); it!=nextPoint.end(); ++it)
	{
		if(getOnePath(*it, curPath))
			return true;
		else
			printf("p<%d,%d> nextPoint<%d,%d> failed\n", p.x, p.y, it->x, it->y);
	}	
	curPath.pop();
	return false;
}

bool getPrePoint(const Point& p, std::list<Point>& nextPoint)
{
	nextPoint.clear();
	if(p.x>1  &&  g_graph[p.x-1][p.y])
		nextPoint.push_back(Point(p.x-1, p.y));
	if(p.y>1  &&  g_graph[p.x][p.y-1])
		nextPoint.push_back(Point(p.x, p.y-1));
	return nextPoint.empty() ?  false : true;
}

// 求(1,1)~(m,n)的棋盘上，一条可行路径
// graph[i][j]表示棋盘(i,j)位置是否可用，1表示可用，0表示不能走
//bool solution3(int m, int n, int graph[m][n])
bool solution3(int m, int n)
{
	Point lastP(m, n);
	//g_graph=graph;
	std::stack<Point> curPath;
	int ret=getOnePath(lastP, curPath);
	if(!ret)
	{
		printf("getOnePath<%d,%d> failed\n", m, n);
		return false;
	}
	printf("get one path ok :");
	while(!curPath.empty())
	{
		printf("<%d,%d> ", curPath.top().x, curPath.top().y);
		curPath.pop();
	}
	printf("\n");
	return true;
}

// ============================================
void printPath(const std::deque<Point>& curPath);

bool getNextPoint(const Point& p, std::queue<Point>& nextPoint)
{
	//std::queue<Point>().swap(nextPoint);
	if(p.x<m)
		nextPoint.push(Point(p.x+1, p.y));
	if(p.y<n  &&  g_graph[p.x][p.y+1])
		nextPoint.push(Point(p.x, p.y+1));
	return nextPoint.empty() ?  false : true;
}

void getAllPath(const Point& curPoint, const Point& targePoint, std::deque<Point>& curPath)
{
	//printf("in getAllPath<%d,%d>\n", curPoint.x, curPoint.y);
	if(curPoint==targePoint)
	{
		curPath.push_back(curPoint);
		printPath(curPath);
		curPath.pop_back();
		return;
	}
	if(g_graph[curPoint.x][curPoint.y]==0)
	{
		//printf("<%d,%d> not valid\n", curPoint.x, curPoint.y);
		return;
	}
	curPath.push_back(curPoint);
	
	std::queue<Point> nextPoint;
	getNextPoint(curPoint, nextPoint);
	//printf("p<%d,%d> has %d nextPoint\n", curPoint.x, curPoint.y, nextPoint.size());
	while(!nextPoint.empty())
	{
		Point np=nextPoint.front();
		nextPoint.pop();
		getAllPath(np, targePoint, curPath);
	}
	curPath.pop_back();
}

void printPath(const std::deque<Point>& curPath)
{
	printf("one path : ");
	for(std::deque<Point>::const_iterator it=curPath.begin(); it!=curPath.end(); ++it)
		printf("<%d,%d> ", it->x, it->y);
	printf("\n");
}


// 从(1, 1)坐标开始搜索所有到达(m, n)的路径
void solution4(int m, int n)
{
	std::deque<Point> curPath;
	getAllPath(Point(1,1), Point(m,n), curPath);
	
}


int main()
{
	{
		printf("%lld, %lld, %lld\n", getPath(2, 3), solution1(2,3), solution2(2,3));
		printf("%lld, %lld, %lld\n", getPath(2, 30), solution1(2,30), solution2(2, 30));
		printf("%lld, %lld, %lld\n", getPath(20, 3), solution1(20,3), solution2(20, 3));
		//printf("%lld, %lld\n", getPath(22, 33), solution1(22,33));
		printf("%lld, %lld\n", solution1(22,33), solution2(22, 33));
		//printf("%lld\n", getPath(22, 33));
	}
	
	{
		int graph[4][6]={1,1,1,1,1,1,
			1,1,1,1,1,1,
			1,1,1,1,1,1,
			1,1,1,1,1,1,
		};
		//g_graph=graph; //error
		//solution3(4,6,graph);
		//solution3(4,6);
	}
	{
		FILE *f=freopen("8.2.in", "r", stdin);
		if(f!=NULL)
		{
			int M, N;
			std::cin>>M>>N;
			// scanf("%d %d", &M, &N);
			printf("M=%d, N=%d\n", M, N);
			for(int i=1; i<=M; ++i)
				for(int j=1; j<=N; ++j)
					std::cin>>g_graph[i][j];
			fclose(stdin);
			
			solution3(M, N);
		}
	}
	
	{
		FILE *f=freopen("8.2.in2", "r", stdin);
		if(f!=NULL)
		{
			int M, N;
			std::cin>>M>>N;
			printf("M=%d, N=%d\n", M, N);
			
			memset(g_graph, 0, sizeof(g_graph));
			for(int i=1; i<=M; ++i)
				for(int j=1; j<=N; ++j)
				{
					std::cin>>g_graph[i][j];
					printf("graph<%d,%d>=%d\n", i, j, g_graph[i][j]);
				}
			fclose(stdin);
			
			solution4(M, N);
		}
		else
			perror("8.2.in2 open error\n");
	}
	return 0;
}