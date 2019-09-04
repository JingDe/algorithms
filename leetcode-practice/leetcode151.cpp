

string reverseWords(string s) {
	string ans;
	string::size_type end, start;
	start=npos;
	while(true)
	{
		if(start==npos)
			end=s.find_last_not_of(" ", npos);
		else
			end=s.find_last_not_of(" ", start-1);
		if(end==npos)
			break;
		start=s.find_last_not_of(" ", end);
		ans+=s.substr(start, end-start+1);
	}
	return ans;
}


string reverseWords(string s) {
	int i=0, j=0;
	int left=0;
	int len=s.length();
	int wordcount=0;
	while(true)
	{
		while(i<len  &&  s[i]==' ')
			i++;
		if(i==len)
			break;
		if(wordcount)
			s[j++]=' ';
		left=j;
		while(i<len  &&  s[i]!=' ')
		{
			s[j]=s[i];
			j++;
			i++;
		}
		reverseword(s, left, j-1);
		wordcount++;
	}
	s.resize(j);
	reverseword(s, 0, j-1);
	return s;
}

void reverseword(string& s, int i, int j)
{
	while(i<j)
	{
		swap(s[i++], s[j--]);
	}
}

// 解答3
void reverseWords(char *text)
{
    int length=strlen(text);
    reverseString(text, 0, length-1, 0);
    int read=0, write=0;
    while (read<length)
    {
        if (text[read]!=' ')
        {
            int wordStart=read;
            for ( ;read<length && text[read]!=' '; read++);
            reverseString(text, wordStart, read-1, write);
            write+=read-wordStart;
            text[write++]=' ';
        }
        read++;
    }
    text[write-1]='\0';
}
 
void reverseString(char *text, int start, int end, int destination)
{
    // reverse the string and copy it to destination
    int length=end-start+1;
    int i;
    memcpy(&text[destination], &text[start], length*sizeof(char));
    for (i=0; i<length/2; i++)
    {
        swap(&text[destination+i], &text[destination+length-1-i]);
    } 
}