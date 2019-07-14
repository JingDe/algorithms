
#include<vector>
#include<stdio.h>
#include<string.h>
#include<string>
#include<assert.h>

static const int MAXSZ=100;

void print(const std::vector<int>& vec)
{
	for(int i=0; i<vec.size(); ++i)
		printf("%d ", vec[i]);
	printf("\n");
}

// 最长公共子序列
int lcSequence(const std::vector<int>& A, const std::vector<int>& B)
{
	int sz1=A.size();
	int sz2=B.size();
	
	int d[MAXSZ+1][MAXSZ+1]={0};
	for(int i=0; i<MAXSZ; ++i)
		d[i][0]=d[0][i]=0;
	// memset(d, 0, sizeof(d));
	for(int i=0; i<sz1; ++i)
		for(int j=0; j<sz2; ++j)
		{
			if(A[i]==B[j])
				d[i+1][j+1]=d[i][j]+1;
			else
				d[i+1][j+1]=std::max(d[i][j+1], d[i+1][j]);
		}
	
	return d[sz1][sz2];
}

// 最长公共(连续)子串
int lcSubstr(const std::string& A, const std::string& B, std::string& AS, std::string& BS)
{
	int res=0;
	int endi=0;
	int endj=0;
	
	int sz1=A.size();
	int sz2=B.size();
	
	int d[MAXSZ+1][MAXSZ+1]={0};
	for(int i=0; i<MAXSZ; ++i)
		d[i][0]=d[0][i]=0;
	// memset(d, 0, sizeof(d));
	for(int i=0; i<sz1; ++i)
		for(int j=0; j<sz2; ++j)
		{
			if(A[i]==B[j])
			{
				d[i+1][j+1]=d[i][j]+1;
				//res=std::max(res, d[i+1][j+1]);
				if(d[i+1][j+1]>res)
				{
					res=d[i+1][j+1];
					endi=i;
					endj=j;
				}
			}
			else
			{
				d[i+1][j+1]=0;
			}
		}
	
	// from endj and endj of A and B, get AS and BS
	AS=A.substr(endi-res+1, res);
	BS=B.substr(endj-res+1, res);
	
	// printf("%d, %s, %s\n", res, AS.c_str(), BS.c_str());
	return res;
}

// 当A.size()==B.size()
int lcSubstr2(const std::string& A, const std::string& B, std::string& AS, std::string& BS)
{
	int res=0;
	int endi=0;
	int endj=0;
	
	int sz1=A.size();
	int sz2=B.size();
	assert(sz1==sz2);
	
	int d[MAXSZ+1]={0};
	memset(d, 0, sizeof(d));
	for(int i=0; i<sz1; ++i)
		for(int j=0; j<sz2; ++j)
		{
			if(A[i]==B[j])
			{
				d[j+1]=d[j]+1; // 错误：此时的d[j]是第i行的，不是第i-1行的
				//printf("A[%d] B[%d]=%c %c, update %d\n", i, j, A[i], B[j], d[j+1]);
				if(d[j+1]>res)
				{
					res=d[j+1];
					endi=i;
					endj=j;
				}
			}
			else
			{
				d[j+1]=0;
			}
			printf("A[%d] B[%d]=%c %c, update %d\n", i, j, A[i], B[j], d[j+1]);
		}
	
	// from endj and endj of A and B, get AS and BS
	AS=A.substr(endi-res+1, res);
	BS=B.substr(endj-res+1, res);
	
	return res;
}

void test1()
{
	std::vector<int> A({1, 2, 4, 5, 6});
	std::vector<int> B({1, 2, 4, 5, 8});
	int ret=lcSequence(A, B);
	print(A);
	print(B);
	printf("%d\n", ret);
	
	
}

void test2()
{
	std::string A="abacdfgdcaba";
	std::string B="abacdgfdcaba";
	std::string a, b;
	int ret=lcSubstr(A, B, a, b);
	printf("%s, %s, ret %d, %s, %s\n", A.c_str(), B.c_str(), ret, a.c_str(), b.c_str());
	
	ret=lcSubstr2(A, B, a, b);
	printf("%s, %s, ret %d, %s, %s\n", A.c_str(), B.c_str(), ret, a.c_str(), b.c_str());
}

int main()
{
	test1();
	test2();
	
	return 0;
}