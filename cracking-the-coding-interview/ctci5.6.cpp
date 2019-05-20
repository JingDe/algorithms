
// 交换一个整数二进制表示中的奇数位和偶数位
int exchange(int a)
{
	// 提取奇数位和偶数位，再组合
	return ((a &  0x55555555) << 1)  |  ((a & 0xAAAAAAAA) >>1);
}

int exchange2(int a)
{
	return ((a &  0x55555555) << 1)  |  ((a>>1) & 0x55555555);
}

int exchange3(int a)
{
	return ((a <<1) &  0xAAAAAAAA)  |  ((a & 0xAAAAAAAA) >>1);
}