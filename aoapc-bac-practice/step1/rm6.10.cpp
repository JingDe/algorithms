#include<iostream>
#include<string>
using namespace std;

const int maxn=200;
int sum[maxn];

void build(int p)
{
	int v;
	cin>>v;
	if(v==-1)  return ;
	sum[p]+=v;
	build(p -1);
	build(p +1);
}

bool init()
{
	int v;
	cin>>v;
	if(v==-1)  return false;
	memset(sum, 0, sizeof(sum));
	int pos=maxn/2;
	sum[pos]=v;
	build(pos-1);
	build(pos+1);
	return true;
}

int main()
{
	int kase=0;
	while(init())
	{
		int p=0;
		while(!sum[p])  p++;
		cout<<"Case "<<kase++<<sum[p];
		while(sum[p])
		{
			cout<<" "<<sum[p++];
		}
		cout<<endl<<endl;
	}
	return 0;
}