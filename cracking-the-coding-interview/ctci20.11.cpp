#include<iostream>
#include<stdio.h>


const int MAX_N = 100;
	
enum Color{
	BLACK=0,
	WHITE=1,
};

bool isBlack(int line, int col, int sz, int matrix[MAX_N][MAX_N]);

void maxSquare(int matrix[MAX_N][MAX_N], int len)
{
	int maxsz=0;
	int curline=0;
	int curcol=0;
	for(int line=0; line<len; ++line)
	{
		for(int col=0; col<len; ++col)
		{
			int maxLen=std::min(len-line, len-col);
			for(int sz=maxsz; sz<maxLen; ++sz)
			{
				if(isBlack(line, col, sz, matrix))
				{
					curline=line;
					curcol=col;
					maxsz=sz;
				}
			}
		}
	}
	printf("%d %d %d\n", curline, curcol, maxsz);
	printf("top bottom left right %d %d %d %d\n", curline, curline+maxsz, curcol, curcol+maxsz);
}

bool isBlack(int line, int col, int sz, int matrix[MAX_N][MAX_N])
{
	for(int i=col; i<col+sz; ++i)
		if(matrix[line][i]!=BLACK  ||  matrix[line+sz][i]!=BLACK)
			return false;
	for(int i=line; i<line+sz; ++i)
		if(matrix[i][col]!=BLACK  ||  matrix[i][col+sz]!=BLACK)
			return false;
	return true;
}

void test()
{
	freopen("20.11.in", "r", stdin);
	int n;
	int matrix[MAX_N][MAX_N];
    std::cin>>n;
    for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j)
            std::cin>>matrix[i][j];
	maxSquare(matrix, n);
	
}

int main()
{
	test();
	
	return 0;
}