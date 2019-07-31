

string multiply(string num1, string num2) 
{
	int sz1=num1.size();
	int sz2=num2.size();
	if(num1.empty()  ||  num2.empty())
		return "";
	if(num1=="0"  ||  num2=="0")
		return "0";

	string res;
	res.reserve(sz1+sz2);
	int c=0;
	for(int k=0; k<sz1+sz2; ++k)
	{
		int sum=c;
		bool exit=true;
		// for(int i=0; i<sz1  &&  i<=k  &&  k-i<sz2; ++i) // 漏掉情况
		// {			
			// sum += (num1[sz1-1-i]-'0') * (num2[sz2-1-(k-i)]-'0');
			// exit=false;
		// }
		for(int i=0; i<sz1  &&  i<=k; ++i)
		{
			int j=k-i;
			if(j>=sz2)
				continue;
						
			sum += (num1[sz1-1-i]-'0') * (num2[sz2-1-(k-i)]-'0');
			exit=false;
		}
		if(sum==0  &&  exit)
			break;
		int remainder=sum%10;
		c=sum/10;
		res=std::to_string(remainder)+res;
	}
	return res;
}