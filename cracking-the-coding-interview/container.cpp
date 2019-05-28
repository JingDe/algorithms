
#include<vector>
#include<stdio.h>

void print(const std::vector<int>& v)
{
	for(int i=0; i<v.size(); ++i)
		printf("%d ", v[i]);
	printf("\n");
}

// 测试 容器对象的引用
void test1()
{
	std::vector<int> vec{1, 2, 3};
	
	std::vector<int>& v=vec;
	v[0]=4;
	
	print(vec);
}



int main()
{
	test1();
	
	return 0;
}