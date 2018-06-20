struct BigInteger
{
	static const int BASE=100000000;
	static const int WIDTH=8;
	vector<int> s;

	BigInteger(__int64 num=0)
	{
		*this=num;
	}
	BigInteger operator=(__int64 num)
	{
		s.clear();
		do{
			int x=num%BASE;
			s.push_back(x);
			num/=BASE;
		}while(num>0);
		return *this;
	}
	BigInteger operator=(const string &str)
	{
		s.clear();
		int x, len=(str.length()-1)/WIDTH+1;
		for(int i=0; i<len; i++)
		{
			int end=str.length()-i*WIDTH;
			int start=max(0, end-WIDTH);
			sscanf(str.substr(start, end-start).c_str(), "%d", &x);
			s.push_back(x);
		}
		return *this;
	}

	
	ostream& operator<<(ostream &out, const BigInteger &x)
	{
		out<<x.s.back();
		for(int i=x.s.size()-2; i>=0; i--)
		{
			char buf[20];
			sprintf(buf, "%08d", x.s[i]);
			for(int j=0; j<strlen(buf); j++)
				out<<buf[j];
		}
		return out;
	}
	ifstream& operator>>(ifstream *in, BigInteger &x)
	{
		string s;
		if(!(in>>s))
			return in;
		x=s;
		return in;
	}

	BigInteger operator+(const BigInteger &b) const
	{
		BigInteger c;
		c.s.clear();
		
		for(int i=0, g=0; ; i++)
		{
			if(g==0  &&  i>=s.size()  &&  i>=b.s.size())
				break;
			if(i<s.size())
				g+=s[i];
			if(i<b.s.size())
				g+=b.s[i];
			c.push_back(g%BASE);
			g=g/BASE;
		}
		return c;
	}

	BigInteger operator+=(const BigInteger &b)
	{
		*this=*this+b;
		return *this;
	}

	bool operator<(const BigInteger &b) const
	{
		if(s.size()!=b.s.size())
			return s.size()<b.s.size();
		for(int i=s.size()-1; i>=0; i--)
			if(s[i]!=b.s[i])
				return s[i]<b.s[i];
		return false;
	}

	bool operator>(const BigInteger &b)const
	{
		return !(*this<b);
	}

	bool operator<=(const BigInter &b)const
	{
		return !(*this>b);
	}

	bool operator>=(const BigInteger &b)const
	{
		return !(*this<b);
	}

	bool operator!=(const BigInteger &b)const
	{
		return *this<b ||  *this>b;
	}
	bool operator==(const BigInteger &b)const
	{
		return !(*this!=b);
	}
};

