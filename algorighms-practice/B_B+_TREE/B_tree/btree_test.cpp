
#include"btree.h"
#include<cstdio>


bool operator<(const BTNode<int, int>::RecordType& lhs, const BTNode<int, int>::RecordType& rhs)
{
	return (lhs.key<rhs.key);
}

void test1()
{
	//printf("%d, %d\n", MIN, MAX);
	BTree<int, int> t1;
	t1.Insert(1, 1);
	t1.Print();
	
	t1.Insert(1, 11);
	t1.Print();
	
	t1.Insert(2, 2);
	t1.Print();
	
	t1.Insert(3, 3);
	t1.Print();
	t1.Insert(4, 4);
	t1.Print();
	t1.Insert(5, 5);
	t1.Print();
	t1.Insert(6, 6);
	t1.Print();
	
	t1.Delete(1);
	t1.Print();
	
	t1.Delete(2);
	t1.Print();
	
	
	t1.Insert(7, 7);
	t1.Print();
	t1.Insert(8, 8);
	t1.Print();
	t1.Insert(9, 9);
	t1.Print();
	t1.Insert(10, 10);
	t1.Print();
}

void test2()
{
	printf("=============== test2 ===================\n");
	BTree<int, int> t1(3);
	t1.Insert(1, 1);
	t1.Print();
	t1.Print2();
	
	t1.Insert(1, 11);
	t1.Print();
	
	t1.Insert(2, 2);
	t1.Print();
	
	t1.Insert(3, 3);
	t1.Print();
	t1.Insert(4, 4);
	t1.Print();
	t1.Insert(5, 5);
	t1.Print();
	t1.Insert(6, 6);
	t1.Print();
	
	t1.Insert(7, 7);
	t1.Print();
	t1.Insert(8, 8);
	t1.Print();
	t1.Insert(9, 9);
	t1.Print();
	t1.Insert(10, 10);
	t1.Print();
	t1.Print2();
}

int main()
{
	//test1();
	
	test2();
	
	return 0;
}