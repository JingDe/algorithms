
#include<stdio.h>
#include<string>
#include<vector>
#include<algorithm>
#include<string.h>

#include"hash.h"

bool len_comp(const std::string& lhs, const std::string& rhs)
{
	return lhs.size() > rhs.size();
}

std::string longestComposedWord(std::vector<std::string>& words);
bool composedByOthers(const std::string& word, std::vector<std::string> &words, int level);
bool foundPrefix(const std::string& prefix, std::vector<std::string> &words);

std::string longestComposedWordVisited(std::vector<std::string>& words);
bool composedByOthersVisited(const std::string& word, std::vector<std::string> &words, int level, bool visited[]);
bool foundPrefixVisited(const std::string& prefix, std::vector<std::string> &words, bool visited[], int *foundIdx);

std::string longestComposedWordVisited2(std::vector<std::string>& words);
bool composedByOthersVisited2(const std::string& word, std::vector<std::string> &words, int level, bool visited[]);

std::string longestComposedWord(std::vector<std::string>& words)
{
	std::sort(words.begin(), words.end(), len_comp);
	for(std::vector<std::string>::iterator iter=words.begin(); iter!=words.end(); ++iter)
	{
		std::string word=*iter;
		printf("judge %s\n", word.c_str());
		
		if(composedByOthers(word, words, 0))
			return word;
	}
	return "";
}

bool composedByOthers(const std::string& word, std::vector<std::string> &words, int level)
{
	int len=word.length();
	// if(level==0)
	//		for(int i=1; i<len; ++i)
	// if(level>=0)
	//		for(int i=1; i<len+1; ++i)
	if(level>0  &&  foundPrefix(word, words))
	{
		printf("%*s%s prefix %s found\n", level*4, "", word.c_str(), word.c_str());
		return true;
	}
	
	for(int i=1; i<len; ++i)
	{
		std::string prefix=word.substr(0, i);
		if(foundPrefix(prefix, words))
		{
			printf("%*s%s prefix %s found\n", level*4, "", word.c_str(), prefix.c_str());
			std::string suffix=word.substr(i, len-i);
			if(composedByOthers(suffix, words, level+1))
				return true;
		}
	}

	return false;
}


bool foundPrefix(const std::string& prefix, std::vector<std::string> &words)
{
	std::vector<std::string>::iterator it=std::find(words.begin(), words.end(), prefix);
	if(it!=words.end())
		return true;
	return false;
}


// 不允许同一个单词被多次组成目标单词

std::string longestComposedWordVisited(std::vector<std::string>& words)
{
	std::sort(words.begin(), words.end(), len_comp);
	bool visited[words.size()];
	memset(visited, 0, sizeof(visited));
	for(std::vector<std::string>::iterator iter=words.begin(); iter!=words.end(); ++iter)
	{
		std::string word=*iter;
		printf("process %s\n", word.c_str());
		
		visited[iter-words.begin()]=true;
		if(composedByOthersVisited(word, words, 0, visited))
			return word;
	}
	return "";
}

bool composedByOthersVisited(const std::string& word, std::vector<std::string> &words, int level, bool visited[])
{
	int len=word.length();
	int foundIdx=0;
	if(level>0  &&  foundPrefixVisited(word, words, visited, &foundIdx))
	{
		printf("%*s%s prefix %s found\n", level*4, "", word.c_str(), word.c_str());
		return true;
	}
	
	for(int i=1; i<len; ++i)
	{
		std::string prefix=word.substr(0, i);
		int foundIdx=0;
		if(foundPrefixVisited(prefix, words, visited, &foundIdx))
		{
			visited[foundIdx]=true;
			printf("%*s%s prefix %s found\n", level*4, "", word.c_str(), prefix.c_str());
			std::string suffix=word.substr(i, len-i);
			if(composedByOthersVisited(suffix, words, level+1, visited))
				return true;
		}
		else
			visited[foundIdx]=false;
	}

	return false;
}

std::string longestComposedWordVisited2(std::vector<std::string>& words)
{
	std::sort(words.begin(), words.end(), len_comp);
	bool visited[words.size()];
	memset(visited, 0, sizeof(visited));
	for(std::vector<std::string>::iterator iter=words.begin(); iter!=words.end(); ++iter)
	{
		std::string word=*iter;
		printf("process %s\n", word.c_str());
		
		visited[iter-words.begin()]=true;
		if(composedByOthersVisited2(word, words, 0, visited))
			return word;
	}
	return "";
}

// 处理特殊情形 arr({"abcdefg", "abcdefg", "mnp"});
bool composedByOthersVisited2(const std::string& word, std::vector<std::string> &words, int level, bool visited[])
{
	int len=word.length();
	int foundIdx=0;
	if(/*level>0  && */ foundPrefixVisited(word, words, visited, &foundIdx))
	{
		printf("%*s%s prefix %s found\n", level*4, "", word.c_str(), word.c_str());
		return true;
	}
	
	for(int i=1; i<len; ++i)
	{
		std::string prefix=word.substr(0, i);
		int foundIdx=0;
		if(foundPrefixVisited(prefix, words, visited, &foundIdx))
		{
			visited[foundIdx]=true;
			printf("%*s%s prefix %s found\n", level*4, "", word.c_str(), prefix.c_str());
			std::string suffix=word.substr(i, len-i);
			if(composedByOthersVisited2(suffix, words, level+1, visited))
				return true;
		}
		else
			visited[foundIdx]=false;
	}

	return false;
}

bool foundPrefixVisited(const std::string& prefix, std::vector<std::string> &words, bool visited[], int* foundIdx)
{
	//std::vector<std::string>::iterator it=std::find(words.begin(), words.end(), prefix);
	std::vector<std::string>::iterator it;
	for(it=words.begin(); it!=words.end(); ++it)
	{
		if(visited[it-words.begin()]==false  &&  *it==prefix)
			break;
		// 当*it长度小于prefix时返回false
		if((*it).size()<prefix.size())
			return false;
	}
	if(it!=words.end())
	{
		*foundIdx=it-words.begin();
		return true;
	}
	return false;
}


void test()
{
	// string arr[] = {"test", "tester", "testertest", "testing", 
			// "apple", "seattle", "banana",  "batting", "ngcat", 
			// "batti","bat", "testingtester", "testbattingcat"};
	{
		std::vector<std::string> arr({"test", "tester", "testertest", "testing", 
			"apple", "seattle", "banana",  "batting", "ngcat", 
			"batti","bat", "testingtester", "testbattingcat"});
		std::string res=longestComposedWord(arr);
		printf("output %s\n", res.c_str());
	}	
	{
		std::vector<std::string> arr({"helloworldhello", "hello", "world"});
		std::string res=longestComposedWordVisited(arr);
		printf("output %s\n", res.c_str());
	}
	{
		std::vector<std::string> arr({"helloworldhello", "hello", "world"});
		std::string res=longestComposedWord(arr);
		printf("output %s\n", res.c_str());
	}
	{
		std::vector<std::string> arr({"abcdefg", "abcdefg", "mnp"});
		std::string res=longestComposedWord(arr);
		printf("output %s\n", res.c_str());
	}
	{
		std::vector<std::string> arr({"abcdefg", "abcdefg", "mnp"});
		std::string res=longestComposedWordVisited(arr);
		printf("output %s\n", res.c_str());
	}
	{
		std::vector<std::string> arr({"abcdefg", "abcdefg", "mnp"});
		std::string res=longestComposedWordVisited2(arr);
		printf("output %s\n", res.c_str());
	}
}


// ctci
Hash hash; // TODO

bool MakeOfWords(std::string word, int length)
{
	int len=word.length();
	if(len==0)
		return true;
	
	for(int i=1; i<=len; ++i)
	{
		if(i==length)
			return false;
		
		std::string str=word.substr(0, i);
		if(hash.find((char*)&str[0]))
		{
			if(MakeOfWords(word.substr(i), length)) // ??
				return true;
		}
	}
	return false;
}

void PrintLongestWord(std::string word[], int n)
{
	for(int i=0; i<n; ++i)
		hash.insert((char*)&word[i][0]);
	std::sort(word, word+n, len_comp);
	
	for(int i=0; i<n; ++i)
	{
		if(MakeOfWords(word[i], word[i].length()))
		{
			printf("output %s\n", word[i].c_str());
			return;
		}
	}
}

void test2()
{
	std::string arr[] = {"test", "tester", "testertest", "testing", 
		"apple", "seattle", "banana",  "batting", "ngcat", 
		"batti","bat", "testingtester", "testbattingcat"};
	
	PrintLongestWord(arr, 13);
}

int main()
{
	//test();
	test2();
	
	
	return 0;
	
}