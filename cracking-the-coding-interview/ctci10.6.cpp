
#include<vector>
#include<stdio.h>
#include<iostream>
#include<limits>

//const static int INF=
const static double epsilon=0.000001; 

struct Point{
	int x;
	int y;
	Point():x(0),y(0){}
	Point(int a, int b):x(a),y(b){}
};


// 当直线垂直于x轴，斜率为INF，y轴截距不存在（x轴截距存在）
// 当直线垂直于y轴，斜率为0，y轴截距存在（x轴截距不存在）
	
	
struct Line{
	double slope; // 斜率。
	double intercept; // x轴或者y轴截距(当直线不垂直于x轴时表示y轴截距，否则表示x轴截距)
	bool isSlope; // true表示斜率存在
		
	Line():slope(0.0),intercept(0.0),slope(true){}
	Line(int s, int i, bool is):slope(s),intercept(i),isSlope(is){}
	Line(const Point& p, const Point& q);
};

Line::Line(const Point& p, const Point& q)
{
	if((p.x-q.x)<epsilon)
	{
		isSlope=false;
		slope=0; // INF
		intercept=p.x; // x轴截距
	}
	else
	{
		isSlope=true;
		slope=(q.y-p.y)/(q.x-p.x);
		intercept=p.y-slope*(p.x);
	}
}

// points是所有的点，求出经过其中点数最多的直线返回
Line mostLine(const std::vector<Point> &points)
{
	if(points.size()<2)
		return Line();
	Line line;
	std::map<int, int> lm;
	for(int i=0; i<points.size(); ++i)
		for(int j=i+1; j<points.size(); ++j)
		{
			Line l(points[i], points[j]);
			
		}
	return line;
}

void test_double()
{
	printf("double max = %.20f\n", std::numeric_limits<double>::max());
	std::cout<<std::numeric_limits<double>::max()<<std::endl;
	
	printf("double min = %.320f\n", std::numeric_limits<double>::min());
	std::cout<<std::numeric_limits<double>::min()<<std::endl;
}


int main()
{
	test_double();
	
	return 0;
}