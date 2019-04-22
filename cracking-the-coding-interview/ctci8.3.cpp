#include<set>
#include<iostream>
#include<stdio.h>
#include<vector>

void printSet(std::set<int> s)
{
	printf("[");
	for(std::set<int>::iterator it=s.begin(); it!=s.end(); ++it)
		printf("%d, ", *it);
	printf("]\n");
}

void printSet(std::vector<int> s)
{
	printf("[");
	for(std::vector<int>::iterator it=s.begin(); it!=s.end(); ++it)
		printf("%d, ", *it);
	printf("]\n");
}

void subset1(const std::set<int>& s)
{
	int sz=s.size();
	printf("%d subset\n", (1<<sz));
	for(int flag=0; flag< (1<<sz); ++flag) // i从0到(2^sz-1), 即00..0~11.1
	{
		//printf("parse one subset, 0x%x.\n", flag);
		std::set<int> subset;
		std::set<int>::iterator it=s.begin();
		// for(int pos=0; pos<sz; ++pos)
		// {
			// if(flag  &  (1<<pos))
			// {
				// subset.insert(*it);
			// }
			// ++it;
		// }		
		int idx=0;
		int f=flag;
		while(f>0)
		{
			//printf("flag =%d\n", f);
			if(f  &  1)
				subset.insert(*it);
			++it;
			f >>= 1;
		}	
		printSet(subset);
	}
}

//
std::vector<std::vector<int> > getSubset(const std::vector<int>& S, int cur);

void subset2(const std::vector<int>& S)
{
	std::vector<std::vector<int> > res=getSubset(S, 0);
	for(std::vector<std::vector<int> >::iterator it=res.begin(); it!=res.end(); ++it)
	{
		printSet(*it);
	}
}

// 求集合S(cur)开始到S(N)的子集合的子问题
// void getSubset(const std::vector<int>& S, int cur, std::set<int>& subset)
// {
	// if(cur==S.size())
	// {
		// printSet(subset);
		// return;
	// }
	// getSubset(S, cur+1, subset);
	
	// subset.insert(S[cur]);
	// getSubset(S, cur+1, subset);
// }
// 子问题：求S[cur]到S[size-1]的子集
std::vector<std::vector<int> > getSubset(const std::vector<int>& S, int cur)
{
	std::vector<std::vector<int> > subsets;
	if(cur==S.size()) // 最小子问题情形
	{
		std::vector<int> emptySet;
		subsets.push_back(emptySet);
		return subsets;
	}
	
	// 一般子问题情形
	std::vector<std::vector<int> > res=getSubset(S, cur+1);
	for(std::vector<std::vector<int> >::iterator it=res.begin(); it!=res.end(); ++it)
	{
		std::vector<int> s=*it;
		subsets.push_back(s);
		
		s.push_back(S[cur]);
		subsets.push_back(s);
	}
	return subsets;
}

// 
void print_subset(const std::vector<int> &S, int cur, std::vector<int>& subset);

void subset3(const std::vector<int> &S)
{
	std::vector<int> subset;
	print_subset(S, 0, subset);
}

void print_subset(const std::vector<int> &S, int cur, std::vector<int>& subset)
{
	if(cur==S.size()-1)
	{
		printSet(subset);
		
		subset.push_back(S[cur]);
		printSet(subset);
		
		subset.resize(subset.size()-1); // 回退
		return;
	}
	
	print_subset(S, cur+1, subset);
	
	subset.push_back(S[cur]);
	print_subset(S, cur+1, subset);
	
	subset.resize(subset.size()-1); // 回退
}

int main()
{
	{		
		FILE *f=freopen("8.3.in", "r", stdin);
		if(f!=NULL)
		{			
			std::set<int> s;
			int ele;
			while(scanf("%d", &ele)!=EOF)
			{
				s.insert(ele);
			}
			fclose(stdin);
			
			subset1(s);
		}
		else
			perror("8.3.in open error");
	}
	printf("======================\n");
	{
		//std::vector<int> S({1,2,3,4,5});
		//std::vector<int> S={1,2,3,4,5};
		std::vector<int> S;
		int array[]={1,2,3,4,5,6};
		for(int i=0; i<sizeof(array)/sizeof(array[0]); ++i)
			S.push_back(array[i]);
		subset2(S);
	}
	
	printf("======================\n");
	{
		std::vector<int> S;
		int array[]={1,2,3,4,5,6};
		for(int i=0; i<sizeof(array)/sizeof(array[0]); ++i)
			S.push_back(array[i]);
		subset3(S);
	}
	return 0;
}