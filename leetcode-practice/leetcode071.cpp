
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
		// ../ ..
		// ..dir  ...file  ...		
		// ./ .
		else if(path[pos]=='.')
		{
			// ../
			// ..
			if( (pos+2<sz  &&  path[pos+1]=='.'   &&  path[pos+2]=='/') ||  (pos+2==sz  &&  path[pos+1]=='.'))
			{
				pos +=3;
				if(!S.empty())
					S.pop();
			}
			// ./ 
			// .
			else if( (pos+1<sz  &&  path[pos+1]=='/')  ||  (pos==sz-1))
			{
				pos +=2;
			}
			// .a ..a ...a ..
			else
			{
				string dirName;
				while(pos<sz  &&  path[pos]!='/')
					dirName = dirName.append(1, path[pos++]);
				pos +=1;
				S.push(dirName);
			}
		}
		else
		{
			string dirName;
			while(pos<sz  &&  path[pos]!='/')
				dirName = dirName.append(1, path[pos++]);
			pos +=1;
			S.push(dirName);
		}		
	}
	
	// if(S.empty())
		// return "/";
	//stack<string> S2;
	while(!S.empty())
	{
		string cur=S.top();
		S.pop();
		resPath="/"+cur+resPath;
	}
	if(resPath.empty())
		resPath="/";
	return resPath;
}