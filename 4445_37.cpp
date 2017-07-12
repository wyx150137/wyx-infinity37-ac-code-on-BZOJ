
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+5;
const double eps = 1e-10;
int dcmp(double x)
{
	if(fabs(x)<eps)return 0;
	if(x>0)return 1;else return -1;
}
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
	friend Point operator +(const Point &a,const Point &b)
	{return Point(a.x+b.x,a.y+b.y);}
	friend Point operator -(const Point &a,const Point &b)
	{return Point(a.x-b.x,a.y-b.y);}
	friend Point operator *(const Point &a,const double &k)
	{return Point(a.x*k,a.y*k);}
	friend double operator *(const Point &a,const Point &b)
	{return a.x*b.x+a.y*b.y;}
	friend double operator ^(const Point &a,const Point &b)
	{return a.x*b.y-a.y*b.x;}

};
struct Line
{
	Point p,v;
	double ang;
	Line(){}
	Line(Point _p,Point _v):p(_p),v(_v)
	{ang = atan2(v.y,v.x);}
	bool operator <(const Line &s)const
	{return ang<s.ang;}
};
bool on_left(const Line &l,const Point &p)
{return dcmp(l.v^(p-l.p))>0;}
Point Get_intersection(const Line &l1,const Line &l2)
{
	double x = ((l2.p-l1.p)^l2.v)/(l1.v^l2.v);
	return l1.p+l1.v*x;
}
double pans;
Line l[N],q[N];
Point t[N],p[N];
void Get_Half_Plane_Intersection(int n)
{
	sort(l+1,l+n+1);
	int hd = 1,tl = 0;
	q[++tl]=l[1];
	for(int i = 2;i<= n;i++)
	{
		while(hd<tl&& !on_left(l[i],p[tl-1]))tl--;
		while(hd<tl&& !on_left(l[i],p[hd]))hd++;
		q[++tl]=l[i];
		if(dcmp(q[tl].v^q[tl-1].v)==0)
		{
			tl--;
			if(hd<tl && !on_left(l[i],p[tl-1]))q[tl]=l[i];
		}
		if(hd<tl)p[tl-1] = Get_intersection(q[tl],q[tl-1]);
	}
	while(hd<tl && !on_left(q[hd],p[tl-1]))tl--;
	if(tl-hd<=1)
	{
		printf("0.0000");
		return ;
	}
	p[tl] = Get_intersection(q[tl],q[hd]);
	double ans = 0;
	for(int i = hd+1;i< tl;i++)
		ans+=((p[i]-p[hd])^(p[i+1]-p[hd]));
	ans = ans*0.5;
	printf("%.4f\n",ans/pans);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%lf%lf",&t[i].x,&t[i].y);
	t[n+1]=t[1];
	for(int i = 2;i<n;i++)
		pans+=((t[i]-t[1])^(t[i+1]-t[1]));
	pans*=0.5;
	int cnt = 0;
	double x1 = t[1].x,y1 = t[1].y;
	double x2 = t[2].x,y2 = t[2].y;
	for(int i = 2;i<= n;i++)
	{
		double x3 = t[i].x,y3 = t[i].y;
		double x4 = t[i+1].x,y4 = t[i+1].y;
		double a = y1+y4-y2-y3;
		double b = x2+x3-x1-x4;
		double c = (t[1]^t[2])+(t[i+1]^t[i]);
		Point p,v;
		if(dcmp(b)!=0)p=Point(0,-c/b);  
        else p=Point(-c/a,0);  
       	v=Point(-b,a);
       	l[++cnt]=Line(p,v);
	}
	for(int i = 1;i<= n;i++)l[++cnt]=Line(t[i],t[i+1]-t[i]);
	Get_Half_Plane_Intersection(cnt);
	return 0;
}
