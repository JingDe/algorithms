
// 不使用临时变量，交换两个数
void swap(int &a, int &b)
{
	a = a^b;
	b = b^a; // b^a^b
	a = a^b; // a^b^a
}

void swap2(int &a, int &b){
    b = a - b;
    a = a - b;
    b = a + b;
}


void test()
{
	int a=4;
	//swap(a, a);
	int b=6;
	swap(a, b);
	
}