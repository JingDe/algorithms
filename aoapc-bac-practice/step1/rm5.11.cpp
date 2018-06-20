/*
Sample Input
MTA London 4 Fiona Paul Heather Nevil
MTA SanFrancisco 3 Mario Luigi Shariff
MTA Paris 3 Jacque Suzanne Maurice
MTA HongKong 3 Chen Jeng Hee
MTA MexicoCity 4 Conrado Estella Eva Raul
MTA Cairo 3 Hamdy Tarik Misa
*
Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
*
Congratulations on your efforts !!
--Hamdy
*
Fiona@London Chen@HongKong Natasha@Paris
*
Thanks for the report! --Fiona
*
*
-----------------------------------------------------
Sample Output
Connection between Cairo and MexicoCity
HELO Cairo
250
MAIL FROM:<Hamdy@Cairo>
250
RCPT TO:<Conrado@MexicoCity>
250
RCPT TO:<Lisa@MexicoCity>
550
DATA
354
Congratulations on your efforts !!
--Hamdy
.
250
QUIT
221						//-------------------------------//
Connection between Cairo and SanFrancisco
HELO Cairo
250
MAIL FROM:<Hamdy@Cairo>
250
RCPT TO:<Shariff@SanFrancisco>
250
DATA
354
Congratulations on your efforts !!
--Hamdy
.
250
QUIT
221					  //-------------------------------//
Connection between London and HongKong
HELO London
250
MAIL FROM:<Fiona@London>
250
RCPT TO:<Chen@HongKong>
250
DATA
354
Thanks for the report! --Fiona
.
250
QUIT
221                     //-------------------------------//
Connection between London and Paris
HELO London
250
MAIL FROM:<Fiona@London>
250
RCPT TO:<Natasha@Paris>
550
QUIT
221

*/


#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
using namespace std;

void parse_address(const string& s, string& user, string& mta)
{
	int k=s.find('@');
	user=s.substr(0, k);
	mta=s.substr(k+1);
}

int main()
{
	int k;
	string s, t;
	string user1, mta1;
	string user2, mta2;
	set<string> addr;

	while(cin>>s  &&  s!="*")
	{
		cin>>s>>k;
		while(k--)
		{
			cin>>t;
			addr.insert(t+"@"+s);
		}
	}

	

	while(cin>>s  &&  s!="*")
	{		
		parse_address(s, user1, mta1);
		
		vector<string> mta;
		map<string , vector<string> > dest;
		set<string> vis;

		while(cin>>t  &&  t!="*")//收件人列表
		{
			parse_address(t, user2, mta2);
			if(vis.count(t))
				continue;
			vis.insert(t);
			if(!dest.count(mta2))
			{
				mta.push_back(mta2);
				dest[mta2]=vector<string>();///////////////
			}
			dest[mta2].push_back(t);
		}

		getline(cin, t);		//把“*”这一行的回车吃掉

		string data;
		while(getline(cin, t)  &&  t[0]!='*')
			data+="     "+t+"\n";

		//处理，输出	
		for(int i=0; i<mta.size(); i++)
		{
			string mta2=mta[i];
			vector<string> users=dest[mta2];
			cout<<"Connection between "<<mta1<<" and "<<mta2<<endl;
			cout<<"HELO "<<mta1<<endl;
			cout<<"250\n";
			cout<<"MAIL FROM:<"<<s<<">\n";
			cout<<"250\n";

			bool ok=false;
			for(int j=0; j<users.size(); j++)
			{
				cout<<"RCPT TO:<"<<users[j]<<">\n";
				if(addr.count(users[j]))
				{
					cout<<"250\n";
					ok=true;
				}
				else
					cout<<"550\n";
			}

			if(ok)
			{
				cout<<"DATA\n";
				cout<<"354\n";
				cout<<data<<endl;
				cout<<".\n";
				cout<<"250\n";
			}
			cout<<"QUIT\n";
			cout<<"221\n";
		}
	}
	return 0;
}