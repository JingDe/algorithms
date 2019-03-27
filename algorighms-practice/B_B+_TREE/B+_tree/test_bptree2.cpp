
#include<stdio.h>
#include<vector>
#include"bptree2.h"

typedef int keytype;
typedef int valuetype;

void print(const std::vector<int>& vec);

void test1()
{
	BPlusTree<keytype, valuetype> bpt1;
	BPlusTree<keytype, valuetype> bpt2(200, 20);
	
	bpt1.Print();
	bpt2.Print();
}

void test_insert()
{
	printf("\n===============================\n");
	BPlusTree<keytype, valuetype> bpt1(4, 3);
	bpt1.Print();
	
	bpt1.Insert(1, 1);
	bpt1.Print();
	bpt1.Insert(2, 2);
	bpt1.Print();
	
	bpt1.Insert(3, 3);
	bpt1.Print();
	bpt1.Insert(4, 4);
	bpt1.Print();
	bpt1.Insert(5, 5);
	bpt1.Print();
	bpt1.Insert(6, 6);
	bpt1.Print();
	
	bpt1.Insert(7, 7);
	bpt1.Print();
	bpt1.Insert(8, 8);
	bpt1.Print();
	bpt1.Insert(9, 9);
	bpt1.Print();
	bpt1.Insert(10, 10);
	bpt1.Print();
}

void test_delete()
{
	printf("\n================test_delete===============\n");
	BPlusTree<keytype, valuetype> bpt1(4, 3);	
	bpt1.Insert(1, 1);
	bpt1.Insert(2, 2);	
	bpt1.Insert(3, 3);
	bpt1.Insert(4, 4);
	bpt1.Print();
	bpt1.Insert(5, 5);
	bpt1.Print();
	bpt1.Insert(6, 6);
	bpt1.Print();		
	bpt1.Insert(7, 7);
	bpt1.Print();
	bpt1.Insert(8, 8);
	bpt1.Print();
	bpt1.Insert(9, 9);
	bpt1.Print();
	bpt1.Insert(10, 10);
	bpt1.Print();
	
	bpt1.Delete(1);
	bpt1.Print();
	bpt1.Delete(2);
	bpt1.Print();
	bpt1.Delete(3);
	bpt1.Print();		
	bpt1.Delete(4);
	bpt1.Print();
	bpt1.Delete(5);
	bpt1.Print();
	bpt1.Delete(6);
	bpt1.Print();
	bpt1.Delete(8);
	bpt1.Print();
	bpt1.Delete(9);
	bpt1.Print();
}


void test_search()
{
	printf("\n================test_search===============\n");
	BPlusTree<keytype, valuetype> bpt1(4, 3);	
	bpt1.Insert(1, 1);
	bpt1.Insert(2, 2);	
	bpt1.Insert(3, 3);
	bpt1.Insert(4, 4);
	bpt1.Insert(5, 5);
	bpt1.Insert(6, 6);
	bpt1.Insert(7, 7);
	bpt1.Insert(8, 8);
	bpt1.Insert(9, 9);
	bpt1.Insert(10, 10);
	bpt1.Print();
	
	int value=-1;
	bool ret=bpt1.Get(5, &value);
	printf("查找%d，结果%s, %d\n", 5, ret ? "成功" : "失败", value);
	bpt1.Get(6, &value);
	printf("查找%d，结果%s, %d\n", 6, ret ? "成功" : "失败", value);
	
	std::vector<int> values;
	if(bpt1.RangeSearch(3, 100, values))
	{
		print(values);
	}
}

void print(const std::vector<int>& vec)
{
	for(std::vector<int>::const_iterator it=vec.begin(); it!=vec.end(); it++)
		printf("%d, ", *it);
	printf("\n");
}

int main()
{
	
	//test_insert();
	//test_delete();
	test_search();
	
	return 0;
}