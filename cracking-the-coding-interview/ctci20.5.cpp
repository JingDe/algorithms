
#include<stdio.h>
#include<string>
#include<vector>
#include<list>
#include<map>
#include<cmath>
#include<algorithm>
#include<utility>
#include<functional>

const static int INT_MAX=~(1<<31);

extern unsigned int stringHashFunction(std::string s);

int shortest_distance(std::vector<std::string> file, std::string worda, std::string wordb)
{
	int pa=-1, pb=-1;
	int min=INT_MAX;
	for(int i=0; i<file.size(); ++i)
	{
		if(file[i]==worda)
			pa=i;
		else if(file[i]==wordb)
			pb=i;
		if(pa!=-1  &&  pb!=-1)
			min = std::min(min, std::abs(pa-pb));
	}
	return min;
}

bool readline(FILE* f, std::string &line)
{
    line.clear();
    if(f==NULL)
        return false;
    char c;
    while(fscanf(f, "%c", &c)!=EOF)
    {   
        if(c!='\n'  &&  c!='\r')
            line.append(1, c); 
        else
        {   
            //printf("get [%c]\n", c);
            // if(c=='\n')
                // printf("get \\n\n");
            // else
                // printf("get \\r\n");
            return true;
        }   
    }   
    return false;
}


int shortest_distance(FILE* file, const std::string& worda, const std::string& wordb)
{
	int pa=-1, pb=-1;
	int min=INT_MAX;
	
	if(file==NULL)
		return min;
	
	std::string word;
	int i=0;
	while(readline(file, word))
	{
		if(word==worda)
			pa=i;
		else if(word==wordb)
			pb=i;
		if(pa!=-1  &&  pb!=-1)
			min = std::min(min, std::abs(pa-pb));
		++i;
	}
	
	return min;
}


void test1()
{
	std::vector<std::string> vec{ "What","is","your","name","My","name","is","Hawstein"};
	int dist=shortest_distance(vec, "is", "name");
	printf("%d\n", dist);
	
	
}



class MinDist{
public:
	std::string first;
	int second;
	
	MinDist():first(), second() {}
	MinDist(const std::string& w, int d):first(w),second(d){}
	
	bool compare_min_dist(const std::string & w)
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


//typedef std::pair<std::string, int> MinDist;
typedef std::list<MinDist> HashList;
typedef std::map<unsigned int, HashList> DiskMap;

DiskMap dm;


bool compare_min_dist(MinDist md, const std::string& s)
{
	if(md.first == s)
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


// std::map<int, std::list<std::pair<std::string, int> > > 哈希值——list<连接字符串, 最短距离>
void pre_shortest_distance(std::vector<std::string> file)
{
	int dist=0;
	std::string worda, wordb, wordab;
	unsigned int hashvalue=0;
	
	dm.clear();
	
	for(int i=0; i<file.size(); ++i)
		for(int j=i+1; j<file.size(); ++j)
		{
			worda=file[i];
			wordb=file[j];
			
			if(worda<wordb)
				wordab=worda+wordb;
			else
				wordab=wordb+worda;
			dist=j-i;
			printf("%s %s %d\n", worda.c_str(), wordb.c_str(), dist);
			
			hashvalue=stringHashFunction(wordab);
			
			DiskMap::iterator it1=dm.find(hashvalue);
			HashList::iterator it2;
			if(it1!=dm.end())
			{
				HashList& hl=it1->second; // 使用引用, 更新dm
				//it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(Cmp_mindist(), wordab));
				it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(std::ptr_fun(compare_min_dist), wordab));
				
				if(it2!=hl.end())
				{
					it2->second=std::min(it2->second, dist);
					printf("%s %s %d, update %s, %d, %d\n", worda.c_str(), wordb.c_str(), dist, it2->first.c_str(), hashvalue, it2->second);
				}
				else
				{
					hl.insert(hl.begin(), MinDist(wordab, dist));
				}
			}
			else
			{
				hl.clear();
				hl.insert(hl.begin(), MinDist(wordab, dist));
				dm.insert(DiskMap::value_type(hashvalue, hl));
				printf("%s %s %d, insert %s, %d, %d\n", worda.c_str(), wordb.c_str(), dist, wordab.c_str(), hashvalue, dist);
			}
				
		}
}
// O(n*n*logn*logm) // m是具有相同哈希值的链表的平均长度

void print_pre_state()
{
	for(DiskMap::iterator it1=dm.begin(); it1!=dm.end(); ++it1)
	{
		HashList hl=it1->second;
		for(HashList::iterator it2=hl.begin(); it2!=hl.end(); ++it2)
		{
			printf("%d %s %d\n", it1->first, it2->first.c_str(), it2->second);
		}
	}
}

int shortest_distance2(const std::string& a, const std::string& b)
{
	std::string wordab=a+b;
	if(a>b)
		wordab=b+a;
	unsigned hashvalue=stringHashFunction(wordab);
	DiskMap::iterator it1=dm.find(hashvalue);
	if(it1==dm.end())
		return -1;
	HashList hl=it1->second;
	
	// 非成员函数
	HashList::iterator it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(std::ptr_fun(compare_min_dist), wordab));
	// 成员函数
	//HashList::iterator it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(std::mem_fun(&MinDist::compare_min_dist), wordab));
	// 判别式类
	//HashList::iterator it2=std::find_if(hl.begin(), hl.end(), std::bind2nd(Cmp_mindist(), wordab));
	// std::function
	
	// lambda表达式
	
	
	
	if(it2==hl.end())
		return -1;
	printf("%d, %s, %d\n", hashvalue, it2->first.c_str(), it2->second);
	return it2->second;
}



void test2()
{
	std::vector<std::string> vec{ "What","is","your","name","My","name","is","Hawstein"};
	pre_shortest_distance(vec);
	
	print_pre_state();
	
	int dist=shortest_distance2("is", "name");
	printf("%d\n", dist);
	
	dist=shortest_distance2("name", "is");
	printf("%d\n", dist);
}




int main()
{
	test1();
	
	test2();
	
	return 0;
}

