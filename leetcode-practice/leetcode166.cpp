
string fractionToDecimal(int numerator, int denominator) {
	if(numerator==0)
		return 0;
	string ans;
	if(numerator<0  ^  denominator<0)
		ans='-';
	
	long dividend=abs((long)numerator);
	long divisor=abs((long)denominator);
	ans.append(itoa(dividend/divisor));
	long remainder=dividend%divisor;
	if(remainder==0)
		return ans;
	
	ans.append(".");
	map<long, int> m;
	while(remainder!=0)
	{
		if(m.contains(remainder))
		{
			ans.insert(m[remainder], "(");
			ans.append(")");
			break;
		}
		
		m[remainder]=ans.size();// 保存余数出现在小数的位置
		remainder*=10;
		ans.append(itoa(remainder/divisor));
		remainder%=divisor;
	}
	return ans;
}