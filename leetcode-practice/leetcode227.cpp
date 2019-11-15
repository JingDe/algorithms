enum State{
	COMMON,
	WAIT_MUTIPLY,
	WAIT_DIVIDE,
};

int calculate(string s) {
	std::stack<int> numStack;
	std::stack<char> opStack;

	State state=COMMON;
	for(int i=0; i<s.size(); ++i)
	{
		if(s[i]==' ')
			continue;

		if(isdigit((int)s[i]))
		{
			if(state==COMMON)
				numStack.push(s[i]-'0');
			else
			{
				int rhs=s[i]-'0';
				assert(numStack.empty()==false);
				int lhs=numStack.top();
				numStack.pop();
				
				int tmp=0;
				if(state==WAIT_DIVIDE)
					tmp=lhs/rhs;
					//numStack.push(lhs/rhs);
				else
					tmp=lhs*rhs;
					//numStack.push(lhs*rhs);
				printf("push tmp %d\n", tmp);
				numStack.push(tmp);
			}
		}
		else if(s[i]=='*')
		{
			assert(state==COMMON);
			state=WAIT_MUTIPLY;
		}
		else if(s[i]=='/')
		{
			assert(state==COMMON);
			state=WAIT_DIVIDE;
		}
		else if(s[i]=='+'  ||  s[i]=='-')
		{
			opStack.push(s[i]);
		}
		else
		{
			assert(false);
		}
	}
	
	printf("%d, %d\n", numStack.size(), opStack.size());
	assert(numStack.size() == opStack.size()+1);
	while(numStack.size()>=2)
	{
		char op=opStack.top();
		opStack.pop();
		int rhs=numStack.top();
		numStack.pop();
		int lhs=numStack.top();
		numStack.pop();
		printf("%d %c %d\n", lhs, op, rhs);

		if(op=='+')
			numStack.push(lhs+rhs);
		else
			numStack.push(lhs-rhs);
	}
	return numStack.top();
}

int calculate(string s) 
{
	istringstream in('+'+s+'+');
	long long total=0, term=0, n;
	char op;
	while(in>>op)
	{
		if(op=='+'  ||  op=='-') 
		{
			total+=term; // 如果当前遇到+或者-，表明前一个数字term可以加到最终结果中
			in>>term; // 允许数字不是一位数
			//term*=44-op; // +的ascii是43, -是45
			term*= (op=='+'? 1 : -1);
		}
		else // 遇到*或者/，和前一个数字term一起计算
		{
			in>>n;
			if(op=='*')
				term*=n;
			else
				term/=n;
		}
	}
	return total;
}

int calculate(string s) 
{
	stack<long> myStack;
	char sign = '+';
	long res = 0;
	long tmp = 0;
	for (unsigned int i = 0; i < s.size(); i++) {
		if (isdigit(s[i]))
			tmp = 10*tmp + s[i]-'0';
		if (!isdigit(s[i]) && !isspace(s[i]) || i == s.size()-1) {
			if (sign == '-')
				myStack.push(-tmp);
			else if (sign == '+')
				myStack.push(tmp);
			else {
				long num;
				if (sign == '*' )
					num = myStack.top()*tmp;
				else
					num = myStack.top()/tmp;
				myStack.pop();
				myStack.push(num);
			} 
			sign = s[i];
			tmp = 0;
		}
	}
	while (!myStack.empty()) {
		res += myStack.top();
		myStack.pop();
	}
	return res;
}