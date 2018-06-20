//数字三角形问题
//方法1：递归计算
int solve(int i, j)
{
	return a[i][j]+(i==n ? 0 : max(solve(i+1, j), solve(i+1, j+1)));
}

//方法2：递推计算
void solve()
{
	int i, j;
	for(j=1; j<=n; j++)
		d[n][j]=a[n][j];
	for(i=n-1; j<=i; j++)
		for(j=1; j<=i; j++)
			d[i][j]=a[i][j]+max(d[i+1][j], d[i+1][j+1]);
}

//方法3：记忆化搜索
memset(d, -1, sizeof(d));
int solve(int i, int j)
{
	if(d[i][j]>=0)
		return d[i][j];
	return d[i][j]=a[i][j]+(i==n ? 0 : max(solve(i+1, j), solve(i+1, j+1)))
}


//嵌套矩形问题
//记忆化搜索
int dp(int i)
{
	int & ans=d[i];
	if(ans>0)
		return ans;
	ans = 1;
	for(int j=1; j<=n; j++)
		if(G[i][j])
			ans=max(ans, dp(j)+1);
	return ans;
}
//输出字典序最小的路径
void print_ans(int i)
{
	printf("%d", i);
	for(int j=1; j<=n; j++)
		if(G[i][j]  &&  d[i]==d[j]+1)
		{
			print_ans(j);
			break;
		}
}


//硬币问题
//最长路问题
memset(d, -1, sizeof(d));
int dp(int s)
{
	int & ans=d[s];
	if(ans!=-1)
		return ans;
	ans = -(1<<30);//表示“无法到达”
	for(int i=-1; i<=n; i++)
		if(s>=V[i])
			ans = max( ans, dp(s-V[i])+1 );
	return ans;
}
//另一种方法：不用特殊值表示还没算过，而用另一个数组vis[i]表示状态i是否被访问过
memset(s, 0, sizeof(s));
int dp(int s)
{
	if(vis[s])
		return d[s];
	vis[s]=1;
	int & ans=d[s];
	ans = -(1<<30);
	for(int i=1; i<=n; i++)
		if(s>=V[i])
			ans=max(ans, dp(s-V[i])+1 );
	return ans;
}
//递推，同时求最长路和最短路
void solve()
{
	minv[0]=maxv[0]=0;
	for(int i=1; i<=S; i++)
	{
		minv[i]=INF;
		maxv[i]=-INF;
	}
	for(int i=1; i<=S; i++)
		for(int j=1; j<=n; j++)
			if(i>=V[j])
			{
				minv[i]=min(minv[i], minv[i-V[j]]+1 );
				maxv[i]=max(maxv[i], maxv[i-V[j]]+1);
			}
	printf("%d %d\n", minv[S], maxv[S]);
}
//输出字典序最小的方案
void print_ans(int *d, int S)
{
	for(int i=1; i<=n; i++)
		if(S>=V[i]  &&  d[S]==d[S-V[i]]+1)
		{
			printf(i);
			print_ans(d, S-V[i]);
			break;
		}
}
print_ans(minv, S);
cout<<endl;
print_ans(maxv, S);


//另一种打印路径的方法：递推时直接用min_coin[S]记录满足min[S]==min[S-V[i]]+1的最小的i，
//则打印路径时可以省去print_ans函数中的循环，并可以方便地把递归改成迭代
//把递推过程改成以下形式
void solve()
{
	min[0]=max[0]=0;
	for(int i=1; i<S; i++)
	{
		min[i]=INF;
		max[i]=-INF;
	}
	for(int i=1; i<=S; i++)
		for(int j=1; j<=n; j++)
			if(i>=V[j])
			{
				if(min[i]>min[i-V[j]]+1)//
				{
					min[i]=min[i-V[j]]+1;
					min_coin[i]=j;
				}
				if(max[i]<max[i-V[j]]+1)//
				{
					max[i]=max[i-V[j]]+1;
					max_coin[i]=j;
				}
			}
}
//判断中用 > 和 < :字典序最小解要求min、max值相同时同时取最小的i值。
//反过来，如果j是从大到小枚举的，就需要用 >= 和 <= 才能求出字典序最小解
void print_ans(int *d, int S)
{
	while(S)
	{
		printf("%d ", d[S]);
		S -= V[d[S]];
	}
}
print_ans(min_coin, S);
print_ans(max_coin, S);



//地铁是线性的，有n个车站，从左到右编号为1-n。有M1辆列车从第1站开始往右开，还有M2辆列车从第n站开始往左开。
//在时刻0，Mario从第1站出发，目的是在时刻T（0<=T<=200）回见车站n的一个间谍。
//输入第一行为n，第二行为T，第三行有n-1个整数t1,t2,...tn-1(1<=ti<=70)，其中ti表示地铁从车站i到i+1的行驶时间。
//第四行为M1（1<=M1<=50）,即从第一站出发向右开的列车数目。第五行包含M1个整数d1,d2...dM1(0<=di<=250, di<di+1),即各列车的出发时间。
//时间是个天然的序。影响决策的只有当前时间和所处的车站。所以可以用d(i, j)表示时刻i，在车站j（1-n），最少还需要等待多长时间。
//边界条件是d(T, n)=0，其他d(T, i)(i不等于n)为正无穷。
//有如下三种决策
//决策1：等一分钟
//决策2：搭乘往右开的列车（如果有）
//决策3：搭乘往左开的列车（如果有）
void solve()
{
	for(int i=1; i<=n-1; i++)
		dp[T][i]=INF;
	dp[T][n]=0;

	for(int  i=T-1; i>=0; i--)
		for(int j=1; j<=n; j++)
		{
			dp[i][j]=dp[i+1][j]+1;//等待一分钟
			if(j<n  &&  has_train[i][j][0]  &&  i+t[j]<=T)
				dp[i][j]=min(dp[i][j], dp[i+t[j]][j+1]);
			if(j>1  &&  has_train[i][j][1]  &&  i+t[j-1]<=T)
				dp[i][j]=min(dp[i][j], dp[i+t[j-1]][j-1]);
		}

	cout<<"Case Number "<<++kase<<": ";
	if(dp[0][1]>INF)
		cout<<"impossible\n";
	else
		cout<<dp[0][1]<<endl;
}


//有n（n<=30）中立方体，每种都有无穷多个。要求选一些立方体摞成一根尽量高的柱子（可以自选哪一条边作为高），
//使得每个立方体的底面长宽分别小于它下方立方体的地面长宽
//分析：只有顶面的尺寸会影响后续决策，因此可以用二元组(a, b)来表示顶面尺寸为a*b这个状态。
//不能直接用d(a, b)表示状态值，因为a和b可能会很大。可以用(idx, k)来间接表示这个状态。idx是顶面立方体的序号，
//k是高的序号。idx是0到n-1的整数，k是0-2的整数。

//dp[idx][k]表示顶面立方体是第idx个立方体且高为第k条边时能达到的最大高度
//先将所有立方体存储为一个DAG矩阵E，求DAG的最长路
//(i, j)输入E，表示i为顶面立方体时，j可以放置在其上面
//dp[x][k]=max{ max{dp[y][0], dp[y][1], dp[y][2]} |  (x, y)属于E }
//结果：dp[][]的最大值
#define REP(i, n) for(int i=0; i<(n); i++)

const int maxn=30+5;
int n, blocks[maxn][3], d[maxn][3];

void get_dimensions(int *v, int b, int dim)
//获得第b个立方体高为第dim边时的顶面长和宽，存于v[0]-v[1]
{
	int idx=0;
	REP(i, 3)
		if(i!=dim)
			v[idx++]=blocks[b][i];
}

int dp(int i, int j)
//顶面为第i个立方体且高为第j边时，能达到的最大高度
{
	int & ans=d[i][j];
	if(ans>0)
		return ans;

	ans=0;
	int v[2], v2[2];
	get_dimensions(v, i, j);//获得此时顶面长和宽
	REP(a, n)
		REP(b, 3)
		{
			get_dimensions(v2, a, b);//获得所有的长和宽
			if(v2[0]<v[0]  &&  v2[1]<v[1])
				ans=max(ans, dp(a,b));
		}
	ans += blocks[i][j];
	return ans;
}

int main()
{
	int kase=0;
	while(scanf("%d", &n)==1  &&  n)
	{
		REP(i, n)
		{
			REP(j, 3)
				scanf("%d", &blocks[i][j]);
			sort(blocks[i], blocks[i]+3);
		}
		memset(d, 0, sizeof(d));
		int ans=0;
		REP(i, n)
			REP(j, 3)
				ans=max(ans, dp(i, j));
		printf("Case %d: maximum height = %d\n", ++kase, ans);
	}
	return 0;
}



//给定平面上n（n<=1000）个点的坐标（按照x递增的顺序给出。各点x坐标不同，且均为正整数），你的任务是设计一条路线，
//从最左边的点出发，走到最右边的点后再返回，要求除了最左点和最右点之外每个点恰好经过一次，且路径总长度最短。
//两点间的长度为它们的欧几里得距离。
//改成：两个人同时从最左点出发，沿着两条不同的路径走，最后都走到最右点，且除了起点和终点外其余每个点恰好被
//一个人经过。可以用d(i, j)表示一个人走到i，第二个人走到j，还需要走多长的距离
//这样无法表示状态转移
//修改为：d(i, j)表示1-max(i, j)全部走过，且两个人的当前位置分别为i和j，还需要走多长的距离。i>j
//d(i, j)状态只能转移到d(i+1, j)和d(i+1, i)
//边界是d(n-1, j)=dist(n-1, n)+dist(j, n)，其中dist(a, b)表示点a和b之间的距离。
//所求结果是dist(1,2)+d(2, 1)
//状态总数是O(n*n)，每个状态的决策只有两个，因此总时间复杂度为O(n*n)

const int maxn=50+5;
double x[maxn], y[maxn], dist[maxn][maxn], d[maxn][maxn];

int main()
{
	int n;
	while(scanf("%d", &n)==1)
	{
		for(int i=1 i<=n; i++)
			scanf("%lf%lf", &x[i], &y[i]);
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				dist[i][j]=sqrt( (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) );
		
		for(int i=n-1; i>=2; i--)
			for(int j=1; j<i; j++)
			{
				if(i==n-1)
					d[i][j]=dist[i][n]+dist[j][n];
				else
					d[i][j]=min(dist[i][i+1]+d[i+1][j] , dist[j][i+1]+d[i+1][i]);
			}
		printf("%.2lf\n", dist[1][2]+d[2][1]);
	}
	return 0;
}


//给一个m行n列（m<=10, n<=100）的整数矩阵，从第一列任何一个位置出发每次往右, 右上或右下走一格，最终到达最后一列。
//要求经过的整数之和最小。整个矩阵是环形的。输出路径上每列的行号。多解时输出字典序最小的。
//每一列就是一个阶段（状态），每个阶段都有3种决策。直行、右上、右下
//多阶段决策的最优化问题往往可以用动态规划解决。状态及其转移类似于回溯法中的解答树。解答树中的“层数”，
//也就是递归函数中的“当前填充位置”cur，描述的是即将完成得决策序号，在动态规划中被称为“阶段”
//状态：设d(i, j)为从格子(i, j)出发到最后一列的最小开销。
//要求字典序最小，需要在计算d(i, j)的同时记录“下一列的行号”的最小值
const int maxn=100+5;
const int INF=1000000000;
int m, n, a[maxn][maxn], d[maxn][maxn], next[maxn][maxn];

int main()
{
	while(scanf("%d%d", &m, &n)==2  &&  m)
	{
		for(int i=0; i<m; i++)
			for(int j=0; j<n; j++)
				scanf("%d", &a[i][j]);

		int ans=INF, first=0;
		for(int j=n-1; j>=0; j--)
		{
			for(int i=0; i<m; i++)
			{
				if(j==n-1)  d[i][j]=a[i][j];
				else
				{
					int rows[3]={i, i-1, i+1};
					if(i==0)  rows[1]=m-1;
					if(i==m-1)  rows[2]=0;
					sort(rows, rows+3);
					d[i][j]=INF;
					for(int k=0; k<3; k++)
					{
						int v=d[rows[k]][j+1] + a[i][j];
						if(v>d[i][j])
						{
							d[i][j]=v;
							next[i][j]=rows[k];
						}
					}
				}
				if(j==0  &&  d[i][j]<ans)
				{  
					ans=d[i][j];
					first=i;
				}
			}
		}

		printf("%d", first+1);
		for(int i=next[first][0], j=1; j<n; i=next[i][j], j++)
			printf("%d", i+1);
		printf("\n%d\n", ans);
	}
	return 0;
}


//物品无限的背包问题：有n中物品，每种均有无穷多个。第i种物品的体积为Vi，重量为Wi。
//选一些物品装到一个容量为C的背包中，使得背包内物品在总体积不超过C的前提下重量尽量大。
//1<=n<=100，1<=Vi<=C<=10000, 1<=Wi<=106。
memset(d, -1, sizeof(d));
int dp(int s)
{
	int &ans=d[s];
	if(ans!=-1)
		return ans;
	ans=-INF;
	for(int i=1; i<=n; i++)
		if(s>=V[i])
			ans=max(ans, dp(s-V[i])+W[i]);
	return ans;
}
//输出字典序最小
void print_ans(int *d, int s)
{
	for(int i=1; i<=n; i++)
		if(s>=V[i]  &&  d[s]==d[s-V[i]]+W[i])
		{
			printf("%d:  %d", i, W[i]);
			print_ans(d, s-V[i]);
			break;
		}
}
print_ans(d, S);


//0-1背包问题：有n中物品，每种只有一个。第i种物品的体积为Vi，重量为Wi。
//选一些物品装到一个容量为C的背包，使得背包内物品在总体积不超过C的前提下重量尽量大。
//1<=n<=100, 1<=Vi<=C<=10000, 1<=Wi<=106。
//用d(i, j)表示当前在第i层，背包剩余容量为j时接下来的最大重量和，
//则 d(i,j)=max{ d(i+1, j), d(i+1, j-V[i])+W[i] }，边界是i>n时d(i, j)=0，j<0时为负无穷
void solve()
{
	for(int i=n+1; i<maxsize; i++)
		for(int j=0; j<=C; j++)
			d[i][j]=0;


	for(int i=n; i>=1; i--)
		for(int j=0; j<=C; j++)
		{
			d[i][j]= (i==n ? 0 : d[i+1][j]);
			if(j>=V[i])
				d[i][j]=max(d[i][j], d[i+1][j-V[i]]+W[i] );
		}
}
//另外一种"对称"的状态定义:用f(i, j)表示“把前i个物品装到容量为j的背包中的最大总重量”，
//其状态转移方程：f(i, j)=max{ f(i-1, j), f(i-1, j-V[i])+W[i] }，
//边界：i=0时为0，j<0时为负无穷，最终答案为f(n, C)。
void solve()
{
	for(int i=1; i<=n; i++)
		for(int j=0; j<=C; j++)
		{
			f[i][j]= (i==1 ? 0 : f[i-1][j]);
			if(j>=V[i])
				f[i][j]=max(f[i][j], f[i-1][j-V[i]]+W[i]);
		}
}
//新的状态定义f(i, j)允许边读入边计算，而不必把V和W保存下来
void solve()
{
	for(int i=1; i<=n; i++)
	{
		scanf("%d%d", &V, &W);
		for(int j=0; j<=C; j++)
		{
			f[i][j]= (i==1 ? 0 : f[i-1][j]);
			if(j>=V)
				f[i][j]=max(f[i][j], f[i-1][j-V]+W);
		}
	}//结果为f[n][C];
}
//滚动数组：还可以把数组f变成一维的
void solve()
{
	memset(f, 0, sizeof(f));
	for(int i=1; i<=n; i++)
	{
		scanf("%d%d", &V, &W);
		for(int j=C; j>=0; j--)
		{
			if(j>=V)
				f[j]=max(f[j], f[j-V]+W);
		}		
	}//结果为f[C]
}


//假定你在唱KTV，还剩t秒时间。你决定接下来只唱你最爱的n首歌，在时间结束之前再唱一个《劲歌金曲》，
//使得唱的总曲目尽量多，在此前提下尽量晚的离开KTV
//输入n(n<=50), t(t<=109)和每首歌的长度，输出唱的总曲目以及时间总长度。
const int maxn=50+5;
const int INF=1000000000

int n, t, len[maxn], d[2][maxn*180+678];//滚动数组

void solve()
{
//	for(int i=1; i<=n; i++)
//		scanf("%d", &len[i]);

	for(int i=0; i<t; i++)
		d[0][i]=-1;
	d[0][0]=0;

	int p=1, ans=0;
	for(int i=1; i<=n; i++)
	{
		for(int j=0; j<t; j++)
		{
			d[p][j]=d[p^1][j];
			if(j>=len[i]  &&  d[p^1][j-len[i]]>=0)
				d[p][j] = max( d[p][j], d[p^1][j-len[i]]+1 );	
			ans=max(ans, d[p][j]);
		}
		p ^= 1;
	}

	for(int i=t-1; i>=0; i--)
	{
		if(d[p^1][i]==ans)
		{
			printf("%d  %d", ans+1, i+689);
			break;
		}
	}
}


//最长上升子序列
//d(i)=max{0, d(j) | j<i, Aj<Ai}+1
//所求结果为max{d(i)}
//临界条件：d(0)=0;
void solve()
{
	int ans=0;
	for(int i=1; i<=n; i++)
	{
		d[i]=0;
		for(int j=1; j<i; j++)
		{
//			if(A[j]<A[i])
//				d[i]=max(d[i], d[j]);
			if(A[j]<A[i]  &&　d[j]>d[i])
			{
				d[i]=d[j];
				before[i]=j;
			}
		}
		d[i]+=1;

		if(d[i]>ans)
		{
			ans=d[i];
			index=i;
		}
	}

	for(int k=0; k<ans; k++, index=before[index])
		printf("%d  ", index);
}
//优化到O(nlogn)
int binary_search(int i){  //从ans[1]到ans[len-1]中查找到下标j，ans[j-1]<arr[i]<ans[j]
    int left,right,mid;  
    left=1,right=len-1;  
    while(left<=right){  
		mid = left+(right-left)/2;  
		if(ans[mid]==arr[i]) return mid;
		else if(ans[mid]>arr[i]) right=mid-1;  
		else left=mid+1;  
    }  
	return left;  
}  
void solve()
{
	ans[1] = arr[1];  
	len=1;  
	for(i=2; i<=p; ++i)
	{  
		if(arr[i]>ans[len])  
			ans[++len]=arr[i];  
		else{  
			int pos=binary_search(i);   // 如果用STL： pos=lower_bound(ans,ans+len,arr[i])-ans;   
			ans[pos] = arr[i];  
        }  
	}
	printf("%d\n",len);  
}


//最长公共子序列
//当A[i]=B[j], d(i, j)=d(i-1, j-1)+1
//否则，d(i, j)=max(d(i-1, j), d(i, j-1))
//所求结果d(n, m)
//临界条件: d[0][j]=0;  d[i][0]=0;
void solve()
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(A[i]==B[j])
				d[i][j]=d[i-1][j-1]+1;
			else
				d[i][j]=max(d[i-1][j], d[i][j-1]);
		}
	}
	printf("%d", d[n][m]);
}


//照明系统设计
const int maxn=1000+5;

struct Lamp{
	int v, k, c, l;//电压   电源   单价   数量
	bool operator < (const Lamp& rhs) const{
		return v<rhs.v;
	}
}lamp[maxn];

int n, s[maxn], d[maxn];

void solve()
{
	sort(lamp+1, lamp+n+1);
	s[0]=0;
	for(int i=1; i<=n; i++)
		s[i]=s[i-1]+lamp[i].l;

	d[0]=0;
	for(int 1; i<=n; i++)
	{
		d[i]=s[i]*lamp[i].c+lamp[i].k;//j=0时
		for(int j=1; j<=i; j++)
		{
			d[i]=min(d[i], d[j]+(s[i]-s[j])*lamp[i].c+lamp[i].k);
		}
	}
	cout<<d[n]<<endl;
}

//划分成回文串
//输入一个由小写字母组成的字符串，你的任务是把它划分成尽量少的回文串。字符串长度不超多1000
//分析：d[i]为字符0-i划分成的最小回文串的个数，则d[i]=min{d[j]+1  |  s[j+1--- i]是回文串}。
//状态O（n），决策O（n），每次转移O（n）
//可以先用O（n*n）时间预处理s[i...j]是否为回文串。
//方法是枚举中心，然后不断向左右延伸并且标记当前子串是回文串，直到延伸的左右字符不同为止。
//每次转移O（1），总时间复杂度O（n*n）
const int maxn=1000+5;
int n, kase, vis[maxn][maxn], p[maxn][maxn], d[maxn];
char s[maxn];

int is_palindrome(int i, int j)
{
	if(i>=j)  return 1;//是回文串
	if(s[i]!=s[j])  return 0;//不是回文串

	if(vis[i][j]==kase)  return p[i][j];
	vis[i][j]=kase;
	p[i][j]=is_palindrome(i+1, j-1);
	return p[i][j];
}

void solve()
{
	memset(vis, 0, sizeof(vis));//访问标志

	n=strlen(s+1);//s[1-n]为输入字符串

	d[0]=0;
	for(int i=1; i<=n; i++)
	{
		d[i]=i+1;//d[i]为s[1-i]划分成的最小回文串的个数
		for(int j=0; j<i; j++)
			if(is_palindrome(j+1, i))//s[j+1]-s[i]是回文串
				d[i]=min(d[i], d[j]+1);
	}
	printf("%d\n", d[n]);
}


//颜色的长度
const int maxn=5000+5;
const int INF=1000000000;

char p[maxn], q[maxn];//两个颜色序列
int sp[26], sq[26], ep[26], eq[26];
//sp、sq分别表示p和q中26个字母的最早出现时间
//ep、eq分别表示p和q中26个字母的最后出现时间
int d[2][maxn], c[2][maxn];

void solve()
{
	int n=strlen(p+1);
	int m=strlen(q+1);
	for(int i=1; i<=n; i++)  p[i] -= 'A';
	for(int i=1; i<=m; i++)  q[i] -= 'A';

	for(int i=0; i<26; i++)
	{
		sp[i]=sq[i]=INF;
		ep[i]=eq[i]=0;
	}
	for(int i=1; i<=n; i++)
	{
		sp[p[i]]=min(sp[p[i]], i);
		ep[p[i]]=i;
	}
	for(int i=1; i<=m; i++)
	{
		sq[q[i]]=min(sq[q[i]], i);
		eq[q[i]]=i;
	}

	int t=0;//d、c为循环数组
	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	//d[t][j]表示两个序列分别移到i和j时，还需要多少费用
	//c[t][j]表示两个序列分别移到i和j时，混合序列中有多少开始没有结束的颜色
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
		{
			if(!i  &&  !j)//i==j==0
				continue;//c[0][0]=d[0][0]=0;

			int v1=INF, v2=INF;
			if(i)  v1=d[t^1][j] + c[t^1][j];//取p中颜色
			if(j)  v2=d[t][j-1] + c[t][j-1];//取q中颜色
			d[t][j] = min(v1, v2);

			//更新c[t][j]
			if(i)
			{
				c[t][j]=c[t^1][j];//取p中颜色
				if(sp[p[i]]==i  &&  sq[p[i]]>j)  c[t][j]++;
				if(ep[p[i]]==i  &&  eq[p[i]]<=j) c[t][j]--;
			}
			else if(j)
			{
				c[t][j]=c[t][j-1];//取q中颜色
				if(sq[q[j]]==j  &&  sp[q[j]]>i)  c[t][j]++;
				if(eq[q[j]]==j  &&  ep[q[j]]<=i) c[t][j]--;
			}
		}
		t ^= 1;
	}
	printf("%d\n", d[t^1][m]);//m=q颜色序列的长度
}

//切木棍
//d(i, j)为切木棍i-j的最优费用，则d(i, j)=min{ d(i,k)+d(i, j)}+a[j]-a[i]
//临界条件d(i, i+1)=0
const int maxn=50+5;
int n, L, a[maxn], vis[maxn][maxn], d[maxn][maxn];

int dp(int i, int j)
{
	if(i>=j-1)  return 0;
	if(vis[i][j])  return d[i][j];
	vis[i][j]=1;

	int &ans=d[i][j];
	ans =-1;//ans<0
	for(int k=i+1; k<=j-1; k++)
	{
		int v=dp(i, k)+dp(k, j)+ a[j]-a[i];
		if(ans<0  ||  v<ans)
			ans=v;
	}
	return ans;
}

void solve()
{
	a[0]=0;
	a[n+1]=L;
	memset(vis, 0, sizeof(vis));
	printf("The minimum cutting is %d.\n", dp(0, n+1));
}

//括号序列
//d(i, j)表示字串S[i...j]至少需要添加几个括号
//决策1，如果S形如(S1)、[S1]，转移到d(S1)
//决策2，如果S至少有两个字符，则可以分成AB，转移到d(A)+d(B)
//当满足第一条时，仍然要尝试第二种转移
//边界条件：d(i+1, i)=0;  d(i, i)=1;
const int maxn=100+5;
char S[maxn];
int n, d[maxn][maxn];

bool match(char a, char b)
{
	return (a=='('  &&  b==')')  ||  (a=='['  &&  b==']');
}
//递推写法
void dp()
{
	for(int i=0;; i<n; i++)
	{
		d[i+1][i]=0;
		d[i][i]=1;
	}

	for(int i=n-2; i>=0; i--)
		for(int j=i+1; j<n; j++)
		{
			d[i][j]=n;
			if(match(S[i], S[j]))
				d[i][j]=min(d[i][j], d[i+1][j-1]);
			for(int k=i; k<j; k++)
				d[i][j]=min(d[i][j], d[i][k]+d[k+1][j]);
		}
}
//记忆化搜索写法
int dp(int i, int j)
{
	if(i>j)  return 0;
	if(i==j)  return 1;
	int &ans=d[i][j];
	if(ans>=0)  return ans;
	ans=n;
	if(match(S[i], S[j]))
		ans=min(ans, dp(i+1, j-1));
	for(int k=i; k<j; k++)
		ans=min(ans, dp(i, k)+dp(k+1, j) );
	return ans;
}

void print(int i, int j)
{
	if(i>j)  return ;
	if(i==j)
	{
		if(S[i]=='('  ||  S[i]==')')  printf("()");
		else printf("[]");
		return ;
	}
	int ans=d[i][j];//记忆化搜索改成：int ans=dp(i, j);
	if(match(S[i], S[j])  &&  ans==d[i+1][j-1])
	{
		printf("%c", S[i]);
		print(i+1, j-1);
		printf("%c", S[j]);
		return ;
	}
	for(int k=i; k<j; k++)
		if(ans==d[i][k]+d[k+1][j])
		{
			print(i, k);
			print(k+1, j);
			return ;
		}
}

void readline(char *S)
{
	fgets(S, maxn, stdin);
}

void main()
{
	readline(S);
	n=strlen(S)-1;
	memset(d, -1, sizeof(d));

	dp();
	print(0, n-1);
	printf("\n");
}


//最大面积最小的三角剖分
//状态：d(i, j)为子多边形i, i+1,...,j的最优解
//状态转移方程d(i, j)=min{S(i,j,k), d(i, k), d(k, j) | i<k<j}
//边界条件
//递推顺序
const double eps=1e-10;
int dcmp(double x)//x接近0时返回0； x为负时返回-1； x为正时返回1
{
	if(fabs(x)<eps)  return 0;
	else return x<0 ? -1 : 1;
}

struct Point{
	double x, y;
	Point(double x=0, double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator + (const Vector &A, const Vector &B)
{
	return Vector(A.x+B.x, A.y+B.y);
}
Vector operator - (const Vector &A, const Vector *B)
{
	return Vector(A.x-B.x, A.y-B.y);
}
Vector operator * (const Vector &A, double p)
{
	return Vector(A.x*p, A.y*p);
}
bool operator < (const Pooint &a, const Point &b)//a<b: a在b左边，或者下面
{
	return a.x<b.x  ||  (a.x==b.x  &&  a.y<b.y)
}
bool operator == (const Point &a, const Point &b)
{
	return dcmp(a.x-b.x)==0  &&  dcmp(a.y-b.y)==0;
}

double Dot(const Vector &A, const Vector &B)//x1*x2 + y1*y2
{
	return A.x*B.x+A.y*B.y;
}
//向量叉积的数字部分
//x1*y2-x2*y1，平行四边形面积
//等于0：O A B共线
//大于0：夹角在0-180度
//小于0：夹角在-180到0度
double Cross(const Vector &A, const Vector &B)
{
	return A.x*B.y-A.y*B.x;
}
double Length(Vector A)// OA 的长度
{
	return sqrt(Dot(A, A));
}

bool SegmentProperIntersection(const Point &a1, const Point &a2,
							   const Point &b1, const Point &b2)
{
	double c1=Cross(a2-a1, b1-a1), 
	double c2=Cross(a2-a1, b2-b1);
	double c3=Cross(b2-b1, a1-b1);
	double c4=Cross(b2-b1, a2-b1);
	return dcmp(c1)*dcmp(c2)<0  &&  dcmp(c3)*dcmp(c4)<0;
}
//p在线段a1-a2
bool OnSegment(const Point &p, const Point &a1, const Point &a2)
	return dcmp(Cross(a1-p, a2-p))==0  &&  dcmp(Dot(a1-p, a2-p))<0;
}

typedef vector<Point> Polygon;

int isPointPolygon(const Point &p, const Polygon &poly)
{
	int n=poly.size();
	int wn=0;
	for(int i=0; i<n; i++)
	{
		const Point &p1=poly[i];
		const Point *p2=poly[(i+1)%n];
		if(p1==p  ||  p2==p  ||  OnSegment(p,p1,p2))
			return -1;//在边界上
		int k=dcmp(Cross(p2-p1, p-p1));
		int d1=dcmp(p1.y-p.y);
		int d2=dcmp(p2.y-p.y);
		if(k>0  &&  d1<=0  &&  d2>0)  wn++;
		if(k<0  &&  d2<=0  &&  d1>0)  wn--;
	}
	if(wn!=0) return 1;//内部
	return 0;//外部
}

const int maxn=100+5;

bool isDiagonal(const Polygon &poly, int a, int b)
{
	int n=poly.size;
	for(int i=0; i<n; i++)
		if(i!=a  &&  i!=b  &&  OnSegment(poly[i], poly[a], poly[b]))
			return false;// 中间不能有其他点
	for(int i=0; i<n; i++)
		if(SegmentProperIntersection(poly[i], poly[(i+1)%n], poly[a], poly[b]))
			return false;// 不能和多边形的边规范相交
	Point midp=(poly[a] + poly[b])*0.5;
	return (isPointInPolygon(midp, poly)==1)// 整条线段在多边形内
}

const double INF=1e9;
double d[maxn][maxn];
//状态：d(i, j)为子多边形i, i+1,...,j的最优解，最小的最大面积
//状态转移方程d(i, j)=min{S(i,j,k), d(i, k), d(k, j) | i<k<j}
double solve(const Polygon &poly)
{
	int n=poly.size;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			d[i][j]=-1;//初始化
	for(int i=n-2; i>=0; i--)
		for(int j=i+1; j<n; j++)
		{
			if(i+1==j)  d[i][j]=0;//临界条件，ij不是对角线时d(i, j)无穷大
			else if(!(i==0  &&  j==n-1)  &&  !isDiagonal(poly, i, j))
				d[i][j]=INF;
			else
			{
				d[i][j]=INF;
				for(int k=i+1; k<j; j++)
				{//d(i, j)=min{S(i,j,k), d(i, k), d(k, j) | i<k<j}
					double m=max(d[i][k], d[k][j]);
					dounle area=fabs(Cross(poly[j]-poly[i], poly[k]-poly[i]));
					m=max(m, area);
					d[i][j]=min(d[i][j], m);
				}
			}
		}
	return d[0][n-1];
}

int main()
{
	scanf("%d", &n);
	Polygon poly;
	for(int i=0; i<n; i++)
	{
		scanf("%lf%lf", &x, &y);
		poly.push_back(Point(x, y));
		printf("%.1lf\n", solve(poly));
	}
}