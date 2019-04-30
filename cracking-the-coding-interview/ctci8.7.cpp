#include<stdio.h>
#include<stdlib.h>

//int cnt=0;

// enum coin{
	// C1=25,
	// C2=10,
	// C3=5,
	// C4=1,
// };

// 
void dfsSearch(int curSum, int target, int coin[], int len, int *res)
{
	if(curSum>target)
		return;
	if(curSum==target)
	{
		//++cnt;
		++(*res);
		return;
	}
	for(int i=0; i<len; ++i)
		dfsSearch(curSum+coin[i], target, coin, len, res);
}

void dfsSearch1(int curSum, int curMax, int target, int coin[], int len, int *res)
{
	if(curSum>target)
		return;
	if(curSum==target)
	{
		//++cnt;
		++(*res);
		return;
	}
	for(int i=0; i<len; ++i)
		if(curMax==-1  ||  coin[i]<=curMax)
			dfsSearch1(curSum+coin[i], coin[i], target, coin, len, res);
			//dfsSearch(curSum+coin[i], std::min(curMax,coin[i]), target, coin, len, res);
}

int dfsSearch2(int curSum, int curMax, int target, int coin[], int len)
{
	int res=0;
	if(curSum>target)
		return 0;
	if(curSum==target)
	{
		return 1;
	}
	for(int i=0; i<len; ++i)
		if(curMax==-1  ||  coin[i]<=curMax)
			res+=dfsSearch2(curSum+coin[i], coin[i], target, coin, len);
	return res;
}

int dfsSearch3(int target, int coin)
{
	int res=0;
	int nextCoin=coin;
	if(coin==25)
		nextCoin=10;
	if(coin==10)
		nextCoin=5;
	if(coin==5)
		nextCoin=1;
	if(coin==1)
		return 1;
	for(int i=0; i*coin<=target; ++i)
		res+=dfsSearch3(target-i*coin, nextCoin);
	return res;
}

int make_change(int n, int denom){
    int next_denom = 0;
    switch(denom){
    case 25:
        next_denom = 10;
        break;
    case 10:
        next_denom = 5;
        break;
    case 5:
        next_denom = 1;
        break;
    case 1:
        return 1;
    }
    int ways = 0;
    for(int i=0; i*denom<=n; ++i)
        ways += make_change(n-i*denom, next_denom);
    return ways;
}

int main()
{
	int target=34;
	{
		int coin[4]={25, 10, 5, 1};
		int len=sizeof(coin)/sizeof(coin[0]);
		int res=0;
		dfsSearch(0, target, coin, len, &res);
		printf("%d\n", res);
	}
	
	{
		int coin[4]={25, 10, 5, 1};
		int len=sizeof(coin)/sizeof(coin[0]);
		int res=0;
		dfsSearch1(0, -1, target, coin, len, &res);
		printf("%d\n", res);
	}
	
	{
		int coin[4]={25, 10, 5, 1};
		int len=sizeof(coin)/sizeof(coin[0]);
		int res=dfsSearch2(0, -1, target, coin, len);
		printf("%d\n", res);
	}
	
	{
		int coin[4]={25, 10, 5, 1};
		int len=sizeof(coin)/sizeof(coin[0]);
		int res=dfsSearch3(target, 25);
		printf("%d\n", res);
	}
	
	{
		int coin[4]={25, 10, 5, 1};
		int len=sizeof(coin)/sizeof(coin[0]);
		int res=make_change(0, 25);
		printf("%d\n", res);
	}
	
	getchar();
	system("pause");
	return 0;
}