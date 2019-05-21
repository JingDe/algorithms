
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<utility>
#include<time.h>

void print(std::vector<int> vec)
{
    for(int i=0; i<vec.size(); ++i)
        printf("%d ", vec[i]);
    printf(", (%d)\n", vec.size());
}

// 随机洗牌函数，返回（0~n-1）一个随机的排列
std::vector<int> randomShuffle(int n)
{
	std::vector<int> cards;
	cards.reserve(n);
	for(int i=0; i<n; ++i)
		cards.push_back(i);
	
	std::srand(time(NULL));
	for(int i=0; i<n; ++i)
	{
		int idx=std::rand()%(n-i)+i; // 剩余n-i张牌，0~（n-i-1）
		std::swap(cards[i], cards[idx]);
		
	}
	return cards;
}

void solve()
{
	std::vector<int> shuffle=randomShuffle(52);
	print(shuffle);
}

int main()
{
	solve();
	
	return 0;
}