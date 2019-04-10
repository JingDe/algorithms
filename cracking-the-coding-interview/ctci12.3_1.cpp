#include<stdio.h>


#ifdef DEBUG
#defind LOG_DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG
#endif

int main()
{
	const char fileName[]="input12.3.txt";
	
 	// int fd=open(fileName, O_RDONLY); // O_WRONLY O_RDWR
	// int fd=open(fileName, O_RDONLY | O_CREAT, S_IRWXU/*00700*/); // 实际访问权限(mode & ~进程umask)
	// read write
	
	// FILE* f=fopen(fileName, r);
	// FILE* f=fdopen(fd, r);
	// FILE* stream=NULL; 
	// FILE* f=freopen(fileName, r, stream); // 修改文件关联到流stream，通常是stderr stdin stdout 
	// fscanf
	
	FILE* f=freopen(fileName, "r", stdin);
	
	int bits_in_a_int=sizeof(int)*8;
	int int_array_len=0xFFFFFFFF/bits_in_a_int; // int数组长度
	int* array=new int[int_array_len];
	
	int v;
	while(scanf("%d", &v)!=EOF)
	{
		LOG_DEBUG("scanf get %d\n", v);
		array[v/bits_in_a_int] |= 1 << (v%bits_in_a_int);
	}
	
	bool found=false;
	int res=-1;
	for(int i=0; i<int_array_len; i++)
	{
		for(int j=0; j<bits_in_a_int; j++)
		{
			if(!(array[i] & (1<<j)))
			{
				res=i*bits_in_a_int+j;
				found=true;
				break;
			}
		}
		if(found)
			break;
	}
	delete array;
	
	printf("%d\n", res);
	
	return 0;
}