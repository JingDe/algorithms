#include<iostream>
#include<stdio.h>
#include<string.h>


void test_bool()
{
	bool b_uninit;
	printf("%d\n", b_uninit);
	std::cout<<std::boolalpha<<b_uninit<<std::noboolalpha<<b_uninit<<"\t"<<std::endl;
}

void test_memset()
{
	int a[3][4];
	printf("sizeof a[][]=%d, sizeof a[]=%d, sizeof a[][]=%d, sizeof int=%d\n", sizeof(a), sizeof(a[0]), sizeof(a[0][0]), sizeof(int));
	memset(a, 0, sizeof(a)); // 复制0（int转换到unsigned char)到a指向的连续多少个字节
	//memset(a, 0, 3*4*sizeof(int));
	
	int **b=new int*[3];
	printf("sizeof b[][]=%d, sizeof int**=%d, sizeof b[]=%d, sizeof int*=%d, sizeof void*=%d\n", sizeof(b), sizeof(int**), sizeof(b[0]), sizeof(int*), sizeof(void*));
	//memset(b, 0, sizeof(int*)*3);
	memset(b, 0, sizeof(b[0])*3);
	for(int i=0; i<3; i++)
	{
		b[i]=new int[4];
		printf("sizeof b[][]=%d, sizeof b[]=%d\n", sizeof(b[i][0]), sizeof(b[i]));
		memset(b[i], 0, sizeof(b[i][0])*4);
	}	
}

void test_memset_minus1()
{
	int array[10]={0};
	memset(array, -1, sizeof(array));
	for(int i=0; i<sizeof(array)/sizeof(array[0]); i++)
		printf("%d, %c\n", array[i], array[i]);
	printf("\n");
	
	char c=(char)-1;
	printf("c=%c, %d\n", c, (int)c);
	
	char c2=static_cast<unsigned char>(c);
	printf("c2= %c, %d\n", c, (int)c);
	printf("c2-'a'=%d", c2-'a');
	
	int i=c2;
	printf("%d\n", i);
	
	unsigned int i2=c2;
	printf("%u\n", i2);
}


int main()
{
	test_bool();
	
	test_memset();
	test_memset_minus1();
	
	return 0;
}