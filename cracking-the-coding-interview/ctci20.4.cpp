#include<iostream>
#include<stdio.h>
#include<cmath>

// 返回十进制表示a中，数组2出现的次数
int number2(int a)
{
	int cnt=0;
	int num=0;
	while(a)
	{
		num=a%10;
		cnt += (num==2) ? 1 : 0;
		a=a/10;
	}
	return cnt;
}

// 从0到n，出现的2的次数
int solve(int n)
{
	int res=0;
	for(int i=0; i<=n; ++i)
		res+=number2(i);
	return res;
}

void test_number2()
{
	int v=122;
	std::cout<<v<<", "<<number2(v)<<std::endl;
	
	v=200;
	std::cout<<v<<", "<<number2(v)<<std::endl;
	
	v=456;
	std::cout<<v<<", "<<number2(v)<<std::endl;	
	
	v=0;
	std::cout<<v<<", "<<number2(v)<<std::endl;
}

 
int solve2(int a)
{
	// 依次判断十进制a的每一位，累加[0, n]范围内、该位出现2的的数字的个数
	// 当某一位数子小于2，[0,n]范围内，该位是2的数字的个数是：高位数字*当前位数
	// 当某一位数字等于2，[0,n]范围内，该位是2的数字的个数是：高位数字*当前位数+(低位数字+1)
	// 当某一位数字大于2，[0,n]范围内，该位是2的数字的个数是：(高位数字+1)*当前位数
	int res=0;
	int aa=a;
	int high=0, cur=0, low=0;
	int pos=0;
	while(aa)
	{
		//high=aa/10;
		high= a/(std::pow(10, (1+pos)));
		
		//cur=aa%10;
		cur= ((int)a/((int)std::pow(10, pos))) % 10; 
		
		low= a%((int)std::pow(10, (pos)));
		
		printf("%d, %d, %d, %d, %d\n", a, pos, high, cur, low);
		
		if(cur<2)
			res+= high * (int)std::pow(10,pos);
		else if(cur==2)
			res+= high * (int)std::pow(10,pos) + (low+1);
		else
			res+= (high+1) * (int)std::pow(10,pos);
		
		++pos;
		aa=aa/10;
	}
	return res;
}

int Count2s(int n){
    int count = 0;
    int factor = 1;
    int low = 0, cur = 0, high = 0;

    while(n/factor != 0){
        low = n - (n/factor) * factor;//低位数字
        cur = (n/factor) % 10;//当前位数字
        high = n / (factor*10);//高位数字
		
		printf("%d, %d, %d, %d, %d\n", n, factor, high, cur, low);

        switch(cur){
        case 0:
        case 1:
            count += high * factor;
            break;
        case 2:
            count += high * factor + low + 1;
            break;
        default:
            count += (high + 1) * factor;
            break;
        }

        factor *= 10;
    }

    return count;
}

int Countis(int n, int i){
    if(i<1 || i>9) return -1;//i只能是1到9

    int count = 0;
    int factor = 1;
    int low = 0, cur = 0, high = 0;

    while(n/factor != 0){
        low = n - (n/factor) * factor;//低位数字
        cur = (n/factor) % 10;//当前位数字
        high = n / (factor*10);//高位数字

        if(cur < i)
            count += high * factor;
        else if(cur == i)
            count += high * factor + low + 1;
        else
            count += (high + 1) * factor;

        factor *= 10;
    }

    return count;
}

void test()
{
	int n=122;
	printf("[0, %d] : %d\n", n, solve(n));
	printf("[0, %d] : %d\n", n, solve2(n));
	printf("[0, %d] : %d\n", n, Count2s(n));
	
	n=300;
	printf("[0, %d] : %d\n", n, solve(n));
	printf("[0, %d] : %d\n", n, solve2(n));
	printf("[0, %d] : %d\n", n, Count2s(n));
}



int main()
{
	test_number2();
	test();
	
	return 0;
}