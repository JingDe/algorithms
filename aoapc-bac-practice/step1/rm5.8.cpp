#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int maxcol=60;
const int maxn=100+5;
string filenames[maxn];

void print(const string& s, int len, char c)
{
	cout<<s;
	for(int i=0; i<len-s.length(); i++)
		cout<<c;
}

int main()
{
	int n;
	while(cin>>n)
	{
		int M=0;
		for(int i=0; i<n; i++)
		{
			cin>>filenames[i];
			if(M<filenames[i].length())
				M=filenames[i].length();
		}
		int cols=(maxcol-M)/(M+2)+1;
		int rows=(n-1)/cols+1;
		print("", 60, '-');
		cout<<endl;
		sort(filenames, filenames+n);
		for(int r=0; r<rows; r++)
		{
			for(int c=0; c<cols; c++)
			{
				int cnt=r+c*rows;
				if(cnt<n)
					print(filenames[cnt], c==cols ? M : M+2, ' ');
			}
			cout<<endl;
		}

	}
	return 0;
}