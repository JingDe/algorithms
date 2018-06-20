//Ç¶Ì×¾ØĞÎ
//¼ÇÒä»¯ËÑË÷
int dp(int i)
{
	int & ans=d[i];
	if(ans>0)
		return ans;
	ans=1;
	for(int j=1; j<=n; j++)
		if(G[i][j])
			ans=max(ans, dp(j)+1);
	return ans;
}
void print_ans(int i)
{
	printf("%d", i);
	for(int j=1; j<=n; j++)
		if(G[i][j]  &&  d[i]==d[j]+1)
		{
			print_ans(j);
			break;
		}
}
int f=1;
for(int k=2; k<=n; k++)
	if(d[k]>d[f])
		f=k;
print_ans(f);