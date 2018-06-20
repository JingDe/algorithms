#include<stdio.h>
#include<iostream>
#include<string>
#include<stack>
using namespace std;

struct Matrix{
	int a;
	int b;
	Matrix(int a=0, int b=0):a(a),b(b){}
}m[26];

int main()
{
	stack<Matrix> s;
	int n;
	cin>>n;
	for(int i=0; i<n; i++)
	{
		string name;
		scanf("%s", &name);
		int c=name[0]-'A';
		cin>>m[c].a;
		cin>>m[c].b;
	}

	string expr;
	while(cin>>expr)
	{
		int count=0;
		bool error=false;
		for(i=0; i<expr.length(); i++)
		{
			if(isalpha(expr[i]))
				s.push(m[expr[i]-'A']);
			else if(expr[i]==')')
			{
				Matrix m2=s.top();	s.pop();
				Matrix m1=s.top();	s.pop();
				if(m1.b != m2.a)	{error=true;break;}
				count += m1.a*m1.b*m2.b;
				s.push(Matrix(m1.a, m1.b));
			}
		}
		if(error)
			printf("error\n");
		else
			printf("%d\n", count);
	}
	return 0;
}
