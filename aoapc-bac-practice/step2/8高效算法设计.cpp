//8.1
//最大连续和问题
//枚举
//O(n^3)
void solve()
{
	tot=0;
	best=A[1];//初始最大值
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++)
		{
			int sum=0;
			for(int k=i; k<=j; k++)
			{  sum += A[k]; tot++;  }//tot是加法运算的次数
			if(sum>best)
				best=sum;
		}
}
//优化这个算法。设Si=A1+A2+...+Ai，则Ai+...+Aj=Sj-Si-1。
//直观含义是“连续子序列之和等于两个前缀和之差”。
//有了这个结论，最内层循环就可以省略。
//O(n^2)
void solve()
{
	//先计算S数组，递推，O(n)
	S[0]=0;
	for(int i=1; i<=n; i++)
		S[i]=S[i-1]+A[i];
	//二层循环，省略最内层累加元素和的循环
	for(int j=1; j<=n; j++)
		for(int j=i; j<=n; j++)
			best=max(best, S[j]-S[i-1]);
}
//分治法
//O(nlogn)
int maxsum(int *A, int x, int y)//返回数组在左闭右开区间[x, y)中的最大连续和
{
	int v, L, R, maxs;
	if(y-x == 1)
		return A[x];//只有一个元素，直接返回
	//分治第一步，划分成[x, m)和[m, y)
	int m=x+(y-x)/2;
	//分治第二步，递归求解
	int maxs=max(maxsum(A, x, m), maxsum(A, m, y));

	//分治第三步：合并1，从分界点开始往左的最大连续和L
	v=0;
	L=A[m-1];
	for(int i=m-1; i>=x; i--)
		L=max(L, v += A[i]);
	//分治第三步：合并2，从分界点往右的最大连续和R
	v=0;
	R=A[m];
	for(int i=m; i<y; i++)
		R=max(R, v += A[i]);
	//把子问题的解与L和R比较
	return max(maxs, L+R);
}
//对于最大连续和问题，把O(n^2)算法稍作修改，便可以得到一个O(n)算法：
//当j确定时，S[j]-S[i-1]最大相当于S[i-1]最小，
//因此只需要扫描一次数组，维护“目前遇到过的最小S”即可。
//O(n)
//遍历的时候，找出以当前位置为尾端，以此前的某一点为首端的和最大的子序列，然后更新最大值
void solve()
{
	int max=-INF;
	sum=0;
	recMin=0;
	l=0;
	recL=0, recR=1;
	for(int i=1; i<=n; i++)
	{
		sum += a[i];
		if(sum-recMin>max)
		{
			max=sum-recMin;//更新最大值max，最小和以及最大和的右边界recL和recR
			recL=l;
			recR=i;
		}
		if(sum<recMin)
		{
			recMin=sum;//更新最小和，当前最小和的右边界
			l=i;
		}
	}
	cout<<max<<recL+1<<recR;
}
//另一种O(n)算法，累计求和
void solve()
{
	int maxSum=A[1];
	int thisSum=0;
	int start=0;
	int end=0;
	for(int i=1; i<=n; i++)
	{
		thisSum += A[i];
		if(thisSum<0)//结果至少为0
		{
			thisSum=0;
			start=i+1;
		}
		if(thisSum>maxSum)
		{
			maxSum=thisSum;
			end=i;
		}	
	}
	cout<<start<<end<<maxSum<<endl;
}


//8.2
//归并排序
//对A[x, y)归并排序，T为辅助数组，排序结果暂存在T[x, y)中
void merge_sort(int *A, int x, int y, int *T)
{
	if(y-x>1)
	{
		//划分问题
		int m=x+(y-x)/2;
		int p=x, q=m, i=x;
		//递归求解
		merge_sort(A, x, m, T);
		merge_sort(A, m, y, T);
		//合并问题
		while(p<m  ||  q<y)
		{
			if(q>=y  ||  (p<m  &&  A[p]<=A[q]))
				T[i++]=A[p++];
			else
				T[i++]=A[q++];
		}
		for(i=x; i<y; i++)//从辅助空间复制回A数组
			A[i]=T[i];
	}
}

//逆序对的个数
//n个数求逆序对数
int cnt=0;
int T[maxn];
void solve(int *a, int n)//a[0]-a[n-1]
{
	cnt=0;
	merge_sort(int a, 0, n, T);
	cout<<cnt<<endl;
}
void merge_sort(int *A, int x, int y, int *T)
{
	if(y-x>1)
	{
		int m=x+(y-x)/2;
		merge_sort(A, x, m, T);
		merge_sort(A, m, y, T)
		int p=x, q=m, i=x;
		while(p<m  ||  q<y)
		{
			if(q>y  ||  (p<m  &&  A[p]<=A[q]))
				T[i++]=A[p++];
			else
			{   T[i++]=A[q++];	cnt += m-p;	}
		}
		for(i=x; i<y; i++)
			A[i]=T[i];
	}
}


//快速排序
void QuickSort(ElemType A[], int low, int high)//对A[low...high]进行快速排序
{
	if(low<high)
	{
		//划分问题，将A[low...high]划分为满足条件的两个字表
		int pivotPos=Partion(A, low, high);
		//递归求解，依次对两个字表进行递归排序
		QuickSort(A, low, pivotPos-1);
		QuickSort(A, pivotPos+1, high);
	}
}
int Partition(ElemType A[], int low, int high)
{
	ElemType pivot=A[low];
	while(low<high)
	{
		while(low<high  &&  A[high]>=pivot)  --high;
		A[low]=A[high];
		while(low<high  &&  A[low]<=pivot)   ++low;
		A[high]=A[low];
	}
	A[low]=pivot;
	return low;
}

//快速选择问题
//输入n个整数和一个正整数k(1<=k<=n)，输出这些整数从小到大排序后的第k个
//（例如，k=1就只最小值）。n<=10^7。
ElemType QuickSelect(ElemType A[], int low, int high, int k)//从A[low...high]中选择第k大的数
{
	if(low+k-1<=high)
	{
		int pivotPos=Partition(A, low, high);//第pivotPos-low+1个
		if(pivotPos-low+1 == k)
			return A[pivotPost);
		else if(pivotPos-low+1>k)
			return QuickSelect(A, low, pivotPos-1, k);
		else
			return QuickSelect(A, pivotPost+1, high, low+k-pivotPos-1);
	}
	return NULL;
}
int Partition(ElemType A[], int low, int high)
{
	ElemType pivot=A[low];
	while(low<high)
	{
		while(low<high  &&  A[high]>=pivot)  --high;
		A[low]=A[high];
		while(low<high  &&  A[low]<=pivot)  ++low;
		A[high]=A[low];
	}
	A[low]=pivot;
	return low;
}


//二分查找
//非递归
int bsearch(int *A, int x, int y, int v)//从A[x, y)中查找元素v的位置
{
	int m;
	while(x<y)
	{
		m=x+(y-x)/2;
		if(A[m]==v)
			return m;
		else if(A[m]>v)
			y=m;
		else 
			x=m+1;
	}
	return -1;
}
//二分查找求下界
int lower_bound(int *A, int x, int y, int v)
{
	int m;
	while(x<y)
	{
		m=x+(y-x)/2;
		if(A[m]>=v)
			y=m;
		else
			x=m+1;
	}
	return x;
}
//二分法求上界
int upper_bound(int *A, int x, int y, int v)
{
	int m;
	while(x<y)
	{
		m=x+(y-x)/2;
		if(A[m]<=v)
			x=m+1;
		else
			y=m;
	}
	return x;
}


//8.3
//棋盘覆盖问题
//有一个2^k * 2^k的方格棋盘，恰有一个方格是黑色的，其他为白色。
//你的任务是用包含3个方格的L型牌覆盖所有白色方格。
//黑色方格不能被覆盖，且任意一个白色方格不能同时被两个或更多牌覆盖。
int Board[100][100];//记录棋盘覆盖的L型牌的编码
int amount=0;//L型牌的编号，从1开始

// (tr tc)：棋盘左上角的位置坐标
// (dr dc)：残缺的位置
// size：棋盘大小
void Cover(int tr, int tc, int dr, int dc, int size)//当前棋盘状态
{
	int s, t;
	if(size<2) return ;//递归边界：k=1，即size=2时一块牌就够了
	amount=amount+1;
	t=amount;
	s=size/2;//取棋盘大小一半
	if(dr<tr+s  &&  dc<tc+s)//残缺位置在左上部分
	{
		Cover(tr, tc, dr, dc, s);//递归解决左上部分
		Board[tr+s-1][tc+s]=t;//在中间放一个L型牌
		Board[tr+s][tc+s-1]=t;
		Board[tr+s][tc+s]=t;
		Cover(tr, tc+s, tr+s-1, tc+s, s);//递归解决右上部分
		Cover(tr+s, tc, tr+s, tc+s-1, s);//递归解决左下部分
		Cover(tr+s, tc+s, tr+s, tc+s, s);//递归解决右下部分
	}
	else if(dr<tr+s  &&  dc>=tc+s)//残缺位置在右上部分
	{
		Cover(tr, tc+s, dr, dc, s);
        Board[tr+s-1][tc+s-1]=t;
        Board[tr+s][tc+s-1]=t;
        Board[tr+s][tc+s]=t;
        Cover(tr, tc, tr+s-1, tc+s-1, s);
        Cover(tr+s, tc, tr+s, tc+s-1, s);
        Cover(tr+s, tc+s, tr+s, tc+s, s);
	}
	else if(dr>=tr+s  &&  dc<tc+s)//残缺位置在左下部分
	{
		Cover(tr+s, tc, dr, dc, s);
        Board[tr+s-1][tc+s-1]=t;
        Board[tr+s-1][tc+s]=t;
        Board[tr+s][tc+s]=t;
        Cover(tr, tc, tr+s-1, tc+s-1, s);
        Cover(tr, tc+s, tr+s-1, tc+s, s);
        Cover(tr+s, tc+s, tr+s, tc+s, s);
	}
	else if(dr>=tr+s  &&  dc>=tc+s)//残缺位置在右下部分
	{
		Cover(tr+s, tc+s, dr, dc, s);
		Board[tr+s-1][tc+s-1]=t;
		Board[tr+s-][tc+s]=t;
		Board[tr+s][tc+s-1]=t;
		Cover(tr, tc, tr+s-1, tc+s-1, s);
		Cover(tr, tc+s, tr+s-1, tc+s, s);
		Cover(tr+s, tc, tr+s, tc+s-1, s);
	}
}
void OutputBoard(int size)
{
	int i, j;
	ofstream f;
	F.open("output.dat");
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
			F<<setw(5)<<Board[i][j];
		F<<endl;
	}
	F.close();
}
void main()
{
	int size=1, x, y, i, j, k;
	cin>>k;
	for(i=0; i<k; i++)
		size*=2;
	cout<<"input incomplete pane:"<<endl;
	cin>>x>>y;
	Cover(0, 0, x, y, size);
	OutputBoard(size);
	system("PAUSE");
	return 0;
}

//循环日程表问题
//n=2^k个运动员进行网球循环赛，需要设计比赛日程表。
//每个选手必须与其他n-1个选手各赛一次：每个选手一天只能赛一次：循环赛一共进行n-1天。
//按此要求设计一张比赛日程表，该表有n行和n-1列，第i行第j列为第i个选手第j天遇到的选手。
int Result[maxn][maxn];//比赛日程表，第0行不使用，
//第0列从第1行开始从上到下是1到n，
//从第1行往下的每一行，第i行，每一行从第1列往后，第j列，Result[i][j]表示第i个选手第j天遇到的对手
void solve(int k)//当前比赛日程表大小为2^k
//求从左上角Result[1][0]开始，大小为n=2^k
{
	if(k==1)
	{
		Result[1][0]=1;
		Result[1][1]=2;
		Result[2][0]=2;
		Result[2][1]=1;
		return ;
	}
	int size=1;
	for(int i=0; i<k; i++)
		size *= 2;//size=2^k=n
	//递归求解
	solve(k-1);
	//左下角部分：
	//左上角位置Result[1+2^(k-1) ][0]，大小n/2=size/2
	for(i=1+size/2; i<=size; i++)
		for(int j=0; j<size/2; j++)
		{
			Result[i][j]=Result[i-size/2][j]+size/2;
		}
	//右上角部分：
	//左上角位置Result[1][size/2]，大小n/2=size/2
	for(i=1; i<size/2; i++)
		for(j=size/2; j<size; j++)
		{
			Result[i][j]=Result[i+size/2][j-size/2];
		}
	//右下角部分：
	//左上角位置Result[1+size/2][size/2]，大小n/2=size/2
	for(i=1+size/2; i<=size; i++)
		for(j=size/2; j<size; j++)
		{
			Result[i][j]=Result[i-size/2][j-size/2];
		}
}

//巨人与鬼
//在平面上有n个巨人和n个鬼，没有三者在同一条直线上。
//每个巨人需要选择一个不同的鬼，向其发送质子流消灭它。
//质子流由巨人发射，沿直线行进，遇到鬼后消失。
//由于质子流交叉是很危险的，所有质子流经过的线段不能有交点。
//请设计一种给巨人和鬼配对的方法。
/*typedef struct{
	int x;
	int y;
}Point;
Point hero[maxn];
Point ghost[maxn];*/

int n;
int hero[maxn][4];//4个值，依次表示配对的ghost的下标(初始为-1)，该hero的x，y，与当前起始点（左边最低点）的夹角
int ghost[maxn][4];
void solve()
{
	cin>>n;
	for(int i=0; i<n; i++)
		cin>>hero[i][1]>>hero[i][2];
	for(i=0; i<n; i++)
		cin>>ghost[i][1]>>ghost[i][2];
	match(hero, ghost, n);
	print(hero, ghost, n);
}
void match(int *hero, int *ghost, int n)
{
	int id, type;
	findStart(hero, ghost, n, id, type);//在所有点中寻找最左边最低点，type区分巨人和鬼，id是下标
	computeAngle(id, type, hero, ghost, n);//计算所有角与最左边最低点的夹角
	sortByAngle(hero, ghost, n);
}


//8.4
//哈弗曼编码
//先按照频率把所有字符排序成表P，然后创建一个新结点队列Q，在每次合并两个结点后把新结点放到队列Q中。
//由于后合并的频率和一定比先合并的频率和大，因此Q内的元素是有序的。
//类似有序表的合并过程，每次只需要检查P和Q的首元素即可找到频率最小的元素，时间复杂度为O(n)。
//算上排序，时间复杂度为O(nlogn)。
void solve()
{


}


//8.5
//传说中的车
//行和列是无关的，因此可以把原题分解成两个一维问题。
//在区间[1-n]内选择n个不同的整数，使得第i个整数在闭区间[n1i, n2i]内
#include<algorithm>

//解决一维问题：找一个c，使得a[i]<=c[i]<=b[i] (0<=i<n)
bool solve(int *a, int *b, int *c, int n)
{
	fill(c, c+n, -1);
	for(int col=1; col<=n; col++)
	{
		int rook=-1, minb=n+1;
		for(int i=0; i<n; i++)
			if(c[i]<0  &&  b[i]<minb  &&  col>=a[i])
			{
				rook=i;
				minb=b[i];//??
			}
		if(rook<0  ||  col>minb)
			return false;
		c[rook]=col;
	}
	return true;
}

const int maxn=5000+5;
int n, x1[maxn], y1[maxn], x2[maxn], y2[maxn], x[maxn], y[maxn];

int main()
{
	while(scanf("%d", &n)==1  &&  n)
	{
		for(int i=0; i<n; i++)
			scanf("%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
		if(solve(x1, x2, x, n)  &&  solve(y1, y2, y, n))
			for(int i=0; i<n; i++)
				printf("%d\n", x[i], y[i]);
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}


//Gergovia的酒交易
void solve()
{
	int n;
	while(cin>>n  &&  n)
	{
		long long ans=0, a, last=0;
		for(int i=0; i<n; i++)
		{
			cin>>a;
			ans += abs(last);
			last += a;
		}
		cout<<ans<<endl;
	}
	return 0;
}



//两亲性分子
const int maxn=1000+5;

struct Point{
	int x, y;
	double rad;//关于当前点的极角
	bool operator<(const Point &rhs) const
	{
		return rad<rhs.rad;
	}
}op[maxn], p[maxn];
//op记录原始所有点，p记录按照相对当前基准点的极角由小到大排序的所有其它点

int n, color[maxn];

//从0-A到0-B，是不是偏向左？
//叉积
bool left(Point A, Point B)
{
	return A.x * B.y -A.y * B.x >= 0;
}

int solve()
{
	 if(n<=2)  return 2;
	 int ans=0;

	 //基准点
	 for(int i=0; i<n; i++)
	 {
		 int k=0;

		 //其它点的列表，按照rad增加的顺序排序
		 for(int j=0; j<n; j++)
			 if(j != i)
			 {
				p[k].x=op[j].x - op[i].x;
				p[k].y=op[j].y - op[i].y;
				if(color[j])
				{
					p[k].x= -p[k].x;
					p[k].y= -p[k].y;
				}
				p[k].rad=atan2(p[k].y, p[k].x);
				k++;
			 }
		sort(p, p+k);

		//扫描。cnt是rad在p[L]和p[R]之间的点的数量
		int L=0, R=0, cnt=2;
		while(L<K)
		{
			if(R==L)//空区间
			{
				R = (R+1)%k;
				cnt++;
			}
			//当[L, R]范围超过180度时停止
			while(R!=L  &&  Left(p[L], p[R]))
			{
				R=(R+1)%k;
				cnt++;
			}
			cnt--;
			L++;
			ans=max(ans, cnt);
		}

	 }
	 return ans;
}

void main()
{
	while(scanf("%d", &n)==1  &&  n)
	{
		for(int i=0; i<n; i++)
			scanf("%d%d", &op[i].x, &op[i].y, &color[i]);
		printf("%d\n", solve());
	}
}


//唯一的雪花
//输入一个长度为n（n<=10^6）的序列A，找到一个尽量长的连续子序列AL~AR，使得该序列中没有相同的元素。
//set
const int maxn=1000000+5;
int A[maxn];

void solve()
{
	set<int> s;
	int L=0, R=0, ans=0;
	while(R<n)
	{
		while(R<n  &&  !s.count(A[R]))
			s.insert(A[R++]);
		ans=max(ans, R-L);
		s.erase(A[L++]);
	}
	printf("%d\n", ans);
}
//map
const int maxn=1000000+5;
int A[maxn], last[maxn];
map<int, int> cur;

void solve()
{
	for(int i=0; i<n; i++)
	{
		scanf("%d", &A[i]);
		if(!cur.count(A[i]))
			last[i]=-1;
		else
			last[i]=cur[A[i]];
		cur[A[i]]=i;
	}

	int L=0, R=0, ans=0;
	while(R<n)
	{
		while(R<n  &&  last[R]<L)
			R++;
		ans=max(ans, R-L);
		L++;
	}
	printf("%d\n", ans);
}



//防线
//给一个长度为n（n<=200000）的序列，删除一个连续子序列，
//使得剩下的序列中有一个长度最大的连续递增子序列。
const int maxn=200000+5;
int n, a[maxn], f[maxn], g[maxn];

//二元组( A[j], g(j) )
struct Candidate{
	int a, g;
	Candidate(int a, int g):a(a), g(g){}
	bool operator < (const Candidate& rhs) const{
		return a<rhs.a;
	}
};

//二元组( A[j], g(j) )表示“有保留价值”的东西，
//以A[j]为关键字放在一个STL集合s中：
set<Candidate> s;

int main()
{
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);
	if(n==1)
	{
		printf("1\n");
		continue;
	}

	//g[i]是以A[i]结尾的最长连续递增序列的长度
	g[0]=1;
	for(int i=1; i<n; i++)
		if(a[i-1]<a[i])
			g[i]=g[i-1]+1;
		else
			g[i]=1;

	//f[i]是以A[i]开头的最长连续递增序列的长度
	f[n-1]=1;
	for(int i=n-2; i>=0; i--)
		if(a[i]<a[i+1])
			f[i]=f[i+1]+1;
		else
			f[i]=1;

	s.clear();
	s.insert(Candidate(a[0], g[0]));
	int ans=1;
	for(int i=1; i<n; i++)//更新集合s，更新最长连续递增子序列长度ans
	{
		Candidate c(a[i], g[i]);
		set<Candidate>::iterator it=s.lower_bound(c);//找到第一个>=c的元素（插入位置）
		bool keep=true;
		if(it != s.begin())
		{
			Candidate last=*(--it);//(--it)指向最大的<c的元素（前一个元素）
			int len=f[i]+last.g;
			ans=max(ans, len);
			if(c.g<=last.g)
				keep=false;//如果前一个元素的g[]更大，不保留这一个
		}

		if(keep)//如果保留，再往后遍历，删除所有不再需要保留的元素
		{
			s.erase(c);//如果c.a已经存在，原来的g肯定是<=c.g的，故删除，重新插入
			s.insert(c);
			it=s.find(c);//
			it++;
			while(it!=s.end()  &&  it->a > c.a  &&  it->g<=c.g)
				s.erase(it++);
		}
	}
	printf("%d\n", ans);
	return 0;
}



//平均值
//给定一个长度为n的01串，选一个长度至少为L的连续子串，使得子串中数字的平均值最大。
//如果有多解，子串长度应尽量小；如果仍有多解，起点编号尽量小。
//序列中的字符编号为1-n，因此[1, n]就是完整的字符串。
//1<=n<=100000，1<=L<=1000
const int maxn=100000+5;

int n, L;
char s[maxn];//字符串
int sum[maxn], p[maxn];//i-j的平均值是(sum[j]-sum[i-1])/(j-i+1)
//p是下凸线上的点

//比较 s[x1-x2]的平均值 和 s[x3-x4]的平均值
//也就是直线 P(x1-1)P(x2) 与 直线P(x3-1)P(x4) 的斜率
int compare_average(int x1, int x2, int x3, int x4)
{
	return (sum[x2]-sum[x1-1])*(x4-x3+1) - (sum[x4]-sum[x3-1])/(x2-x1+1);
}

void solve()
{
	scanf("%d%d%s", &n, &L, s+1);//n为字符串长度，L为连续子串最小长度，s是字符串

	//先计算字符串s的前缀和
	sum[0]=0;
	for(int i=1; i<=n; i++)
		sum[i]=sum[i-1]+s[i]-'0';

	int ansL=1, ansR=L;//子串的起点和终点

	//p[i..j]是candidate开始点的序列
	int i=0, j=0;
	//从小到大枚举t，快速找到t'<=t-L，使得Pt'Pt的斜率最大
	for(int t=L; t<=n; t++)
	{
		//删除上凸点
		while(j-i>1  &&  compare_average(p[j-2], t-L, p[j-1], t-L)>=0)
			j--;

		//加入一个新点
		p[j++]=t-L+1;//新candidate

		//更新正切点
		while(j-i>1  &&  compare_average(p[i], t, p[i+1], t)<=0)
			i++;

		//比较和更新答案
		int c=compare_average(p[i], t, ansL, ansR);
		if(c>0  ||  c==0  &&  t-p[i]<ansR-ansL)
		{//c>0，表示新子串的平均值更大
			//c=0时，t-p[i]<ansR-ansL，表示新子串的平均值相同，但是长度更小
			ansL=p[i];
			ansR=t;
		}
	}
	printf("%d %d\n", ansL, ansR);
}
