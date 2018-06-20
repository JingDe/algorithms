//硬币问题
//最长路径
memset(d, -1, sizeof(d));
int dp(int S)
{
	int& ans=d[S];
	if(ans>=0)
		return ans;
	ans=0;
	for(int i=1; i<=n; i++)
		if(S>=V[i])
			ans=max(ans, dp(S-V[i])+1);
	return ans;
}
//错误：需要特殊的d[S]值表示无法到达，显然0不合适
memset(d, -1, sizeof(d))
int dp(int S)
{
	int & ans=d[S];
	if(ans!=-1)
		return ans;
	ans=-(1<<30);
	for(int i=1; i<=n; i++)
		if(S>=V[i])
			ans=max(ans, dp(S-V[i])+1);
	return ans;
}
//提示：在记忆化搜索中，如果用特殊值表示还没有算过，必须将其同其他特殊值如无解区分开
//另一种解决方法：数组标记
memset(vis, 0, sizeof(vis));
int dp(int S)
{
	if(vis[S])
		return d[S];
	vis[S]=1;
	int & ans=d[S];
	ans=-(1<<30);
	for(int i=1; i<=n; i++)
		if(S>=V[i])
			ans=max(ans, dp(S-V[i])+1);
	return ans;
}
//提示：如果状态比较复杂，无法用数组下标表示状态。用STL的map保存状态值。if(map.count(S))判断状态值S
//递推
minv[0]=maxv[0]=0;
for(int i=1; i<=S; i++)
{
	minv[i]=INF; maxv[i]=-INF;
}
for(int i=1; i<=S; i++)
	for(j=1; j<=n; j++)
		if(i>=V[j])
		{
			minv[i]=min(minv[i], minv[i-V[j]]+1);
			maxv[i]=max(maxv[i], maxv[i-V[j]]+1);
		}
printf("%d %d\n", minv[S], maxv[S]);

void print_ans(int *d, int S)
{
	for(int i=1; i<=n; i++)
		if(S>=V[i]  &&  d[S]==d[S-V[i]]+1)
		{
			printf("%d ", i);
			print_ans(d, S-V[i]);
			break;
		}
}
print_ans(minv, S);
print_ans(maxv, S);
//提示：当用递推法计算出各个状态的指标之后，可以用与记忆化搜索完全相同的方式打印方案。
//另一种打印路径的方法：地推时直接用min_coin[S]记录满足min[S]==min[S-V[j]]+1的最小的j，
//则打印路径时可以省去print_ans函数中的循环，并可以方便地把递归改成迭代。
for(int i=1; i<=S; i++)
	for(int j=1; j<=n; j++)
		if(i>=V[j])
		{
			if(minv[i]>minv[i-V[j]]+1)
			{
				minv[i]=minv[i-V[j]]+1;
				min_coin[i]=j;
			}
			if(maxv[i]<maxv[i-V[i]]+1)
			{
				maxv[i]=maxv[i-V[j]]+1;
				max_coin[i]=j;
			}
		}

void print_ans(itn *d, int S)
{
	while(S)
	{
		printf("%d ", d[S]);
		S -= V[d[S]];
	}
}
print_ans(min_coin, S);
print_ans(max_coin, S);
//提示：无论是用记忆化搜索还是递推，如果让计算最优值的同时顺便算出各个状态下的
//第一次最优决策，则往往能让打印方案的过程更加简单高效