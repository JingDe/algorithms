
vector<int> grayCode(int n) {
	if(n==0)
	{
		vector<int> ans;
		ans.push_back(0);
		return ans;
	}
	if(n==1)
	{
		vector<int> ans;
		ans.push_back(0);
		ans.push_back(1);
		return ans;
	}

	vector<string> code;
	code.push_back("0");
	code.push_back("1");
	for(int i=2; i<=n; ++i)
	{
		vector<string> tmp;
		for(int a=0; a<code.size(); ++a)
		{
			tmp.push_back(code[a]+"0");
		}
		for(int a=code.size()-1; a>=0; --a)
			tmp.push_back(code[a]+"1");

		code.swap(tmp);
	}

	vector<int> ans;
	for(int i=0; i<code.size(); ++i)
	{
		//ans.push_back(atoi(code[i].c_str()));
		ans.push_back(binaryStrToInt(code[i]));
	}
	return ans;
}

int binaryStrToInt(string str)
{
	int res=0;
	int weight=1;
	for(int i=0; i<str.size(); ++i)
	{
		res=res+(str[str.size()-1-i]-'0')*weight;
		weight=weight*2;
	}
	return res;
}


vector<int> grayCode(int n) 
{
	vector<int> rs;
	rs.push_back(0);
	for(int i=0; i<n; ++i)
	{
		int size=rs.size();
		for(int k=size-1; k>=0; k--)
			rs.push_back(rs[k] |  1<<i);
	}
	return rs;
}

n==0时：0
n==1时：0, 1。
	i从0到0，修改第0位
n==2时：
	i从0到1，
	修改第0位，0,1
	修改第1位，10, 11
	

// 格雷编码的二进制序列，
// 就是递归遍历/回溯法求解：n个数的子集的位向量
// 错误！

vector<int> grayCode(int n) {
	vector<int> ans;
	int choose[nums.size()];
	memset(choose, 0, sizeof(choose));
	backtracking3(ans, choose, 0);
	return ans;
}

void backtracking3(vector<int>& ans, int choose[], int cur)
{
	if(cur==n)
	{
		int value=getValue(choose, n);
		ans.push_back(value);
		return;
	}
	choose[cur]=0;
	backtracking3(ans, choose, cur+1);
	choose[cur]=1;
	backtracking3(ans, choose, cur+1);
}

int getValue(int choose[], int sz)
{
	int res=0;
	int weight=1;
	for(int i=0; i<sz; ++i)
	{
		res=res+choose[i]*weight;
		weight=weight*2;
	}
	return res;
}

