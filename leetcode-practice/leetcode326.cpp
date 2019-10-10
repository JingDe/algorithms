

// 方法一：循环迭代
bool isPowerOfThree(int n) {
	while(n%3==0)
	{
		n=n/3;
	}
	return n==1;
}

// 递归
bool isPowerOfThree(int n)
{
	if(n==0)
		return false;
	if(n==1)
        return true;
	return n%3==0  &&  isPowerOfThree(n/3);
}


// 方法二：基准转换
bool isPowerOfThree(int n) 
{
	
}

// 方法三：运算法
bool isPowerOfThree(int n) 
{
	double i=std::log(n) / std::log(3);
	double epsilon=pow(10, -6);
	printf("%20.10f\n", epsilon);
	//return (i+epsilon) % 1 <= 2*epsilon;
	return std::fmod(i+epsilon, (double)1) <= 2*epsilon;
}

bool isPowerOfThree(int n) 
{
	return fmod(log10(n)/log10(3), 1)==0;
}

// 方法四：整数限制
bool isPowerOfThree(int n) 
{
	if(n<=0)
		return false;
	int max=pow(3, 19);
	return max%n==0;
}