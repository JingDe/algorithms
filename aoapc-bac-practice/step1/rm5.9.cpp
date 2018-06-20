#include<iostream>
#include<map>
#include<sstream>
using namespace std;

typedef pair<int, int>  PII;

const int maxr=10000+5;
const int maxc=10+5;

int m, n, db[maxr][maxc];

int cnt;
map<string, int> id;
int ID(const string & str)
{
	if(id.count(str))
		return id[str];
	else
		return id[str]=++cnt;
}

void find()
{
	for(int c1=0; c1<m; c1++)
		for(int c2=c1+1; c2<m; c2++)
		{
			map<PII, int> t;
			for(int i=0; i<n; i++)
			{
				PII p=make_pair(db[i][c1], db[i][c2]);
				if(t.count(p))
				{
					cout<<"NO:\n";
					printf("%d %d\n", t[p]+1, i+1);
					printf("%d %d\n", c1+1, c2+1);
				}
				t[p]=i;
			}
		}
	printf("YES\n");
}

int main()
{
	string s;
	while(getline(cin, s))
	{
		stringstream ss(s);
		if(!(ss>>n>>m))
			break;

		cnt=0;
		id.clear();
		for(int i=0; i<n; i++)
		{
			getline(cin, s);
			int lastpos=-1;
			for(int j=0; j<m; j++)
			{
				int p=s.find(',', lastpos+1);
				if(p==string::npos)
					p=s.length();
				string a=s.substr(lastpos+1, p-lastpos-1);
				db[i][j]=ID(a);
				lastpos=p;
			}
		}
		find();
	}
	return 0;
}