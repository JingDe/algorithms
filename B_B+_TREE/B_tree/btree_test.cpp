
#include"btree.h"
#include<cstdio>

int main()
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
	
	return 0;
}