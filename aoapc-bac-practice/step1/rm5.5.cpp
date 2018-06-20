#include<iostream>
#include<set>
#include<string>
#include<cctype>
#include<map>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x, x.begin())

typedef set<int> Set;
map<Set, int> IDcache;
vector<Set> Setcache;

stack<int> s;

int ID(Set x)
{
	if(IDcache.count(x))
		return IDcache[x];
	Setcache.push_back(x);
	return IDcache[x]=Setcache.size()-1;
}

int main()
{
	string str;
	int n;
	cin>>n;
	while(n--)
	{
		cin>>str;
		if(str[0]=='P')
			s.push(ID(Set()));
		else if(str[0]=='D')
			s.push(s.top());
		else
		{
			Set x1=Setcache[s.top()];
			s.pop();
			Set x2=Setcache[s.top()];
			s.pop();
			Set x;
			if(str[0]=='U')
				set_union(ALL(x1), ALL(x2), INS(x));
			else if(str[0]=='I')
				set_intersection(ALL(x1), ALL(x2), INS(x));
			else if(str[0]=='A')
			{		x=x2;	x.insert(ID(x1));	}
			s.push(ID(x));
		}
	}
	cout<<Setcache[s.top()].size()<<endl;
	return 0;
}