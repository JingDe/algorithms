
#include<stdio.h>
#include<list>
#include<iostream>

struct coordinate{
	int x;
	int y;
	coordinate(int a, int b):x(a),y(b){}
};

// 矩阵初始左上角为(minrow, mincol)，右下角为(maxrow, maxcol)
std::list<coordinate> matrixSearch(int **matrix, int minrow, int maxrow, int mincol, int maxcol, int x)
{
	std::list<coordinate> result;
	int rightTop;
	// 初始右上角(minrow, maxcol)
	int curTopRow=minrow;
	int curRightCol=maxcol;
	
	while(curRightCol>=mincol  &&  curTopRow<=maxrow)
	{
		rightTop=matrix[curTopRow][curRightCol];
		if(rightTop==x)
		{
			result.push_back(coordinate(curTopRow, curRightCol));
			++curTopRow;
			--curRightCol;
		}
		else if(rightTop<x)
		{
			++curTopRow;
		}
		else
		{
			--curRightCol;
		}
	}
	return result;
}

void test()
{
	FILE* f=freopen("9.6.in", "r", stdin);
	if(f==NULL)
		return;
	
    int m, n;
    std::cin>>m>>n;
	int** d=new int*[m];
	for(int i=0; i<m; ++i)
		d[i]=new int[n];
	
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            std::cin>>d[i][j];
		
	std::list<coordinate> res=matrixSearch(d, 0, m-1, 0, n-1, 9);
	for(std::list<coordinate>::iterator it=res.begin(); it!=res.end(); ++it)
		printf("(%d, %d)\n", it->x, it->y);
	
	for(int i=0; i<m; ++i)
		delete [](d[i]);
	delete []d;
}

int main()
{
	test();
	return 0;
}