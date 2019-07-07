

// 测试 string()构造函数 VS std::to_string()


void test()
{
	char a='a';
	char b='b';
	
	string s1=std::to_string(a);
	// 等价于std::to_string(int(a));
	
}