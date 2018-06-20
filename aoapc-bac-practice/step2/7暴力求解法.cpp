//7.1 ��ö��
//����
//����������n������С�����˳�������������abcde/fghij=n�ı��ʽ��
//����a-jǡ��Ϊ����0-9��һ�����У�������ǰ��0����2<=n<=79
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

//���˻�
//����n��Ԫ����ɵ�����S������Ҫ�ҳ�һ���˻��������������С�
//���������ĳ˻�����������Ӧ���0����ʾ�޽⣩��1<=n<=18, -1<=Si<=10
//����������������Ҫ�أ������յ㣬���ֻ��ö�������յ㼴�ɡ�
//����ÿ��Ԫ�صľ���ֵ������10�Ҳ�����18��Ԫ�أ������ܵĳ˻����ᳬ��1018��������long long��64λ���洢��
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

//�������
//����������k���ҵ����е�������x>=y, ʹ��1/k = 1/x + 1/y
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

//7.2 ö������
//����1-n������
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

//���ɿ��ؼ�������
//����ĳɣ���������P�������ֵ����������A��Ԫ�ص�����ȫ����
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

//��һ������
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


//7.3 �Ӽ�����
//�������취
//һ��ѡ��һ��Ԫ�طŵ�������
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

//λ������
//����һ��λ����B[i]��������ֱ�ӹ����Ӽ�A��������B[i]=1�����ҽ���i���Ӽ�A��
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

//�����Ʒ�
//�ö���������ʾ{0�� 1��..., n-1}���Ӽ�S�����������iλ����λ��0��ʼ��ţ���ʾԪ��i�Ƿ��ڼ���S��
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


//7.4���ݷ�

//�˻ʺ�����
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

//���ö�ά����vis[3][]ֱ���жϵ�ǰ���ԵĻʺ����ڵ��к������Խ����Ƿ����������ʺ�
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

//������
//����������n��������1,2��...,n���һ������ʹ��������������֮�;�Ϊ������
//���ʱ������1��ʼ��ʱ�����С�ͬһ����Ӧǡ��������Ρ�n<=16
//���ɲ��Է�
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
//���ݷ�
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

//���ѵĴ�
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

//����
//����һ��n������ͼG��һ���������У�
//������i�Ĵ���b(i)Ϊi�����ڽ���������е���Զ���룬
//������b(i)�����ֵ��������ͼ�Ĵ���
//����ͼG������ô�����С�Ľ�����С�

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

	// ���������n, ������ĸ���letter[0 ... n]
	int n=0;
	for(char ch='A'; ch<='Z'; ch++)//'A'=65, 'Z'=90
		if(strchar(input , ch)!=NULL)
			//�����ַ���input���״γ����ַ�ch��λ��
		{
			id[ch]=n++; 
			letter[id[ch]]=ch; 
			// id      Ϊ  ��ĸ   �� ��ĸ��   ��ӳ��
			// letter  Ϊ  ��ĸ�� �� ��ĸ     ��ӳ��
		}

	//��������
	//  u[i]  v[i]�ԣ�Ϊ���ڱ�
	//  u v  Ϊ  �±� �� ��ĸ�� ��ӳ��
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
		}//  u[i]  v[i]�ԣ�Ϊ���ڱ�
		p++;
		q++;
	}

	//ö��ȫ����
	int P[maxn], bestP[maxn], pos[maxn], ans=n;
	for(int i=0; i<n; i++)
		P[i]=i;// P[0 ... n-1 ]={ 0, ..., n-1}
	do{
		for(int i=0; i<n; i++)
			pos[P[i]]=i;
		// P  Ϊ  i����ĸ�򣩵�P[i]��������  ��ӳ�䣻
		//pos Ϊ  P[i]�������򣩵�i����ĸ��  ��ӳ��
		int bandwidth=0;
		for(i=0;; i<u.size(); i++)
			bandwidth=max(bandwidth, abs(pos[u[i]]-pos[v[i]]) );
		if(bandwidth<ans)
		{
			ans=bandwidth;
			memcpy(bestP, P, sizeof(P));
		}
	}while(next_permutation(P, P+n));

	//���
	for(int i=0; i<n; i++)
		printf("%c", letter[bestP[i]]);
	printf("-> %d\n", ans);
}


//��ƽ����
//��������Ŀ��r��s����׹������wi�����һ������������Ȳ��ܳ���������r��
//����ƽ���������й�׹����ƽ��һЩ����Ϊ1��ľ����ɡ�
//ľ����ÿһ��Ҫô��һ����׹��Ҫô������һ��ľ����
//��n��m�ֱ������˹ҵ���������Ҫô����ƽƽ�⣬��������n*a=m*b��
//���룺ÿ������ǰ����Ϊ������r�͹�׹��Ŀs��0<r<10, 1<=s<=6��
//����s��ÿ��Ϊһ����׹������Wi(1<=Wi<=1000)��
struct Tree{//������
	double L, R;//L��ʾ��������ľ�����
	Tree():L(0), R(0) {}
};
const int maxn=6;//����n��Ҷ�����2^(n-1)�������2^n-1

int n, vis[1<<maxn];//n�ǹ�׹����
double r, w[maxn], sum[1<<maxn];//rΪ�����ȣ�w[i]Ϊ��׹������
//sum[i]Ϊ��iΪ�����������

vector<Tree> tree[1<<maxn];//����Ԫ����vector<Tree>

//�Զ����¹��죬ÿ��ö���������õ��ĸ��Ӽ���������������ʹ��ʣ�µ��Ӽ���
void dfs(int subset)
{
	if(vis[subset])  return ;
	vis[subset]=true;

	bool have_children=false;
	for(int left=(subset-1)&subset; left; left=(left-1)&subset)
		//for�������ܵ����������
		//�����ǣ�����
	{
		have_children=true;

		int right=subset^left;
		double d1=sum[right]/sum[subset];//ľ����߳���
		double d2=sum[left]/sum[subset];//ľ���ұ߳���

		dfs(left);
		dfs(right);

		for(int i=0; i<tree[left].size(); i++)
		{
			for(int j=0; j<tree[right].size(); j++)
			{
				Tree t;
				t.L=max(tree[left][i].L+d1, tree[right][j].L-d2);//������
				t.R=max(tree[right][j].R+d2, tree[left][i].R-d1);//������
				if(t.L+t.R<r)
					tree[subset].push_back(t);
			}
		}
	}//for�������ܵ����������
	if(!have_children)
		tree[subset].push_back(Tree());
}

void main()
{
	scanf("%lf%d", &r, &n);//r�Ƿ����ȣ�n�ǹ�׹��Ŀ
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


//7.5·��Ѱ������
typedef int State[9];//���塰״̬�����ͣ�9��intԪ�ص�int����
const int maxstate=1000000;
State st[maxstate], goal;//״̬���顣����״̬�����������goalΪĿ��״̬
int dist[maxstate];//��������
//���Ҫ��ӡ�����������������һ�������ױ�š�����int fa[maxstate]

const int dx[]={-1, 1, 0, 0};
const int dy[]={0, 0, -1, 1};//���ң��£���

int bfs()//��Ȩͼ�ϵ����·����
{
	init_lookup_table();//��ʼ�����ұ�:frontΪ��ʼ״̬
	int front=1, rear=2;//��ʹ���±�0����Ϊ0�������������ڡ�
	while(front<rear)
	{
		State &s=st[front];//�á����á��򻯴���
		if(memcmp(goal, s, sizeof(s))==0)//�ҵ�Ŀ��״̬���ɹ�����
			return front;

		int z;
		for(z=0; z<9; z++)//ջ0��λ��
			if(!s[z])
				break;
		int x=z/3, y=z%3;//�ո������кš��кţ�0-2��
		for(int d=0; d<4; d++)//�����Ʒ��������չ�ĸ��½��
		{
			int newx=x+dx[d];//���к�
			int newy=y+dy[d];//���к�
			int newz=newx*3 + newy;//�±��
			if(newx>=0  &&  newx<3  &&  newy>=0  &&  newy<3)//����ƶ��Ϸ�
			{
				State &t=st[rear];
				memcpy(&t, &s, sizeof(s));//��չ�½��
				t[newz]=s[z];
				t[z]=s[newz];
				dist[rear]=dist[front]+1;//�����½��ľ���ֵ
				if(try_to_insert(rear))//����ɹ�������ұ��޸Ķ�βָ��
					rear++;
			}
		}
		front++;//��չ��Ϻ����޸Ķ���ָ��
	}
	return 0;//ʧ��
}

void main()
{
	for(int i=0; i<9; i++)
		scanf("%d", &st[1][i]);//��ʼ״̬
	for(int i=0; i<9; i++)
		scanf("%d", &goal[i]);//Ŀ��״̬
	int ans=bfs();
	if(ans>0)
		printf("%d\n", dist[ans]);
	else
		printf("-1\n");
}

//��1�ַ����ǣ������С���ɡ�������Ȼ��ֻ��һ��һά���顣
//Ҳ����˵�����һ�����еı���ͽ��뺯������0-8��ȫ���к�0-362879������һһ��Ӧ������
int vis[362880], fact[9];
void init_lookup_table()
{
	fact[0]=1;
	for(int i=1; i<9; i++)
		fact[i]=fact[i-1]*i;
}
int try_to_insert(int s)
{
	int code=0;//��st[s]ӳ�䵽����code
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

//��2�ַ�����ʹ�ù�ϣ�������ѽ�㡰��ɡ���������������һһ��Ӧ��
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

//��3�ַ�������STL����t����״̬ת����9λʮ�����������Ϳ�����set<int>������
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


//��ˮ����
//���һ���Ե����⣺��3�����ӵ������ֱ�Ϊa,b,c,���ֻ�е�3������װ����c��ˮ��������������Ϊ�ա�
//������Ҫ��������ˮ������ĳһ�������е�ˮ��d���أ�
//����޷�����ǡ��d��������ĳһ���������ˮ��d'��������d'<d���Ҿ����ӽ�d��
//��1<=a,b,c,d<=200����
//Ҫ��������ٵĵ�ˮ����Ŀ��ˮ����d����d'��
struct Node{
	int v[3], dist;//��ǰϵͳ״̬��3�����ӵ�ˮ����distΪ�����״̬�ĵ�ˮ����
	bool operator < (const Node & rhs) const
	{
		return dist > rhs.dist;
	}
};

const int maxn=200+5;
int vis[maxn][maxn], cap[3], ans[maxn];//vis�Ƿ��ʱ�ǡ�
//cap���������ӵ�������
//ans�Ǽ�¼������Ӧ�±�ˮ������Ҫ�ĵ�ˮ��

void update_ans(const Node & u)//���µ�����Ӧˮ������Ҫ�ĵ�ˮ��
{
	for(int i=0; i<3; i++)
	{
		int d=u.v[i];//���u״̬�µ�3�����ӵ�ˮ��
		if(ans[d]<0  ||  u.dist<ans[d])
			ans[d]=u.dist;
	}
}

void solve(int a, int b, int c, int d)
{
	cap[0]=a; cap[1]=b; cap[2]=c;//cap�����ʾ�������ӵ�����
	memset(vis, 0, sizeof(vis));//��ʼ�����ʱ�־����Ϊ0
	memset(vis, -1, sizeof(ans));//��ʼ����ˮ������Ϊ-1
	priority_queue<Node> q;//���ȶ��У�ÿ��ȡ����ˮ�����ٵĽ�������չ

	Node start;
	start.dist=0;
	start.v[0]=0; start.v[1]=0;	start.v[2]=c;
	q.push(start);

	vis[0][0]=1;
	while(!q.empty())//ÿ��ȡ����ˮ�����ٵĽ�������չ��ֱ������Ŀ��ˮ��d
	{
		Node u=q.top(); q.pop();
		update_ans(u);//���µ�ˮ��
		if(ans[d]>=0)//���Ŀ��ˮ����ֹͣ��չ
			break;
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				if(i!=j)//�������п��ܵĵ�ˮ����
				{
					if(u.v[i]==0  ||  u.v[j]==cap[j]) continue;
					int amount=min(cap[j], u.v[i]+u.v[j])-u.v[j];//��ˮ���������ˮ��һ������j�������ߵ���i����ˮ
					Node u2;//��չ�½��
					memcpy(&u2, &u, sizeof(u));
					u2.dist=u.dist+amount;//���µ����½��ĵ�ˮ��
					u2.v[i] -= amount;
					u2.v[j] += amount;
					if(!vis[u2.v[0]][u2.v[1]])//����½��δ���ʹ������÷��ʱ�־�����������ȶ���
					{
						vis[u2.v[0]][u2.v[1]]=1;
						q.push(u2);
					}
				}
	}
	while(d>=0)//��ӡ��ӽ�d�Ľ������ˮ����Ŀ��ˮ��
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


//��ʥ�ں���糿
//w*h��w, h<=16����������n��n<=3����Сд��ĸ���������
//Ҫ������Ƿֱ��ƶ�����Ӧ�Ĵ�д��ĸ�
//ÿ�������ж����ͬʱ�ƶ�����Ϊ����������4������֮һ�ƶ�����
//��ÿ������֮���κ���������ռ��ͬһ��λ�ã�Ҳ������һ��֮�ڽ���λ�á�
//���뱣֤���пո���ͨ�������ϰ���Ҳ��ͨ�����κ�һ��2*2��������������һ���ϰ���
//������ٵĲ��������뱣֤�н⡣
//
//�Ե�ǰ3��Сд��ĸ��λ��Ϊ״̬��������ת��Ϊͼ�ϵ����·���⡣
//״̬����Ϊ256^3��ÿ��ת��ʱ��Ҫ5^3ö��ÿһ��Сд��ĸ��һ�����߷����������Ҽ��ϡ�����������
//״̬���ܴ�ת�ƴ����ֱȽϸߣ������׳�ʱ����Ҫ�Ż���
//�����Ż�ת�ƴ��ۡ���������һ��2*2��������������һ���ϰ���
//��ʾ�źܶ���Ӷ����ϰ������Ҵ󲿷ֿյض����ϰ����ڣ�
//��˲�������4���������ƶ�����˿��԰����пո����������һ��ͼ��
//������ÿ����ʱ�ж�5�ַ����Ƿ�Ϸ���
//��������Ż��Ժ�BFS�Ϳ���ͨ������������ˡ�

const int maxs=20;
const int maxn=150;//14*14*0.75+2��λ��
const int dx[]={1, -1, 0, 0, 0};//�ҡ����ϡ��¡�����
const int dy[]={0, 0, 1, -1, 0};

inline int ID(int a, int b, int c)//����ǰ�������λ��a,b,cת��Ϊ����ID��Ϊ��ʶ
{
	return (a<<16) | (b<<8) |  c;
}

int s[3], t[3];//ÿһ����Ŀ�ʼ�ͽ���λ��

int deg[maxn], G[maxn][5];
	//deg[i]��ʾiλ����deg[i]��������5�������е��ƶ�λ��
	//G[i][j]�ֱ��ʾiλ�õĵ�j���ƶ�λ��

inline bool conflict(int a, int b, int a2, int b2)
{
	return a2==b2  ||  (a2==b  &&  b2==a);
}

int d[maxn][maxn][maxn];//�ӿ�ʼλ�õ�i, j, kλ�õĲ���Ϊd[i][j][k]

int bfs()
{
	queue<int> q;//�����У���int�ͱ�ʾ������ĵ�ǰλ��
	memset(d, -1, sizeof(d));//��ʼ������Ϊ-1
	q.push(ID(s[0], s[1], s[2]));//��ʼ���������
	d[s[0]][s[1]][s[2]]=0;//��ʼ����Ϊ0
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		int a=(u>>16) & 0xff, b=(u>>8) & 0xff, c=u & 0xff;//��õ�ǰ�����������λ��a,b,c
		if(a==t[0]  &&  b==t[1]  &&  c==t[2])//���ѵ���Ŀ��λ�ã�ֹͣ��չ�����ز���
			return d[a][b][c];

		//��չ��ǰ���u
		for(int i=0; i<deg[a]; i++)
		{
			int a2=G[a][i];//��ǰu���ʱ������a���ƶ�λ��
			for(int j=0; j<deg[b]; j++)
			{
				int b2=G[b][j];//��ǰu���ʱ������b���ƶ�λ��
				if(conflict(a, b, a2, b2))   continue;
				for(int k=0; k<deg[c]; k++)
				{
					int c2=G[c][k];//��ǰu���ʱ������c���ƶ�λ��
					if(conflict(a, c, a2, c2))  continue;
					if(conflict(b, c, b2, c2))  continue;
					if(d[a2][b2][c2] != -1)  continue;//��λ���Ѵ���
					d[a2][b2][c2]=d[a][b][c]+1;//���¸�λ�õĲ�������1
					q.push(ID(a2, b2, c2));//�����λ�õ�������
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
		//��ȡ�������maze[20][20]����
		char maze[20][20];
		for(int i=0; i<h; i++)
			fget(maze[i], 20, stdin);

		//��ȡ���пո�
		//��Ŀ����cnt���������x[]��y[]��
		//����x,y�ı�Ŵ���id[x][y]
		int cnt, x[maxn], y[maxn], id[maxs][maxs];
			//cnt�ǿո���Ŀ
			//x[i]�ǿո��x��y[i]�ǿո��y
			//id[i][j]��(x,y)�ո�λ�������пո��еı��
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

		//�����пո����������һ�ű�
		for(int i=0; i<cnt; i++)
		{
			deg[i]=0;
			for(int dir=0; dir<5; dir++)
			{
				int nx=x[i]+dx[dir], ny=y[i]+dy[dir];
				//�������λ�����ϰ�����˲��迼�Ǳ߽�
				if(maze[nx][ny]!='#')
					G[i][deg[i]++]=id[nx][ny];
			}
		}

		//���Ӽٽ�㣬ʹ���κ�ʱ����3����ʹ��������
		if(n<=2)//���ӵ�3����
		{
			deg[cnt]=1;//��3����ֻ��һ���ƶ�λ��
			G[cnt][0]=cnt;//����������
			s[2]=t[2]=cnt++;//��3����Ŀ�ʼλ�úͽ���λ�ö�Ϊcnt
		}
		if(n<=1)//���ӵ�2����
		{
			deg[cnt]=1;
			G[cnt][0]=cnt;
			s[1]=t[1]=cnt++;
		}
		printf("%d\n", bfs());//��ӡ�������
	}
}


//������������
//ʹ�õ�λ�����ĺͣ���1/a��a����Ȼ������ʾһ���������������в���������ͬ�ġ�
//����һ������a/b����ʾ�����кܶ��֣����м����ٵıȼ�����ĺã��������������ͬ������С�ķ���Խ��Խ�á�
//��������a,b(0<a<b<500)���Ա�̼�����ѱ��ʽ��
int a, b, maxd;//a,bΪ����������������a/b��maxdΪ�������
typedef long long LL;
LL gcd(LL a, LL b)//��a��b�����Լ��
{
	return b==0 ?  a :  gcd(b, a%b);
}

//������1/c <= a/b����С��c ,�� c>=b/a
inline int get_first(LL a, LL b)
{
	return b/a+1;
}

const int maxn=100+5;//

LL v[maxn], ans[maxn];//v[]Ϊ��ǰ�⣬ans[]Ϊ���Ž�

//�����ǰ��v��Ŀǰ���Ž�ans���ţ�����ans
//�����ٵıȼ�����ĺã�ǰ�ߣ���С����ö���������maxd
//�������������ͬ������С�ķ���Խ��Խ�á����ߣ�better(d)
bool better(int d)
{
	for(int i=d; i>=0; i--)//����С�ķ�����ʼ�Ƚ�
		if(v[i]!=ans[i])
		{
			return ans[i]==-1  ||  v[i]<ans[i];
		}
	return false;
}

//��ǰ���Ϊd����ĸ����С��from������֮��ǡ��Ϊaa/bb
//�ӷ�ĸ��С����λ�������ʼ��չ
bool dfs(int d, int from, LL aa, LL bb)
{
	if(d==maxd)//�ѵ����������
	{
		if(bb % aa)// aa/bb�����ǵ�λ���������һ����
			return false;
		v[d]=bb/aa;//���һ������d����λ�����ķ�ĸ
		if(better(d))//�����ǰ��v��Ŀǰ���Ž�ans���ţ�����ans
			memcpy(ans, v, sizeof(LL)*(d+1));
		return true;  
	}

	bool ok=false;
	from=max(from, get_first(aa, bb));//ö�ٵ����
	for(int i=from; ; i++)
	{
		//��֦�����ʣ�µ�maxd+1-d������ȫ����1/i����������Ȼ������aa/bb�����޽�
		if(bb*(maxd+1-d)<=i*aa)  break;
		v[d]=i;
		//����aa/bb-1/i������Ϊa2/b2
		LL b2=bb*i;
		LL a2=aa*i-bb;
		LL g=gcd(a2, b2);//Լ��
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

//�༭���
//��һƪ��n��2<=n<=9������Ȼ����ɵ����£�ϣ�����������г�1,2,...,n��
//�����ü��к�ճ����ݼ����������ÿ�ο��Լ���һ����������Ȼ�Σ�
//ճ��ʱ����˳��ճ����������ֻ��һ�������Բ��������������Σ�ֻ�ܼ��к�ճ�����档
const int maxn=9;
int n, a[maxn];//nΪʵ����Ȼ����Ŀ��a����Ϊ��ǰ����

bool is_sorted()//�ж�a����(��ǰ����)�Ƿ��ź���
{
	for(int i=0; i<n-1; i++)
		if(a[i]>=a[i+1])
			return false;
	return true;
}

int h()//ͳ�ƺ�̲���ȷ�����ָ���
{
	int cnt=0;
	for(int i=0; i<n-1; i++)
		if(a[i]+1 != a[i+1])
			cnt++;
	if(a[n-1] != n)//ע�⣿
		cnt++;
	return cnt;
}

//�����������
bool dfs(int d, int maxd)//dΪ��ǰ��ȣ�maxdΪ�������
{
	if(d*3+h()>maxd*3)//����h()ͳ�ƺ�̲���ȷ�����ָ���
		return false;//��֦
	if(is_sorted())
		return true;//���ź��򣬳ɹ�����

	int b[maxn], olda[maxn];
	memcpy(olda, a, sizeof(a));//��a���鱣�浽olda������

	for(int i=0; i<n; i++)// ö��a[i...j]
		for(int j=i; j<n; j++)
		{
			//���е�a[i..j]���õ�ʣ�µ�b����
			int cnt=0;
			for(int k=0; k<n; k++)
				if(k<i  ||  k>j)
					b[cnt++]=a[k];

			//ճ����k֮ǰ
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
				memcpy(a, olda, sizeof(a));//���ݣ��ָ�a����
			}
		}
	return false;
}

int solve()
{
	if(is_sorted())
		return 0;
	int max_ans=5;//��n<=9����ans<=5
	for(int maxd=1; maxd<max_ans; maxd++)
		if(dfs(0, maxd))//��ǰ���Ϊ0���������Ϊmaxd
			return maxd;//���ص�ǰ�������maxd
	return max_ans;//����5
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