/*
时间复杂度O(n*n)
空间复杂度O()

*/

#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>

#define CLD_NUM 26

typedef struct TrieNode
{
	bool isStr;
	struct TrieNode *next[CLD_NUM];
}Trie;


// 将单词s插入到字典树中
void insert(Trie* root, const char* s)
{
	printf("insert %s\n", s);
	if(root==NULL  ||  *s=='\0')
		return;

	Trie* p=root;
	int v=0;
	while(*s!='\0')
	{
		v=*s-'a';
		if(p->next[v]==NULL) // 节点*s不存在，创建之
		{
			TrieNode* tmp=(Trie*)malloc(sizeof(Trie));
			for(int i=0; i<CLD_NUM; ++i)
			{
				tmp->next[i]=NULL;
			}
			tmp->isStr=false;
			p->next[v]=tmp;
			p=p->next[v];
		}
		else
			p=p->next[v];
		s++;
	}
	p->isStr=true;
}

int search(Trie* root, const char* s)
{
	Trie *p=root;
	while(p!=NULL  &&  *s!='\0')
	{
		p=p->next[*s-'a'];
		++s;
	}
	return (p!=NULL  &&  p->isStr==true);
}

int searchPrefix(Trie* root, const char* s)
{
	Trie *p=root;
	while(p!=NULL  &&  *s!='\0')
	{
		p=p->next[*s-'a'];
		++s;
	}
	return p!=NULL;
}


void destroy(Trie* root)
{
	for(int i=0; i<CLD_NUM; ++i)
	{
		if(root->next[i]!=NULL)
			destroy(root->next[i]);
	}
	free(root);
}

Trie* create(const std::string& s)
{
	Trie* tree=new TrieNode();
	const char* str=s.c_str();
	for(int i=0; i<s.size(); ++i)
		insert(tree, str+i);
	return tree;
}

void test()
{
	std::string str="mississippi";
	Trie* tree=create(str);
	
	std::string patt[] = {
        "is", "sip", "hi", "sis", "mississippa"
    };
	int ret=0;
	for(int i=0; i<5; ++i)
	{
		ret = searchPrefix(tree, patt[i].c_str());
		printf("%s, %d, %s\n", patt[i].c_str(), ret, ret ? "yes" : "no");
	}
	destroy(tree);
}

int main()
{
	test();
	
	return 0;
}

