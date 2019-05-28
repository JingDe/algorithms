
#include<string>
#include<algorithm>
#include<list>
#include<functional>


class MinDist{
public:
	std::string first;
	int second;
	
	MinDist():first(), second() {}
	MinDist(const std::string& w, int d):first(w),second(d){}
	
	bool equal_min_dist(const std::string & w)
	{
		if(first==w)
			return true;
		return false;
	}
	
	MinDist& operator=(const MinDist& rhs)
	{
		first=rhs.first;
		second=rhs.second;
		return *this;
	}
	
};

bool operator==(const MinDist& lhs, const MinDist& rhs)
{
	return lhs.first==rhs.first  &&  lhs.second==rhs.second;
}


bool compare_min_dist(const MinDist& md, const std::string& s)
{
	if(md.first == s)
		return true;
	return false;
}
bool compare3_min_dist(MinDist md, const std::string& s)
{
	if(md.first == s)
		return true;
	return false;
}
bool compare4_min_dist(MinDist& md, const std::string& s)
{
	if(md.first == s)
		return true;
	return false;
}

bool compare2_min_dist(MinDist* md, const std::string& s)
{
	if(md->first == s)
		return true;
	return false;
}


//class Cmp_mindist : public std::binary_function<const Widget&, const std::string&, bool>
class Cmp_mindist : public std::binary_function<MinDist, std::string, bool>
{
public:
	bool operator()(const MinDist& w, const std::string& s) const
	{
		if(w.first == s)
			return true;
		return false;
	}
};

void test()
{
	std::list<MinDist> hl;
	std::string wordab="hello";
	hl.push_back(MinDist("hello", 123));
	hl.push_back(MinDist("music", 202));
	hl.push_back(MinDist("iphone", 300));
	std::list<MinDist>::iterator it2=hl.end();
	
	std::list<MinDist*> h2;
	MinDist a("good", 900);
	MinDist b("bad", 800);
	MinDist c("hello", 120);
	h2.push_back(&a);
	h2.push_back(&b);
	h2.push_back(&c);
	std::list<MinDist*>::iterator it=h2.end();
	
		
	//非成员函数
	//it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(std::ptr_fun(compare_min_dist), wordab));
	it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(std::ptr_fun(compare3_min_dist), wordab));
	
	//成员函数
	it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(std::mem_fun_ref(MinDist::equal_min_dist), wordab));

	it=std::find_if(h2.begin(), h2.end(), std::bind2nd(std::mem_fun(MinDist::equal_min_dist), wordab));
	
	//判别式类
	it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(Cmp_mindist(), wordab));
	
	//std::function
	std::function<bool(const MinDist&)> f=std::bind(compare_min_dist, std::placeholders::_1, wordab);
	it2=std::find_if(hl.begin(), hl.end(), f);
	
	std::function<bool(MinDist*)> ff = std::bind(compare2_min_dist, std::placeholders::_1, wordab);
	it=std::find_if(h2.begin(), h2.end(), ff);
	
	//lambda表达式
	it2=std::find_if(hl.begin(), hl.end(), 
		[&](const MinDist& md) -> bool {
				if(md.first == wordab)
					return true;
				return false;
		});		
		
	it=std::find_if(h2.begin(), h2.end(), 
		[=, &wordab](MinDist* md) -> bool {
				if(md->first == wordab)
					return true;
				return false;
		});
	
	
	
	if(it2!=hl.end())
		printf("%s, %d\n", it2->first.c_str(), it2->second);
	
	if(it!=h2.end())
		printf("%s, %d\n", (*it)->first.c_str(), (*it)->second);
}


int main()
{
	test();
	
	return 0;
}