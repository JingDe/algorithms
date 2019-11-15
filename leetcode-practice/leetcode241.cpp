// 数字是一位数
// vector<int> diffWaysToCompute(string input) {
	// vector<int> ans;

	// ans = diffWays(input, 0, input.size()-1);
	// return ans;
// }


// vector<int> diffWays(const string& input, int start, int end)
// {
	// if(end-start==0)   
		// return vector<int>({atoi(input.substr(start, 1).c_str())});

	// vector<int> ans;
	// for(int i=start+1; i<=end-1; i+=2)
	// {
		// vector<int> leftAns = diffWays(input, start, i-1);
		// vector<int> rightAns = diffWays(input, i+1, end);

		// for(int a=0; a<leftAns.size(); ++a)
		// {
			// for(int b=0; b<rightAns.size(); ++b)
			// {
				// if(input[i]=='+')
					// ans.push_back(leftAns[a]+rightAns[b]);
				// else if(input[i]=='-')
					// ans.push_back(leftAns[a]-rightAns[b]);
				// else if(input[i]=='*')
					// ans.push_back(leftAns[a]*rightAns[b]);
				// else
					// assert(false);
			// }
		// }
	// }
	// return ans;
// }


vector<int> diffWaysToCompute(string input)
{
	vector<int> ans;
	ans = diffWays(input, 0, input.size()-1);
	return ans;
}


vector<int> diffWays(const string& input, int start, int end)
{
	vector<int> ans;
	bool oneNum=true;
	for(int i=start+1; i<end; ++i)
	{
		if(input[i]=='+'  ||  input[i]=='-'  ||  input[i]=='*')
		{
			oneNum=false;
			vector<int> leftAns=diffWays(input, start, i-1);
			vector<int> rightAns=diffWays(intput, i+1, end);
			for(int a=0; a<leftAns.size(); ++a)
			{
				for(int b=0; b<rightAns.size(); ++b)
				{
					if(input[i]=='+')
						ans.push_back(leftAns[a]+rightAns[b]);
					else if(input[i]=='-')
						ans.push_back(leftAns[a]-rightAns[b]);
					else if(input[i]=='*')
						ans.push_back(leftAns[a]*rightAns[b]);
					else
						assert(false);
				}
			} 
		}
	}
	if(oneNum)
		return vector<int>({input.substr(start, end-start+1).c_str()});
	else
		return ans;
}