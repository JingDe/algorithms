#include<iostream>
#include<stdio.h>
#include<string>
#include<utility>
#include<cassert>
#include<string.h>

// 给定一个真实排列、一个猜测排列，计算hits和pseudo-hits
std::pair<int, int> computeHits(std::string rs, std::string gs)
{
	assert(rs.size()==gs.size());
	int hits=0, pseudo=0;
	bool visited[rs.size()];
	for(int i=0; i<rs.size(); ++i)
	{
		if(gs[i]==rs[i])
			++hits;
		else
		{
			for(int j=0; j<rs.size(); ++j)
				if(gs[i]==rs[j]  &&  rs[j]!=gs[j]  &&  !visited[j])
				{
					visited[j]=true;
					++pseudo;
				}
		}
	}
	return std::make_pair<int, int>(hits, pseudo);
}// O(N*N)

void solve()
{
	{
		std::pair<int,int> res=computeHits("RYGB", "YRRR");
		std::cout<<res.first<<" "<<res.second<<std::endl;
	}
	
	{
		std::pair<int,int> res=computeHits("RGGB", "YRGB");
		std::cout<<res.first<<" "<<res.second<<std::endl;
	}
}

std::pair<int, int> estimate1(const char* solution, const char* guess)
{
	int hits=0, pseudo=0;
	int solution_mask=0;
	for(int i=0; i<4; ++i)
	{
		solution_mask |= 1<<(solution[i]-'A'); // 设置二进制形式的solution_mask表示的26位字母数组, 对应比特位为1
		//printf("%s, 0x%o\n", solution, solution_mask);
	}
	//printf("%s, 0x%o\n", solution, solution_mask);
	
	for(int i=0; i<4; ++i)
	{
		if(guess[i]==solution[i])
			++hits;
		else if(solution_mask  &  (1<<(guess[i]-'A'))) // 如果guess[i]的字母，在solution中也出现过。
		//当solution中有一个某字母X，guess中有多个X，统计了多个
			++pseudo;
	}
	return std::make_pair<int, int>(hits, pseudo);
}// O(N)

int min(int a, int b){
    return a < b ? a : b;
}

std::pair<int, int> estimate2(const char* solution, const char* guess)
{
	int hits=0, pseudo=0;
	int num=26+5;
	int guess_count[num], solution_count[num];
	memset(guess_count, 0, sizeof(guess_count));
	memset(solution_count, 0, sizeof(solution_count));
	
	for(int i=0; i<4; ++i)
	{
		if(guess[i] == solution[i])
			++hits;
		++guess_count[(int)(guess[i]-'A')];
		++solution_count[(int)(solution[i]-'A')];
	}
	char color[]="RGBY";
	for(int i=0; i<4; ++i)
	{
		int idx=(int)(color[i]-'A');
		pseudo+=min(guess_count[idx], solution_count[idx]);
	}
	pseudo-=hits;
	return std::make_pair<int, int>(hits, pseudo);
} // O(N+N)=O(N)

void solve2()
{
	{
		std::pair<int,int> res=estimate1("RYGB", "YRRR");
		std::cout<<res.first<<" "<<res.second<<std::endl;
	}
	
	{
		std::pair<int,int> res=estimate1("RGGB", "YRGB");
		std::cout<<res.first<<" "<<res.second<<std::endl;
	}
}

void solve3()
{
	{
		std::pair<int,int> res=estimate2("RYGB", "YRRR");
		std::cout<<res.first<<" "<<res.second<<std::endl;
	}
	
	{
		std::pair<int,int> res=estimate2("RGGB", "YRGB");
		std::cout<<res.first<<" "<<res.second<<std::endl;
	}
}

int main()
{
	solve();
	solve2();
	solve3();
	
	return 0;
}