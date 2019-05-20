
#include<stdio.h>

int checkRow(int board[], int n)
{
	int winer=0;
	// 判断第i行是否都相同
	for(int i=0; i<n; ++i)
	{
		winer=board[i*n]; // 第i行第1个
		for(int j=1; j<n; ++j)
		{
			if(board[i*n+j]!=winer)
			{
				winer=0;
				break;
			}
		}
		if(winer)
			break;
	}
	return winer;
}

int checkCol(int board[], int n)
{
	int winer=0;
	
	for(int i=0; i<n; ++i) // 判断第i列是否都相同
	{
		winer=board[i]; // 第i列第1个
		for(int j=1; j<n; ++j) // 第j行第i列
		{
			if(board[j*n+i]!=winer)
			{
				winer=0;
				break;
			}
		}
		if(winer)
			break;
	}
	return winer;
}

// 检查左对角线
int checkDiagonal1(int board[], int n)
{
	int winer=0;
	
	winer=board[n-1]; // 右上角
	for(int j=1; j<n; ++j) // 第j行
	{
		if(board[j*n+(n-1-j)]!=winer) // 第j行第n-1-j列
		{
			winer=0;
			break;
		}
	}

	return winer;
}

// 检查右对角线
int checkDiagonal2(int board[], int n)
{
	int winer=0;
	
	winer=board[n-1]; // 左上角
	for(int j=1; j<n; ++j) // 第j行
	{
		if(board[j*n+j]!=winer) // 第j行第j列
		{
			winer=0;
			break;
		}
	}

	return winer;
}

// n*n棋盘，
void solve()
{
	int n = 3; // 3*3
    int board[] = {
        2, 2, 1,
        2, 1, 1,
        1, 2, 0,
    };
	int winer=0;
	if((winer=checkRow(board, n)))
	{
		printf("%d won\n", winer);
		return;
	}
	if((winer=checkCol(board, n)))
	{
		printf("%d won\n", winer);
		return;
	}
	if((winer=checkDiagonal1(board, n)))
	{
		printf("%d won\n", winer);
		return;
	}
	if((winer=checkDiagonal2(board, n)))
	{
		printf("%d won\n", winer);
		return;
	}
}

int main()
{
	solve();
	
	return 0;
}