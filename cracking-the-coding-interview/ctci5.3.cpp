
int32_t bit1cnt(int32_t a)
{
	int cnt=0;
	for(int32_t i=0; i<32; ++i)
		if(a & (1<<i))
			cnt++;
	return cnt;
}

bool samebitcnt(int32_t a, int32_t b)
{
	if(bit1cnt(a)==bit1cnt(b))
		return true;
	return false;
}

int32_t next(int32_t x)
{
	int32_t INT_MAX=~(1<<31);
	for(int32_t a=x+1; a<=INT_MAX ; ++a)
		if(samebitcnt(a, x))
			return a;
	return x;
}

int next(int x)
{
	int max_int=~(1<<31);
	int num=count_one(x);
	// 0或者-1不存在
	if(num==0  ||  x==-1)
		return -1;
	for(++x; count_one(x) != num && x < max_int; ++x);
    if(count_one(x) == num) 
		return x;
    return -1;
}

int32_t prev(int32_t x)
{
	int32_t INT_MIN=1<<31;
	for(int32_t a=x-1; a>=INT_MIN; --a)
		if(samebitcnt(a, x))
			return a;
	return x;
}

int prev(int x)
{
	int min_int=1<<31;
	int num=count_one(x);
	// x为0或者-1
	if(num==0  ||  x==-1)
		return -1;
	for(--x; count_one(x) != num && x > min_int; --x);
    if(count_one(x) == num) return x;
    return -1;	
}

int count_one(int x){
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));
    return x;
}

// ================
int32_t next2(int32_t x)
{
	for(int p1=0; p1<32; ++p1)
		if(x  &  (1<<p1))
			break;
	if(p1==32) // x==0
		return -1;
	
	for(int p2=p1; p2<32; ++p2)
		if(!(x  &  (1<<p2)))
			break;
	if(p2==31) // x是01....形式
		return -1;
	if(p2==32) // x是 111...形式
	{
		// 0~p1-1是0,  p1~31是1，一共31-p1+1个1
		x= (1<<(32-p1)) -1;
		return x;
	}
	else // x是其他 ..01..1...形式
	{
		// 将x的p2位置1，右边置0。右边的1原来个数为c(p2-p1)，则最低c-1位置1
		x|=(1<<p2);
		x>>p2; x<<p2;//将p2右边比特全部置0
		
		x|=(1<<(p2-p1-1))-1;
		return x;
	}
}





