#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

double multi(double a, double b)
{
	return a*b;
}

void print_double(double f)
{
	printf("%f ", f);
}

void test_ptrfun()
{
	std::vector<double> a={0, 1.2, 30, 8.8};
	std::for_each(a.begin(), a.end(), std::ptr_fun(print_double));
}

void test_bind1st()
{
	std::vector<double> a={0, 1.2, 30, 8.8};
	std::vector<double> r(a.size());
	double pi=3.14;
	
	//std::transform(a.begin(), a.end(), r.begin(), std::bind1st(std::ptr_fun(multi), pi));// 普通函数不可适配
	std::transform(a.begin(), a.end(), r.begin(), std::bind2nd(std::ptr_fun(multi), pi));
	//std::transform(a.begin(), a.end(), r.begin(), std::bind1st(std::multiplies<double>(), pi));
	
	for(size_t n = 0; n < a.size(); ++n)
        std::cout << a[n] << " deg = " << r[n] << " rad\n";
}

int main()
{
	test_bind1st();
	
	test_ptrfun();
	
	return 0;
}