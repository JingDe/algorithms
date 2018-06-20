
void gcd(int a, int b, int& d, int& x, int& y)
{
	if(!b)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		gcd(b, a % b, d, y, x);
		y -= x*(a/b);
	}
}
