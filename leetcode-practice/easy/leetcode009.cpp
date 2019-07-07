#include<stdio.h>
#include<stdint.h>
#include<climits>


void test()
{
	int intmax=INT_MAX; 
	// int32_t i32max = ~(1<<31);
	// uint32_t ui32max = ~0;
	printf("%d\n", intmax);// 2147483647
}

class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0)
			return false;
		if(x==0)
			return true;
		
		int intmax=INT_MAX;
		
		int x2=x;
		int xr=0;
		while(x2)
		{
			int rightest=x2%10;
			x2=x2/10;
			
			if((intmax-rightest)/10 <  xr)
				return false;
			
			xr=xr*10+rightest;			
		}
		return (xr==x) ?  true  :  false;
    }
	
	bool isPalindrome2(int x) {
		if(x<0)
			return false;
		if(x==0)
			return true;
		if(x%10==0)
			return false;
		
		int xr=0;
		while(xr<x)
		{
			int lastDigit=x%10;
			xr=xr*10+lastDigit;
			x=x/10;
			
			// if(xr==x)
				// return true;
		}
		if(xr==x  ||  xr/10==x)
			return true;
		return false;
	}
	
	bool isPalindrome3(int x) {
		// 当x最后一位是0，只有0是回文数，其他如120/30都不是
		if(x<0  ||  (x%10==0  &&  x!=0)
			return false;
		
		int revertedNumber=0;
		while(x>revertedNumber)
		{
			revertedNumber = revertedNumber*10 + x%10;
			x=x/10;
		}
		
		return x==revertedNumber  ||  x==revertedNumber/10;
	}
};

int main()
{
	test();
	
	return true;
}