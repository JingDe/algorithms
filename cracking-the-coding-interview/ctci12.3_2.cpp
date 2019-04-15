
#include<stdio.h>
#include<math.h>
#include<string.h>

#ifdef DEBUG
#defind LOG_DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG
#endif

const char* file=NULL;

int get_int_cnt_per_block()
{
	float cnt=10*10^20*8/32; 
	int res=floor(cnt);
	printf("%f %d %d\n", cnt, (int)cnt, res);
	return res;
}

void get_block_stat(int* blockStat, int size, int blockLen)
{
	FILE* f=freopen(file, "r", stdin);
	int v=0;
	while(scanf("%d", &v)!=EOF)
	{
		LOG_DEBUG("scanf get %d\n", v);
		blockStat[v/blockLen]++;
	}
	//fclose(stdin);
	
	for(int i=0; i<size; i++)
	{
		printf("blockStat[%d]=%d\n", i, blockStat[i]);
	}
}

int get_res_in_block(int blockStart, int blockLen) // 遍历文件，查找[blockStart, blockEnd)范围内第一个缺失整数返回
{
	int blockEnd=blockStart+blockLen;
	FILE* f=freopen(file, "r", stdin);
	
	int bits_in_a_int=sizeof(int)*8;
	int int_array_len=ceil(blockLen/bits_in_a_int); // int数组长度
	printf("blockLen=%d, need int_array_len=%d\n", blockLen, int_array_len);
	
	int* bitmap=new int[int_array_len];
	
	int v;
	while(scanf("%d", &v)!=EOF)
	{
		LOG_DEBUG("scanf get %d\n", v);
		if(v>=blockStart  &&  v<blockStart+blockLen)
			bitmap[(v-blockStart)/bits_in_a_int] |= 1 << ((v-blockStart)%bits_in_a_int);
	}
	//fclose(f);
	fclose(stdin);
	
	bool found=false;
	int res=-1;
	for(int i=0; i<int_array_len; i++)
	{
		for(int j=0; j<bits_in_a_int; j++)
		{
			if(!(bitmap[i] & (1<<j)))
			{
				res=i*bits_in_a_int+j+blockStart;
				found=true;
				break;
			}
		}
		if(found)
			break;
	}
	
	delete[] bitmap;
	
	return res;
}

int main()
{
	const char fileName[]="input12.3.txt";
	file=fileName;
	
	int blockLen=get_int_cnt_per_block(); // 10MB 最多存储的整数个数
	int blockCnt=(2^32)/blockLen;
	printf("use %d block, each count %d int\n", blockCnt, blockLen);
	int* blockStat=new int[blockCnt]; // blockStat[i]将统计第i个块的整数个数
	memset(blockStat, 0, blockCnt);
	get_block_stat(blockStat, blockCnt, blockLen);
	
	int i=0;
	for(i=0; i<blockCnt; i++)
	{
		if(blockStat[i]<blockLen)
			break;
	}
	delete[] blockStat;
	
	int blockStart=i*blockLen;
	int res=get_res_in_block(blockStart, blockLen);
	printf("%d\n", res);
	
	return 0;
}

