
int compareVersion(string version1, string version2) {
	int i=0;
	int j=0;
	int n1=version1.size();
	int n2=version2.size();
	
	int num1=0;
	int num2=0;
	while(i<n1  ||  j<n2)
	{
		while(i<n1  &&  version1[i]!='.')
		{
			num1=num1*10 + (version1[i]-'0');
			i++;
		}
		while(j<n2  &&  version2[j]!='.')
		{
			num2=num2*10 + (version2[j]-'0');
			j++;
		}
		if(num1>num2)
			return 1;
		else if(num1<num2)
			return -1;
		
		num1=0;
		num2=0;
		i++;
		j++;
	}
	return 0;
}

void test1()
{
	string s="12345";
	size_type p=s.find('3',6);
	if(p==npos)
		printf("npos\n");
	else
		printf("%d\n", p);
}

void test2()
{
	string::size_type p=string::npos;
	string::size_type p2=p+1;
	if(p2==string::npos)
		printf("npos\n");
	else
		printf("%d\n", p2);
}

int compareVersion(string version1, string version2) 
{
	istringstream ver1(version1+".");
	istringstream ver2(version2+".");
	int val1=0;
	int val2=0;
	char dot='.';
	while(ver1.good()  ||  ver2.good())
	{
		if(ver1.good())
			ver1>>val1>>dot;
		else
			printf("1 bad\n");
		if(ver2.good())
			ver2>>val2>>dot;
		else
			printf("2 bad\n");
		if(val1>val2)
			return 1;
		else if(val1<val2)
			return -1;
		val1=val2=0;
	}
	return 0;
}


int compareVersion(string version1, string version2) 
{
	for(auto& w : version1)
		if(w=='.')
			w=' ';
	for(auto& w : version2)
		if(w='.')
			w=' ';
	istringstream s1(version1),s2(version2);
	while(true)
	{
		int n1, n2;
		if(not(s1>>n1))
			n1=0;
		if(not(s2>>n2))
			n2=0;
		if(not s1  and  not s2)
			return 0;
		if(n1<n2)
			return -1;
		if(n1>n2)
			return 1;
	}
}