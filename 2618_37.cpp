
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 510;
const double eps = 1e-7;
struct Point
{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){}
	Point operator+(const Point &a)const
	{
		return Point(x+a.x,y+a.y);
	}
	Point operator-(const Point &a)const
	{
		return Point(x-a.x,y-a.y);
	}
	double operator*(const Point &a)const
	{
		return x*a.y-y*a.x;
	}
	Point operator*(const double &s)const
	{
		return Point(x*s,y*s);
	}
	void getp()
	{
		scanf("%lf%lf",&x,&y);
	}
}poi[N];
struct Line
{
	Point p,v;
	double alpha;
	Line(){}
	Line(const Point &a,const Point &b):p(a),v(b-a)
	{
		alpha = atan2(v.y,v.x);
	}
	bool operator<(const Line &a)const
	{
		return alpha<a.alpha;
	}
}line[N];
int n,m,tot,r,h;
Line *q[N];
double ans;
bool on_left(const Point &p,const Line &l)
{
	return (l.p-p)*l.v>=0;
}
Point get_its(const Line &l1,const Line &l2)
{
	Point u = l1.p-l2.p;
	double tmp = (l2.v*u)/(l1.v*l2.v);
	return l1.p+l1.v*tmp;
}
void Get_hpits()
{
	for(int i = 1;i<= tot;i++)
	{
		while(r-h>=2&& !on_left(get_its(*q[r],*q[r-1]),line[i]))
			q[r--]=NULL;
		if(r-h>=1&&fabs(line[i].v*q[r]->v)<=0)
			q[r] = on_left(line[i].p,*q[r])?&line[i]:q[r];
		else q[++r]=&line[i];
	}
	while(true)
	{
		if(r-h>=2&& !on_left(get_its(*q[h+1],*q[h+2]),*q[r]))
			q[++h]=NULL;
		else if(r-h>=2&& !on_left(get_its(*q[r],*q[r-1]),*q[h+1]))
			q[r--]=NULL;
		else break;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		Point fir,p1,p2;
		scanf("%d",&m);
		fir.getp();p2 = fir;
		for(int j = 2;j<= m;j++)
		{
			p1 = p2;p2.getp();
			line[++tot]=Line(p1,p2);
		}
		line[++tot] = Line(p2,fir);
	}
	sort(line+1,line+tot+1);
	Get_hpits();
	if(r-h<=2)
		return printf("0.000\n"),0;
	tot = 0;
	for(int i = h+2;i<= r;i++)
		poi[++tot] = get_its(*q[i],*q[i-1]);
	poi[++tot]=get_its(*q[r],*q[h+1]);
	for(int i = 2;i<= tot;i++)
		ans+=poi[i-1]*poi[i];
	ans+=poi[tot]*poi[1];
	printf("%.3lf\n",ans/2.0);
	return 0;
}
