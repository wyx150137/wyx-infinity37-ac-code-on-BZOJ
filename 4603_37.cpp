
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 105;
const double pi = 3.14159265358979323;
struct Point
{
	double x,y,z;
	Point(){}
	Point(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
	friend Point operator +(const Point &a,const Point &b)
	{
		return Point(a.x+b.x,a.y+b.y,a.z+b.z);
	}
	friend Point operator -(const Point &a,const Point &b)
	{
		return Point(a.x-b.x,a.y-b.y,a.z-b.z);
	}
	friend Point operator *(const Point &a,double b)
	{
		return Point(a.x*b,a.y*b,a.z*b);
	}
	friend Point operator /(const Point &a,double b)
	{
		return Point(a.x/b,a.y/b,a.z/b);
	} 
	friend double operator &(const Point &a,const Point &b)
	{
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}
	friend Point operator |(const Point &a,const Point &b)
	{
		return Point(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
	}
	friend double getdis(const Point &a)
	{
		return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	}
}poi[N],centre;
struct Shape
{
	int num;
	Point vec[N];
}sur[N];
int n,f;
double getV(Point p,Point a,Point b,Point c)
{
	a = a-p,b = b-p,c = c-p;
	double ans = (a|b)&c;
	ans = ans/6.0;
	return fabs(ans);
}
Point getC(const Point &p,const Point &a,const Point &b,const Point &c)
{
	Point C;
	C = p+a+b+c;
	return C/4.0;
}
void getcentre()
{
	double sumv = 0;
	Point t = Point(0,0,0);
	for(int i = 1;i<= f;i++)
	{
		int num = sur[i].num;
		for(int j = 1;j<= num-2;j++)
		{
			double v = getV(centre,sur[i].vec[0],sur[i].vec[j],sur[i].vec[j+1]);
			Point c = getC(centre,sur[i].vec[0],sur[i].vec[j],sur[i].vec[j+1]);
			c = c*v,sumv+=v,t = t+c;
		}
	}
	centre = t/sumv;
}
double getAngle(Point p,Point x,Point y,Point z)
{
	x = x-p,y = y-p,z = z-p;
	x = x/getdis(x),y = y/getdis(x),z = z/getdis(x);
	Point a = x|y,b = x|z;
	double ans = (a&b)/getdis(a)/getdis(b);
	return acos(ans);
}
double getS(const Shape &x,const Point &y)
{
	double ans = -(x.num-2)*pi;
	for(int i = 0;i<x.num;i++)
		ans+=getAngle(y,x.vec[i],x.vec[(i+1)%x.num],x.vec[(i-1+x.num)%x.num]);
	return ans;
}
int main()
{
	int x;
	scanf("%d%d",&n,&f);
	for(int i = 1;i<= n;i++)
		scanf("%lf%lf%lf",&poi[i].x,&poi[i].y,&poi[i].z);
	for(int i = 1;i<= f;i++)
	{
		scanf("%d",&sur[i].num);
		for(int j = 0;j<sur[i].num;j++)
			scanf("%d",&x),sur[i].vec[j]=poi[x];
	}
	centre = Point(0,0,0);
	for(int i = 1;i<= n;i++)
		centre = centre+poi[i];
	centre = centre/(double)n;
	getcentre();
	for(int i = 1;i<= f;i++)
	{
		double ans = getS(sur[i],centre);
		ans /= 4.0*pi;
		printf("%.7lf\n",ans);
	}
	return 0;
}
