#include<stdio.h>

//const int N=2.5*(10^8);
const int N=100;
const int BITS_OF_INT=32;
//const int SHIFT=5;
const int SHIFT=4;
//const int MASK=0x1F;
const int MASK=0xF;

int bitmap[1+N*2/BITS_OF_INT];

// 若一个bit对应一个整数，整数i对应bitmap[i>>SHIFT]的i&MASK位
	// bitmap[i/32]的i%32位
// 若两个bit对应一个整数，整数i对应的两个bit分别是：
// bitmap[i/16]的(i%16)*2位
// bitmap[i/16]的(i%16)*2+1位

void set(int i)
{
	if(bitmap[i>>SHIFT]  &  1<<((i & MASK)*2+1)) // 10 -> 10
		return;
	if(bitmap[i>>SHIFT]  &  1<<((i & MASK)*2)) // 01 -> 10
	{
		bitmap[i>>SHIFT] |= 1<<((i & MASK)*2+1);
		bitmap[i>>SHIFT] &= ~(1<<((i & MASK)*2));
	}
	else // 00 -> 01
	{
		bitmap[i>>SHIFT] |= 1<<((i & MASK)*2);
	}
}

int get(int i)
{
	int value= 0; //(bitmap[i>>SHIFT] )*2 + bitmap[i>>SHIFT];
	
	if(bitmap[i>>SHIFT]  &  1<<((i & MASK)*2) )
		value+=1;
	if(bitmap[i>>SHIFT]  &  1<<((i & MASK)*2+1) )
		value+=1*2;
	return value;
}

void clr(int i)
{
	bitmap[i>>SHIFT] &= ~(1<<((i & MASK)*2));
	bitmap[i>>SHIFT] &= ~(1<<((i & MASK)*2+1));
}

int main()
{
	int i;
	for (i = 0; i < N; i++)
		clr(i);  
	while (scanf("%d", &i) != EOF)
		set(i);
	
	int cnt=0;
	for (i = 0; i < N; i++)
		if (get(i)==1)
		{
			cnt++;
			printf("%d hit %d\n", i, get(i));
		}
	printf("%d\n", cnt);
	return 0;
}

