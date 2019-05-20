
int bit1cnt(int a)
{
	int cnt=0;
	int sz=sizeof(a)*8;
	for(int i=0; i<sz; ++i)
		if( a  &  (1<<sz) )
			++cnt;
	return cnt;
}

int changeCnt(int a, int b)
{
	int c= a ^ b;
	return bit1cnt(c);
}


