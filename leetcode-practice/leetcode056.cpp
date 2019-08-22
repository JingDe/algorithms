

vector<vector<int>> merge(vector<vector<int>>& intervals) {
	vector<vector<int> > answer;
	if(intervals.empty())
		return answer;
	
	std::sort(intervals.begin(), intervals.end(), sortByLeft);
	//int curr=0;
	vector<vector<int> >::iterator curr=intervals.begin();
	int start=0;
	int end=0;
	//while(curr<intervals.size())
	while(curr!=intervals.end())
	{
		// start=intervals[curr][0];
		// end=intervals[curr][1];
		start=(*curr)[0];
		end=(*curr)[1];
		
		std::vector<vector<int>> ::iterator it;
		// 寻找第一个区间右边界超过end的区间，(左边界要么小于end，要么大于end)
		it=std::find_if(inervals.begin()+curr, intervals.end(), std::bind(rightBiggerThan, std::placeholders::_1, end));
		RightComp rc;
		rc.setEnd(end);
		it=std::find_if(inervals.begin()+curr, intervals.end(), rc);
		
		if(it==intervals.end())
		{
			answer.push_back(vector<int>({start, end}));
			break;
		}
		
		// 当左边界小于end，更新end
		vector<int> elem=*it;
		if(elem[0]<=end)
		{
			
		}
	}
	return answer;
}

bool sortByLeft(const vector<int>& lhs, const vector<int>& rhs)
{
	if(lhs[0]<rhs[0])
		return true;
	if(lhs[0]==rhs[0]  &&  lhs[1]<=rhs[1])
		return true;
	return false;
}

bool rightBiggerThan(const vector<int>& elem, int end)
{
	if(elem[1]>end)
		return true;
	return false;
}

class RightComp{
public:
	void setEnd(int end) { this.end=end; }
	bool operator(const vector<int>& elem){
		return elem[1]>end;
	}

private:
	int end;
	
};


// 方法一：遍历
vector<vector<int>> merge(vector<vector<int>>& intervals) {
	vector<vector<int> > answer;
	if(intervals.empty())
		return answer;
	
	std::sort(intervals.begin(), intervals.end(), sortByLeft);
	
	int targetLeft=intervals[0][0];
	int targetRight=intervals[0][1];
	int curr=1;
	while(curr<intervals.size())
	{
		vector<int> currInterval=intervals[curr];
		if(currInterval[1]<=targetRight)
		{}
		else if(currInterval[0]<=targetRight  &&  currInterval[1]>=targetRight)
		{
			targetRight=currInterval[1];
		}
		else // currInterval[0]>targetRight
		{
			answer.push_back(vector<int>({targetLeft, targetRight}));
			targetLeft=currInterval[0];
			targetRight=currInterval[1];
			//curr++;
			// if(curr>=intervals.size())
				// answer.push_back(vector<int>({targetLeft, targetRight}));
		}
		curr++;
	}
	answer.push_back(vector<int>({targetLeft, targetRight}));
	return answer;
}


Line 941: Char 34: runtime error: reference binding to null pointer of type 'const value_type' (stl_vector.h)


// 方法二：排序
vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
	std::sort(intervals.begin(), intervals.end(), sortByLeft);
	// sort(ins.begin(), ins.end(), [](vector<int> a, vector<int> b){return a[0] < b[0];});

	vector<vector<int> > merged;
	for(vector<int> interval : intervals)
	{
		if(merged.empty()  ||  (merged.back())[1]<interval[0])
		{
			merged.push_back(interval);
		}
		else
		{
			(merged.back())[1]=std::max((merged.back())[1], interval[1]);
		}
	}
	return merged;
｝

// AC
vector<vector<int>> merge(vector<vector<int>>& ins) {
	if (ins.empty()) return vector<vector<int>>{};
	vector<vector<int>> res;
	sort(ins.begin(), ins.end(), [](vector<int> a, vector<int> b){return a[0] < b[0];});
	res.push_back(ins[0]);
	for (int i = 1; i < ins.size(); i++) {
		if (res.back()[1] < ins[i][0]) res.push_back(ins[i]);
		else
			res.back()[1] = max(res.back()[1], ins[i][1]);
	}
	return res;

}


// 方法二：图的深度遍历
typedef Interval vector<int>;
map<Interval, vector<Interval> > graph; // 邻接表表示,两条有向边表示无向边
map<int, vector<Interval> > nodesInComp;
set<Interval> visited;

vector<vector<int>> merge(vector<vector<int>>& intervals) 
{
	buildGraph(intervals);
	buildComponents(intervals);
	
	vector<Interval> merged;
	
	for(map<int, list<Interval> >::iterator it=nodesInComp.begin(); it!=nodesInComp.end(); ++it)
	{
		vector<Interval> tmp=it->second;
		merged.push_back(mergeNodes(tmp));
	}
	
	return merged;
}

Interval mergeNodes(vector<Interval> nodes)
{
	int minStart=nodes[0][0];
	for(Interval node:nodes)
	{
		minStart=std::min(minStart, node[1]);
	}
	
	int maxEnd=nodes[0][1];
	for(Interval node:nodes)
	{
		maxEnd=std::max(maxEnd, node[1]);
	}
	
	return Interval(minStart, maxEnd);
}

void buildGraph(const vector<Interval>& intervals)
{
	for(Interval interval : intervals)
	{
		graph.insert(map<Interval, list<Interval> >::value_type(interval, vector<Interval>()));
	}
	
	for(Interval interval : intervals)
	{
		for(Interval interval2 : intervals)
		{
			if(overlap(interval, interval2))
			{
				graph[interval].push_back(interval2);
				graph[interval2].push_back(interval);
			}
		}
	}
}

void buildComponents(const vector<Interval>& intervals)
{
	int compNumber=0;
	
	for(Interval interval : intervals)
	{
		if(visited.contains(interval)==false) // 对每个未被访问节点，DFS遍历连通分量
		{
			markComponentDFS(interval, compNumber);
			compNumber++;
		}
	}
}

// DFS遍历
//  同一个连通分量的点，属于compNumber
void markComponentDFS(Interval start, int compNumber)
{
	stack<Interval> S;
	S.push(start);
	
	while(!S.empty())
	{
		Interval node=S.top();
		S.pop();
		
		if(!visited.contains(node))
		{
			visited.insert(node);
			
			if(!nodesInComp.contains(compNumber))
			{
				nodesInComp[compNumber]=vector<Interval>();
			}
			nodesInComp[compNumber].push_back(node);
			
			for(Interval child : graph[node])
			{
				S.push(child);
			}
		}
	}
}

// 图的DFS，递归解法
// 非递归解法，使用stack


void markComponentDFS(Interval start, int compNumber)
{
	// if(visited.contains(start))
		// return;
			
	visited.insert(start);
	
	if(!nodesInComp.contains(compNumber))
	{
		nodesInComp[compNumber]=vector<Interval>();
	}
	nodesInComp[compNumber].push_back(node);
	for(Interval interval : graph[node])
	{
		if(visited.contains(interval)==false)
			markComponentDFS(interval, compNumber);
	}
}




