
// 1-n的排列

// STL 算法
void solve()
{
	int p[MAXN];
	
	sort(p, p+n);
	do{
		print(p);
	}while(next_permutation(p, p+n));
	
}

// 递归枚举
