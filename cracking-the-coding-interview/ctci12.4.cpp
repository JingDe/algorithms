#include<vector>
#include<stdio.h>
#include<string.h>

// 内存限制 4KB

// 测试x的pos位是否设置1
bool test_bit(int x, int pos)
{
	if(x  &  1<<pos )
		return true;
	else
		return false;
}

void set_bit(int& x, int pos)
{
	x = x | (1<<pos);
}

void clear_bit(int& x, int pos)
{
	x = x & ~(1<<pos);
}

void print(std::vector<int> vec)
{
	for(int i=0; i<vec.size(); ++i)
		printf("%d ", vec[i]);
	printf(", (%d)\n", vec.size());
}

// 打印arr数组中重复元素
std::vector<int> getDuplicate(std::vector<int> arr)
{
	std::vector<int> res;
	// 32000bit的数组
	int cap=sizeof(int)*8;
	int sz=32000/cap;
	int bm[sz];
	memset(bm, 0, sizeof(bm));
	
	for(int i=0; i<arr.size(); ++i)
	{
		int data=arr[i];
		// data对应bm中的bit：bm[cnt]的第pos位
		int cnt= (data-1)/cap;
		int pos= (data-1)%cap;
		if(test_bit(bm[cnt], pos))
			res.push_back(data);
		else
			set_bit(bm[cnt], pos);
	}
	return res;
}

void solve()
{
	int a[] = {
        1,2,3,4,5,32000,7,8,9,10,11,1,2,13,15,16,32000,11,5,8
    };
	int sz=sizeof(a)/sizeof(*a);
	std::vector<int> vec;
	vec.reserve(sz);
	for(int i=0; i<sz; ++i)
		vec.push_back(a[i]);
	
	std::vector<int> res=getDuplicate(vec);
	print(res);
}

int main()
{
	solve();
	
	return 0;
}