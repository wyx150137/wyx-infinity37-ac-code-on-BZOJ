
#include <stdio.h>
#include <queue>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const double eps = 1e-9;
const int N = 1005;
inline int dcmp(double x)
{
	if(fabs(x)<eps)return 0;
	return x>0?1:-1;
}
inline int sqr(int x)
{
	return x*x;
}
struct Point
{
	double x,y;
	Point(){}
	Point(double _x,double _y):x(_x),y(_y){}
	friend Point operator +(const Point &a,const Point &b)
	{return Point(a.x+b.x,a.y+b.y);}
	friend Point operator -(const Point &a,const Point &b)
	{return Point(a.x-b.x,a.y-b.y);}
	friend double operator *(const Point &a,const Point &b)
	{return a.x*b.y-a.y*b.x;}
	friend bool operator !=(const Point &a,const Point &b)
	{return a.x!=b.x||a.y!=b.y;}
	friend bool operator ==(const Point &a,const Point &b)
	{return a.x==b.x&&a.y==b.y;} 
}poi[N];
struct Line
{
	Point a,b;
	Line(){}
	Line(const Point &_a,const Point &_b):a(_a),b(_b){}
}line[N];
struct E
{int next,to;}e[N*N];
int head[N],tot;
void add(int x,int y)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
bool Inter(const Line &l1,const Line &l2)
{
	return dcmp((l1.b-l1.a)*(l2.a-l1.a))*dcmp((l1.b-l1.a)*(l2.b-l1.a))<0
			&& dcmp((l2.b-l2.a)*(l1.a-l2.a))*dcmp((l2.b-l2.a)*(l1.b-l2.a))<0;
}
int col[N];
queue<int>Q;
int main()
{
	int n,m,x,y,id;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d",&x,&y);
		poi[i] = Point(x,y);
	}
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d",&id,&x,&y);
		line[i].a = poi[id];
		line[i].b = Point(x,y);
	}
	for(int i = 1;i<= m;i++)
		for(int j = i+1;j<= m;j++)
			if((Inter(line[i],line[j])||line[i].b==line[j].b)&&
				line[i].a!=line[j].a&&line[i].a!=line[j].b&&line[i].b!=line[j].a)
					add(i,j),add(j,i);
	for(int i = 1;i<= m;i++)
	{
		if(col[i])continue;
		col[i] = 1;
		Q.push(i);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(int j = head[x];j;j=e[j].next)
			{
				if(col[e[j].to])
				{
					if(col[e[j].to]==col[x])
					{
						printf("impossible\n");
						return 0;
					}
				}else
				{
					col[e[j].to] = col[x]==1?2:1;
					Q.push(e[j].to);
				}
			}
		}
	}
	printf("possible\n");
	return 0;
}
