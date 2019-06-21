
#include<string.h>

using namespace std;

class Tire{
public:
	static const int MAX_N = 100*100; // 主串长度
	static const int CLD_NUM = 26; // 每个节点的儿子数量
	int size; // 
	int tire[MAX_N][CLD_NUM];
	
	Tire(const char* s);
	void insert(const char* s);
	bool find(const char* s);
	
};

Tire::Tire(const char* s)
{
	memset(trie[0], -1, sizeof(trie[0]));
	size=1;
	while(*s)
	{
		insert(s);
		++s;
	}
}

void Tire::insert(const char* s)
{
	int p=0;
	while(*s)
	{
		int i=*s-'a';
		if(-1  == tire[p][i])
		{
			memset(tire[size], -1, sizeof(tire[size]));
			tire[p][i]=size++; 
			// tire[p][i] 表示 
		}
		p = tire[p][i];
		++s;
	}
}

