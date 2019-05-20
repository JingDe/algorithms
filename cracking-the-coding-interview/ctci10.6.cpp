
#include<vector>
#include<map>
#include<stdio.h>
#include<iostream>
#include<limits>
#include<stdlib.h>

//const static int INF=
const static double epsilon=0.000001; 
const static int multi=100000;

// const static double test_epsilon=0.0001;
// const static int test_multi=1000;
const static double INF=0.0;

struct Point{
	double x;
	double y;
	Point():x(0),y(0){}
	Point(double a, double b):x(a),y(b){}
};


// 当直线垂直于x轴，斜率为INF，y轴截距不存在（x轴截距存在）
// 当直线垂直于y轴，斜率为0，y轴截距存在（x轴截距不存在）
	
	
struct Line{
	double slope; // 斜率。
	double intercept; // x轴或者y轴截距(当直线不垂直于x轴时表示y轴截距，否则表示x轴截距)
	bool isSlope; // true表示斜率存在
		
	Line():slope(0.0),intercept(0.0),isSlope(true){} // x轴
	Line(double s, double i, bool is):slope(s),intercept(i),isSlope(is){}
	Line(const Point& p, const Point& q);
	
	int hashcode(){
		if(isSlope)
		{
			int sl = (int)(slope * multi);
			int in = (int)(intercept * multi);
			return sl*1000 +  in;
		}
		else
		{
			int in = (int)(intercept * multi);
			return in;
		}
	}
	void print()
	{
		if(isSlope)
			printf("Line : slope %.20f, y intercept %.20f, isSlope %d, hashcode %d\n", slope, intercept, isSlope, hashcode());
		else
			printf("Line : slope INF, x intercept %.20f, isSlope %d, hashcode %d\n", intercept, isSlope, hashcode());
	}
	
	Line& operator=(const Line& rhs)
	{
		slope=rhs.slope;
		intercept=rhs.intercept;
		isSlope=rhs.isSlope;
		return *this;
	}
};

Line::Line(const Point& p, const Point& q)
{
	if((p.x-q.x)<epsilon)
	{
		isSlope=false;
		slope=INF;
		printf("INF\n");
		intercept=p.x; // x轴截距
	}
	else
	{
		isSlope=true;
		slope=(q.y-p.y)/(q.x-p.x);
		intercept=p.y-slope*(p.x);
		printf("slope = (%f-%f)/(%f-%f) = %.20f/%.20f = %.20f, intercept = %f\n", q.y, p.y, q.x, p.x, (q.y-p.y), (q.x-p.x), slope, intercept);
	}
}

// points是所有的点，求出经过其中点数最多的直线返回
Line mostLine(const std::vector<Point> &points)
{
	if(points.size()<2)
		return Line();
	Line resLine;
	bool first=true;
	
	std::map<int, int> lm;
	for(int i=0; i<points.size(); ++i)
		for(int j=i+1; j<points.size(); ++j)
		{
			Line l(points[i], points[j]);
			if(lm.find(l.hashcode()) == lm.end())
				lm[l.hashcode()]=0;
			lm[l.hashcode()]=lm[l.hashcode()]+1;
			
			if(first)
			{
				resLine=l;
				printf("first set resLine : %d,%d, slope %f, intercept %f\n", i, j, l.slope, l.intercept);
				first=false;
			}
			else if(lm[resLine.hashcode()]<lm[l.hashcode()])
			{
				resLine=l;			
				printf("set resLine : %d,%d, slope %f, intercept %f\n", i, j, l.slope, l.intercept);
			}
		}
	
	return resLine;
}

Line mostLine2(const std::vector<Point> &points)
{
	if(points.size()<2)
		return Line();
	Line resLine;
	bool first=true;
	
	Line resLine2;
	bool first2=true;
	
	std::map<int, int> lm;
	std::map<int, int> lm2;
	for(int i=0; i<points.size(); ++i)
		for(int j=i+1; j<points.size(); ++j)
		{
			Line l(points[i], points[j]);
			if(l.isSlope)
			{
				if(lm.find(l.hashcode()) == lm.end())
					lm[l.hashcode()]=0;
				lm[l.hashcode()]=lm[l.hashcode()]+1;
				
				if(first)
				{
					resLine=l;
					printf("first set resLine : %d,%d, %d,%d, slope %f, intercept %f\n", i, j, l.hashcode(), lm[l.hashcode()], l.slope, l.intercept);
					first=false;
				}
				else if(lm[resLine.hashcode()]<lm[l.hashcode()])
				{
					resLine=l;			
					printf("set resLine : %d,%d, %d,%d, slope %f, intercept %f\n", i, j, l.hashcode(), lm[l.hashcode()], l.slope, l.intercept);
				}
			}
			else
			{
				if(lm2.find(l.hashcode()) == lm2.end())
					lm2[l.hashcode()]=0;
				lm2[l.hashcode()]=lm2[l.hashcode()]+1;
				
				if(first2)
				{
					resLine2=l;
					printf("first set resLine2 : %d,%d, %d,%d, slope %f, intercept %f\n", i, j, l.hashcode(), lm2[l.hashcode()], l.slope, l.intercept);
					first2=false;
				}
				else if(lm2[resLine2.hashcode()]<lm2[l.hashcode()])
				{
					resLine2=l;			
					printf("set resLine2 : %d,%d, %d,%d, slope %f, intercept %f\n", i, j, l.hashcode(), lm2[l.hashcode()], l.slope, l.intercept);
				}
			}
		}
	
	if(lm[resLine.hashcode()]>lm2[resLine2.hashcode()])
	{
		printf("resLine %d > resLine2 %d\n", lm[resLine.hashcode()], lm2[resLine2.hashcode()]);
		resLine.print();
		return resLine;
	}
	else
	{
		printf("resLine %d <= resLine2 %d\n", lm[resLine.hashcode()], lm2[resLine2.hashcode()]);
		resLine2.print();
		return resLine2;
	}
}

void test_double()
{
	printf("double max = %.20f\n", std::numeric_limits<double>::max());
	std::cout<<std::numeric_limits<double>::max()<<std::endl;
	
	printf("double min = %.320f\n", std::numeric_limits<double>::min());
	std::cout<<std::numeric_limits<double>::min()<<std::endl;
}

void test_hashcode()
{
	double slope=1.0;
	double intercept=4.0;
	Line l1(slope, intercept, true);
	Line l2(slope+epsilon*0.999, intercept+epsilon*0.999, true);
	Line l3(slope+epsilon*0.999, intercept+epsilon*1.001, true);
	l1.print();
	l2.print();
	l3.print();
}

void test_hashcode2()
{
	double slope=INF;
	double intercept=4.0;
	Line l1(slope, intercept, false);
	Line l2(slope, intercept+epsilon*0.999, false);
	Line l3(slope, intercept+epsilon*1.0001, false);
	l1.print();
	l2.print();
	l3.print();
	//printf("%d, %d, %d\n", l1.hashcode(), l2.hashcode(), l3.hashcode());
}

void solve()
{
	srand((unsigned)time(0));
    int graph_size = 100;
    int point_num = 500;
    std::vector<Point> vec;
    for(int i=0; i<point_num; ++i){
		Point p;
        p.x = rand()/double(RAND_MAX) * graph_size;
        p.y = rand()/double(RAND_MAX) * graph_size;
        //std::cout<<p.x<<", "<<p.y<<std::endl;
		vec.push_back(p);
    }
	Line l=mostLine2(vec);
	l.print();
}

int main()
{
	//test_double();
	
	test_hashcode();
	test_hashcode2();
	
	solve();
	
	return 0;
}