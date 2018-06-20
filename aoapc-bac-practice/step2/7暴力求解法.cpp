//7.1 简单枚举
//除法
//输入正整数n，按从小到大的顺序输出所有形如abcde/fghij=n的表达式，
//其中a-j恰好为数字0-9的一个排列（可以有前导0），2<=n<=79
void solve()
{
	char buf[99];
	int cnt=0;
	for(int fghij=1234; ; fghij++)
	{
		int abcde=fghij * n;
		sprintf(buf, "%05d%05d", abcde, fghij);
		if(strlen(buf)>10) break;
		sort(buf, buf+10);
		bool ok=true;
		for(int i=0; i<10; i++)
			if(buf[i]!='0'+i)
				ok=false;
		if(ok)
		{
			cnt++;
			printf("%05d / %05d = %d\n", abced, fghij, n);
		}
	}
	if(!cnt)
		printf("There are no solutions for %d.\n", n);
}

//最大乘积
//输入n个元素组成的序列S，你需要找出一个乘积最大的连续子序列。
//如果这个最大的乘积不是正数，应输出0（表示无解）。1<=n<=18, -1<=Si<=10
//连续子序列有两个要素：起点和终点，因此只需枚举起点和终点即可。
//由于每个元素的绝对值不超过10且不超过18个元素，最大可能的乘积不会超过1018，可以用long long（64位）存储。
void solve()
{
	int S[20];
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>S[i];

	long long ans=0;
	for(int i=0; i<n; i++)
	{
		long long v=1;
		for(int j=i; j<n; j++)
		{
			v *= S[j];
			if(v>ans)  ans=v;
		}
	}
	cout<<"The maximum product is "<<ans<<"\n";
}

//分数拆分
//输入正整数k，找到所有的正整数x>=y, 使得1/k = 1/x + 1/y
void solve()
{
	int k;
	vector<int> X, Y;
	for(int y=k+1; y<=k*2; y++)
	{
		if(k*y%(y-k))==0
		{
			X.push_back(k*y/(y-k));
			Y.push_back(y);
		}
	}
	printf("%d\n", X.size());
	for(int i=0; i<X.size(); i++)
		printf("1/%d = 1/%d + 1/%d\n", k, X[i], Y[i]);
}

//7.2 枚举排列
//生成1-n的排列
void print_permutation(int n, int *A, int cur)
{
	if(cur==n)
	{
		for(int i=0; i<n; i++)   printf("%d ", A[i]);
		printf("\n");
	}
	else
		for(int i=1; i<=n; i++)
		{
			int ok=1;
			for(int j=0; j<cur; j++)
				if(A[j]==i)
					ok=0;
			if(ok)
			{
				A[cur]=i;
				print_permutation(n, A, cur+1);
			}
		}
}

//生成可重集的排列
//问题改成：输入数组P，并按字典序输出数组A各元素的所有全排列
void print_permutation(int n, int *A, int cur)
{
	if(cur==n)
	{
		for(int i=0; i<n; i++)  printf("%d ", A[i]);
		printf("\n")
	}
	else
		for(int i=0; i<n; i++)
		{
			int c1=0, c2=0;
			for(int j=0; j<cur; j++)  if(A[j]==P[i])  c1++;
			for(j=0; j<cur; j++)  if(P[j]==P[i])  c2++;
			if(c1<c2)
			{
				A[cur]=P[i];
				print_permutation(n, P, A, cur+1);
			}
		}
}

//下一个排列
void solve()
{
	int n, p[10];
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &p[i]);
	sort(p, p+n);
	do{
		for(int i=0; i<n; i++)  printf("%d ", p[i]);
		printf("\n");
	}while(next_permutation(p, p+n));
}


//7.3 子集生成
//增量构造法
//一次选出一个元素放到集合中
void print_subset(int n, int *A, int cur)
{
	for(int i=0; i<cur; i++)
		printf("%d", A[i]);
	printf("\n");
	int s=cur ? A[cur-1]+1 : 0;
	for(int i=s; i<n; i++)
	{
		A[cur]=i;
		print_subset(n, A, cur+1);
	}
}

//位向量法
//构造一个位向量B[i]，而不是直接构造子集A本身，其中B[i]=1，当且仅当i在子集A中
void print_subset(int n, int *B, int cur)
{
	if(cur==n)
	{
		for(int i=0; i<cur; i++)
			if(B[i])
				printf("%d", i);
		printf("\n");
		return ;
	}
	B[cur]=1;
	print_subset(n, B, cur+1);
	B[cur]=0;
	print_subset(n, B, cur+1);
}

//二进制法
//用二进制来表示{0， 1，..., n-1}的子集S：从右往左第i位（各位从0开始编号）表示元素i是否在集合S中
void print_subset(int n, int s)
{
	for(int i=0; i<n; i++)
		if(s&(1<<i))
			printf("%d ", i);
	printf("\n");
}
void solve()
{
	for(int i=0; i<(1<<n); i++)
		print_subset(n, i);
}


//7.4回溯法

//八皇后问题
void search(int cur)
{
	if(cur==n)  tot++;
	else
		for(int i=0; i<n; i++)
		{
			int ok=1;
			C[cur]=1;
			for(int j=0; i<cur; j++)
				if(C[cur]==C[j]  ||  cur-C[cur]==j-C[j]  ||  cur+C[cur]==j+C[j])
				{
					ok=0;
					break;
				}
			if(ok)
				search(cur+1);
		}
}

//利用二维数组vis[3][]直接判断当前尝试的皇后所在的列和两个对角线是否已有其他皇后
void search(int cur)
{
	if(cur==n)  tot++;
	else
		for(int i=0; i<n; i++)
		{
			if(!vis[0][i]  &&  !vis[1][cur+i]  &&  !vis[2][cur-i+n])
			{
				c[cur]=i;
				vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=1;
				search(cur+1);
				vis[0][i]=vis[1][cur+1]=vis[2][cur-i+n]=0;
			}
		}
}

//素数环
//输入正整数n，把整数1,2，...,n组成一个环，使得相邻两个整数之和均为素数。
//输出时从整数1开始逆时针排列。同一个环应恰好输出依次。n<=16
//生成测试法
void solve()
{
	for(int i=2; i<=n*2; i++)
		isp[i]=is_prime(i);
	for(int i=0; i<n; i++)
		A[i]=i+1;
	do{
		int ok=1;
		for(int i=0; i<n; i++)
			if(!isp[A[i]+A[(i+1)%n]])
			{
				ok=0;
				break;
			}

		if(ok)
		{
			for(i=0; i<n; i++)
				printf("%d ", A[i]);
			printf("\n");
		}
	}while(next_permutation(A+1, A+n));
}
//回溯法
void dfs(int cur)
{
	if(cur==n  &&  isp[A[0]+A[n-1]])
	{
		for(int i=0; i<n; i++)
			printf("%d ", A[i]);
		printf("\n");
	}
	else
		for(int i=2; i<=n; i++)
		{
			if(!vis[i]  &&  isp[i+A[cur-1]])
			{
				A[cur]=i;
				vis[i]=1;
				dfs(cur+1);
				vis[i]=0;
			}
		}
}

//困难的串
int cnt=0;
int dfs(int cur)
{
	if(cnt++ == k)
	{
		for(int i=0; i<cur; i++)
			printf("%d ", 'A'+S[i]);
		printf("\n");
		return 0;
	}
	for(int i=0; i<L; i++)
	{
		S[cur]=i;
		int ok=1;
		for(int j=1; j*2<=cur+1; j++)
		{
			int equal=1;
			for(int c=0; c<j; c++)
				if(S[cur-c]!=S[cur-c-j])
				{
					equal=0;
					break;
				}
			if(equal)
			{
				ok=0;
				break;
			}
		}
		if(ok)
			if(!dfs(cur+1))
				return 0;
	}
	return 1;
}

//带宽
//给出一个n个结点的图G和一个结点的排列，
//定义结点i的带宽b(i)为i和相邻结点在排列中的最远距离，
//而所有b(i)的最大值就是整个图的带宽。
//给定图G，求出让带宽最小的结点排列。

//	Sample input
//					A:FB;B:GC;D:GC;F:AGH;E:HD

//	Sample output
//					A B C F G D H E -> 3

const int maxn=10;
int id[256], letter[maxn];

void solve()
{
	char input[1000];
	scanf("%s", input);

	// 计算结点个数n, 并给字母编号letter[0 ... n]
	int n=0;
	for(char ch='A'; ch<='Z'; ch++)//'A'=65, 'Z'=90
		if(strchar(input , ch)!=NULL)
			//查找字符串input中首次出现字符ch的位置
		{
			id[ch]=n++; 
			letter[id[ch]]=ch; 
			// id      为  字母   到 字母序   的映射
			// letter  为  字母序 到 字母     的映射
		}

	//处理输入
	//  u[i]  v[i]对，为相邻边
	//  u v  为  下标 到 字母序 的映射
	int len=strlen(input), p=0, q=0;
	vector<int> u, v;
	while(true)
	{
		while(p<len  &&  input[p]!=':')
			p++;
		if(p==len)
			break;
		while(q<len  &&  input[q]!=';')
			q++;
		for(int i=p+1; i<q; i++)
		{
			u.push_back(id[input[p-1]]);
			v.push_back(id[input[i]]);
		}//  u[i]  v[i]对，为相邻边
		p++;
		q++;
	}

	//枚举全排列
	int P[maxn], bestP[maxn], pos[maxn], ans=n;
	for(int i=0; i<n; i++)
		P[i]=i;// P[0 ... n-1 ]={ 0, ..., n-1}
	do{
		for(int i=0; i<n; i++)
			pos[P[i]]=i;
		// P  为  i（字母序）到P[i]（排列序）  的映射；
		//pos 为  P[i]（排列序）到i（字母序）  的映射
		int bandwidth=0;
		for(i=0;; i<u.size(); i++)
			bandwidth=max(bandwidth, abs(pos[u[i]]-pos[v[i]]) );
		if(bandwidth<ans)
		{
			ans=bandwidth;
			memcpy(bestP, P, sizeof(P));
		}
	}while(next_permutation(P, P+n));

	//输出
	for(int i=0; i<n; i++)
		printf("%c", letter[bestP[i]]);
	printf("-> %d\n", ans);
}


//天平难题
//给出房间的宽度r和s个挂坠的重量wi。设计一个尽量宽（但宽度不能超过房间宽度r）
//的天平，挂着所有挂坠。天平由一些长度为1的木棍组成。
//木棍的每一端要么挂一个挂坠，要么挂另外一个木棍。
//设n和m分别是两端挂的总重量，要么让天平平衡，必须满足n*a=m*b。
//输入：每行数据前两行为房间宽度r和挂坠数目s（0<r<10, 1<=s<=6）
//以下s行每行为一个挂坠的重量Wi(1<=Wi<=1000)。
struct Tree{//二叉树
	double L, R;//L表示左子树的木棍宽度
	Tree():L(0), R(0) {}
};
const int maxn=6;//树高n，叶结点树2^(n-1)，结点数2^n-1

int n, vis[1<<maxn];//n是挂坠个数
double r, w[maxn], sum[1<<maxn];//r为房间宽度，w[i]为挂坠重量，
//sum[i]为以i为顶点的子树的

vector<Tree> tree[1<<maxn];//数组元素是vector<Tree>

//自顶向下构造，每次枚举左子树用到哪个子集，则右子树就是使用剩下的子集。
void dfs(int subset)
{
	if(vis[subset])  return ;
	vis[subset]=true;

	bool have_children=false;
	for(int left=(subset-1)&subset; left; left=(left-1)&subset)
		//for遍历可能的左子树结点
		//规则是？？？
	{
		have_children=true;

		int right=subset^left;
		double d1=sum[right]/sum[subset];//木棍左边长度
		double d2=sum[left]/sum[subset];//木棍右边长度

		dfs(left);
		dfs(right);

		for(int i=0; i<tree[left].size(); i++)
		{
			for(int j=0; j<tree[right].size(); j++)
			{
				Tree t;
				t.L=max(tree[left][i].L+d1, tree[right][j].L-d2);//左子树
				t.R=max(tree[right][j].R+d2, tree[left][i].R-d1);//右子树
				if(t.L+t.R<r)
					tree[subset].push_back(t);
			}
		}
	}//for遍历可能的左子树结点
	if(!have_children)
		tree[subset].push_back(Tree());
}

void main()
{
	scanf("%lf%d", &r, &n);//r是房间宽度，n是挂坠数目
	for(int i=0; i<n; i++)
		scanf("%lf", &w[i]);
	for(int i=0; i<(1<<n); i++)
	{
		sum[i]=0;
		tree[i].clear();
		for(int j=0; j<n; j++)
			if(i  &  (1<<j) )
				sum[i]+=w[j];
	}
	int root=(1<<n)-1;
	memset(vis, 0, sizeof(vis));
	dfs(root);

	double ans=-1;
	for(int i=0; i<tree[root].size(); i++)
		ans=max(ans, tree[root][i].L+tree[root][i].R);
	printf("%.10lf\n", ans);
}


//7.5路径寻找问题
typedef int State[9];//定义“状态”类型：9个int元素的int数组
const int maxstate=1000000;
State st[maxstate], goal;//状态数组。所有状态都保存在这里。goal为目标状态
int dist[maxstate];//距离数组
//如果要打印方案，可以在这里加一个“父亲编号”数组int fa[maxstate]

const int dx[]={-1, 1, 0, 0};
const int dy[]={0, 0, -1, 1};//左，右，下，上

int bfs()//无权图上的最短路问题
{
	init_lookup_table();//初始化查找表:front为初始状态
	int front=1, rear=2;//不使用下标0，因为0被看做“不存在”
	while(front<rear)
	{
		State &s=st[front];//用“引用”简化代码
		if(memcmp(goal, s, sizeof(s))==0)//找到目标状态，成功返回
			return front;

		int z;
		for(z=0; z<9; z++)//栈0的位置
			if(!s[z])
				break;
		int x=z/3, y=z%3;//空格所在行号、列号（0-2）
		for(int d=0; d<4; d++)//四种移法，最多扩展四个新结点
		{
			int newx=x+dx[d];//新行号
			int newy=y+dy[d];//新列号
			int newz=newx*3 + newy;//新编号
			if(newx>=0  &&  newx<3  &&  newy>=0  &&  newy<3)//如果移动合法
			{
				State &t=st[rear];
				memcpy(&t, &s, sizeof(s));//扩展新结点
				t[newz]=s[z];
				t[z]=s[newz];
				dist[rear]=dist[front]+1;//更新新结点的距离值
				if(try_to_insert(rear))//如果成功插入查找表，修改队尾指针
					rear++;
			}
		}
		front++;//扩展完毕后再修改队首指针
	}
	return 0;//失败
}

void main()
{
	for(int i=0; i<9; i++)
		scanf("%d", &st[1][i]);//起始状态
	for(int i=0; i<9; i++)
		scanf("%d", &goal[i]);//目标状态
	int ans=bfs();
	if(ans>0)
		printf("%d\n", dist[ans]);
	else
		printf("-1\n");
}

//第1种方法是：把排列“变成”整数，然后只开一个一维数组。
//也就是说，设计一套排列的编码和解码函数，把0-8的全排列和0-362879的整数一一对应起来。
int vis[362880], fact[9];
void init_lookup_table()
{
	fact[0]=1;
	for(int i=1; i<9; i++)
		fact[i]=fact[i-1]*i;
}
int try_to_insert(int s)
{
	int code=0;//把st[s]映射到整数code
	for(int i=0; i<9; i++)
	{
		int cnt=0;
		for(int j=i+1; j<9; j++)
			if(st[s][j]<st[s][i])
				cnt++;
		code+=fact[8-i] * cnt;
	}
	if(vis[code])
		return 0;
	return vis[code]=1;
}

//第2种方法是使用哈希技术。把结点“变成”整数，但不必是一一对应。
const int hashsize=1000003;
int head[hashsize], next[maxstate];
void init_lookup_table()
{
	memset(head, 0, sizeof(head));
}
int hash(State &s)
{
	int v=0;
	for(int i=0; i<9; i++)
		v=v*10+s[i];
	return v%hashsize;
}
int try_to_insert(int s)
{
	int h=hash(st[s]);
	int u=head[h];
	while(u)
	{
		if(memcmp(st[u], st[s], sizeof(st[s]))==0)
			return 0;
		u=next[u];
	}
	next[s]=head[h];
	head[h]=s;
	return 1;
}

//第3种方法是用STL集合t。把状态转化成9位十进制整数，就可以用set<int>判重了
set<int> vis;
void init_lookup_table()
{
	vis.clear();
}
int try_to_insert(int s)
{
	int v=0;
	for(int i=0; i<9; i++)
		v=v*10+st[s][i];
	if(vis.count(v))
		return 0;
	vis.insert(v);
	return 1;
}


//倒水问题
//解决一般性的问题：设3个杯子的容量分别为a,b,c,最初只有第3个杯子装满了c升水，其他两个杯子为空。
//最少需要倒多少升水才能让某一个杯子中的水有d升呢？
//如果无法做到恰好d升，就让某一个杯子里的水是d'升，其中d'<d并且尽量接近d。
//（1<=a,b,c,d<=200）。
//要求输出最少的倒水量和目标水量（d或者d'）
struct Node{
	int v[3], dist;//当前系统状态：3个杯子的水量。dist为到达该状态的倒水量。
	bool operator < (const Node & rhs) const
	{
		return dist > rhs.dist;
	}
};

const int maxn=200+5;
int vis[maxn][maxn], cap[3], ans[maxn];//vis是访问标记。
//cap是三个杯子的容量。
//ans是记录到达相应下标水量所需要的倒水量

void update_ans(const Node & u)//更新到达相应水量所需要的倒水量
{
	for(int i=0; i<3; i++)
	{
		int d=u.v[i];//结点u状态下的3个杯子的水量
		if(ans[d]<0  ||  u.dist<ans[d])
			ans[d]=u.dist;
	}
}

void solve(int a, int b, int c, int d)
{
	cap[0]=a; cap[1]=b; cap[2]=c;//cap数组表示三个杯子的容量
	memset(vis, 0, sizeof(vis));//初始化访问标志数组为0
	memset(vis, -1, sizeof(ans));//初始化倒水量数组为-1
	priority_queue<Node> q;//优先队列，每次取出倒水量最少的结点进行扩展

	Node start;
	start.dist=0;
	start.v[0]=0; start.v[1]=0;	start.v[2]=c;
	q.push(start);

	vis[0][0]=1;
	while(!q.empty())//每次取出倒水量最少的结点进行扩展，直到出现目标水量d
	{
		Node u=q.top(); q.pop();
		update_ans(u);//更新倒水量
		if(ans[d]>=0)//获得目标水量，停止扩展
			break;
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				if(i!=j)//遍历所有可能的倒水方案
				{
					if(u.v[i]==0  ||  u.v[j]==cap[j]) continue;
					int amount=min(cap[j], u.v[i]+u.v[j])-u.v[j];//倒水量。如果倒水，一定倒满j杯，或者倒光i杯的水
					Node u2;//扩展新结点
					memcpy(&u2, &u, sizeof(u));
					u2.dist=u.dist+amount;//更新到达新结点的倒水量
					u2.v[i] -= amount;
					u2.v[j] += amount;
					if(!vis[u2.v[0]][u2.v[1]])//如果新结点未访问过，则置访问标志，并插入优先队列
					{
						vis[u2.v[0]][u2.v[1]]=1;
						q.push(u2);
					}
				}
	}
	while(d>=0)//打印最接近d的结果：倒水量和目标水量
	{
		if(ans[d]>=0)
		{
			printf("%d %d\n", ans[d], d);
			return ;
		}
		d--;
	}
}

int main()
{
	int T, a, b, c, d;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		solve(a, b, c, d);
	}
	return 0;
}


//万圣节后的早晨
//w*h（w, h<=16）网格上有n（n<=3）个小写字母（代表鬼）。
//要求把它们分别移动到对应的大写字母里。
//每步可以有多个鬼同时移动（均为往上下左右4个方向之一移动），
//但每步结束之后任何两个鬼不能占用同一个位置，也不能在一步之内交换位置。
//输入保证所有空格连通，所有障碍格也连通，且任何一个2*2子网格中至少有一个障碍格。
//输出最少的步数。输入保证有解。
//
//以当前3个小写字母的位置为状态，则问题转化为图上的最短路问题。
//状态总数为256^3，每次转移时需要5^3枚举每一个小写字母下一步的走法（上下左右加上“不动”）。
//状态数很大，转移代价又比较高，很容易超时，需要优化。
//首先优化转移代价。条件“何一个2*2子网格中至少有一个障碍格”
//暗示着很多格子都是障碍，并且大部分空地都和障碍相邻，
//因此不是所有4个方向都能移动，因此可以把所有空格提出来建立一张图，
//而不是每次临时判断5种方案是否合法。
//加入这个优化以后BFS就可以通过本题的数据了。

const int maxs=20;
const int maxn=150;//14*14*0.75+2个位置
const int dx[]={1, -1, 0, 0, 0};//右、左、上、下、不动
const int dy[]={0, 0, 1, -1, 0};

inline int ID(int a, int b, int c)//将当前三个鬼的位置a,b,c转化为整数ID作为标识
{
	return (a<<16) | (b<<8) |  c;
}

int s[3], t[3];//每一个鬼的开始和结束位置

int deg[maxn], G[maxn][5];
	//deg[i]表示i位置有deg[i]（不超过5）个可行的移动位置
	//G[i][j]分别表示i位置的第j个移动位置

inline bool conflict(int a, int b, int a2, int b2)
{
	return a2==b2  ||  (a2==b  &&  b2==a);
}

int d[maxn][maxn][maxn];//从开始位置到i, j, k位置的步数为d[i][j][k]

int bfs()
{
	queue<int> q;//结点队列：用int型表示三个鬼的当前位置
	memset(d, -1, sizeof(d));//初始化步数为-1
	q.push(ID(s[0], s[1], s[2]));//开始结点进入队列
	d[s[0]][s[1]][s[2]]=0;//开始步数为0
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		int a=(u>>16) & 0xff, b=(u>>8) & 0xff, c=u & 0xff;//获得当前结点的三个鬼的位置a,b,c
		if(a==t[0]  &&  b==t[1]  &&  c==t[2])//若已到达目的位置，停止扩展，返回步数
			return d[a][b][c];

		//扩展当前结点u
		for(int i=0; i<deg[a]; i++)
		{
			int a2=G[a][i];//当前u结点时遍历鬼a的移动位置
			for(int j=0; j<deg[b]; j++)
			{
				int b2=G[b][j];//当前u结点时遍历鬼b的移动位置
				if(conflict(a, b, a2, b2))   continue;
				for(int k=0; k<deg[c]; k++)
				{
					int c2=G[c][k];//当前u结点时遍历鬼c的移动位置
					if(conflict(a, c, a2, c2))  continue;
					if(conflict(b, c, b2, c2))  continue;
					if(d[a2][b2][c2] != -1)  continue;//该位置已存在
					d[a2][b2][c2]=d[a][b][c]+1;//更新该位置的步数，增1
					q.push(ID(a2, b2, c2));//插入该位置到队列中
				}
			}
		}

	}//while
	return -1;
}

void main()
{
	int w, h, n;
	while(scanf("%d%d%d\n", &w, &h, &n)==3  &&  n)
	{
		//读取网格存入maze[20][20]数组
		char maze[20][20];
		for(int i=0; i<h; i++)
			fget(maze[i], 20, stdin);

		//提取所有空格：
		//数目存于cnt，坐标存于x[]和y[]，
		//坐标x,y的编号存于id[x][y]
		int cnt, x[maxn], y[maxn], id[maxs][maxs];
			//cnt是空格数目
			//x[i]是空格的x；y[i]是空格的y
			//id[i][j]是(x,y)空格位置在所有空格中的编号
		cnt=0;
		for(int i=0; i<h; i++)
			for(int j=0; j<w; j++)
				if(maze[i][j]!='#')
				{
					x[cnt]=i; y[cnt]=j; id[i][j]=cnt;
					if(islower(maze[i][j]))
						s[maze[i][i]-'a']=cnt;
					else if(isupper(maze[i][j]))
						t[maze[i][j]-'A']=cnt;
					cnt++;
				}

		//把所有空格提出来建立一张表
		for(int i=0; i<cnt; i++)
		{
			deg[i]=0;
			for(int dir=0; dir<5; dir++)
			{
				int nx=x[i]+dx[dir], ny=y[i]+dy[dir];
				//最外面的位置是障碍格，因此不需考虑边界
				if(maze[nx][ny]!='#')
					G[i][deg[i]++]=id[nx][ny];
			}
		}

		//增加假结点，使得任何时候都有3个鬼，使代码更简短
		if(n<=2)//增加第3个鬼
		{
			deg[cnt]=1;//第3个鬼只有一个移动位置
			G[cnt][0]=cnt;//即“不动”
			s[2]=t[2]=cnt++;//第3个鬼的开始位置和结束位置都为cnt
		}
		if(n<=1)//增加第2个鬼
		{
			deg[cnt]=1;
			G[cnt][0]=cnt;
			s[1]=t[1]=cnt++;
		}
		printf("%d\n", bfs());//打印结果步数
	}
}


//埃及分数问题
//使用单位分数的和（即1/a，a是自然数）表示一切有理数。加数中不允许有相同的。
//对于一个分数a/b，表示方法有很多种，其中加数少的比加数多的好，如果加数个数相同，则最小的分数越大越好。
//输入整数a,b(0<a<b<500)，试编程计算最佳表达式。
int a, b, maxd;//a,b为输入整数，有理数a/b，maxd为最大上限
typedef long long LL;
LL gcd(LL a, LL b)//求a，b的最大公约数
{
	return b==0 ?  a :  gcd(b, a%b);
}

//求满足1/c <= a/b的最小的c ,即 c>=b/a
inline int get_first(LL a, LL b)
{
	return b/a+1;
}

const int maxn=100+5;//

LL v[maxn], ans[maxn];//v[]为当前解，ans[]为最优解

//如果当前解v比目前最优解ans更优，更新ans
//加数少的比加数多的好；前者：从小到大枚举深度上限maxd
//如果加数个数相同，则最小的分数越大越好。后者：better(d)
bool better(int d)
{
	for(int i=d; i>=0; i--)//从最小的分数开始比较
		if(v[i]!=ans[i])
		{
			return ans[i]==-1  ||  v[i]<ans[i];
		}
	return false;
}

//当前深度为d，分母不能小于from，分数之和恰好为aa/bb
//从分母最小、单位分数最大开始扩展
bool dfs(int d, int from, LL aa, LL bb)
{
	if(d==maxd)//已到达深度上限
	{
		if(bb % aa)// aa/bb必须是单位分数（最后一个）
			return false;
		v[d]=bb/aa;//最后一个、第d个单位分数的分母
		if(better(d))//如果当前解v比目前最优解ans更优，更新ans
			memcpy(ans, v, sizeof(LL)*(d+1));
		return true;  
	}

	bool ok=false;
	from=max(from, get_first(aa, bb));//枚举的起点
	for(int i=from; ; i++)
	{
		//剪枝：如果剩下的maxd+1-d个分数全部是1/i，加起来仍然不超过aa/bb，则无解
		if(bb*(maxd+1-d)<=i*aa)  break;
		v[d]=i;
		//计算aa/bb-1/i，设结果为a2/b2
		LL b2=bb*i;
		LL a2=aa*i-bb;
		LL g=gcd(a2, b2);//约分
		if(dfs(d+1, i+1, a2/g, b2/g))
			ok=true;
	}
	return ok;
}

void main()
{
	cin>>a>>b;
	int ok=0;
	for(maxd=1; maxd<=100; maxd++)
	{
		memset(ans, -1, sizeof(ans));
		if(dfs(0, get_first(a, b), a, b))
		{
			ok=1; break;
		}
	}
	if(ok)
	{
		cout<<a<<"/"<<b<<"=";
		for(int i=0; i<maxd; i++)
			cout<<"1/"<<ans[i]<<"+";
		cout<<"1/"<<ans[maxd]<<endl;
	}
	else
		cout<<"No solution.\n";
}

//编辑书稿
//有一篇由n（2<=n<=9）个自然段组成的文章，希望将它们排列成1,2,...,n。
//可以用剪切和粘贴快捷键来完成任务。每次可以剪切一段连续的自然段，
//粘贴时按照顺序粘贴。剪贴板只有一个，所以不能连续剪切两次，只能剪切和粘贴交替。
const int maxn=9;
int n, a[maxn];//n为实际自然段数目；a数组为当前排列

bool is_sorted()//判断a数组(当前排列)是否排好序
{
	for(int i=0; i<n-1; i++)
		if(a[i]>=a[i+1])
			return false;
	return true;
}

int h()//统计后继不正确的数字个数
{
	int cnt=0;
	for(int i=0; i<n-1; i++)
		if(a[i]+1 != a[i+1])
			cnt++;
	if(a[n-1] != n)//注意？
		cnt++;
	return cnt;
}

//深度优先搜索
bool dfs(int d, int maxd)//d为当前深度；maxd为深度上限
{
	if(d*3+h()>maxd*3)//函数h()统计后继不正确的数字个数
		return false;//剪枝
	if(is_sorted())
		return true;//已排好序，成功返回

	int b[maxn], olda[maxn];
	memcpy(olda, a, sizeof(a));//将a数组保存到olda数组中

	for(int i=0; i<n; i++)// 枚举a[i...j]
		for(int j=i; j<n; j++)
		{
			//剪切掉a[i..j]，得到剩下的b数组
			int cnt=0;
			for(int k=0; k<n; k++)
				if(k<i  ||  k>j)
					b[cnt++]=a[k];

			//粘贴在k之前
			for(int k=0; k<=cnt; k++)
			{
				int cnt2=0;
				for(int p=0; p<k; p++)
					a[cnt2++]=b[p];
				for(int p=i; p<=j; p++)
					a[cnt2++]=olda[p];
				for(int p=k; p<cnt; p++)
					a[cnt2++]b[p];

				if(dfs(d+1, maxd))  return true;
				memcpy(a, olda, sizeof(a));//回溯，恢复a数组
			}
		}
	return false;
}

int solve()
{
	if(is_sorted())
		return 0;
	int max_ans=5;//对n<=9，答案ans<=5
	for(int maxd=1; maxd<max_ans; maxd++)
		if(dfs(0, maxd))//当前深度为0，深度上限为maxd
			return maxd;//返回当前深度上限maxd
	return max_ans;//返回5
}

int main()
{
	int kase=0;
	while(scanf("%d", &n)==1  &&  n)
	{
		for(int i=0; i<n; i++)
			scanf("%d", &a[i]);
		printf("Case %d: %d\n", ++kase, solve());
	}
	return 0;
}