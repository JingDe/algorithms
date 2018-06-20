
// 散列函数
// TableSize必须是素数
// 1, 当key是整数，直接key % TableSize
// 2, 当key是字符串，
// 2.1, 计算key的每个字符的ASCII值之和，% TableSize
		// 当TableSize太大，不能均匀分布
// 2.2，计算key的3个字符的27进制的十进制值：key[0]+key[1]*27+key[2]*27*27，% TableSize
		// 英文单词的字母不是随机的
int hash(const string& key, int tableSize)
{
	return (key[0]+27*key[1]+729*key[2]) % tableSize;
}

// 2.3, 计算所有key的37进制的十进制值
		// 当key较长，可以只计算部分长度
		// 或者只计算奇数或偶数位
int hash(const string& key, int tableSize)
{
	int hashVal=0;
	
	int sz=key.size();
	for(int i=0; i<sz; i++)
	{
		hashVal=hashVal*37+key[sz-i-1];
	}
	hashVal=hashVal % tableSize;
	if(hashVal<0)
		hashVal+=tableSize;
	return hashVal;
}