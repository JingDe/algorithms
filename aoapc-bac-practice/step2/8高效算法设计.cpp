//8.1
//�������������
//ö��
//O(n^3)
void solve()
{
	tot=0;
	best=A[1];//��ʼ���ֵ
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++)
		{
			int sum=0;
			for(int k=i; k<=j; k++)
			{  sum += A[k]; tot++;  }//tot�Ǽӷ�����Ĵ���
			if(sum>best)
				best=sum;
		}
}
//�Ż�����㷨����Si=A1+A2+...+Ai����Ai+...+Aj=Sj-Si-1��
//ֱ�ۺ����ǡ�����������֮�͵�������ǰ׺��֮���
//����������ۣ����ڲ�ѭ���Ϳ���ʡ�ԡ�
//O(n^2)
void solve()
{
	//�ȼ���S���飬���ƣ�O(n)
	S[0]=0;
	for(int i=1; i<=n; i++)
		S[i]=S[i-1]+A[i];
	//����ѭ����ʡ�����ڲ��ۼ�Ԫ�غ͵�ѭ��
	for(int j=1; j<=n; j++)
		for(int j=i; j<=n; j++)
			best=max(best, S[j]-S[i-1]);
}
//���η�
//O(nlogn)
int maxsum(int *A, int x, int y)//��������������ҿ�����[x, y)�е����������
{
	int v, L, R, maxs;
	if(y-x == 1)
		return A[x];//ֻ��һ��Ԫ�أ�ֱ�ӷ���
	//���ε�һ�������ֳ�[x, m)��[m, y)
	int m=x+(y-x)/2;
	//���εڶ������ݹ����
	int maxs=max(maxsum(A, x, m), maxsum(A, m, y));

	//���ε��������ϲ�1���ӷֽ�㿪ʼ��������������L
	v=0;
	L=A[m-1];
	for(int i=m-1; i>=x; i--)
		L=max(L, v += A[i]);
	//���ε��������ϲ�2���ӷֽ�����ҵ����������R
	v=0;
	R=A[m];
	for(int i=m; i<y; i++)
		R=max(R, v += A[i]);
	//��������Ľ���L��R�Ƚ�
	return max(maxs, L+R);
}
//����������������⣬��O(n^2)�㷨�����޸ģ�����Եõ�һ��O(n)�㷨��
//��jȷ��ʱ��S[j]-S[i-1]����൱��S[i-1]��С��
//���ֻ��Ҫɨ��һ�����飬ά����Ŀǰ����������СS�����ɡ�
//O(n)
//������ʱ���ҳ��Ե�ǰλ��Ϊβ�ˣ��Դ�ǰ��ĳһ��Ϊ�׶˵ĺ����������У�Ȼ��������ֵ
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
			max=sum-recMin;//�������ֵmax����С���Լ����͵��ұ߽�recL��recR
			recL=l;
			recR=i;
		}
		if(sum<recMin)
		{
			recMin=sum;//������С�ͣ���ǰ��С�͵��ұ߽�
			l=i;
		}
	}
	cout<<max<<recL+1<<recR;
}
//��һ��O(n)�㷨���ۼ����
void solve()
{
	int maxSum=A[1];
	int thisSum=0;
	int start=0;
	int end=0;
	for(int i=1; i<=n; i++)
	{
		thisSum += A[i];
		if(thisSum<0)//�������Ϊ0
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
//�鲢����
//��A[x, y)�鲢����TΪ�������飬�������ݴ���T[x, y)��
void merge_sort(int *A, int x, int y, int *T)
{
	if(y-x>1)
	{
		//��������
		int m=x+(y-x)/2;
		int p=x, q=m, i=x;
		//�ݹ����
		merge_sort(A, x, m, T);
		merge_sort(A, m, y, T);
		//�ϲ�����
		while(p<m  ||  q<y)
		{
			if(q>=y  ||  (p<m  &&  A[p]<=A[q]))
				T[i++]=A[p++];
			else
				T[i++]=A[q++];
		}
		for(i=x; i<y; i++)//�Ӹ����ռ临�ƻ�A����
			A[i]=T[i];
	}
}

//����Եĸ���
//n�������������
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


//��������
void QuickSort(ElemType A[], int low, int high)//��A[low...high]���п�������
{
	if(low<high)
	{
		//�������⣬��A[low...high]����Ϊ���������������ֱ�
		int pivotPos=Partion(A, low, high);
		//�ݹ���⣬���ζ������ֱ���еݹ�����
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

//����ѡ������
//����n��������һ��������k(1<=k<=n)�������Щ������С���������ĵ�k��
//�����磬k=1��ֻ��Сֵ����n<=10^7��
ElemType QuickSelect(ElemType A[], int low, int high, int k)//��A[low...high]��ѡ���k�����
{
	if(low+k-1<=high)
	{
		int pivotPos=Partition(A, low, high);//��pivotPos-low+1��
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


//���ֲ���
//�ǵݹ�
int bsearch(int *A, int x, int y, int v)//��A[x, y)�в���Ԫ��v��λ��
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
//���ֲ������½�
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
//���ַ����Ͻ�
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
//���̸�������
//��һ��2^k * 2^k�ķ������̣�ǡ��һ�������Ǻ�ɫ�ģ�����Ϊ��ɫ��
//����������ð���3�������L���Ƹ������а�ɫ����
//��ɫ�����ܱ����ǣ�������һ����ɫ������ͬʱ������������Ƹ��ǡ�
int Board[100][100];//��¼���̸��ǵ�L���Ƶı���
int amount=0;//L���Ƶı�ţ���1��ʼ

// (tr tc)���������Ͻǵ�λ������
// (dr dc)����ȱ��λ��
// size�����̴�С
void Cover(int tr, int tc, int dr, int dc, int size)//��ǰ����״̬
{
	int s, t;
	if(size<2) return ;//�ݹ�߽磺k=1����size=2ʱһ���ƾ͹���
	amount=amount+1;
	t=amount;
	s=size/2;//ȡ���̴�Сһ��
	if(dr<tr+s  &&  dc<tc+s)//��ȱλ�������ϲ���
	{
		Cover(tr, tc, dr, dc, s);//�ݹ������ϲ���
		Board[tr+s-1][tc+s]=t;//���м��һ��L����
		Board[tr+s][tc+s-1]=t;
		Board[tr+s][tc+s]=t;
		Cover(tr, tc+s, tr+s-1, tc+s, s);//�ݹ������ϲ���
		Cover(tr+s, tc, tr+s, tc+s-1, s);//�ݹ������²���
		Cover(tr+s, tc+s, tr+s, tc+s, s);//�ݹ������²���
	}
	else if(dr<tr+s  &&  dc>=tc+s)//��ȱλ�������ϲ���
	{
		Cover(tr, tc+s, dr, dc, s);
        Board[tr+s-1][tc+s-1]=t;
        Board[tr+s][tc+s-1]=t;
        Board[tr+s][tc+s]=t;
        Cover(tr, tc, tr+s-1, tc+s-1, s);
        Cover(tr+s, tc, tr+s, tc+s-1, s);
        Cover(tr+s, tc+s, tr+s, tc+s, s);
	}
	else if(dr>=tr+s  &&  dc<tc+s)//��ȱλ�������²���
	{
		Cover(tr+s, tc, dr, dc, s);
        Board[tr+s-1][tc+s-1]=t;
        Board[tr+s-1][tc+s]=t;
        Board[tr+s][tc+s]=t;
        Cover(tr, tc, tr+s-1, tc+s-1, s);
        Cover(tr, tc+s, tr+s-1, tc+s, s);
        Cover(tr+s, tc+s, tr+s, tc+s, s);
	}
	else if(dr>=tr+s  &&  dc>=tc+s)//��ȱλ�������²���
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

//ѭ���ճ̱�����
//n=2^k���˶�Ա��������ѭ��������Ҫ��Ʊ����ճ̱�
//ÿ��ѡ�ֱ���������n-1��ѡ�ָ���һ�Σ�ÿ��ѡ��һ��ֻ����һ�Σ�ѭ����һ������n-1�졣
//����Ҫ�����һ�ű����ճ̱��ñ���n�к�n-1�У���i�е�j��Ϊ��i��ѡ�ֵ�j��������ѡ�֡�
int Result[maxn][maxn];//�����ճ̱���0�в�ʹ�ã�
//��0�дӵ�1�п�ʼ���ϵ�����1��n��
//�ӵ�1�����µ�ÿһ�У���i�У�ÿһ�дӵ�1�����󣬵�j�У�Result[i][j]��ʾ��i��ѡ�ֵ�j�������Ķ���
void solve(int k)//��ǰ�����ճ̱��СΪ2^k
//������Ͻ�Result[1][0]��ʼ����СΪn=2^k
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
	//�ݹ����
	solve(k-1);
	//���½ǲ��֣�
	//���Ͻ�λ��Result[1+2^(k-1) ][0]����Сn/2=size/2
	for(i=1+size/2; i<=size; i++)
		for(int j=0; j<size/2; j++)
		{
			Result[i][j]=Result[i-size/2][j]+size/2;
		}
	//���Ͻǲ��֣�
	//���Ͻ�λ��Result[1][size/2]����Сn/2=size/2
	for(i=1; i<size/2; i++)
		for(j=size/2; j<size; j++)
		{
			Result[i][j]=Result[i+size/2][j-size/2];
		}
	//���½ǲ��֣�
	//���Ͻ�λ��Result[1+size/2][size/2]����Сn/2=size/2
	for(i=1+size/2; i<=size; i++)
		for(j=size/2; j<size; j++)
		{
			Result[i][j]=Result[i-size/2][j-size/2];
		}
}

//�������
//��ƽ������n�����˺�n����û��������ͬһ��ֱ���ϡ�
//ÿ��������Ҫѡ��һ����ͬ�Ĺ����䷢����������������
//�������ɾ��˷��䣬��ֱ���н������������ʧ��
//���������������Ǻ�Σ�յģ������������������߶β����н��㡣
//�����һ�ָ����˺͹���Եķ�����
/*typedef struct{
	int x;
	int y;
}Point;
Point hero[maxn];
Point ghost[maxn];*/

int n;
int hero[maxn][4];//4��ֵ�����α�ʾ��Ե�ghost���±�(��ʼΪ-1)����hero��x��y���뵱ǰ��ʼ�㣨�����͵㣩�ļн�
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
	findStart(hero, ghost, n, id, type);//�����е���Ѱ���������͵㣬type���־��˺͹�id���±�
	computeAngle(id, type, hero, ghost, n);//�������н����������͵�ļн�
	sortByAngle(hero, ghost, n);
}


//8.4
//����������
//�Ȱ���Ƶ�ʰ������ַ�����ɱ�P��Ȼ�󴴽�һ���½�����Q����ÿ�κϲ�����������½��ŵ�����Q�С�
//���ں�ϲ���Ƶ�ʺ�һ�����Ⱥϲ���Ƶ�ʺʹ����Q�ڵ�Ԫ��������ġ�
//���������ĺϲ����̣�ÿ��ֻ��Ҫ���P��Q����Ԫ�ؼ����ҵ�Ƶ����С��Ԫ�أ�ʱ�临�Ӷ�ΪO(n)��
//��������ʱ�临�Ӷ�ΪO(nlogn)��
void solve()
{


}


//8.5
//��˵�еĳ�
//�к������޹صģ���˿��԰�ԭ��ֽ������һά���⡣
//������[1-n]��ѡ��n����ͬ��������ʹ�õ�i�������ڱ�����[n1i, n2i]��
#include<algorithm>

//���һά���⣺��һ��c��ʹ��a[i]<=c[i]<=b[i] (0<=i<n)
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


//Gergovia�ľƽ���
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



//�����Է���
const int maxn=1000+5;

struct Point{
	int x, y;
	double rad;//���ڵ�ǰ��ļ���
	bool operator<(const Point &rhs) const
	{
		return rad<rhs.rad;
	}
}op[maxn], p[maxn];
//op��¼ԭʼ���е㣬p��¼������Ե�ǰ��׼��ļ�����С�������������������

int n, color[maxn];

//��0-A��0-B���ǲ���ƫ����
//���
bool left(Point A, Point B)
{
	return A.x * B.y -A.y * B.x >= 0;
}

int solve()
{
	 if(n<=2)  return 2;
	 int ans=0;

	 //��׼��
	 for(int i=0; i<n; i++)
	 {
		 int k=0;

		 //��������б�����rad���ӵ�˳������
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

		//ɨ�衣cnt��rad��p[L]��p[R]֮��ĵ������
		int L=0, R=0, cnt=2;
		while(L<K)
		{
			if(R==L)//������
			{
				R = (R+1)%k;
				cnt++;
			}
			//��[L, R]��Χ����180��ʱֹͣ
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


//Ψһ��ѩ��
//����һ������Ϊn��n<=10^6��������A���ҵ�һ��������������������AL~AR��ʹ�ø�������û����ͬ��Ԫ�ء�
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



//����
//��һ������Ϊn��n<=200000�������У�ɾ��һ�����������У�
//ʹ��ʣ�µ���������һ�����������������������С�
const int maxn=200000+5;
int n, a[maxn], f[maxn], g[maxn];

//��Ԫ��( A[j], g(j) )
struct Candidate{
	int a, g;
	Candidate(int a, int g):a(a), g(g){}
	bool operator < (const Candidate& rhs) const{
		return a<rhs.a;
	}
};

//��Ԫ��( A[j], g(j) )��ʾ���б�����ֵ���Ķ�����
//��A[j]Ϊ�ؼ��ַ���һ��STL����s�У�
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

	//g[i]����A[i]��β��������������еĳ���
	g[0]=1;
	for(int i=1; i<n; i++)
		if(a[i-1]<a[i])
			g[i]=g[i-1]+1;
		else
			g[i]=1;

	//f[i]����A[i]��ͷ��������������еĳ���
	f[n-1]=1;
	for(int i=n-2; i>=0; i--)
		if(a[i]<a[i+1])
			f[i]=f[i+1]+1;
		else
			f[i]=1;

	s.clear();
	s.insert(Candidate(a[0], g[0]));
	int ans=1;
	for(int i=1; i<n; i++)//���¼���s��������������������г���ans
	{
		Candidate c(a[i], g[i]);
		set<Candidate>::iterator it=s.lower_bound(c);//�ҵ���һ��>=c��Ԫ�أ�����λ�ã�
		bool keep=true;
		if(it != s.begin())
		{
			Candidate last=*(--it);//(--it)ָ������<c��Ԫ�أ�ǰһ��Ԫ�أ�
			int len=f[i]+last.g;
			ans=max(ans, len);
			if(c.g<=last.g)
				keep=false;//���ǰһ��Ԫ�ص�g[]���󣬲�������һ��
		}

		if(keep)//��������������������ɾ�����в�����Ҫ������Ԫ��
		{
			s.erase(c);//���c.a�Ѿ����ڣ�ԭ����g�϶���<=c.g�ģ���ɾ�������²���
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



//ƽ��ֵ
//����һ������Ϊn��01����ѡһ����������ΪL�������Ӵ���ʹ���Ӵ������ֵ�ƽ��ֵ���
//����ж�⣬�Ӵ�����Ӧ����С��������ж�⣬����ž���С��
//�����е��ַ����Ϊ1-n�����[1, n]�����������ַ�����
//1<=n<=100000��1<=L<=1000
const int maxn=100000+5;

int n, L;
char s[maxn];//�ַ���
int sum[maxn], p[maxn];//i-j��ƽ��ֵ��(sum[j]-sum[i-1])/(j-i+1)
//p����͹���ϵĵ�

//�Ƚ� s[x1-x2]��ƽ��ֵ �� s[x3-x4]��ƽ��ֵ
//Ҳ����ֱ�� P(x1-1)P(x2) �� ֱ��P(x3-1)P(x4) ��б��
int compare_average(int x1, int x2, int x3, int x4)
{
	return (sum[x2]-sum[x1-1])*(x4-x3+1) - (sum[x4]-sum[x3-1])/(x2-x1+1);
}

void solve()
{
	scanf("%d%d%s", &n, &L, s+1);//nΪ�ַ������ȣ�LΪ�����Ӵ���С���ȣ�s���ַ���

	//�ȼ����ַ���s��ǰ׺��
	sum[0]=0;
	for(int i=1; i<=n; i++)
		sum[i]=sum[i-1]+s[i]-'0';

	int ansL=1, ansR=L;//�Ӵ��������յ�

	//p[i..j]��candidate��ʼ�������
	int i=0, j=0;
	//��С����ö��t�������ҵ�t'<=t-L��ʹ��Pt'Pt��б�����
	for(int t=L; t<=n; t++)
	{
		//ɾ����͹��
		while(j-i>1  &&  compare_average(p[j-2], t-L, p[j-1], t-L)>=0)
			j--;

		//����һ���µ�
		p[j++]=t-L+1;//��candidate

		//�������е�
		while(j-i>1  &&  compare_average(p[i], t, p[i+1], t)<=0)
			i++;

		//�ȽϺ͸��´�
		int c=compare_average(p[i], t, ansL, ansR);
		if(c>0  ||  c==0  &&  t-p[i]<ansR-ansL)
		{//c>0����ʾ���Ӵ���ƽ��ֵ����
			//c=0ʱ��t-p[i]<ansR-ansL����ʾ���Ӵ���ƽ��ֵ��ͬ�����ǳ��ȸ�С
			ansL=p[i];
			ansR=t;
		}
	}
	printf("%d %d\n", ansL, ansR);
}
