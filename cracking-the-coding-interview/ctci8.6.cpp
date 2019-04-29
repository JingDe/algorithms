#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>

using std::cout;
using std::cin;
using std::endl;

struct Point{
	int x;
	int y;
	Point(int a, int b):x(a),y(b){}
	Point& operator=(const Point& rhs)
	{
		x=rhs.x;
		y=rhs.y;
		return *this;
	}
};

enum color{
	red, green, black,
};

void dfsFill(Point seed, color c, color **field, int m, int n)
{
	if(seed.x<0  ||  seed.x>=m  ||  seed.y<0  ||  seed.y>=n)
		return;
	if(field[seed.x][seed.y]==c)
		return;
	field[seed.x][seed.y]=c;
	dfsFill(Point(seed.x-1, seed.y), c, field, m, n);
	dfsFill(Point(seed.x+1, seed.y), c, field, m, n);
	dfsFill(Point(seed.x, seed.y-1), c, field, m, n);
	dfsFill(Point(seed.x, seed.y+1), c, field, m, n);
}


void bfsFill(Point seed, color c, color **field, int m, int n)
{
	std::queue<Point> Q;
	if(seed.x<0  ||  seed.x>=m  ||  seed.y<0  ||  seed.y>=n)
		return;
	Q.push(seed);
	while(!Q.empty())
	{
		Point cur=Q.front();
		Q.pop();
		if(cur.x<0  ||  cur.x>=m  ||  cur.y<0  ||  cur.y>=n)
			continue;
		if(field[cur.x][cur.y]==c)
			continue;
		field[cur.x][cur.y]=c;
		Q.push(Point(cur.x-1, cur.y));
		Q.push(Point(cur.x+1, cur.y));
		Q.push(Point(cur.x, cur.y-1));
		Q.push(Point(cur.x, cur.y+1));
	}
}

int main()
{
	{
		freopen("8.6.in", "r", stdin);
		int m, n;
		cin>>m>>n;
		color **screen = new color*[m];
		for(int i=0; i<m; ++i)
			screen[i] = new color[n];
		for(int i=0; i<m; ++i)
			for(int j=0; j<n; ++j){
				int t;
				cin>>t;
				screen[i][j]=(color)t;
			}
		fclose(stdin);
		
		for(int i=0; i<5; ++i){
			for(int j=0; j<5; ++j)
				cout<<screen[i][j]<<" ";
			cout<<endl;
		}
		
		printf("\n--------\n");
		bfsFill(Point(1, 2), green, screen, 5, 5);
		for(int i=0; i<5; ++i){
			for(int j=0; j<5; ++j)
				cout<<screen[i][j]<<" ";
			cout<<endl;
		}
	}
	
	int c=getchar();
	printf("%d\n", c);
	system("pause");
	return 0;
}
