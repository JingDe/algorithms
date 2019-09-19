
vector<string> findRepeatedDnaSequences(string s) {
	vector<string> ans;
	map<string, int> ht;
	for(int i=0; i+9<s.size(); ++i)
	{
		string str=s.substr(i, 10);
		ht[str]++;
	}
	for(map<string,int>::iterator it=ht.begin(); it!=ht.end(); ++it)
		if(it->second>1)
			ans.push_back(it->first);
	return ans;
}

SELECT 
	weather.id AS 'Id'
FROM
	weather	JOIN weather w ON DATEDIFF(weather.RecordDate , w.RecordDate )=1 
	AND weather.Temperature > w.Temperature