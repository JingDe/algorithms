#include<stdio.h>
#include<stdlib.h>

void seq1(int left, int right, char curStr[], int curCnt)
{
	if(left<0  ||  right<left)
		return;
	if(left==0  &&  right==0)
	{
		for(int i=0; i<curCnt; ++i)
			printf("%c", curStr[i]); 
		printf("\n");
		return ;
	}
	if(left>0)
	{
		curStr[curCnt]='(';
		seq1(left-1, right, curStr, curCnt+1);	
	}
	if(left<right)
	{
		curStr[curCnt]=')';
		seq1(left, right-1, curStr, curCnt+1); 
	}
}

int main()
{
 	{
		int cnt=3;
		char str[cnt];
	    seq1(cnt, cnt, str, 0); 	  
    }
    system("pause");
 	return 0;
}
 
