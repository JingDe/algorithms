
map<int, std::string, std::greater<int> > int2c;

void init_map()
{
	int2c[1000]="M";
	int2c[500]="D";
	int2c[100]="C";
	int2c[50]="L";
	int2c[10]="X";
	int2c[5]="V";
	int2c[1]="I";
	
	int2c[4]="IV";
	int2c[9]="IX";
	int2c[40]="XL";
	int2c[90]="XC";
	int2c[400]="CD";
	int2c[900]="CM";
}

// string intToRoman(int num)  // 输入在1到3999之间
// {
	// init_map();
	// std::string res;
	int sz=int2c.size();
	// int cur=0;
	// while(num>0 )
	// {
		// if(num>=(int2c.begin()+cur)->first)
		// {
			// res+=(int2c.begin()+cur)->second;
			// num-=(int2c.begin()+cur)->first;
		// }
		// else
			// ++cur;
	// }
	// return res;
// }

string intToRoman(int num)  // 输入在1到3999之间
{
	init_map();
	std::string res;
	//int sz=int2c.size();
	map<int, string>::iterator cur=int2c.begin();
	while(num>0 )
	{
		if(num>=cur->first)
		{
			res+=cur->second;
			num-=cur->first;
		}
		else
			++cur;
	}
	return res;
}
