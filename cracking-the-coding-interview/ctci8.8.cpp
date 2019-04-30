#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using std::cout;
using std::endl;

int eightQueen(int curRow, int col[8]);
bool posValid(int row, int col, int state[8]);
void printState(int col[8]);
void printRow(int pos);

// 当前放置curRow行的皇后，已放置的皇后第i行的位置在col[i]
int cnt0=0;
int eightQueen(int curRow, int col[8])
{
	int res=0;
	if(curRow==8)
	{
		//printState(col);
		++cnt0;
		return 1;
	}
	for(int c=0; c<8; ++c)
	{
		// 如果在curRow行放置在c位置可行
		if(posValid(curRow, c, col))
		{
			col[curRow]=c;
			res+=eightQueen(curRow+1, col);
		}
	}
	return res;
}


// 主对角线上y-x相同，副对角线上x+y相同
bool posValid(int row, int col, int state[8])
{
	// state[0~row-1]的皇后已放置好
	for(int r=0; r<row; ++r)
	{
		if(state[r]==col)
			return false;
		//if(col-row==state[r]-r  ||  row+col==r+state[r])
		if(abs(row-r)==abs(col-state[r]))
			return false;
	}
	return true;
}

void printState(int col[8])
{
	printf("\n8 Queen:\n");
	for(int i=0; i<8; ++i)
	{
		printRow(col[i]);
		printf("\n");
	}
	printf("\n");
}

void printRow(int pos)
{
	for(int i=0; i<pos; ++i)
		printf(" * ");
	printf(" Q ");
	for(int i=pos+1; i<8; ++i)
		printf(" * ");
}

// int tot=0;
// int C[8]={0};
int cnt1=0;
void search(int cur, int &tot, int C[], int n)
{
	if(cur==n)  
	{
		tot++;
		++cnt1;
	}
	else
		for(int i=0; i<n; i++)
		{
			int ok=1;
			C[cur]=i;
			for(int j=0; j<cur; ++j)
				if(C[cur]==C[j]  ||  cur-C[cur]==j-C[j]  ||  cur+C[cur]==j+C[j])
				{
					ok=0;
					break;
				}
			if(ok)
				search(cur+1, tot, C, n);
		}
}


int cnt2=0;
int search2(int row, int visit[3][16], int n)
{
	int res=0;
	if(row==n)
	{
		++cnt2;
		return 1;
	}
	for(int c=0; c<n; ++c)
	{
		if(visit[0][c]  ||  visit[1][row+c]  ||  visit[2][c-row+n])
			continue;
		visit[0][c]=visit[1][row+c]=visit[2][c-row+n]=1;
		res+=search2(row+1, visit, n);
		visit[0][c]=visit[1][row+c]=visit[2][c-row+n]=0;
	}
	return res;
}

int cnt3=0;
void search3(int cur, int vis[3][16], int c[], int n, int &tot3)
{
	if(cur==n)  
	{
		tot3++;
		++cnt3;
	}
	else
		for(int i=0; i<n; i++)
		{
			if(!vis[0][i]  &&  !vis[1][cur+i]  &&  !vis[2][cur-i+n])
			{
				c[cur]=i;
				vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=1;
				search3(cur+1, vis, c, n, tot3);
				vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=0;
			}
		}
}

long long C64_8()
{
	long long res=1;
	for(int i=57; i<=64; ++i)
		res*=i;
	printf("%lld\n", res);
	for(int i=2; i<=8; ++i)
		res/=i;
	printf("C64_8=%lld\n", res);
	return res;
}

// =============================
int c[20], n=8, cnt=0;
void print(){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(j == c[i]) cout<<"1 ";
            else cout<<"0 ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void search5(int r){
    if(r == n){
        //print();
        ++cnt;
        return;
    }
    for(int i=0; i<n; ++i){
        c[r] = i;
        int ok = 1;
        for(int j=0; j<r; ++j)
            if(c[r]==c[j] || r-j==c[r]-c[j] || r-j==c[j]-c[r]){
                ok = 0;
                break;
            }
        if(ok) search5(r+1);
    }
}


int main()
{
	{
		C64_8();
	}
	{
		int col[8];
		int cnt=eightQueen(0, col);
		printf("%d %d state\n", cnt, cnt0);
	}
	{
		int tot=0;
		int C[8]={0};
		int n=8;
		search(0, tot, C, n);
		printf("tot1=%d, %d\n", tot, cnt1);
	}
	
	{
		int visit[3][16]={0};
		int tot2=search2(0, visit, 8);
		printf("tot2=%d, %d\n", tot2, cnt2);
	}
	
	{
		int visit[3][16]={0};
		int c[8];
		int tot3=0;
		search3(0, visit, c, 8, tot3);
		printf("tot3=%d, %d\n", tot3, cnt3);
	}
	{
		search5(0);
		printf("cnt=%d\n", cnt);
	}
	
	getchar();
	system("pause");
	return 0;
}