
int evalRPN(vector<string>& tokens) {
	if(tokens.empty())
		return 0;
	int res;
	stack<int> S;
	for(int i=0; i<tokens.size(); ++i)
	{
		if(!isOperator(tokens[i]))
		{
			S.push(atoi(tokens[i]));
		}
		else
		{
			int right=S.top();
			S.pop();
			int left=S.top();
			S.pop();
			int tmp=compute(left, right, tokens[i]);
			S.push(tmp);
		}
	}
	return S.top();
}

bool isOperator(const string& str)
{
	if(str=="+"  ||  str=="-"  ||  str=="*"  ||  str=="/")
		return true;
	return false;
}

int compute(int left, int right, const string& operator)
{
	if(operator=="*")
		return left*right;
	if(operator=="/")
		return left/right;
	if(operator=="-")
		return left-right;
	return left+right;
}