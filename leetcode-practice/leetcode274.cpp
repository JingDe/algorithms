
int hIndex(vector<int>& citations) {
	map<int, int> citations2papers;
	int max_citations=0;
	for(int i=0; i<citations.size(); ++i)
	{
		citations2papers[citations[i]]++;
		max_citations=std::max(max_citations, citations[i]);
	}
	
	debug_print(citations2papers);

	int sum_papers=0;
	int cur_cications=max_citations;
	while(cur_cications>=0)
	{
		sum_papers+=citations2papers[cur_cications];
		if(sum_papers >= cur_cications)
			return cur_cications;
		
		cur_cications--;
	}
	return 0;
}

void debug_print(const map<int, int>& citations2papers)
{
	for(map<int,int>::iterator it=citations2papers.begin(); it=citations2papers.end(); it++)
	{
		printf("被引用次数为 %d 的论文有 %d 篇\n", it->begin(), it->second());
	}
}