
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


int main()
{
	test1();
	
	
	return 0;
}