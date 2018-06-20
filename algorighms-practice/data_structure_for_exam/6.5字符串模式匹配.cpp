//�򵥵�ģʽƥ���㷨
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



//��next����ֵ���㷨
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




//KMP�㷨
int KMP(char S[], char T[], int next[], int pos)
{
	//����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�KMP�㷨��1<=pos<=strlen(S)
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