//Ӳ������
//�·��
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
//������Ҫ�����d[S]ֵ��ʾ�޷������Ȼ0������
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
//��ʾ���ڼ��仯�����У����������ֵ��ʾ��û����������뽫��ͬ��������ֵ���޽����ֿ�
//��һ�ֽ��������������
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
//��ʾ�����״̬�Ƚϸ��ӣ��޷��������±��ʾ״̬����STL��map����״ֵ̬��if(map.count(S))�ж�״ֵ̬S
//����
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
//��ʾ�����õ��Ʒ����������״̬��ָ��֮�󣬿���������仯������ȫ��ͬ�ķ�ʽ��ӡ������
//��һ�ִ�ӡ·���ķ���������ʱֱ����min_coin[S]��¼����min[S]==min[S-V[j]]+1����С��j��
//���ӡ·��ʱ����ʡȥprint_ans�����е�ѭ���������Է���ذѵݹ�ĳɵ�����
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
//��ʾ���������ü��仯�������ǵ��ƣ�����ü�������ֵ��ͬʱ˳���������״̬�µ�
//��һ�����ž��ߣ����������ô�ӡ�����Ĺ��̸��Ӽ򵥸�Ч