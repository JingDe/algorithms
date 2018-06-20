//简单的模式匹配算法
int Index(SString S, SString T)
{
	int i=1; j=1;
	while(i<=S[0]  &&  j<=T[0])
	{
		if(S[i]==T[i])
			++i, ++j;
		else
			i=i-j+2, j=1;
	}
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}



//求next函数值的算法
void get_next(char T[], int next[])
{
	i=1;
	next[1]=0;
	j=0;
	while(i<=T[0])
	{
		if(j==0  ||  T[i]==T[j])
		{
			++i;
			++j;
			next[i]=j;
		}
		else
			j=next[j];
	}
}




//KMP算法
int KMP(char S[], char T[], int next[], int pos)
{
	//利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法。1<=pos<=strlen(S)
	i=pos;
	j=1;
	while(i<=S[0]  &&  j<=T[0])
	{
		if(j==0  ||  S[i]==T[j])
		{
			++i;
			++j;
		}
		else
			j=next[j];
	}
}