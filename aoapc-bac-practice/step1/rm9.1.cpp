//数字三角形

//递归计算
int solve(int i, int j)
{
	return a[i][j]+( i==n  ? 0 : max(solve(i+1, j), solve(i+1, j+1)));
}
solve(1, 1);

//递推计算
int i, j;
for(j=1; j<=n; j++)
	d[n][j]=a[n][j];
for(i=n-1; i>=1; i--)
	for(j=1; j<=i; j++)
		d[n][j]=a[n][j]+max(d[n+1][j], d[n+1][j+1]);
d[1][1];

//记忆化搜索
int solve(int i, int j)
{
	if(d[i][j]>=0)
		return d[i][j];
	return d[i][j]=a[i][j]+(i==n ? 0 : max(solve(i+1, j), solve(i+1, j+1)));
}
solve(1,1);