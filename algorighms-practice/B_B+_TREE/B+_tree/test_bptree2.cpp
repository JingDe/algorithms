
#include<stdio.h>

#include"bptree2.h"

typedef int keytype;
typedef int valuetype;


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
	printf("\n===============================\n");
	BPlusTree<keytype, valuetype> bpt1(4, 3);
	bpt1.Print();
	
	bpt1.Insert(1, 1);
	bpt1.Insert(2, 2);	
	bpt1.Insert(3, 3);
	bpt1.Insert(4, 4);
	bpt1.Insert(5, 5);
	bpt1.Insert(6, 6);
	bpt1.Print();
	
	bpt1.Delete(9);
	bpt1.Delete(1);
	bpt1.Print();
	bpt1.Delete(4);
	bpt1.Print();
	
	bpt1.Insert(7, 7);
	bpt1.Print();
	bpt1.Insert(8, 8);
	bpt1.Print();
	
	bpt1.Delete(8);
	bpt1.Print();
	
	bpt1.Insert(9, 9);
	bpt1.Print();
	bpt1.Insert(10, 10);
	bpt1.Print();
}

int main()
{
	
	//test_insert();
	test_delete();
	
	return 0;
}