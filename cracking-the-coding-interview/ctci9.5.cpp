
#include<string>
#include<vector>
#include<stdio.h>

//int binary_search_emptyStr(const std::vector<std::string>& strs, std::string s, int low, int high)
int binary_search_emptyStr(std::string strs[], std::string s, int low, int high)
{
	if(s=="")
		return -1;
	int mid, rmid;
	
	while(low<=high)
	{
		mid=low+(high-low)/2;
		if(strs[mid]=="")
		{
			rmid=mid;
			while(strs[rmid]==""  &&  ++rmid<=high)
				;
			// while(strs[rmid]==""  &&  rmid<=high) ++rmid;
			if(rmid>high)
				high=mid-1;
			else
			{
				if(strs[rmid]==s)
					return rmid;
				else if(strs[rmid]<s)
					low=rmid+1;
				else
					high=mid-1;
			}
		}
		else
		{
			if(strs[mid]==s)
				return mid;
			else if(strs[mid]<s)
				low=mid+1;
			else
				high=mid-1;
		}
		
	}
	return -1;
}

//int binary_search_emptyStr2(const std::vector<std::string>& strs, std::string s, int low, int high)
int binary_search_emptyStr2(std::string strs[], std::string s, int low, int high)
{
	if(s=="")
		return -1;
	int mid, rmid;
	
	while(low<=high)
	{
		mid=low+(high-low)/2;
		rmid=mid;
		while(strs[rmid]==""  &&  ++rmid<=high) ;
		// while(strs[rmid]==""  &&  rmid<=high) ++rmid;

		if(rmid>high)
			high=mid-1;
		else
		{
			if(strs[rmid]==s)
				return rmid;
			else if(strs[rmid]<s)
				low=rmid+1;
			else
				high=mid-1;
		}		
	}
	return -1;
}

void test()
{
	//std::vector<std::string> svec({"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""});
	//std::vector<std::string> svec;
	std::string svec[]={"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};
	int sz=13;
	
	int pos;
	pos=binary_search_emptyStr(svec, "ball", 0, sz-1);
	printf("%d\n", pos);
	pos=binary_search_emptyStr(svec, "ballcar", 0, sz-1);
	printf("%d\n", pos);
	
	pos=binary_search_emptyStr2(svec, "ball", 0, sz-1);
	printf("%d\n", pos);
	pos=binary_search_emptyStr2(svec, "ballcar", 0, sz-1);
	printf("%d\n", pos);
}

int main()
{
	test();
	return 0;
}