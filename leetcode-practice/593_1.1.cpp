
class Solution{
public:
	void print(const std::vector<vector<int> >& points)
	{
		for(std::vector<vector<int> >::const_iterator it=points.begin(); it!=points.end(); it++)
			std::cout<<"("<<(*it)[0]<<","<<(*it)[1]<<")  ";
		std::cout<<std::endl;
	}

	struct{
    	bool operator()(vector<int> a, vector<int> b) const
    	{
    		return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<b[1]);
		}
	}comp;
	
	bool comp2(vector<int> a, vector<int> b) 
	{
		return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
	}
		
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) 
	{
         vector<vector<int> > points{p1, p2, p3, p4};
         std::sort(points.begin(), points.end(), [&flag](vector<int> a, vector<int> b){
			return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		});
		
		
		int i=0;
		do{
			if(validThisSquare(points[0], points[1], points[2], points[3]))
				return true;
			print(points);
		}
		while(next_permutation(points.begin(), points.end(), comp));//有重复 
		// while(next_permutation(points.begin(), points.end(), std::bind1st(comp2, this)));
		return false;
    }
    bool validThisSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4)
    {
    	// 四边形4顶点顺序p1、p2、p3、p4
		// 判断4条边、对角线是否相等
		 return distance2(p1,p2)==distance2(p2,p3) &&  distance2(p2,p3)==distance2(p3,p4) && distance2(p3,p4)==distance2(p4,p1)  &&  distance2(p1,p3)==distance2(p2,p4);
	}
	double distance2(vector<int>& p1, vector<int>& p2)
	{
		return (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]); 
	}
};

