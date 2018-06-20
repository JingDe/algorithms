#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cassert>
using namespace std;

#define REP(i,n) for(int i=0; i<n; i++)

const int maxn=144;
const int n_cut=70;

struct Player{
	char name[25];
	int amateur;
	int sc[4];
	int sc36;
	int sc72;
	int dq;
	int rnds;//ÂÖÊý
}player[maxn];

int n;
double purse, p[n_cut];


bool cmp1(const Player &p1, const Player & p2)
{
	if(p1.sc36<0  &&  p2.sc36<0)
		return false;
	if(p1.sc36<0)
		return false;
	if(p2.sc36<0)
		return true;//p1¸üÐ¡
	return p1.sc36<p2.sc36;
}

bool cmp2(const Player &p1, const Player & p2)
{
	if(p1.dq  &&  p2.dq)
	{
		if(p1.rnds!=p2.rnds)
			return p1.rnds>p2.rnds;
		if(p1.sc72!=p2.sc72)
			return p1.sc72<p2.sc72;
		return strcmp(p1.name, p2.name)<0;
	}
	if(p1.dq)
		return false;
	if(p2.dq)
		return true;
	if(p1.sc72!=p2.sc72)
		return p1.sc72<p2.sc72;
	return strcmp(p1.name, p2.name)<0;
}

void print_result() 
{ 
	printf("Player Name          Place     RD1  RD2"); 
    printf("  RD3  RD4  TOTAL     Money Won\n"); 
    printf("---------------------------------------"); 
    printf("--------------------------------\n"); 

	int i=0;
	int pos=1;
	while(i<n)
	{
		if(player[i].dq)
		{
			printf("%s           ", player[i].name);
			REP(i, player[i].rnds) printf("%-5d", player[i].sc[i]);
			REP(j, 4-player[i].rnds) printf("     ");
			printf("DQ\n");
			i++;
			continue;
		}

		int j=i;
		int m=0;
		double tot=0.0;
		bool have_money=false;
		while(j<n  &&  player[i].sc72==player[j].sc72)
		{
			if(!player[j].amateur)
			{
				m++;
				if(pos<n_cut)
				{
					have_money=true;
					tot+=p[pos++];
				}
			}
			j++;
		}

		int rank=i+1;
		int my=purse * tot / m;
		while(i<j)
		{
			printf("%s ", player[i].name);
			char t[5];
			sprintf(t, "%d%c", rank, m>1  &&  have_money &&  !player[i].amateur ? 'T' : ' ');
			printf("%-10s", t);
			REP(k, 4)
				printf("%-5d", player[i].sc[k]);
			if(!player[i].amateur  &&  have_money)
			{
				printf("%-10d", player[i].sc72);
				printf("$%9.2lf", my/100.0);
			}
			else
				printf("%d\n", player[i].sc72);
			i++;
		}
	}
}


int main()
{
	int T=0;
	char s[40];
	gets(s);
	sscanf(s, "%d", T);
	while(T--)
	{
		gets(s);
		
		gets(s);
		scanf(s, "%d", purse);
		REP(i, n_cut)
		{
			gets(s);
			scanf(s, "%lf", &p[i]);
		}
		gets(s);
		scanf(s, "%d", n);
		assert(n<=144);
		REP(k, n)
		{
			gets(s);
			strncpy(player[k].name, s, 20);
			player[k].name[20]=0;
			player[k].amateur=0;
			if(strchr(player[k].name, '*'))
				player[k].amateur=1;

			player[k].dq=player[k].sc36=player[k].sc72=0;
			memset(player[k].sc, -1, sizeof(player[k].sc));
			REP(i, 4)
			{
				char t[5];
				REP(j, 3)
					t[j]=s[20+i*3+j];
				t[3]='\n';
				if(!scanf(t, "%d", player[k].sc[i]))
				{
					player[k].rnds=i;
					player[k].dq=-1;
					if(i<2)
						player[k].sc36=-1;
					break;
				}
				else
				{
					player[k].sc72+=player[k].sc[i];
					if(i<2)
						player[k].sc36+=player[k].sc[i];
				}
			}
		}

		sort(player, player+n, cmp1);
		assert(player[n_cut-1].sc36>=0);
		for(i=n_cut-1; i<n; i++)
			if(player[i].sc36!=player[i+1].sc36  ||  i==n-1)
			{
				n=i+1;
				break;
			}

		sort(player, player+n, cmp2);

		print_result();
		
		if(T)
			printf("\n");
	}
	return 0;
}