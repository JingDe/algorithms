
class Solution{
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) 
	{
		return (distance2(p1,p2)  &&  distance2(p1,p2)==distance2(p2,p3)  &&  distance2(p2,p3)==distance2(p3,p4)  &&  distance2(p3,p4)==distance2(p4,p1)  &&  distance2(p1,p3)==distance2(p2,p4))   
		||  (distance2(p1,p2)  &&  distance2(p1,p2)==distance2(p2,p4)  &&  distance2(p2,p4)==distance2(p3,p4)  &&  distance2(p3,p4)==distance2(p3,p1)  &&  distance2(p1,p4)==distance2(p2,p3))  
		||  (distance2(p1,p3)  &&  distance2(p1,p3)==distance2(p2,p3)  &&  distance2(p2,p3)==distance2(p2,p4)  &&  distance2(p2,p4)==distance2(p4,p1)  &&  distance2(p1,p2)==distance2(p3,p4));
	}
	double distance2(vector<int>& p1, vector<int>& p2)
	{
		return (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]); 
	}
}
