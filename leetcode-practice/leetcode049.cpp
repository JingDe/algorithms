
// void fun(const Type &a);
// void fun(Type a);
void sorter(string s, string r)
{
	std::sort(s.begin(), s.end());
	std::sort(r.begin(), r.end());
	return s<r;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
	multimap<string, string> sortedStrs;
	for(int i=0; i<strs.size(); ++i)
	{
		string copy=strs[i];
		std::sort(copy.begin(), copy.end());
		sortedStrs.insert(multimap<string,string>::value_type(copy, strs[i]));
	}
	
	vector<vector<string> > res;
	string curS;
	vector<string> curV;
	multimap<string, string>::iterator it=sortedStrs.begin();
	for(int i=0; i<strs.size(); ++i)
	{
		if(it==sortedStrs.begin())
		//if(curS.empty())
		{
			curS=it->first;
			//curV.clear();
			curV.push_back(it->second);
		}
		else
		{
			if(curS==it->first)
			{
				curV.push_back(it->second);
			}
			else
			{
				res.push_back(curV);
				
				curV.clear();				
				curS.clear();
				curS=it->first;
				curV.push_back(it->second);
			}
		}
		++it;
	}
	//if(curV.empty()==false)
		res.push_back(curV);
	return res;
}