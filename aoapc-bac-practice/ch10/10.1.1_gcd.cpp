
// gcd算法
int gcd_rec(int a, int b) 
{
	if(a==0)
		return b;
	else if(b==0)
		return a;
	if(a<b)
		return gcd_rec(a, b % a);
	else
		return gcd_rec(b, a % b);
}

int gcd(int a, int b)
{
	int tmp;
	if(a<b)
	{
		tmp=a;
		a=b;
		b=tmp;
	}
	while(b)
	{
		tmp=a;
		a=b;
		b=tmp % b;
	}
	return a;
}

int lcm(int a, int b) 
{
	return (a/gcd(a, b))*b;
}


// vec 依次存储 X1 X2 ... Xk
// 判断： X2能不能  被 X1*X3*..*Xk 整除 
bool match(std::vector<int> vec) 
{
	assert(vec.size()>=2);
	int x2=vec[1];

	for(int i=0; i<vec.size()  &&  i!=1; i++)
	{
		x2=x2/gcd(x2, vec[i]);
		if(x2==1)
			return true;
	}
	return x2==1  ?  true  :  false;
}


