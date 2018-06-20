//6.1
//���г���ģ��
const int maxn=1000;

dequeue<int> readyQ;//�ȴ�����
dequeue<int> blockQ;//��ֹ����
int n, quantum, c[5], var[26], ip[maxn];
//n������quantum�����Q��c��5����䵥λʱ�䣻var��¼���б�����ֵ��
//ip[pid]�ǳ���pid�ĵ�ǰ�кš�
bool locked;
char prog[maxn][10];//���г��򶼴���prog���飬��������ʵ�����������Ҳ����

void run(int pid)//����pid��������̬
{
	int q=quantum;//���
	while(q>0)
	{
		char *p=prog[ip[pid]];//��ȡpid����ĵ�ǰ��
		switch(p[2])
		{
		case '='://��ֵ��䣺var = constant
			var[p[0]-'a']=isdigit(p[5]) ? (p[4]-'0')*10+p[5]-'0' : p[4]-'0';
			q-=c[0];
			break;
		case 'i'://��ӡ��䣺print var
			printf("%d: %d\n", pid+1, var[p[6]-'a']);
			q-=c[1];
			break;
		case 'c'://lock���
			if(locked)
			{
				blockQ.push(pid);
				return;
			}
			locked=true;
			q-=c[2];
			break;
		case 'l'://unlock���
			locked=false;
			if(!blockQ.empty())//��ֹ���еĵ�һ���������ȴ����е��ײ�
			{
				int pid2=blockQ.front();
				blockQ.pop();
				readyQ.push_front(pid2);
			}
			q-=c[3];
			break;
		case 'd'://end���
			reurn;
		}
		ip[pid]++;//pid���������һ��
	}
	readyQ.push_back(pid);//pid�����������꣬����ȴ����ж�β
}

void solve()
{
	scanf("%d %d %d %d %d %d %d\n", &n, &c[0], &c[1], &c[2] &c[3], &c[4], &quantum);
	memset(var, 0, sizeof(var));

	int line=0;
	//���λ��0 ~ n-1 ���г����ȫ����䣬����prog������
	for(int i=0; i<n; i++)
	{
		fgets(prog[line++], maxn, stdin);
		ip[i]=line-1;//��¼����i�ĵ�ǰ�кţ���ʼ�к�
		while(prog[line-1][2]!='d')
			fgets(prog[line++], maxn, stdin);
		readQ.push_back(i);
	}

	locked=false;
	//ѭ���ӵȴ����ж��׵��ȳ�������run
	while(!readQ.empty())
	{
		int pid=readQ.front();
		readyQ.pop_front();
		run(pid);
	}
}


//����
#include<stack>
const int MAXN=1000+10;

int n, target[MAXN];

void solve()
{
	scanf("%d", &n);
	stack<int> s;
	int A=1, B=1;
	for(int i=1; i<=n; i++)
		scanf("%d", &target[i]);
	int ok=1;
	//����Ŀ������target[B]
	while(B<=n)
	{
		if(A==target[B])
		{
			A++;
			B++;
		}
		else if(!s.empty()  &&  s.top()==target[B])
		{
			s.pop();
			B++;
		}
		else if(A<=n)
			s.push(A++);
		else
		{
			ok=0;
			break;
		}
	}
	printf("%s\n", ok? "YES" : "NO");
}



//��������
struct Matrix{
	int a, b;
	Matrix(int a=0, int b=0):a(a), b(b){}
}m[26];

stack<Matrix> s;

void solve()
{
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
	{
		string name;
		cin>>name;
		int k=name[0]-'A';
		cin>>m[k].a>>m[k].b;
	}
	string expr;
	while(cin>>expr)
	{
		int len=expr.length();
		bool error=false;
		int ans=0;
		for(int i=0; i<len; i++)
		{
			if(isalpha(expr[i]))
				s.push(m[expr[i]-'A']);
			else if(expr[i]==')')
			{
				Matrix m2=s.top(); s.pop();
				Matrix m1=s.top(); s.pop();
				if(m1.b != m2.a)
				{
					error=true;
					break;
				}
				ans += m1.a*m1.b*m2.b;
				s.push(Matrix(m1.a, m2.b));
			}
		}
		if(error)
			printf("error\n");
		else 
			printf("%d\n", ans);
	}
}


//����ļ���/�����ı�
const int maxn=100000+5;
int last, cur, next[maxn];
//���λ��cur���ַ��ĺ���
//lastΪ���һλ�ַ��±�
char s[maxn];

void solve()
{
	//���뱣����s[1...]��
	scanf("%s", s+1);
	int n=strlen(s+1);
	last=cur=0;
	next[0]=0;//next[0]�ͱ�ʾ��ʾ������ߵ��ַ�
			//0Ϊ�������

	for(int i=1; i<=n; i++)
	{
		char ch=s[i];
		if(ch=='[')
			cur=0;
		else if(ch==']')
			cur=last;
		else
		{
			//��������
			next[i]=next[cur];
			next[cur]=i;
			if(cur==last)//���¡����һ���ַ����±�
				last=i;
			cur=i;//�ƶ����
		}
	}
	for(int i=next[0]; i!=0; i=next[i])
		printf("%c", s[i]);
	printf("\n");
}



//�ƶ�����
void solve()
{
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++)
	{
		left[i]=i-1;
		right[i]=(i+1)%(n+1);
	}
	left[0]=n;
	right[0]=1;
	int op, X, Y, inv=0;

	while(m--)
	{
		scanf("%d", &op);
		if(op==4)
			inv=!inv;
		else
		{
			scanf("%d%d", &X, &Y);
			if(op==3  &&  right[Y]==X)
				swap(X, Y);
			if(op!=3  &&  inv)
				op=3-op;

			if(op==1  &&  X==left[Y])
				continue;
			if(op==2  &&  X==right[Y])
				continue;

			int LX=left[X], RX=right[X], LY=left[Y], RY=right[Y];
			if(op==1)
			{
				link(LX, RX); link(LY, X); link(X, Y);
			}
			else if(op==2)
			{
				link(LX, RX); link(Y, X); link(X, RY);
			}
			else if(op==3)
			{
				if(right[X]==Y)
				{
					link(LX, Y); link(Y, X); link(X, RY);
				}
				else
				{
					link(LX, Y); link(Y, RX); link(LY, X); link(X, RY);
				}
			}
		}
	}

	int b=0;
	long long ans=0;
	for(int i=1; i<=n; i++)
	{
		b=right[b];
		if(i%2==1)
			ans+=b;
	}
	if(inv  &&  n%2==0)
		ans=(long long) n*(n+1)/2 -ans;
	printf("%lld\n", ans);
}