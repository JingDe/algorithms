
class Solution{
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) 
	{
        // 对4个点排序，排序规则：先x从小到大，再y从小到大
        vector<vector<int> > points{p1, p2, p3, p4};
        
		/*struct{
        	bool operator()(vector<int> a, vector<int> b) const
        	{
        		return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
			}
		}comp;
		sort(points.begin(), points.end(), comp);
		*/
		sort(points.begin(), points.end(), [](vector<int> a, vector<int> b){
			return (a[0]<b[0]  ||  a[0]==b[0]  &&  a[1]<=b[1]);
		});
		
		p1=points[0];
		p2=points[1];
		p3=points[2];
		p4=points[3];
		return distance2(p1, p2)!=0  &&  distance2(p1,p2)==distance2(p2,p4) &&  distance2(p2,p4)==distance2(p4,p3) && distance2(p4,p3)==distance2(p3,p1)  &&  distance2(p1,p4)==distance2(p2,p3);
	}
	double distance2(vector<int>& p1, vector<int>& p2)
	{
		return (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]); 
	}
} 
