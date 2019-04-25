#include<iostream>


// 逆时针旋转矩阵a[N][N]
void leftRotate(int a[][4], int n)
{
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<i; ++j)
			std::swap(a[i][j], a[j][i]);
	}
	
	for(int row=0; row<n/2; ++row)
		for(int col=0; col<n; ++col)
			std::swap(a[row][col], a[n-1-row][col]);
}

int main()
{
	{
		int a[4][4]={
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
		};
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j)
				std::cout<<a[i][j]<<" ";
			std::cout<<std::endl;
		}
		
		leftRotate(a, 4);
		for(int i=0; i<4; ++i){
			for(int j=0; j<4; ++j)
				std::cout<<a[i][j]<<" ";
			std::cout<<std::endl;
		}
	}
	return 0;
}