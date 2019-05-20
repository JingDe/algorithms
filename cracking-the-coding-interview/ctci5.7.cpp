#include<string>


// fetch1(int i, j)// 取出A[i]的第j位

// fetch2(int i, j)// 取出A的第j位


int solve1(int a[], int len, int n)
{
	int num=0;
	for(int i=0; i<n; ++i)
		num = num ^ i;
	for(int i=0; i<len; ++i)
		num = num ^ a[i];
	return num;
}

// 数组被表示成0/1字符串，返回arr[i]的第j位
int fetch1(std::string s, int i, int j)
{
	int pos=i*32+j;
	if(s[pos]=='1')
		return 1;
	else
		return 0;
}

// 求arr[i]
int getEle(std::string s, int i)
{
	int res=0;
	for(int j=0; j<32; ++j)
	{
		res = res | (fetch1(s, i, j) << j);
	}
	return res;
}

int solve2(std::string arr, int n)
{
	int num=0;
	for(int i=0; i<n; ++i)
		num = num ^ i;
	
	assert(arr.size()%32==0);
	int len=arr.size()/32;
	for(int i=0; i<len; ++i)
	{
		int ele=getEle(arr, i);
		num = num ^ ele;
	}
	return num;
}

int main()
{
	
	
	return 0;
}