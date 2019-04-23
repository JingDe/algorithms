#include<stdio.h>
#include<stack>
#include<string>


std::string getIntFromStack(std::stack<char>& st)
{
	std::string str="";
	while(!st.empty())
	{
		str.append(1, st.top());
		//printf("append %c, %s, %d\n", st.top(), str.c_str(), str.size());
		st.pop();
	}
	if(str.empty())
		return "0";
	return str;
}

int parseInt(const std::string& str, std::string::size_type pointPos)
{
	int res=0;
	int endPos=pointPos;
	if(pointPos==std::string::npos)
		endPos=str.size();
	for(int i=0; i<endPos; ++i)
	{
		//int a=atoi(str[i]);
		int a=str[i]-'0';
		res=res*10+a;
	}
	return res;
}

float parseFloat(const std::string& str, std::string::size_type pointPos)
{
	float res=0.0;
	if(pointPos==std::string::npos)
	{
		printf("parseFloat npos\n");
		return res;
	}
	int cnt=10;
	for(int i=pointPos+1; i<str.size(); ++i)
	{
		float a=str[i]-'0';
		res += a/cnt;
		cnt*=10;
	}
	return res;
}


std::string print_binary(const std::string& num)
{
	std::string::size_type pointPos=num.find('.');

	// 整数部分
	int i=parseInt(num, pointPos);
	//printf("parseInt %d\n", i);
	std::stack<char> st;
	while(i)
	{
		char c=i%2+'0';
		st.push(c);
		//printf("push %c\n", st.top());
		//i=i/2;
		i=i<<1;
	}
	std::string s1=getIntFromStack(st);
	//printf("getIntFromStack %s, %d\n", s1.c_str(), s1.size());
	
	// 小数部分
	std::string s2="";
	float f=parseFloat(num, pointPos);
	printf("parseFloat %f\n", f);
	int cnt=32;
	while(f!=0.0f  &&  cnt--)
	{
		//printf("cur %f\n", f);
		//f=f*2;
		f=f<<1;
		if(f>=1.0)
		{
			s2.append(1, '1');
			f-=1;
		}
		else if(f>0.0)
			s2.append(1, '0');
	}
	if(f!=0.0f)
		return "ERROR";
	if(s2.empty())
		return s1;
	return s1+'.'+s2;
}

using std::string;
string print_binary2(string val)
{
	std::string::size_type pos=val.find('.', 0);
	int intpart=atoi(val.substr(0,pos).c_str());
	double decpart=atof(val.substr(pos, val.length()-pos).c_str());
	string intstr="", decstr="";
	while(intpart>0)
	{
		if(intpart & 1)
			intstr="1"+intstr;
		else
			intstr="0"+intstr;
		intstr >>= 1;
	}
	while(decpart >0)
	{
		if(decstr.length()>32) return "ERROR";
		decpart *=2;
		if(decpart >=1 )
		{
			decpart += "1";
			decpart -= 1;
		}
		else
			decpart += "0";
	}
	return intstr+"."+decstr;
}

void test_npos()
{
	std::string s="123";
	//for(int i=0; i<std::string::npos; ++i)
	//for(int i=0; i!=std::string::npos; ++i)
	for(int i=0; i<s.size(); ++i)
		printf("%c ", s[i]);
	printf("\n");
}

int main()
{
	test_npos();
	
	{
		std::string s1="101.25";
		std::string s2="225";
		std::string s3="0.45";
		std::string s4="0.5";
		printf("%s ——> %s\n", s1.c_str(), (print_binary(s1)).c_str());
		printf("%s ——> %s\n", s2.c_str(), (print_binary(s2)).c_str());
		printf("%s ——> %s\n", s3.c_str(), (print_binary(s3)).c_str());
		printf("%s ——> %s\n", s4.c_str(), (print_binary(s4)).c_str());
	}
	return 0;
	
}

