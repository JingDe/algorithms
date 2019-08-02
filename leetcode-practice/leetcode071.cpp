
string simplifyPath(string path) {
	std::stack<std::string> S;
	string resPath;
	
	int sz=path.size();
	int pos=0;
	while(pos<sz)
	{
		if(path[pos]=='/')
		{
			while(pos<sz  &&  path[pos]=='/')
				++pos;				
		}
		// ..dir  ...file
		// ../
		// 
		else if(path[pos]=='.'  &&  pos<sz-1  &&  path[pos+1]=='.'  &&  !S.empty())
		{
			S.pop();
			pos +=2;
		}
		else if(path[pos]='.'  &&  pos<sz-1  ||  path[pos+1])
			++pos;
		else if()
	}
}