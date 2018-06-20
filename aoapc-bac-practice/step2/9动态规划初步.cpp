//��������������
//����1���ݹ����
int solve(int i, j)
{
	return a[i][j]+(i==n ? 0 : max(solve(i+1, j), solve(i+1, j+1)));
}

//����2�����Ƽ���
void solve()
{
	int i, j;
	for(j=1; j<=n; j++)
		d[n][j]=a[n][j];
	for(i=n-1; j<=i; j++)
		for(j=1; j<=i; j++)
			d[i][j]=a[i][j]+max(d[i+1][j], d[i+1][j+1]);
}

//����3�����仯����
memset(d, -1, sizeof(d));
int solve(int i, int j)
{
	if(d[i][j]>=0)
		return d[i][j];
	return d[i][j]=a[i][j]+(i==n ? 0 : max(solve(i+1, j), solve(i+1, j+1)))
}


//Ƕ�׾�������
//���仯����
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
//����ֵ�����С��·��
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


//Ӳ������
//�·����
memset(d, -1, sizeof(d));
int dp(int s)
{
	int & ans=d[s];
	if(ans!=-1)
		return ans;
	ans = -(1<<30);//��ʾ���޷����
	for(int i=-1; i<=n; i++)
		if(s>=V[i])
			ans = max( ans, dp(s-V[i])+1 );
	return ans;
}
//��һ�ַ�������������ֵ��ʾ��û�����������һ������vis[i]��ʾ״̬i�Ƿ񱻷��ʹ�
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
//���ƣ�ͬʱ���·�����·
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
//����ֵ�����С�ķ���
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


//��һ�ִ�ӡ·���ķ���������ʱֱ����min_coin[S]��¼����min[S]==min[S-V[i]]+1����С��i��
//���ӡ·��ʱ����ʡȥprint_ans�����е�ѭ���������Է���ذѵݹ�ĳɵ���
//�ѵ��ƹ��̸ĳ�������ʽ
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
//�ж����� > �� < :�ֵ�����С��Ҫ��min��maxֵ��ͬʱͬʱȡ��С��iֵ��
//�����������j�ǴӴ�Сö�ٵģ�����Ҫ�� >= �� <= ��������ֵ�����С��
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



//���������Եģ���n����վ�������ұ��Ϊ1-n����M1���г��ӵ�1վ��ʼ���ҿ�������M2���г��ӵ�nվ��ʼ���󿪡�
//��ʱ��0��Mario�ӵ�1վ������Ŀ������ʱ��T��0<=T<=200���ؼ���վn��һ�������
//�����һ��Ϊn���ڶ���ΪT����������n-1������t1,t2,...tn-1(1<=ti<=70)������ti��ʾ�����ӳ�վi��i+1����ʻʱ�䡣
//������ΪM1��1<=M1<=50��,���ӵ�һվ�������ҿ����г���Ŀ�������а���M1������d1,d2...dM1(0<=di<=250, di<di+1),�����г��ĳ���ʱ�䡣
//ʱ���Ǹ���Ȼ����Ӱ����ߵ�ֻ�е�ǰʱ��������ĳ�վ�����Կ�����d(i, j)��ʾʱ��i���ڳ�վj��1-n�������ٻ���Ҫ�ȴ��೤ʱ�䡣
//�߽�������d(T, n)=0������d(T, i)(i������n)Ϊ�����
//���������־���
//����1����һ����
//����2��������ҿ����г�������У�
//����3��������󿪵��г�������У�
void solve()
{
	for(int i=1; i<=n-1; i++)
		dp[T][i]=INF;
	dp[T][n]=0;

	for(int  i=T-1; i>=0; i--)
		for(int j=1; j<=n; j++)
		{
			dp[i][j]=dp[i+1][j]+1;//�ȴ�һ����
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


//��n��n<=30���������壬ÿ�ֶ�����������Ҫ��ѡһЩ����������һ�������ߵ����ӣ�������ѡ��һ������Ϊ�ߣ���
//ʹ��ÿ��������ĵ��泤��ֱ�С�����·�������ĵ��泤��
//������ֻ�ж���ĳߴ��Ӱ��������ߣ���˿����ö�Ԫ��(a, b)����ʾ����ߴ�Ϊa*b���״̬��
//����ֱ����d(a, b)��ʾ״ֵ̬����Ϊa��b���ܻ�ܴ󡣿�����(idx, k)����ӱ�ʾ���״̬��idx�Ƕ������������ţ�
//k�Ǹߵ���š�idx��0��n-1��������k��0-2��������

//dp[idx][k]��ʾ�����������ǵ�idx���������Ҹ�Ϊ��k����ʱ�ܴﵽ�����߶�
//�Ƚ�����������洢Ϊһ��DAG����E����DAG���·
//(i, j)����E����ʾiΪ����������ʱ��j���Է�����������
//dp[x][k]=max{ max{dp[y][0], dp[y][1], dp[y][2]} |  (x, y)����E }
//�����dp[][]�����ֵ
#define REP(i, n) for(int i=0; i<(n); i++)

const int maxn=30+5;
int n, blocks[maxn][3], d[maxn][3];

void get_dimensions(int *v, int b, int dim)
//��õ�b���������Ϊ��dim��ʱ�Ķ��泤�Ϳ�����v[0]-v[1]
{
	int idx=0;
	REP(i, 3)
		if(i!=dim)
			v[idx++]=blocks[b][i];
}

int dp(int i, int j)
//����Ϊ��i���������Ҹ�Ϊ��j��ʱ���ܴﵽ�����߶�
{
	int & ans=d[i][j];
	if(ans>0)
		return ans;

	ans=0;
	int v[2], v2[2];
	get_dimensions(v, i, j);//��ô�ʱ���泤�Ϳ�
	REP(a, n)
		REP(b, 3)
		{
			get_dimensions(v2, a, b);//������еĳ��Ϳ�
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



//����ƽ����n��n<=1000����������꣨����x������˳�����������x���겻ͬ���Ҿ�Ϊ����������������������һ��·�ߣ�
//������ߵĵ�������ߵ����ұߵĵ���ٷ��أ�Ҫ��������������ҵ�֮��ÿ����ǡ�þ���һ�Σ���·���ܳ�����̡�
//�����ĳ���Ϊ���ǵ�ŷ����þ��롣
//�ĳɣ�������ͬʱ����������������������ͬ��·���ߣ�����ߵ����ҵ㣬�ҳ��������յ�������ÿ����ǡ�ñ�
//һ���˾�����������d(i, j)��ʾһ�����ߵ�i���ڶ������ߵ�j������Ҫ�߶೤�ľ���
//�����޷���ʾ״̬ת��
//�޸�Ϊ��d(i, j)��ʾ1-max(i, j)ȫ���߹����������˵ĵ�ǰλ�÷ֱ�Ϊi��j������Ҫ�߶೤�ľ��롣i>j
//d(i, j)״ֻ̬��ת�Ƶ�d(i+1, j)��d(i+1, i)
//�߽���d(n-1, j)=dist(n-1, n)+dist(j, n)������dist(a, b)��ʾ��a��b֮��ľ��롣
//��������dist(1,2)+d(2, 1)
//״̬������O(n*n)��ÿ��״̬�ľ���ֻ�������������ʱ�临�Ӷ�ΪO(n*n)

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


//��һ��m��n�У�m<=10, n<=100�����������󣬴ӵ�һ���κ�һ��λ�ó���ÿ������, ���ϻ�������һ�����յ������һ�С�
//Ҫ�󾭹�������֮����С�����������ǻ��εġ����·����ÿ�е��кš����ʱ����ֵ�����С�ġ�
//ÿһ�о���һ���׶Σ�״̬����ÿ���׶ζ���3�־��ߡ�ֱ�С����ϡ�����
//��׶ξ��ߵ����Ż��������������ö�̬�滮�����״̬����ת�������ڻ��ݷ��еĽ������������еġ���������
//Ҳ���ǵݹ麯���еġ���ǰ���λ�á�cur���������Ǽ�����ɵþ�����ţ��ڶ�̬�滮�б���Ϊ���׶Ρ�
//״̬����d(i, j)Ϊ�Ӹ���(i, j)���������һ�е���С������
//Ҫ���ֵ�����С����Ҫ�ڼ���d(i, j)��ͬʱ��¼����һ�е��кš�����Сֵ
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


//��Ʒ���޵ı������⣺��n����Ʒ��ÿ�־�������������i����Ʒ�����ΪVi������ΪWi��
//ѡһЩ��Ʒװ��һ������ΪC�ı����У�ʹ�ñ�������Ʒ�������������C��ǰ��������������
//1<=n<=100��1<=Vi<=C<=10000, 1<=Wi<=106��
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
//����ֵ�����С
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


//0-1�������⣺��n����Ʒ��ÿ��ֻ��һ������i����Ʒ�����ΪVi������ΪWi��
//ѡһЩ��Ʒװ��һ������ΪC�ı�����ʹ�ñ�������Ʒ�������������C��ǰ��������������
//1<=n<=100, 1<=Vi<=C<=10000, 1<=Wi<=106��
//��d(i, j)��ʾ��ǰ�ڵ�i�㣬����ʣ������Ϊjʱ����������������ͣ�
//�� d(i,j)=max{ d(i+1, j), d(i+1, j-V[i])+W[i] }���߽���i>nʱd(i, j)=0��j<0ʱΪ������
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
//����һ��"�Գ�"��״̬����:��f(i, j)��ʾ����ǰi����Ʒװ������Ϊj�ı����е��������������
//��״̬ת�Ʒ��̣�f(i, j)=max{ f(i-1, j), f(i-1, j-V[i])+W[i] }��
//�߽磺i=0ʱΪ0��j<0ʱΪ��������մ�Ϊf(n, C)��
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
//�µ�״̬����f(i, j)����߶���߼��㣬�����ذ�V��W��������
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
	}//���Ϊf[n][C];
}
//�������飺�����԰�����f���һά��
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
	}//���Ϊf[C]
}


//�ٶ����ڳ�KTV����ʣt��ʱ�䡣�����������ֻ�������n�׸裬��ʱ�����֮ǰ�ٳ�һ���������������
//ʹ�ó�������Ŀ�����࣬�ڴ�ǰ���¾�������뿪KTV
//����n(n<=50), t(t<=109)��ÿ�׸�ĳ��ȣ������������Ŀ�Լ�ʱ���ܳ��ȡ�
const int maxn=50+5;
const int INF=1000000000

int n, t, len[maxn], d[2][maxn*180+678];//��������

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


//�����������
//d(i)=max{0, d(j) | j<i, Aj<Ai}+1
//������Ϊmax{d(i)}
//�ٽ�������d(0)=0;
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
			if(A[j]<A[i]  &&��d[j]>d[i])
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
//�Ż���O(nlogn)
int binary_search(int i){  //��ans[1]��ans[len-1]�в��ҵ��±�j��ans[j-1]<arr[i]<ans[j]
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
			int pos=binary_search(i);   // �����STL�� pos=lower_bound(ans,ans+len,arr[i])-ans;   
			ans[pos] = arr[i];  
        }  
	}
	printf("%d\n",len);  
}


//�����������
//��A[i]=B[j], d(i, j)=d(i-1, j-1)+1
//����d(i, j)=max(d(i-1, j), d(i, j-1))
//������d(n, m)
//�ٽ�����: d[0][j]=0;  d[i][0]=0;
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


//����ϵͳ���
const int maxn=1000+5;

struct Lamp{
	int v, k, c, l;//��ѹ   ��Դ   ����   ����
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
		d[i]=s[i]*lamp[i].c+lamp[i].k;//j=0ʱ
		for(int j=1; j<=i; j++)
		{
			d[i]=min(d[i], d[j]+(s[i]-s[j])*lamp[i].c+lamp[i].k);
		}
	}
	cout<<d[n]<<endl;
}

//���ֳɻ��Ĵ�
//����һ����Сд��ĸ��ɵ��ַ�������������ǰ������ֳɾ����ٵĻ��Ĵ����ַ������Ȳ�����1000
//������d[i]Ϊ�ַ�0-i���ֳɵ���С���Ĵ��ĸ�������d[i]=min{d[j]+1  |  s[j+1--- i]�ǻ��Ĵ�}��
//״̬O��n��������O��n����ÿ��ת��O��n��
//��������O��n*n��ʱ��Ԥ����s[i...j]�Ƿ�Ϊ���Ĵ���
//������ö�����ģ�Ȼ�󲻶����������첢�ұ�ǵ�ǰ�Ӵ��ǻ��Ĵ���ֱ������������ַ���ͬΪֹ��
//ÿ��ת��O��1������ʱ�临�Ӷ�O��n*n��
const int maxn=1000+5;
int n, kase, vis[maxn][maxn], p[maxn][maxn], d[maxn];
char s[maxn];

int is_palindrome(int i, int j)
{
	if(i>=j)  return 1;//�ǻ��Ĵ�
	if(s[i]!=s[j])  return 0;//���ǻ��Ĵ�

	if(vis[i][j]==kase)  return p[i][j];
	vis[i][j]=kase;
	p[i][j]=is_palindrome(i+1, j-1);
	return p[i][j];
}

void solve()
{
	memset(vis, 0, sizeof(vis));//���ʱ�־

	n=strlen(s+1);//s[1-n]Ϊ�����ַ���

	d[0]=0;
	for(int i=1; i<=n; i++)
	{
		d[i]=i+1;//d[i]Ϊs[1-i]���ֳɵ���С���Ĵ��ĸ���
		for(int j=0; j<i; j++)
			if(is_palindrome(j+1, i))//s[j+1]-s[i]�ǻ��Ĵ�
				d[i]=min(d[i], d[j]+1);
	}
	printf("%d\n", d[n]);
}


//��ɫ�ĳ���
const int maxn=5000+5;
const int INF=1000000000;

char p[maxn], q[maxn];//������ɫ����
int sp[26], sq[26], ep[26], eq[26];
//sp��sq�ֱ��ʾp��q��26����ĸ���������ʱ��
//ep��eq�ֱ��ʾp��q��26����ĸ��������ʱ��
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

	int t=0;//d��cΪѭ������
	memset(c, 0, sizeof(c));
	memset(d, 0, sizeof(d));
	//d[t][j]��ʾ�������зֱ��Ƶ�i��jʱ������Ҫ���ٷ���
	//c[t][j]��ʾ�������зֱ��Ƶ�i��jʱ������������ж��ٿ�ʼû�н�������ɫ
	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=m; j++)
		{
			if(!i  &&  !j)//i==j==0
				continue;//c[0][0]=d[0][0]=0;

			int v1=INF, v2=INF;
			if(i)  v1=d[t^1][j] + c[t^1][j];//ȡp����ɫ
			if(j)  v2=d[t][j-1] + c[t][j-1];//ȡq����ɫ
			d[t][j] = min(v1, v2);

			//����c[t][j]
			if(i)
			{
				c[t][j]=c[t^1][j];//ȡp����ɫ
				if(sp[p[i]]==i  &&  sq[p[i]]>j)  c[t][j]++;
				if(ep[p[i]]==i  &&  eq[p[i]]<=j) c[t][j]--;
			}
			else if(j)
			{
				c[t][j]=c[t][j-1];//ȡq����ɫ
				if(sq[q[j]]==j  &&  sp[q[j]]>i)  c[t][j]++;
				if(eq[q[j]]==j  &&  ep[q[j]]<=i) c[t][j]--;
			}
		}
		t ^= 1;
	}
	printf("%d\n", d[t^1][m]);//m=q��ɫ���еĳ���
}

//��ľ��
//d(i, j)Ϊ��ľ��i-j�����ŷ��ã���d(i, j)=min{ d(i,k)+d(i, j)}+a[j]-a[i]
//�ٽ�����d(i, i+1)=0
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

//��������
//d(i, j)��ʾ�ִ�S[i...j]������Ҫ��Ӽ�������
//����1�����S����(S1)��[S1]��ת�Ƶ�d(S1)
//����2�����S�����������ַ�������Էֳ�AB��ת�Ƶ�d(A)+d(B)
//�������һ��ʱ����ȻҪ���Եڶ���ת��
//�߽�������d(i+1, i)=0;  d(i, i)=1;
const int maxn=100+5;
char S[maxn];
int n, d[maxn][maxn];

bool match(char a, char b)
{
	return (a=='('  &&  b==')')  ||  (a=='['  &&  b==']');
}
//����д��
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
//���仯����д��
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
	int ans=d[i][j];//���仯�����ĳɣ�int ans=dp(i, j);
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


//��������С�������ʷ�
//״̬��d(i, j)Ϊ�Ӷ����i, i+1,...,j�����Ž�
//״̬ת�Ʒ���d(i, j)=min{S(i,j,k), d(i, k), d(k, j) | i<k<j}
//�߽�����
//����˳��
const double eps=1e-10;
int dcmp(double x)//x�ӽ�0ʱ����0�� xΪ��ʱ����-1�� xΪ��ʱ����1
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
bool operator < (const Pooint &a, const Point &b)//a<b: a��b��ߣ���������
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
//������������ֲ���
//x1*y2-x2*y1��ƽ���ı������
//����0��O A B����
//����0���н���0-180��
//С��0���н���-180��0��
double Cross(const Vector &A, const Vector &B)
{
	return A.x*B.y-A.y*B.x;
}
double Length(Vector A)// OA �ĳ���
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
//p���߶�a1-a2
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
			return -1;//�ڱ߽���
		int k=dcmp(Cross(p2-p1, p-p1));
		int d1=dcmp(p1.y-p.y);
		int d2=dcmp(p2.y-p.y);
		if(k>0  &&  d1<=0  &&  d2>0)  wn++;
		if(k<0  &&  d2<=0  &&  d1>0)  wn--;
	}
	if(wn!=0) return 1;//�ڲ�
	return 0;//�ⲿ
}

const int maxn=100+5;

bool isDiagonal(const Polygon &poly, int a, int b)
{
	int n=poly.size;
	for(int i=0; i<n; i++)
		if(i!=a  &&  i!=b  &&  OnSegment(poly[i], poly[a], poly[b]))
			return false;// �м䲻����������
	for(int i=0; i<n; i++)
		if(SegmentProperIntersection(poly[i], poly[(i+1)%n], poly[a], poly[b]))
			return false;// ���ܺͶ���εı߹淶�ཻ
	Point midp=(poly[a] + poly[b])*0.5;
	return (isPointInPolygon(midp, poly)==1)// �����߶��ڶ������
}

const double INF=1e9;
double d[maxn][maxn];
//״̬��d(i, j)Ϊ�Ӷ����i, i+1,...,j�����Ž⣬��С��������
//״̬ת�Ʒ���d(i, j)=min{S(i,j,k), d(i, k), d(k, j) | i<k<j}
double solve(const Polygon &poly)
{
	int n=poly.size;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			d[i][j]=-1;//��ʼ��
	for(int i=n-2; i>=0; i--)
		for(int j=i+1; j<n; j++)
		{
			if(i+1==j)  d[i][j]=0;//�ٽ�������ij���ǶԽ���ʱd(i, j)�����
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