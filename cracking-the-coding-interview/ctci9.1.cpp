#include<stdio.h>
#include<algorithm>
#include<utility>
#include<assert.h>
#include<iostream>

void merge(int a[], int sz1, int b[], int sz2)
{
	int last=sz1+sz2-1;
	int i=0, j=0;
	for(i=sz1-1, j=sz2-1; i>=0  &&  j>=0; )
	{
		if(a[i]>b[j])
			a[last--]=a[i--];
		else
			a[last--]=b[j--];
	}
	while(j>=0)
		a[last--]=b[j--];
}

void print(int a[], int sz)
{
	for(int i=0;i<sz; i++)
		printf("%d, ", a[i]);
	printf("\n");
}

void swap(int a[], int i, int j);
void sortFirst(int array[], int j, int end);
void swap(int& a, int &b);

// array[0~(sz1-1)]局部有序，array[sz1~(sz1+sz2-1)]局部有序
void sort_2part(int array[], int sz1, int sz2)
{
	int i=0,j=0;
	for(i=0, j=sz1; i<sz1; )
	{
		if(array[i]<array[j])
		{
			i++;
			continue;
		}
		else
		{
			swap(array, i, j);// 交换i和j位置元素
			i++;
			sortFirst(array, j, sz1+sz2-1);// 将j位置的元素在j开始的序列(j~(sz1+sz2-1))中移动到合适的位置
		}
	}
}

void sort_2part2(int a[], int begin, int mid, int end)
{
	for(int i=begin; i<=mid; ++i)
	{
		if(a[i]>a[mid+1])
		{
			swap(a[i], a[mid+1]);
			for(int j=mid+1; j<end; ++j)
			{
				if(a[j]<=a[j+1])
					break;
				swap(a[j], a[j+1]);
			}
		}
	}
}

void swap(int a[], int i, int j)
{
	std::swap(a[i], a[j]);
}

void swap(int& a, int &b)
{
	a = a^b;
	b = b^a;
	a = a^b;
}

void sortFirst(int array[], int j, int end)
{	
	int ej=array[j];
	int i=0;
	for(i=j+1; i<=end; i++)
	{
		if(array[i]<ej)
			array[i-1]=array[i];
		else
			break;
	}
	assert(i==end+1  ||  array[i]>=ej);
	if(i<=end)
		array[i-1]=ej;
	else if(array[end]<ej)
		array[end]=ej;
	
	printf("sortFirst: ");
	print(array+j, end-j+1);
}

int main()
{
	{
		int a[12]={0,2,5,6};
		int b[6]={1,1,3,4,5,9};
		merge(a, 4, b, 6);
		print(a, 10);
	}
	
	{
		int array[]={1,3,5,7,9,2,4,6};
		print(array, sizeof(array)/sizeof(array[0]));
		sort_2part(array, 5, 3);
		print(array, sizeof(array)/sizeof(array[0]));
	}
	
	{
		int a[10] = {
			8, 9, 11, 15, 17, 1, 3, 5, 12, 18
		};
		sort_2part2(a, 0, 4, 9);
		for(int i=0; i<10; ++i)
			std::cout<<a[i]<<" ";
		return 0;
	}
	return 0;
}