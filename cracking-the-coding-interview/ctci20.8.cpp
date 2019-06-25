/*
原字符串长度n
时间复杂度O(n*n)
空间复杂度O(n*n*26)=O(n*n)
*/

#include<iostream>
#include<string>
#include<string.h>

using namespace std;

class Trie{
public:
	static const int MAX_N = 100*100; // 主串长度100
	static const int CLD_NUM = 26; // 每个节点的儿子数量
	int size; // 用到的当前节点编号
	int tire[MAX_N][CLD_NUM];
	// size从0开始，tire[size][CLD_NUM]存储插入的节点(字符)的信息(即子节点数组)
	
	Trie(const char* s);
	void insert(const char* s);
	bool find(const char* s);
	
};

Trie::Trie(const char* s)
{
	memset(tire[0], -1, sizeof(tire[0]));
	size=1;
	while(*s)
	{
		insert(s); // 插入每一个后缀字符串
		++s;
	}
}

void Trie::insert(const char* s)
{
	int p=0; // 从根节点开始，根节点的所有子节点存储在tire[0][26]中
	while(*s)
	{
		int i=*s-'a';
		if(-1  == tire[p][i]) // 当前节点*s不存在
		{
			// 选择tire[size][26]存储节点*s的所有子节点
			memset(tire[size], -1, sizeof(tire[size]));
			tire[p][i]=size++;
		}
		p = tire[p][i]; // p走到当前节点*s的子节点存储数组
		++s;
	}
}

bool Trie::find(const char* s)
{
	int p=0;
	while(*s)
	{
		int i=*s-'a';
		if(-1 == tire[p][i])
			return false;
		p = tire[p][i];
		++s;
	}
	return true;
}

void test()
{
	Trie tree("mississippi");
	std::string patt[] = {
        "is", "sip", "hi", "sis", "mississippa"
    };
    int n = 5;
    for(int i=0; i<n; ++i)
        std::cout<<tree.find((char*)&patt[i][0])<<std::endl;
}

int main()
{
	test();
	
	return 0;
}



