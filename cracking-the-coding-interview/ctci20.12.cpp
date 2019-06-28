#include<stdio.h>
#include<iostream>

// 给一个NxN的矩阵，矩阵上每个格子中填有一个整数(正，负或0)， 写代码计算子矩阵之和的最大值。

#define MAXN 100
#define INT_MIN 1<<31

int max_sum_of_sub_array(int array[MAXN], int N);

void max_sum_of_sub_matrix(int matrix[MAXN][MAXN], int N, int p[MAXN][MAXN])
{
	int res=INT_MIN;
	// 预处理，求p[i][j]表示matrix[0][0]到matrix[i][j]的部分和

	for(int line=0; line<N; ++line)
	{
		for(int col=0; col<N; ++col)
		{
			if(line==0  &&  col==0)
				p[line][col]=matrix[line][col];
			else if(line==0)
				p[line][col]=p[line][col-1] + matrix[line][col];
			else if(col==0)
				p[line][col]=p[line-1][col]+matrix[line][col];
			else
				p[line][col]=p[line-1][col]+p[line][col-1]-p[line-1][col-1]+matrix[line][col];
			printf("%3d ", p[line][col]);
		}
		printf("\n");
	}
	printf("\n");
	
	for(int l1=0; l1<N; ++l1)
	{
		for(int l2=l1; l2<N; ++l2)
		{
			// 将第l1行到第l2行降维成一维、0到N-1列一维数组
			// 求每一列，l1行到l2行的和
			int array[MAXN];
			for(int col=0; col<N; ++col)
			{
				array[col]= p[l2][col] - p[l2][col-1] - p[l1-1][col] + p[l1-1][col-1];
				//printf("%d, ", array[col]);
			}
			//printf("\n");
			int tmp=max_sum_of_sub_array(array, N);
			//printf("%d 到 %d 行, 一维数组最大子数组和 %d\n", l1, l2, tmp);
			res= tmp>res ? tmp : res;
		}
	}
	printf("%d\n", res);
}

int max_sum_of_sub_array(int array[MAXN], int N)
{
	int res=INT_MIN;
	int cur=INT_MIN;
	for(int i=0; i<N; ++i)
	{
		if(cur==INT_MIN)
			cur=array[i];
		else if(cur<0)
			cur=array[i];
		else
			cur=cur+array[i];
		if(cur>res)
			res=cur;
	}
	return res;
}

void test()
{
	freopen("20.12.in", "r", stdin);
	
	int matrix[MAXN][MAXN];
	int p[MAXN][MAXN];
	int n;
    std::cin>>n;
    for(int i=0; i<n; ++i)//元素存储从1开始
        for(int j=0; j<n; ++j)
            std::cin>>matrix[i][j];
    max_sum_of_sub_matrix(matrix, n, p);
    fclose(stdin);
}

int main()
{
	test();
	
	return 0;
}