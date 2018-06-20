#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<map>
#include<algorithm>
using namespace std;

map<string, int> cnt;
vector<string> words;

string standardize(const string & s)
{
	string res=s;
	for(int i=0; i<res.length(); i++)
		res[i]=tolower(res[i]);
	sort(res.begin(), res.end());
	return res;
}

int main()
{
	vector<string> res;
	string buf;
	while(cin>>buf)
	{
		if(buf[0]=='#')
			break;
		words.push_back(buf);
		string tmp=standardize(buf);
		if(cnt.count(tmp)==0)
			cnt[tmp]=0;
		cnt[tmp]++;
	}

	for(int i=0; i<words.size(); i++)
	{
		if(cnt[standardize(words[i])]==1)
			res.push_back(words[i]);
	}
	sort(res.begin(), res.end());
	for(i=0; i<res.size(); i++)
		cout<<res[i]<<endl;
	return 0;
}
