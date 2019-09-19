
int titleToNumber(string s) {
	int ans=0;
	int factor=1;
	for(int i=s.size()-1; i>=0; i--)
	{
		char c=s[i];
		ans+=factor* (c-'A'+1);
		factor*=26;
	}
	return ans;
}