
#include<iostream>
#include<vector>
#include<algorithm>
#include<list>

void print(const std::vector<int>& points)
{
	for(std::vector<int>::const_iterator it=points.begin(); it!=points.end(); it++)
		std::cout<<*it<<"  ";
	std::cout<<std::endl;
}

void permutation1()
{
	std::vector<int> points={1,2,2,3};
	
	int i=0;
	do{
		std::cout<<i++<<std::endl;
		print(points);		
	}
	while(std::next_permutation(points.begin(), points.end()));
}

void print(const std::vector<std::vector<int> >& points)
{
	for(std::vector<std::vector<int> >::const_iterator it=points.begin(); it!=points.end(); it++)
		std::cout<<"("<<(*it)[0]<<","<<(*it)[1]<<")  ";
	std::cout<<std::endl;
}

bool equal(const std::vector<int> &v1, const std::vector<int> &v2)
{
	if(v1[0]==v2[0]  &&  v1[1]==v2[1])
		return true;
	return false;
}

void permutation2(int n, std::vector<std::vector<int> >& current, const std::vector<std::vector<int> >& points, int cur)
{
	if(cur==n)
		print(current);
	else
	{
		for(std::vector<std::vector<int> >::const_iterator it=points.begin(); it!=points.end(); ++it)
		{
			int ok=1;
			for(std::vector<std::vector<int> >::iterator it2=current.begin(); it2!=current.end(); ++it2)
			{
				if(equal(*it, *it2))
					ok=0;
			}
			if(ok)
			{
				current.push_back(*it);
				permutation2(n, current, points, cur+1);
				current.pop_back();
			}
		}
	}
}

void test_permutation2()
{
	
	std::vector<std::vector<int> > current;
	//std::vector<std::vector<int> > points{p1, p2, p3, p4};
	std::vector<std::vector<int> > points{{1,1}, {1,2}, {1,0}, {0,1}};
	
	std::sort(points.begin(), points.end(), [](std::vector<int> a, std::vector<int> b){
			return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		});
	print(points);
	permutation2(4, current, points, 0);
}

// 可重集排列 
void permutation3(int n, std::vector<std::vector<int> >& current, const std::vector<std::vector<int> >& points, int cur)
{
	if(cur==n)
		print(current);
	else 
	{
		for(std::vector<std::vector<int> >::const_iterator it=points.begin(); it!=points.end(); ++it) // 依次考察points中所有元素 
		{
			int c1=0; 
			int c2=0;
			
			for(std::vector<std::vector<int> >::const_iterator it3=points.begin(); it3!=points.end(); ++it3) 
				if(equal(*it, *it3))
					c1++;
						// *it在points中的个数 : c1
			for(std::vector<std::vector<int> >::iterator it2=current.begin(); it2!=current.end(); ++it2) // 对照current中的元素 
			{
				if(equal(*it, *it2))
					c2++; // *it在current中的个数 : c2
			}
			if(c1>c2)
			{
				current.push_back(*it);
				permutation2(n, current, points, cur+1);
				current.pop_back();
			}
		}
	}
}


int main()
{
	test_permutation2();
	
	return 0;
}
